# Amadeus Technical Assessment

Owner: Carlos Figueredo - Software Engineer

This project is a technical assessment for Amadeus. The project is a C++ application that reads a file in format XML or JSON containing a list of employees. It calculates the average salary of the employees, prints the employees with the highest salary and displays the employees ordered by ID.

This proejct was developed on a Macbook Pro with macOS Sonoma 14.3.1 and chip M1 Pro. The project was developed using C++20 in Visual Studio Code.

# Instructions

1. Clone the repository
2. Open the project in Visual Studio Code
3. Open the terminal in Visual Studio Code
4. Give permission to the scripts to compile and run the project:
```bash
chmod +x build.sh run.sh
```

5. Compile the project (optional):
```bash
./build.sh
```

6. Run the project:
```bash
./run.sh
```

5. The program will ask you to enter the name of the file. Your file has to be in the data/ folder and it has to be in XML or JSON format. You can use the next files:
```bash
employees.xml
employees.json
```

If you want to use your own file, you can create a new file in the data/ folder and follow the next format for XML:
```xml
<?xml version="1.0"?>
<?xml version="1.0" encoding="UTF-8"?>
<employees>
    <employee>
        <name>Karl Fix</name>
        <id>103</id>
        <department>Engineering</department>
        <salary>100001</salary>
    </employee>
    <employee>
        <name>John Doe</name>
        <id>101</id>
        <department>HR</department>
        <salary>50000</salary>
    </employee>
</employees>
```

Or follow the next format for JSON:
```json
{
    "employees": [
        {
            "name": "Karl Fix",
            "id": 103,
            "department": "Engineering",
            "salary": 100001
        },
        {
            "name": "John Doe",
            "id": 101,
            "department": "HR",
            "salary": 50000
        }
    ]
}
```
