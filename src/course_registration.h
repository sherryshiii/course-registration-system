#ifndef COURSE_REGISTRATION_H
#define COURSE_REGISTRATION_H

#include <string>
using namespace std;

const int MAX_ENROLLED = 10;

class Student {
private:
    int id;
    string name;
public:
    Student(const int& studentId, const string& studentName);
    int getId() const;
    string getName() const;
    bool equals(const Student* other) const;
    void print() const;
};

class Node {
private:
    Student* data;
    Node* next;
public:
    Node(Student* student);
    Student* getData();
    Node* getNext();
    void setData(Student* Data);
    void setNext(Node* Next);
};

class SingleLinkedList {
private:
    Node* head;
public:
    SingleLinkedList();
    ~SingleLinkedList();
    void add(Student* student);
    bool remove(Student* student);
    bool find(Student* student) const;
    Student* removeFirst();
    void printList() const;
};

class Course {
private:
    string code;
    string title;
    int enrollSize;
    int waitSize;
    SingleLinkedList enrolledList;
    SingleLinkedList waitList;
public:
    Course();
    Course(const string& courseCode, const string& courseTitle, int enrollNum, int waitNum);
    string getCode() const;
    string getTitle() const;
    void addEnrollList(Student* student);
    void addWaitList(Student* student);
    bool registerStudent(Student* student);
    bool cancelStudent(Student* student);
    string findStudent(Student* student);
    void getAllInfo();
};

Course* readFile1(string filename, int& courseCount);
void readFile2(string filename2, Course* courseList, int courseCount);
void menu1(Course* courseList, int courseCount);
void menu2(Course* courseList, int courseCount);
void menu3(Course* courseList, int courseCount);
void menu4(Course* courseList, int courseCount);

#endif //COURSE_REGISTRATION_H