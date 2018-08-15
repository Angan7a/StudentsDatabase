#pragma once
#include "Person.hpp"

class Student : public Person
{
    int index_;
public:
    Student(const std::string & name, const std::string & surname, const std::string & PESEL, char sex, const std::string & address, int index);
    Student(const std::string & dataPacked);
    int getIndex() const override;
    int getPayment() const override;
    void setPayment(int payment) override;
    ~Student();
};
