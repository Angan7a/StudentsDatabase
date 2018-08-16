#include "Worker.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <limits>

Worker::Worker(const std::string & name,
               const std::string & surname,
               const std::string & PESEL,
               char sex,
               const std::string & address,
               int payment) :
    Person(name, surname, PESEL, sex, address),
    payment_(payment)
{}

Worker::Worker(const std::string & dataPacked) :
    Person(dataPacked),
    payment_(std::stoi(dataPacked.substr(96, 7))) //needs implemantation
{}
std::string Worker::toString(char delimeter) const
{
    std::stringstream ss;
    ss << "Worker:  "
       << Person::toString(delimeter)
       << std::setw(7) << payment_ << " PLN" << std::endl;
    return ss.str();
}

int Worker::getPayment() const
{
    return payment_;
}
    
void Worker::setPayment(int payment) 
{
    if ( payment >= 0 )
    payment_ = payment;
}

Worker::~Worker() {}
