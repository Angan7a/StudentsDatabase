#include "Student.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
 
Student::Student(const std::string & name,
                 const std::string & surname,
                 const std::string & PESEL,
                 char sex,
                 const std::string & address,
                 int index) :
    Person(name, surname, PESEL, sex, address),
    index_(index)
{}

Student::Student(const std::string & dataPacked) :
    Person(dataPacked),
    index_(std::stoi(dataPacked.substr(106, 7))) //needs implementation
{}

std::string Student::toString(char delimeter) const
{
    std::stringstream ss;
    ss << "Student: "
       << Person::toString(delimeter)
       << std::setw(17) << index_ << std::endl;
    return ss.str();
}

int Student::getIndex() const
{
    return index_;
}

int Student::getPayment() const 
{
    return 0;
}
    
void Student::setPayment(int payment) 
{
    std::string message = "I can't set payment - " + std::to_string(payment) + " to student";
    throw std::invalid_argument(message);
}

Student::~Student() {}
