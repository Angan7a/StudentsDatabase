#pragma once
#include <string>
#include "Person.hpp"

class Worker : public Person
{
    int payment_;
public:
    Worker(const std::string & name, const std::string & surname, const std::string & PESEL, char sex, const std::string & address, int payment);
    Worker(const std::string & dataPacked);
    int getPayment() const override;
    void setPayment(int payment) override;
    ~Worker();
};
