# Course Registration System

## Project Description
This is a C++ course registration system that supports:
- Students register for courses; if the course is full, they are placed on the waitlist
- Students cancel courses; the first student on the waitlist is automatically promoted
- Students view their registered and waitlisted courses
- Print all courses with their enrollment and waitlist details

## Data Structures Used
- **Singly Linked List**: Stores enrolled students  
- **Queue (implemented with a singly linked list)**: Stores waitlisted students  
- **Dynamic Array**: Stores all course information  

## Project Structure
```text
src/
 ├── course_registration.cpp   # Main program code
 ├── course_registration.h     # Header file
data/
 ├── courses.txt               # Course information
 ├── enrollment.txt            # Student enrollment information
README.md
```text
## Compile and Run
**In the terminal**:
```bash
g++ src/course_registration.cpp -o registration
./registration
**At runtime, provide the file names**:
```text
Enter course filename : data/courses.txt
Enter enrollment filename : data/enrollment.txt
**After running, the program shows the menu**:
```text
================= MENU =================
  1. View your registration         # Check your registered/waitlisted courses
  2. Course registration            # Register for a course (waitlist if full)
  3. Course cancellation            # Cancel a course (waitlist auto-promotion)
  4. Print enrollment list          # Print all courses with students
  5. Exit
**Example Behavior**:
Successful registration → Shows Registration succeed!
Course full → Shows You are on the waitlist
Cancellation → The first student from the waitlist is automatically promoted

## Author  
Sherry Shi  
Date: 10-11-2024
