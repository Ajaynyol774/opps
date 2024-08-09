#include <iostream> // For input and output operations
#include <vector>   // For using vector container
#include <string>   // For using string class
#include <stdexcept> // For handling exceptions like std::bad_alloc

using namespace std; // To avoid prefixing standard library names with std::

class Student {
private:
    // Private member variables to store student details
    string name;                  // Name of the student
    int rollNumber;               // Roll number of the student
    string studentClass;          // Class of the student
    char division;                // Division of the student (e.g., 'A', 'B')
    string dob;                   // Date of Birth (e.g., "DD-MM-YYYY")
    string bloodGroup;            // Blood group of the student
    string contactAddress;        // Contact address of the student
    string telephoneNumber;       // Telephone number of the student
    string drivingLicenseNo;      // Driving license number of the student

public:
    // Default constructor
    Student() : rollNumber(0), division('A') {
        cout << "Default constructor called" << endl; // Notify when the default constructor is called
    }

    // Parameterized constructor
    Student(string name, int rollNumber, string studentClass, char division, string dob, string bloodGroup, string contactAddress, string telephoneNumber, string drivingLicenseNo)
        : name(name), rollNumber(rollNumber), studentClass(studentClass), division(division), dob(dob), bloodGroup(bloodGroup), contactAddress(contactAddress), telephoneNumber(telephoneNumber), drivingLicenseNo(drivingLicenseNo) {
        cout << "Parameterized constructor called" << endl; // Notify when the parameterized constructor is called
    }

    // Copy constructor
    Student(const Student &s) {
        // Copy all member variables from the source student object
        name = s.name;
        rollNumber = s.rollNumber;
        studentClass = s.studentClass;
        division = s.division;
        dob = s.dob;
        bloodGroup = s.bloodGroup;
        contactAddress = s.contactAddress;
        telephoneNumber = s.telephoneNumber;
        drivingLicenseNo = s.drivingLicenseNo;
        cout << "Copy constructor called" << endl; // Notify when the copy constructor is called
    }

    // Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl; // Notify when the destructor is called
    }

    // Static member function to show the total number of students
    static void showTotalStudents(int count) {
        cout << "Total students: " << count << endl; // Display the total number of students
    }

    // Friend class declaration to allow Display class to access private members of Student
    friend class Display;

    // Inline function to display student details
    inline void display() const {
        // Print all student details
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Class: " << studentClass << endl;
        cout << "Division: " << division << endl;
        cout << "Date of Birth: " << dob << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Contact Address: " << contactAddress << endl;
        cout << "Telephone Number: " << telephoneNumber << endl;
        cout << "Driving License No: " << drivingLicenseNo << endl;
    }

    // Overloading new operator for dynamic memory allocation
    void* operator new(size_t size) {
        cout << "Overloading new operator with size: " << size << endl; // Notify size of allocation
        void *p = ::operator new(size); // Allocate memory using default new operator
        return p; // Return allocated memory pointer
    }

    // Overloading delete operator for dynamic memory deallocation
    void operator delete(void *p) {
        cout << "Overloading delete operator" << endl; // Notify deallocation
        ::operator delete(p); // Deallocate memory using default delete operator
    }

    // Function to take input from user
    void input() {
        cout << "Enter Name: ";
        getline(cin, name); // Get student's name from user input
        cout << "Enter Roll Number: ";
        cin >> rollNumber; // Get student's roll number
        cin.ignore(); // Ignore newline character left in buffer
        cout << "Enter Class: ";
        getline(cin, studentClass); // Get student's class
        cout << "Enter Division: ";
        cin >> division; // Get student's division
        cin.ignore(); // Ignore newline character left in buffer
        cout << "Enter Date of Birth (DD-MM-YYYY): ";
        getline(cin, dob); // Get student's date of birth
        cout << "Enter Blood Group: ";
        getline(cin, bloodGroup); // Get student's blood group
        cout << "Enter Contact Address: ";
        getline(cin, contactAddress); // Get student's contact address
        cout << "Enter Telephone Number: ";
        getline(cin, telephoneNumber); // Get student's telephone number
        cout << "Enter Driving License No: ";
        getline(cin, drivingLicenseNo); // Get student's driving license number
    }
};

// Friend class to display student information
class Display {
public:
    // Function to show student details
    void showStudent(const Student &s) {
        s.display(); // Call display function of Student class
    }
};

int main() {
    try {
        vector<Student*> students; // Vector to store pointers to Student objects
        char choice; // Variable to store user choice
        int studentCount = 0; // Variable to keep track of number of students

        do {
            Student *s = new Student(); // Create a new student object dynamically
            s->input(); // Input student details from user
            students.push_back(s); // Add student object to the vector
            studentCount++; // Increment student count
            Student::showTotalStudents(studentCount); // Show updated total number of students

            cout << "Do you want to add another student? (y/n): ";
            cin >> choice; // Get user's choice to continue or stop
            cin.ignore(); // Ignore newline character left in buffer
        } while (choice == 'y' || choice == 'Y'); // Continue if user enters 'y' or 'Y'

        Display d; // Create a Display object
        for (const auto &student : students) {
            d.showStudent(*student); // Display each student's information
        }

        // Deleting all student objects to free allocated memory
        for (auto &student : students) {
            delete student; // Free memory for each student object
        }
    } catch (bad_alloc &e) {
        // Handling memory allocation failure
        cout << "Memory allocation failed: " << e.what() << endl; // Display error message
    }

    return 0; // End of program
}
