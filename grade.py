import os
import sys
from grade_lib import gradeSubmissionCollection


if __name__ == '__main__':
  # ARG1 - Parent folder of submission zip files
  submissionRoot = os.path.abspath(sys.argv[1])

  # ARG2 - cmps231 repo root
  repo = os.path.abspath(sys.argv[2])

  # ARG3 - non-standard test name
  testExecutable = 'testing'
  if len(sys.argv) > 3:
    testExecutable = sys.argv[3]

  gradeSubmissionCollection(submissionRoot, repo, testExecutable)
