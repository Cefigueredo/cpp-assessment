#include <iostream>

using namespace std;

class WrongFileException : public exception {
public:
    const char* what() const noexcept override {
        return "The file is not an XML or JSON file.";
    }
};