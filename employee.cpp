#include <iostream>

using namespace std;

class Employee {
public:
    Employee(
        const string& name,
        int id, 
        const string& department, 
        int salary
    ) : name{name}, id{id}, department{department}, salary{salary} {
        if (name.empty()) {
            throw invalid_argument("Name cannot be empty");
        }
        if (id <= 0) {
            throw invalid_argument("ID must be a positive integer");
        }
        if (department.empty()) {
            throw invalid_argument("Department cannot be empty");
        }
        if (salary <= 0) {
            throw invalid_argument("Salary must be a positive integer");
        }
    }

    string getName() const { return name; }
    int getId() const { return id; }
    string getDepartment() const { return department; }
    int getSalary() const { return salary; }
    void giveData() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
    }

private:
    string name;
    int id;
    string department;
    int salary;
};