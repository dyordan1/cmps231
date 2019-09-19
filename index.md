# CMPS 231 Fall 2019

## Data Structures and Algorithms
**Meeting Time**:  Thursday, 6:05pm - 9:45pm
**Location**:  ASB 429
**Instructor**:   Scott Frees, Professor of Computer Sciennce

### Contact Information
- **Office**: G315
- **Phone**: (201) 684-7726
- **Email**:  [sfrees@ramapo.edu](mailto:sfrees@ramapo.edu)
- **Office Hours**:  Mondays 11:30am-1:00pm and Thursday 4:00pm - 5:30pm

## Course Summary and Objectives
A study of the basic data structures and related algorithms used in software development.  Lists, stacks, queues, arrays, trees, graphs, strings, sorting, searching, and file structures are among the topics presented in this course.

- A reinforced understanding of C++ classes and object oriented programming.
- A fundamental knowledge of abstract data types, their implementation and algorithms that manipulate them.
- An understanding of the analysis of algorithms.
- The ability to select the proper data structure and related algorithm for a given application.
- A better understanding of the aspects of the C/C++ language and improved programming skills.

## Course Materials
**Textbook** &nbsp;&nbsp; [C++ Plus Data Structures, FIFTH EDITION](http://www.amazon.com/Plus-Data-Structures-Nell-Dale/dp/1449646751) by Nell Dale

<img src='http://ecx.images-amazon.com/images/I/51vZCeCp8HL.jpg' width="200"/>

*Note, the textbook is required for this course, and will be relavent to nearly each lecture.*

## Guides
The following guides will be useful to you throughout the course, but especially during the first few weeks.  **Please make sure** you pay very special attention to the Programming Environment guides - you need to get setup quickly!

### Programming Environment
Our code environment is designed to be as similar as possible on all three major operating systems - Windows, MacOS, and Linux.  It is also designed to get you more accustomed to very popular software development tools used in industry.  No matter which OS you are using, I'm going to have you working from the command line (terminal) a fair amount, and using simple file-based tools rather than large integrated devleopment environments (IDEs) like Visual Studio, XCode, and Eclipse.
- [Windows](guides/dev-setup-windows.html)
- [Notes on Ramapo Lab Machines](guides/dev-setup-lab.html)
- [MacOS](guides/dev-setup-mac-os.html)
- [Linux](guides/dev-setup-linux.html)

### Debugging
Debugging is the process of finding out why your program isn't working... and you'll need to get very good at this if you want to be a software developer! 

See the following guide for setting up `gdb` (debugger) and Visual Studio Code on Windows, Mac OS, and Linux.

- [Debugging Guide](guides/debugging.html)

## Schedule

| Week | Topic | Reading | Assignments
|------|-------|---------|------------
| 9/5 |  **Module 00**:  [Course Policies](slides/policies.html)<br/>**Module 01**: [Setting up your Development Environment](slides/dev-setup.html)<br/>**Module 02**:  [Review of Selection, Loops, and Functions](slides/functions.html)| Ch. 1 | 
| 9/12 |  **Module 03**:  [Basics of Unit Testing](slides/unit-testing.html)  <br/>**Module 04**: [Review of Arrays](slides/arrays.html)<br/>**Module 05**:  [Review of Classes and Objects](slides/classes.html) |Ch. 2 | **Lab Assignment**:  [Sort in Place](slides/unit-testing.html#25)<br/>**Lab Assignment**:  [Class wrapper around an array](slides/classes.html#20)
| 9/19 | **Module 06**:  [Lists, Stacks, and Queues with Arrays](slides/lists-queues-stacks.html) | Ch. 3-6 | **Lab Assignment**  [Combined Stack/Query](slides/lists-queues-stacks.html#21)
| 9/26 | **Module 07**:  [Review of Templates](slides/templates.html)<br/>**Module 08**:  [STL:  Vectors, Queue, Stack, Deque](slides/stl-sequences.html) |Ch. 3-6 | [Homework 1](https://github.com/scottfrees/cmps231/tree/master/code/hw-01)
| 10/3 | **Module 09**:  [Review of Pointers](slides/pointers.html)<br/>**Module 10**:  [Linked Lists](slides/linked-list.html) |Ch. 3-6 | [Homework 2](https://github.com/scottfrees/cmps231/tree/master/code/hw-02) 
| 10/10 | **Module 11**:  [STL List and searching](slides/stl-list.html)<br/>**Module 12**:  [Big O Notation and Algorithm Analysis](slides/complexity.html) |Ch. 3-6 | **Homework 1 Due**
| 10/17 | **Exam 1**:  Covers all material up to *and including* linked lists.  Big O notation will not be covered.  Exam will be three hours, and including coding.  It will be open notes, open book, and open internet (subject to academic integrity expectations). | | **Homework 2 Due** 
| 10/24 | **Module 12**:  [Big O Notation and Algorithm Analysis](slides/complexity.html)<br/>**Module 13**:  [Recursion - binary search on arrays](slides/recursion.html)<br/>**Module 14**:  [Binary Search Trees](slides/btrees.html) | Ch. 7-8 | Homework:  (TBD)
|10/31 | **Module 15**:  [Priority Queues, Heaps, STL priority_queue](slides/heaps.html) |Ch. 9.1-9.2 | **Lab Assignment** (TBD)
|11/7 | **Module 16**:  [Hashing and Hashtables](slides/hash.html) | Ch. 10.3| **Lab Assignment** (TBD)
|11/14 | **Module 17**:  [Graphs and Search](slides/graphs.html) | Ch. 9.3|
| 11/21 | **Exam 2**:  Covers all material up to *and including Hashing and STL Maps*.  There will be an emphasis on material covered since the first exam.  Exam will be three hours, and including coding.  It will be open notes, open book, and open internet (subject to academic integrity expecations). | | 
| 11/28 | *No class held - Thanksgiving break* | | 
| 12/5 | **Module 18**:  [Sorting - the simple algorithms](slides/sorting-simple.html)<br/>**Module 19**:  [Sorting - radix sort](slides/radix-sort.html)<br/>**Module 20**:  [Sorting - heap sort](slides/heap-sort.html) | Ch. 10.1 and 10.4 | **Lab Assignment** (TBD)
| 12/12 | **Module 21**:  [Sorting - merge sort](slides/merge-sort.html)<br/>**Module 22**:  [Sorting - quick sort](slides/quicksort.html) | Ch. 10.1 and 10.4| 

## Lab Assignments
Lab assignments are short programs, to be completed in class.  Lab assignments appear on the schedule above, **however please know that these are subject to change**.  Some scheduled labs could be skipped, based on class time.  There may be labs assigned without notice, in class.

Labs may be worked on in teams up to 3 students.

All labs will be distributed with unit tests that I will use for grading purposes.  This means you will know what grade you are likely to receive on your labs simply by running the unit tests.  All lab assignments must be turned in as complete projects - including all source code (including unit tests provided) and CMakeList.txt files.  All files should be zipped into a single files.  **When I extract the file, I should be able to enter the following commands to build and run your lab**:

```
mkdir build
cd build
cmake ..
make
./testing
```

If you rename files, or fail to zip them into the proper directory structure, **you will lose significant points on your grade**.

## Homework Assignments
Unlike labs, homework programs / assignments are to be completed on your own.  Sharing code is strictly forbidden.  

Similar to labs, homework programs will often contain unit tests that I will use to grade your work - so there will be no mystery as to how you will do on the assignment.  If your unit tests pass, you will do well - if they don't, you won't!

Just like labs, homework programs must be submitted as a zip file, and should be buildable and runnable using the commands listed above in the lab section - unless otherwise indicated in the homework assignment.

## Attendance Policy
While attendance is required, it is your responsibility to attend class - it is not graded directly.  Lab Assignments **must** be completed in class however, therefore those nights that we have class, attendance is *indirectly* taken.  If you are not in class to complete the lab, you will receive a zero on the lab.

## Late Policy
All assignments will be turned in electronically. **No late labs are accepted**.  A late penalty of 10 points per day will be applied to all late homework assignments. No assignments over 5 days late will be accepted. The required format/method of your electronic submissions will be outlined for each assignment. Deviation from these requirements may result penalty.

**Please note** that no make up exams will be given, unless there is a documented (medical, family) emergency preventing you from attending class. 


## Grading
| % | Activity
|------------------:|:---------------
|10%| In Class Labs
|10%| Homework Programs
|50%| Quizzes (25% each)
|30%| Final Exam

## Letter Grade Assignment
The following table is used to compute your letter grade, based on the numeric (weighted) average you earn during the semester.

| Letter | Numeric Score | Letter | Numeric Score | Letter | Numeric Score
|--------|---------------| ------ | ------------- | ------ | -------------
| A      | 100-94        |A-      | 93-90         |        |
| B+     | 89-87         | B      | 86-84         | B-     | 83-80 
| C+     | 79-77         |C       | 76-74         |C-      | 73-70
|D+      | 69-67         |D       | 66-60         |F       | < 60 


## Policy on Academic Integrity
Students are expected to read and understand Ramapo College’s Academic Integrity Policy, which can be found in the Ramapo College Catalog.  Members of the Ramapo College community are expected to be honest and forthright in their academic endeavors.  Students who are suspected of violating this policy will be referred to the Office of the Provost.

**Please read a detailed description of my policy on academic integrity [here](../../integrity.html)**

When completing lab programming exercises, you may review code with your fellow students; however, copying source code is strictly forbidden.  For homework programming assignments, you may discuss ideas, however you may not allow others to see your source code or examine others’.  Sharing of source code is extremely easy to detect and is strictly prohibited.   If sharing of source code is suspected, intentional or otherwise, both parties will immediately be referred to the Office of the Provost.

## College-Wide Policies
Please see the [College’s web page](https://www.ramapo.edu/fa/arc/college-wide-policies-courses) on policies that apply to all RCNJ courses, including this one.
