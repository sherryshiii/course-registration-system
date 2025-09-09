// Course Registration System
// Author: Sherry Shi
// Description: Implements a course registration system using linked lists and queues in C++.
// Date: 10-11-2024

#include <iostream>
#include <fstream>
#include <iomanip>
#include "course_registration.h"

using namespace std;

// Student class
// Constructor
// Precondition: `studentId` is a valid integer and `studentName` is a non-empty string.
// Postcondition: A new Student object is created with the given id and name.
Student::Student(const int& studentId, const string& studentName) : id(studentId), name(studentName) {}

// Getter
// Precondition: None.
// Postcondition: Returns the student's id.
int Student::getId() const { return id; }

// Precondition: None.
// Postcondition: Returns the student's name.
string Student::getName() const { return name; }

// Member function
// Precondition: `other` is a valid pointer to a Student object.
// Postcondition: Returns true if the id and name of the current Student object match `other`, otherwise false.
bool Student::equals(const Student* other) const {
    return id == other->getId() && name == other->getName();
}

// Precondition: None.
// Postcondition: The student's id and name are printed to the console in a formatted manner.
void Student::print() const {
    cout << left << setw(15) << id << setw(15) << name << endl;
}

// Node class
// Constructor
// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: A new Node is created with the given student as its data and `next` is set to nullptr.
Node::Node(Student* student) : data(student), next(nullptr) {}

// Getter
// Precondition: None.
// Postcondition: Returns the data stored in the node, which is a pointer to a Student object.
Student* Node::getData(){return data;}

// Precondition: None.
// Postcondition: Returns the next node pointer in the linked list.
Node* Node::getNext(){return next;}

// Setter
// Precondition: `Data` is a valid pointer to a Student object.
// Postcondition: Sets the node's data to `Data`.
void Node::setData(Student* Data){data = Data;}

// Precondition: `Next` is a valid pointer to a Node object or nullptr.
// Postcondition: Sets the node's next pointer to `Next`.
void Node::setNext(Node* Next){next = Next;}

// SingleLinkedList class
// Constructor
// Precondition: None.
// Postcondition: Creates an empty SingleLinkedList object with `head` set to nullptr.
SingleLinkedList::SingleLinkedList() : head(nullptr) {}

// Destructor
// Precondition: None.
// Postcondition: All nodes in the linked list are deleted, including their associated student objects.
SingleLinkedList::~SingleLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->getNext();
        delete temp->getData();
        delete temp;
    }
}

// Member function
// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: The student is added to the list in ascending order by id. The list is still sorted after insertion.
void SingleLinkedList::add(Student* student) {
    Node* newNode = new Node(student);
    // For the first position
    if (head == nullptr || head->getData()->getId() > student->getId()) {
        newNode->setNext(head);
        head = newNode;
    }
    // For other positions
    else {
        Node* current = head;
        while (current->getNext() != nullptr && current->getNext()->getData()->getId() < student->getId()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Removes the node containing the student from the list.
// Returns true if the student was found and removed, otherwise false.
bool SingleLinkedList::remove(Student* student) {
    // Check if the list is empty
    if (head == nullptr) return false;
    // Find the target student and then remove
    // For the first position
    if (head->getData()->equals(student)) {
        Node* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }
    // For other positions
    Node* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getData()->equals(student)) {
            Node* temp = current->getNext();
            current->setNext(current->getNext()->getNext());
            delete temp;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Precondition: None.
// Postcondition: Removes and returns the first student in the list. If the list is empty, returns nullptr.
Student* SingleLinkedList::removeFirst() {
    if (head == nullptr) return nullptr;
    Node* temp = head;
    Student* student = head->getData();
    head = head->getNext();
    delete temp;
    return student;
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Returns true if the student is found in the list, otherwise false.
bool SingleLinkedList::find(Student* student) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->getData()->equals(student)) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Precondition: None.
// Postcondition: Prints all students in the list to the console in a formatted manner.
void SingleLinkedList::printList() const {
    Node* current = head;
    while (current != nullptr) {
        current->getData()->print();
        current = current->getNext();
    }
}

// Course class
// Constructor
// Precondition: None.
// Postcondition: Initializes the course with an empty code, title, enrollSize, and waitSize.
Course::Course() : code(""), title(""), enrollSize(0), waitSize(0) {}

// Precondition: `courseCode` and `courseTitle` are non-empty strings, and `enrollNum` and `waitNum` are non-negative integers.
// Postcondition: Initializes the course with the given values for code, title, enrollSize, and waitSize.
Course::Course(const string& courseCode, const string& courseTitle, int enrollNum, int waitNum)
        : code(courseCode), title(courseTitle), enrollSize(enrollNum), waitSize(waitNum) {}

// Getter
// Precondition: None.
// Postcondition: Returns the course's code.
string Course::getCode() const {return code;}

// Precondition: None.
// Postcondition: Returns the course's title.
string Course::getTitle() const {return title;}

// Member function
// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Adds the student to the enrolled list.
void Course::addEnrollList(Student* student){
    enrolledList.add(student);
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Adds the student to the waitlist.
void Course::addWaitList(Student* student){
    waitList.add(student);
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Adds the student to the enrolled list if enrollment is open, otherwise adds to the waitlist.
bool Course::registerStudent(Student* student) {
    // Check the enrolled list if full
    if (enrollSize < MAX_ENROLLED) {
        enrolledList.add(student);
        enrollSize++;
        return true;
    }
    // If enrolled list full, add the student to the waitlist
    else {
        waitList.add(student);
        waitSize++;
        return false;
    }
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Returns "Enrolled", "Wait", or "Not Found" depending on the student's status in the course.
string Course::findStudent(Student* student){
    if (enrolledList.find(student))
        return "Enrolled";
    if (waitList.find(student))
        return "Wait";

    return "Not Found";
}

// Precondition: `student` is a valid pointer to a Student object.
// Postcondition: Removes the student from the enrolled or waitlist.
// If a student is removed from the enrolled list, promotes a student from the waitlist (if any).
bool Course::cancelStudent(Student* student) {
    string status = findStudent(student);
    if (status == "Enrolled") {
        enrolledList.remove(student);
        enrollSize--;
        // Check the waitlist and move the first student to the enrolled list
        if (waitSize > 0) {
            Student* promotedStudent = waitList.removeFirst();
            if(promotedStudent != nullptr){
                enrolledList.add(promotedStudent);
                enrollSize++;
                waitSize--;
            }
        }
        return true;
    } else if (status == "Wait") {
        waitList.remove(student);
        waitSize--;
        return false;
    }
    return false;
}

// Precondition: None.
// Postcondition: Prints all students of each course to the console in a formatted manner.
void Course::getAllInfo() {
    cout << "[ " << left <<setw(10) << code << setw(15)<< title << " (" << enrollSize << ")  ]" << endl;
    cout << "---------------------------------------" << endl;
    enrolledList.printList();
    cout << endl;
    if (waitSize > 0) {
        cout << "  <  Waitlist  (" << waitSize << ")  >" << endl;
        waitList.printList();
        cout << endl;
    }
}

Course* readFile1(string filename, int& courseCount){
    // Precondition: The file specified by `filename` exists and is readable.
    // Each line in the file contains exactly four entries: course code (string), course title (string),
    // number of enrolled students (int), and number of students on the waitlist (int).

    // Postcondition: `courseCount` is updated to reflect the total number of courses read from the file.
    // A dynamic array of `Course` objects is created and populated with the data from the file.

    fstream infile;
    infile.open(filename);
    if(infile.fail()){
        cout << "Input file opening failed." << endl;
        exit(1);
    }
    // Count the size of the dynamic array
    string code, title;
    int enrollNum, waitNum;
    while(infile >> code >> title >> enrollNum >> waitNum)
        courseCount ++;
    infile.close();
    Course* courseList = new Course[courseCount];
    // Read file again for saving data to course list
    infile.open(filename);
    int i = 0;
    while(infile >> code >> title >> enrollNum >> waitNum){
        courseList[i] = Course(code, title, enrollNum, waitNum);
        i++;
    }
    infile.close();
    return courseList;
}

void readFile2(string filename, Course* courseList, int courseCount){
    // Precondition: The file specified by `filename` exists and is readable.
    // Each student entry in the file starts with an integer ID and a string name,
    // followed by an integer indicating the number of enrolled courses,
    // followed by the course codes of those enrolled courses.
    // Optionally, if there are waitlisted courses, they are listed after the enrolled courses.

    // Postcondition: Each student is added to the enrolled list of their respective courses.
    // If a course has reached its maximum enrollment, the student is added to the waitlist instead.
    // The `courseList` array is updated accordingly with the enrolled and waitlisted students.

    fstream infile;
    infile.open(filename);
    if(infile.fail()){
        cout << "Input file opening failed." << endl;
        exit(1);
    }
    int id, enrolledCourseNum, waitlistCourseNum;
    string name, enrolledCourse, waitlistCourse;
    while(infile >> id >> name){
        // Create a new Student instance
        Student* newStudent = new Student(id, name);
        // Read the number of enrolled courses
        infile >> enrolledCourseNum;
        for(int enrolledIdx = 0; enrolledIdx < enrolledCourseNum; enrolledIdx++){
            infile >> enrolledCourse;
            // Find the corresponding course and add the student to the enrolled list
            bool courseFound = false;
            for(int j = 0; j < courseCount; j++){
                if(courseList[j].getCode() == enrolledCourse){
                    courseList[j].addEnrollList(newStudent);
                    courseFound = true;
                    break;
                }
            }
        }
        // Peek to check if there are waitlist courses
        if (infile.peek() != '\n' && !infile.eof()) {
            infile >> waitlistCourseNum;
            for (int waitlistIdx = 0; waitlistIdx < waitlistCourseNum; waitlistIdx++) {
                infile >> waitlistCourse;
                // Find the corresponding course and add the student to the waitlist
                bool courseFound = false;
                for(int j = 0; j < courseCount; j++){
                    if(courseList[j].getCode() == waitlistCourse){
                        courseList[j].addWaitList(newStudent);
                        courseFound = true;
                        break;
                    }
                }
            }
        }
    }
    infile.close();
}

void menu1(Course* courseList, int courseCount){
    // Precondition: `courseList` points to a valid array of `Course` objects.
    // `courseCount` accurately represents the number of courses in `courseList`.

    // Postcondition: The function outputs the number of courses the student is enrolled in and waitlisted for.
    // It also lists the specific courses under "Registered" and "Waitlisted" categories.
    // No changes are made to the underlying data structures.

    int id;
    string name;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter your name : ";
    cin >> name;
    cout << endl;
    // Create the student object
    Student student(id, name);
    // Go over the course list, print this student's course info
    int registerNum = 0, waitlistNum = 0;
    for (int i = 0; i < courseCount; i++) {
        string status = courseList[i].findStudent(&student);
        if (status == "Enrolled") {
            registerNum++;
        } else if (status == "Wait") {
            waitlistNum++;
        }
    }
    cout << "Your registered " << registerNum << " courses and waitlisted " << waitlistNum <<  " courses." << endl;
    for(int i = 0; i < courseCount; i++){
        string status = courseList[i].findStudent(&student);
        if(status == "Enrolled")
            cout << "(R) " << left << setw(15) << courseList[i].getCode() << setw(15) << courseList[i].getTitle() << endl;
    }
    for(int i = 0; i < courseCount; i++){
        string status = courseList[i].findStudent(&student);
        if (status == "Wait")
            cout << "(W) " << left << setw(15) << courseList[i].getCode() << setw(15) << courseList[i].getTitle() << endl;
    }
    cout << endl;
}

void menu2(Course* courseList, int courseCount){
    // Precondition: `courseList` points to a valid array of `Course` objects.
    // `courseCount` accurately represents the number of courses in `courseList`.

    // Postcondition: The student is either successfully enrolled in the specified course,
    // or added to the waitlist if the course is full.
    // A corresponding message is displayed to inform the user of the outcome.
    // A new `Student` object is dynamically allocated and added to the course's enrollment or waitlist.

    int id;
    string name, code, title;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter your name : ";
    cin >> name;
    cout << "Enter course code : ";
    cin >> code;
    cout << "Enter course title : ";
    cin >> title;
    cout << endl;
    // Create the student object
    Student* student = new Student(id, name);
    // Find the course info then register this student
    bool success = false;
    for(int i = 0; i < courseCount; i++){
        if(courseList[i].getCode() == code && courseList[i].getTitle() == title){
            success = courseList[i].registerStudent(student);
            break;
        }
    }
    if(success)
        cout << "Registration succeed!" << endl;
    else
        cout << "You are on the waitlist for " << code << "." << endl;
    cout << endl;
}

void menu3(Course* courseList, int courseCount){
    // Precondition: `courseList` points to a valid array of `Course` objects.
    // `courseCount` accurately represents the number of courses in `courseList`.

    // Postcondition: The student is removed from the specified course's enrolled list or waitlist.
    // If removed from the enrolled list and the waitlist is not empty,
    // the first student on the waitlist is promoted to the enrolled list.
    // A corresponding message is displayed to inform the user of the outcome.
    // A new `Student` object is dynamically allocated and removed from the course's enrollment or waitlist.

    int id;
    string name, code, title;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter your name : ";
    cin >> name;
    cout << "Enter course code : ";
    cin >> code;
    cout << "Enter course title : ";
    cin >> title;
    cout << endl;
    // Create the student object
    Student* student = new Student(id, name);
    // Find the course info then remove this student
    bool success = false;
    for(int i = 0; i < courseCount; i++){
        if(courseList[i].getCode() == code && courseList[i].getTitle() == title){
            success = courseList[i].cancelStudent(student);
            break;
        }
    }
    if(success)
        cout << "'" << title << "' is removed from your course list." << endl;
    else
        cout << "You have been removed from the waitlist of '" << title << "' ." << endl;
    cout << endl;
}

void menu4(Course* courseList, int courseCount){
    // Precondition: `courseList` points to a valid array of `Course` objects.
    // `courseCount` accurately represents the number of courses in `courseList`.

    // Postcondition: The function outputs detailed information for each course,
    // including the list of enrolled students and those on the waitlist.
    // No changes are made to the underlying data structures.

    for(int i = 0; i < courseCount; i++)
        courseList[i].getAllInfo();
    cout << endl;
}

int main() {

    string filename1, filename2;
    cout << "Enter course filename : ";
    cin >> filename1;
    cout << "Enter enrollment filename : ";
    cin >> filename2;
    cout << endl;

    // Read file1 and save data to a dynamic array
    int courseCount = 0;
    Course* courseList = readFile1(filename1, courseCount);

    // Read file2 and save data as two linked list that connect with the course list
    readFile2(filename2, courseList, courseCount);

    // Show the menu
    int select;
    do{
        cout << "================= MENU =================" << endl;
        cout << "  1. View your registration" << endl;
        cout << "  2. Course registration" << endl;
        cout << "  3. Course cancellation" << endl;
        cout << "  4. Print enrollment list including waitlist" << endl;
        cout << "  5. Exit" << endl;
        cout << "  ---> Select : ";
        cin >> select;
        cout << endl;
        if(select == 1)
            menu1(courseList, courseCount);
        else if(select == 2)
            menu2(courseList, courseCount);
        else if(select == 3)
            menu3(courseList, courseCount);
        else if(select == 4)
            menu4(courseList, courseCount);
    }while(select != 5);

    return 0;
}
