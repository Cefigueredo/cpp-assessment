#include "tinyxml2.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

class Employee {
public:
    Employee(
        const std::string& name,
        int id, 
        const std::string& department, 
        int salary
    ) : name(name), id(id), department(department), salary(salary) {}
    std::string name;
    int id;
    std::string department;
    int salary;
};

std::vector<Employee> employees {};

bool isXMLFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("<?xml") != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool isJSONFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (!line.empty() && (line[0] == '{' || line[0] == '[')) {
            return true;
        }
    }
    return false;
}

void printEmployees() {
    for (const auto& employee : employees) {
        std::cout << "Name: " << employee.name << std::endl;
        std::cout << "ID: " << employee.id << std::endl;
        std::cout << "Department: " << employee.department << std::endl;
        std::cout << "Salary: " << employee.salary << std::endl;
        std::cout << std::endl;
    }
}

void averageSalary() {
    int total = 0;
    for (const auto& employee : employees) {
        total += employee.salary;
    }
    double average = static_cast<double> (total) / employees.size();
    std::cout << "----- Average salary of the employees: ----"  << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << std::endl;
}

void getHighestPaidEmployee() {
    int maxSalary = 0;
    Employee highestPaidEmployee("", 0, "", 0);
    for (const auto& employee : employees) {
        if (employee.salary > maxSalary) {
            maxSalary = employee.salary;
            highestPaidEmployee = employee;
        }
    }
    std::cout << "----- Highest paid employee: -----" << std::endl;
    std::cout << "Name: " << highestPaidEmployee.name << std::endl;
    std::cout << "ID: " << highestPaidEmployee.id << std::endl;
    std::cout << "Department: " << highestPaidEmployee.department << std::endl;
    std::cout << "Salary: " << highestPaidEmployee.salary << std::endl;
    std::cout << std::endl;
}

void orderEmployeesByID() {
    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.id < b.id;
    });
}

void handleOutput() {
    averageSalary();
    getHighestPaidEmployee();
    orderEmployeesByID();
    std::cout << "Employees ordered by ID:\n";
    printEmployees();
}



void addEmployee(const std::string& name, int id, const std::string& department, int salary) {
    employees.push_back(Employee(name, id, department, salary));
}

void parseXML(const std::string& filePath) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_SUCCESS) {
        std::cout << "XML file loaded successfully.\n";
        tinyxml2::XMLElement* root = doc.FirstChildElement("employees");

        if (root) {
            for (tinyxml2::XMLElement* employee = root->FirstChildElement("employee"); employee; employee = employee->NextSiblingElement("employee")) {
                const char* name = employee->FirstChildElement("name")->GetText();
                const char* id = employee->FirstChildElement("id")->GetText();
                const char* department = employee->FirstChildElement("department")->GetText();
                const char* salary = employee->FirstChildElement("salary")->GetText();

                addEmployee(name, std::stoi(id), department, std::stoi(salary));
            }
            handleOutput();
        } else {
            std::cout << "No root element found.\n";
        }
    } else {
        std::cout << "Failed to load XML file.\n";
    }
}

void parseJSON(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json jsonData;

    if (file >> jsonData) {
        std::cout << "JSON file loaded successfully.\n";

        for (const auto& employee : jsonData["employees"]) {
            std::string name = employee["name"];
            int id = employee["id"];
            std::string department = employee["department"];
            int salary = employee["salary"];

            addEmployee(name, id, department, salary);
            
        }
        handleOutput();
    } else {
        std::cout << "Failed to load JSON file.\n";
    }
}

int main() {
    std::cout << "Please insert the name of the file to read:" << std::endl;
    std::string filePath = "data/";
    std::string fileName = "employees.json";
    // std::cin >> fileName;
    filePath += fileName;
    
    if (isXMLFile(filePath)) {
        std::cout << "The file is an XML file.\n";
        parseXML(filePath);
    } else if (isJSONFile(filePath)){
        std::cout << "The file is a JSON file.\n";
        parseJSON(filePath);
    } else {
        std::cerr << "The file is not an XML or JSON file.\n";
    }
    return 0;
}
