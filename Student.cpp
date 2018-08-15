#include "Student.hpp"
#include <stdexcept>
 
Student::Student(const std::string & name, const std::string & surname, const std::string & PESEL, char sex, const std::string & address, int index) :
    Person(name, surname, PESEL, sex, address),
    index_(index)
{}

Student::Student(const std::string & dataPacked) :
    Person(dataPacked),
    index_() //needs implementation
{}

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
