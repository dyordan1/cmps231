import os
import shutil
import subprocess
import re
import time
import zipfile
import difflib


def listdirIgnoringMac(dir):
  return list(filter(lambda f: f != '__MACOSX' and f != '.DS_Store', os.listdir(dir)))


def unzipSubmission(submissions, submission, submissionName, report):
  fullpath = os.path.join(submissions, submission)
  extractedSubmission = os.path.join(submissions, submissionName)

  report.write('=== VALIDATION ===\n\n')

  if os.path.exists(extractedSubmission):
    shutil.rmtree(extractedSubmission)

  zipfile.ZipFile(fullpath, 'r').extractall(extractedSubmission)

  # 'Fix' so that the submission doesn't have nested folders
  submissionRoot = extractedSubmission
  while not os.path.exists(os.path.join(submissionRoot, 'CMakeLists.txt')):
    childPaths = listdirIgnoringMac(submissionRoot)
    if len(childPaths) != 1:
      print(f'Broken submission {submissionName}!')
      report.write('Invalid submission!\n\n')
      shutil.rmtree(extractedSubmission)
      return None

    submissionRoot = os.path.join(submissionRoot, childPaths[0])

  if submissionRoot != extractedSubmission:
    submissionFiles = set(listdirIgnoringMac(submissionRoot))
    relativePath = submissionRoot.replace(extractedSubmission, '')
    report.write(f'Nested directories - moving {relativePath} as root\n')
    for file in submissionFiles:
      shutil.move(os.path.join(submissionRoot, file), extractedSubmission)

    # Clean up the residual nested dir + mac os stuffs
    for file in os.listdir(extractedSubmission):
      if file not in submissionFiles:
        shutil.rmtree(os.path.join(extractedSubmission, file))

  # Clean up build / CMakeCache
  cachePath = os.path.join(extractedSubmission, 'CMakeCache.txt')
  if os.path.exists(cachePath):
    print('Removing cache...')
    report.write(
        'CMakeCache.txt found in root level - did you forget to cd into build before cmake?\n')
    os.remove(cachePath)
  buildPath = os.path.join(extractedSubmission, 'build')
  if os.path.exists(buildPath):
    print('Removing build folder...')
    report.write('build folder found in submission\n')
    shutil.rmtree(buildPath)

  report.write('\n')
  return submissionName


def getTestScore(submissions, submissionName, repo, testExecutable, testSource, report):
  submissionFullPath = os.path.join(submissions, submissionName)
  tempGradingFolder = os.path.join(repo, 'code', 'temp-grading')

  # Clean up previously failed test folder, if it exists
  if os.path.exists(tempGradingFolder):
    shutil.rmtree(tempGradingFolder)

  # Move to repo root
  shutil.copytree(submissionFullPath, tempGradingFolder)

  # Replace test file, if provided
  originalTestFile = os.path.join(tempGradingFolder, 'test.cpp')
  if testSource != None:
    testFile = os.path.join(repo, 'code', testSource, 'test.cpp')
    os.remove(originalTestFile)
    shutil.copyfile(testFile, originalTestFile)

  # Make build folder
  buildDir = os.path.join(tempGradingFolder, 'build')
  subprocess.run(['mkdir', buildDir])

  # Run cmake
  try:
    subprocess.check_output(
        ['cmake', tempGradingFolder], cwd=buildDir, stderr=subprocess.STDOUT)
  except subprocess.CalledProcessError as grepexc:
    print('Failed cmake!')
    report.write('cmake FAILED\n\n')
    shutil.rmtree(tempGradingFolder)
    return 0
  report.write('cmake SUCCESS\n')

  # Run make
  try:
    subprocess.check_output(
        'make', cwd=buildDir, stderr=subprocess.STDOUT)
  except subprocess.CalledProcessError as grepexc:
    makeOutput = grepexc.output.decode('utf-8')
    print(f'Failed make!')
    report.write('make FAILED\n')
    regex = re.compile(
        r'Building CXX object (?P<object>.+\.o)\n(?P<error>.+\n).+\1]\s+Error', flags=re.MULTILINE | re.DOTALL)
    for match in regex.finditer(makeOutput):
      report.write('--- ' + match.group('object') + ' ---\n')
      report.write(match.group('error').replace(tempGradingFolder, ''))
    shutil.rmtree(tempGradingFolder)
    return 0
  report.write('build SUCCESS\n')

  # Run tests
  try:
    testOutput = subprocess.check_output(
        f'./{testExecutable}', cwd=buildDir, stderr=subprocess.STDOUT).decode('utf-8')
    match = re.search(
        r'\((?P<assertions>\d+) assertions in (?P<cases>\d+) test cases\)', testOutput)
    cases, assertions = int(match.group('cases')), int(
        match.group('assertions'))
    print(f'Passed all tests ({cases} cases, {assertions} assertions).')
    report.write(
        f'Passed all tests ({cases} cases, {assertions} assertions).\n\n')
    shutil.rmtree(tempGradingFolder)
    return 100
  except subprocess.CalledProcessError as grepexc:
    # Segfaults, etc.
    if int(grepexc.returncode) < 0:
      print(f'Test executable failed!')
      report.write('Tests FAILED with exception\nFULL OUTPUT:')
      shutil.rmtree(tempGradingFolder)
      report.write(grepexc.output.decode('utf-8'))
      report.write('\n\n')
      return 0

    testOutput = grepexc.output.decode('utf-8')
    match = re.search(
        r'test cases:\s+(?P<total>\d+)\s+\|\s+(?P<passed>\d+)\s+passed\s+\|\s+(?P<failed>\d+)\s+failed', testOutput)
    test_total, test_passed, test_failed = int(match.group('total')), int(
        match.group('passed')), int(match.group('failed'))
    print(f'Passed {test_passed}/{test_total} tests.')
    report.write(f'Passed {test_passed} of {test_total} tests.\n')
    match = re.search(
        r'assertions:\s+(?P<total>\d+)\s+\|\s+(?P<passed>\d+)\s+passed\s+\|\s+(?P<failed>\d+)\s+failed', testOutput)
    assertion_total, assertion_passed, assertion_failed = int(match.group('total')), int(
        match.group('passed')), int(match.group('failed'))
    print(f'Passed {assertion_passed}/{assertion_total} assertions.')
    report.write(
        f'Passed {assertion_passed} of {assertion_total} assertions.\n\n')
    shutil.rmtree(tempGradingFolder)
    return test_passed/test_total * 100


def reportDiff(original, modified, relativePath, report):
  for file in os.listdir(original):
    originalItem, modifiedItem = os.path.join(
        original, file), os.path.join(modified, file)

    # Recurse into directories
    if os.path.isdir(originalItem):
      reportDiff(originalItem, modifiedItem,
                 os.path.join(relativePath, file), report)
      continue

    originalFile, modifiedFile = open(
        originalItem, 'r'), open(modifiedItem, 'r')
    relativeFilePath = os.path.join(relativePath, file)
    try:
      diff = list(difflib.unified_diff(originalFile.read().splitlines(), modifiedFile.read().splitlines(),
                                       fromfile=relativeFilePath,
                                       tofile=relativeFilePath + ' (reviewed)'))
    except UnicodeDecodeError:
      diff = ""

    originalFile.close()
    modifiedFile.close()
    if len(diff) > 0:
      report.write('\n'.join(diff))
      report.write('\n\n')


def getReviewScore(submissions, submissionName, report):
  submissionFullPath = os.path.join(submissions, submissionName)
  tempReviewFolder = os.path.join(submissions, 'temp-review')

  # Clean up previously failed test folder, if it exists
  if os.path.exists(tempReviewFolder):
    shutil.rmtree(tempReviewFolder)

  # Move to temp folder
  shutil.copytree(submissionFullPath, tempReviewFolder)

  report.write('=== CODE REVIEW ===\n\n')

  fudgeFactor = 0
  try:
    print('Opening Editor...')
    subprocess.check_output(
        ['code', tempReviewFolder], stderr=subprocess.STDOUT)
    fudgeFactor = int(input('Enter fudge points: '))
    comment = None
    if fudgeFactor != 0:
      comment = input('Enter comment: ')

    # Assuming review has completed by now...
    reportDiff(submissionFullPath, tempReviewFolder, '/', report)

  except subprocess.CalledProcessError as grepexc:
    pass

  # Clean up
  shutil.rmtree(tempReviewFolder)
  return fudgeFactor, comment


def gradeSubmissionCollection(submissions, repo, testExecutable, testSource):
  reportsLocation = os.path.join(submissions, 'Reports')
  if not os.path.exists(reportsLocation):
    os.mkdir(reportsLocation)

  # For each file
  for submission in listdirIgnoringMac(submissions):
    # Skip canvas stuffs
    if not submission.endswith('.zip'):
      fullpath = os.path.join(submissions, submission)
      if not os.path.isdir(fullpath):
        print(f'Skipping non-zip {submission}')
      continue

    submissionName = os.path.splitext(
        os.path.basename(submission))[0].split('_')[0]
    reportLocation = os.path.join(reportsLocation, f'{submissionName}.txt')
    if os.path.exists(reportLocation):
      print(f'Report for {submissionName} already exists - erase to re-grade')
      continue

    report = open(reportLocation, 'w')

    # Unzip
    submissionName = unzipSubmission(
        submissions, submission, submissionName, report)

    if submissionName == None:
      report.write(f'Final score: 0')
    else:
      # Test
      report.write('=== BUILD / TEST ===\n\n')
      if testSource is not None:
        report.write('--- YOUR TESTS ---\n\n')
        getTestScore(submissions, submissionName, repo,
                     testExecutable, None, report)
        report.write('--- REFERENCE TESTS ---\n\n')

      test_score = getTestScore(
          submissions, submissionName, repo, testExecutable, testSource, report)
      report.write(f'Test score: {test_score}\n\n')

      # Code Review
      review_score, comment = getReviewScore(
          submissions, submissionName, report)
      report.write(f'Review bonus points: {review_score}')
      if review_score != 0:
        report.write(f'\nComment:\n')
        report.write(comment)
      report.write('\n\n')

      # Total
      total = test_score + review_score
      report.write(f'Final score: {total}')

    report.close()
