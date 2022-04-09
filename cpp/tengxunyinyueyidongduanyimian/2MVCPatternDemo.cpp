#include <bits/stdc++.h>
using namespace std;
#include "2Student.cpp"
#include "2StudentView.cpp"
#include "2StudentController.cpp"

Student retrieveStudentFromDatabase()
{
    Student *student = new Student();
    student->setName("Robert");
    student->setRollNo("10");
    return *student;
}

int main(void)
{

    //从数据库获取学生记录
    Student model = retrieveStudentFromDatabase();

    //创建一个视图：把学生详细信息输出到控制台
    StudentView *view = new StudentView();

    StudentController *controller = new StudentController(model, *view);

    controller->updateView();

    //更新模型数据
    controller->setStudentName("John");

    controller->updateView();
    return 0;
}
