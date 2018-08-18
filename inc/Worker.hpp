#pragma once
#include <string>
#include "Person.hpp"

class Worker : public Person
{
    int payment_;
public:
    Worker(const std::string & name,
           const std::string & surname,
           const std::string & PESEL,
           char sex,
           const std::string & address,
           int payment);
    explicit Worker(const std::string & dataPacked);
    std::string toString(char delimeter = ' ') const override;
    int getPayment() const override;
    void setPayment(int payment) override;
    ~Worker();
};
