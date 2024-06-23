#include "tinyxml2.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
class WrongFileException : public std::exception {
public:
    const char* what() const noexcept override {
        return "The file is not an XML or JSON file.";
    }
};

class Employee {
public:
    Employee(
        const std::string& name,
        int id, 
        const std::string& department, 
        int salary
    ) : name{name}, id{id}, department{department}, salary{salary} {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (id <= 0) {
            throw std::invalid_argument("ID must be a positive integer");
        }
        if (department.empty()) {
            throw std::invalid_argument("Department cannot be empty");
        }
        if (salary <= 0) {
            throw std::invalid_argument("Salary must be a positive integer");
        }
    }

    std::string getName() const { return name; }
    int getId() const { return id; }
    std::string getDepartment() const { return department; }
    int getSalary() const { return salary; }
    void giveData() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Department: " << department << std::endl;
        std::cout << "Salary: " << salary << std::endl;
    }

private:
    std::string name;
    int id;
    std::string department;
    int salary;
};

std::vector<Employee> employees {};
std::set<int> employeeIDs {};

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
        employee.giveData();
        std::cout << std::endl;
    }
}

void averageSalary() {
    int total = 0;
    for (const auto& employee : employees) {
        total += employee.getSalary();
    }
    double average = static_cast<double> (total) / employees.size();
    std::cout << "----- Average salary of the employees: ----"  << std::endl;
    std::cout << "Value: " << average << std::endl;
    std::cout << std::endl;
}

void getHighestPaidEmployee() {
    int maxSalary = 0;
    Employee highestPaidEmployee("Dummy", 1, "Dummy", 1);
    for (const auto& employee : employees) {
        if (employee.getSalary() > maxSalary) {
            maxSalary = employee.getSalary();
            highestPaidEmployee = employee;
        }
    }
    std::cout << "----- Highest paid employee: -----\n" << std::endl;
    highestPaidEmployee.giveData();
    std::cout << std::endl;
}

void orderEmployeesByID() {
    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.getId() < b.getId();
    });
}

void handleOutput() {
    std::cout << std::endl;
    std::cout << "############################################\n";
    std::cout << "####### Executing output handling... #######\n";
    std::cout << "############################################\n";
    std::cout << std::endl;
    try {
        if (employees.empty()) {
            throw std::invalid_argument("No employees to handle output.");
            return;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    averageSalary();
    getHighestPaidEmployee();
    orderEmployeesByID();
    std::cout << "----- Employees ordered by ID: -----\n";
    printEmployees();
}



void addEmployee(const std::string& name, int id, const std::string& department, int salary) {
    try {
        std::cout << "* Adding employee: " << name << std::endl;
        if (employeeIDs.find(id) != employeeIDs.end()) {
            throw std::invalid_argument("Duplicate ID found: " + std::to_string(id));
        }
        employees.push_back(Employee(name, id, department, salary));
        employeeIDs.insert(id);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Exception adding employee: " << e.what() << std::endl;
        return;
    }
}

void parseXML(const std::string& filePath) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_SUCCESS) {
        std::cout << "XML file loaded successfully.\n";
        tinyxml2::XMLElement* root = doc.FirstChildElement("employees");

        if (root) {
            for (tinyxml2::XMLElement* employee = root->FirstChildElement("employee"); employee; employee = employee->NextSiblingElement("employee")) {
                const char *name = employee->FirstChildElement("name")->GetText();
                const char *id = employee->FirstChildElement("id")->GetText();
                const char *department = employee->FirstChildElement("department")->GetText();
                const char *salary = employee->FirstChildElement("salary")->GetText();

                addEmployee(name, std::stoi(id), department, std::stoi(salary));
            }
            handleOutput();
        } else {
            std::cout << "No root element found.\n";
        }
    } else {
        throw std::runtime_error("Failed to load XML file.");
    }
}

void parseJSON(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json jsonData;

    try {
        if (file >> jsonData) {
            std::cout << "JSON file loaded successfully.\n";
            std::cout << std::endl;
            for (const auto& employee : jsonData["employees"]) {
                std::string name = employee["name"];
                int id = employee["id"];
                std::string department = employee["department"];
                int salary = employee["salary"];

                addEmployee(name, id, department, salary);
            }
            handleOutput();
        }
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Failed to load JSON file: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Please insert the name of the file to read:" << std::endl;
    std::string filePath = "data/";
    std::string fileName = "";
    std::cin >> fileName;
    filePath += fileName;
    
    try {
        if (isXMLFile(filePath)) {
            parseXML(filePath);
        } else if (isJSONFile(filePath)){
            parseJSON(filePath);
        } else {
            throw WrongFileException();
        }
    } catch (const WrongFileException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
