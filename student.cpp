/*******************************************************************************
 * Name    : student.cpp
 * Author  : Michael McCreesh
 * Version : 1.0
 * Date    : September 4, 2019
 * Description : "Student" class and vectors
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student{
public:
    //constructor
    Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

    //returns full name
    string full_name() const{
        return first_ + " " + last_;
    }

    //accessors
    int id() const{
        return id_;
    }

    float gpa() const{
        return gpa_;
    }

    //prints all of a student's info
    void print_info() const{
        cout << full_name() << fixed << setprecision(2) <<", GPA: " << gpa() << ", ID: " << id() << endl;
    }

private:
    string first_, last_;
    float gpa_;
    int id_;

};

/**
 *TakesavectorofStudentobjects,andreturnsanewvector
 *withallStudentswhoseGPAis<1.0.
 */
vector<Student> find_failing_students(const vector<Student> &students){
    vector<Student> failing_students;
    //Iterates through the students vector, appending each student whose gpa is
    //less than 1.0 to the failing_students vector.
    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        if(it->gpa() < 1.0){
            failing_students.push_back(*it);
        }
    }
    return failing_students;
}

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    for (auto it = students.cbegin(); it != students.cend(); ++it) {
        it->print_info();
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    // TODO
    // Print a space and the word 'None' on the same line if no students are
    // failing.
    // Otherwise, print each failing student on a separate line.
    vector<Student> failing_students = find_failing_students(students);
    if(failing_students.empty()){
        cout << " None" << endl;
    }else{
        cout << "\n";
        print_students(failing_students);
    }
    return 0;
}