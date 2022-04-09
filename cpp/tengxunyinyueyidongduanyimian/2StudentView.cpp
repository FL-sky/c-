#ifndef _student_view_
#define _student_view_

#include <bits/stdc++.h>
using namespace std;

class StudentView
{
public:
    StudentView() {}
    void printStudentDetails(string studentName, string studentRollNo)
    {
        puts("Student: ");
        printf("Name: %s\n", studentName.c_str());
        printf("Roll No: %s\n", studentRollNo.c_str());
    }
};

#endif