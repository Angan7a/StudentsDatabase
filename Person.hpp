#pragma once

#include <string>

class Person
{
    std::string name_;
    std::string surname_;
    std::string PESEL_;
    char sex_;
    std::string address_;
public:
    Person(const std::string & name, const std::string & surname, const std::string & PESEL, char sex, const std::string & address);
    Person(const std::string & dataPacked);
    virtual int getPayment() const = 0;
    std::string getName() const;
    std::string getPESEL() const;
    std::string getSurname() const;
    void setAddress(const std::string & address);
    virtual void setPayment(int payment) = 0;
    static bool checkPESEL(const std::string & PESEL);
    std::string getAddress() const;
    char getSex() const;
    virtual int getIndex() const;
    virtual ~Person();
    std::string toString() const;
};
