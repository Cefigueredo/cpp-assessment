#include "tinyxml2.h"
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

void readXML(const std::string& filePath) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filePath.c_str()) == tinyxml2::XML_SUCCESS) {
        std::cout << "XML file loaded successfully.\n";
        doc.Print();
    } else {
        std::cout << "Failed to load XML file.\n";
    }
}

int main() {
    std::cout << "Please insert the name of the file to read:" << std::endl;
    std::string filePath = "data/";
    std::string fileName = "";
    std::cin >> fileName;
    filePath += fileName;
    
    if (isXMLFile(filePath)) {
        std::cout << "The file is an XML file.\n";
        readXML(filePath);
    } else if (isJSONFile(filePath)){
        std::cout << "The file is a JSON file.\n";
    } else {
        std::cerr << "The file is not an XML or JSON file.\n";
    }
    return 0;
}
