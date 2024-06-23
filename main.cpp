#include "tinyxml2.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

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

                std::cout << "Employee:\n";
                std::cout << "  Name: " << (name ? name : "N/A") << "\n";
                std::cout << "  Id: " << (id ? id : "N/A") << "\n";
                std::cout << "  Department: " << (department ? department : "N/A") << "\n";
                std::cout << "  Salary: " << (salary ? salary : "N/A") << "\n";
            }
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

            std::cout << "Employee:\n";
            std::cout << "  Name: " << name << "\n";
            std::cout << "  Id: " << id << "\n";
            std::cout << "  Deparment: " << department << "\n";
            std::cout << "  Salary: " << salary << "\n";
        }
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
