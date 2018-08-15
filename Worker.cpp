#include "Worker.hpp"

Worker::Worker(const std::string & name, const std::string & surname, const std::string & PESEL, char sex, const std::string & address, int payment) :
    Person(name, surname, PESEL, sex, address),
    payment_(payment)
{}

Worker::Worker(const std::string & dataPacked) :
    Person(dataPacked),
    payment_() //needs implemantation
{}

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
