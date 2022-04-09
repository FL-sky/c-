#ifndef _student_
#define _student_

#include <bits/stdc++.h>
using namespace std;
class Student
{
private:
    string rollNo;
    string name;

public:
    Student() {}
    string getRollNo()
    {
        return rollNo;
    }

    void setRollNo(string rollNo)
    {
        this->rollNo = rollNo;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }
};

#endif