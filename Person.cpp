#include "Person.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <limits>

Person::Person(const std::string & name,
               const std::string & surname,
               const std::string & PESEL,
               char sex,
               const std::string & address) :
    name_(name),
    surname_(surname),
    sex_(sex),
    address_(address)
{
    if (!Person::checkPESEL(PESEL)) throw std::invalid_argument("Bad PESEL");
    PESEL_ = PESEL;
}

Person::Person(const std::string & dataPacked) :
    name_(dataPacked.substr(10, 14)),//need implemantation
    surname_(dataPacked.substr(25, 14)),//need implemantation
    PESEL_(dataPacked.substr(39, 11)),
    sex_(dataPacked[51]),//need implemantation
    address_(dataPacked.substr(54, 40))//need implemantation
{}
/*{
    std::string PESEL; //need implemantation
    if (!Person::checkPESEL(PESEL)) throw std::invalid_argument("Bad PESEL");
    PESEL_(dataPacked.substr(40, 11));
}
*/
std::string Person::getSurname() const
{
    return surname_;
}

std::string Person::getName() const
{
    return name_;
}

std::string Person::getPESEL() const
{
    return PESEL_;
}

void Person::setAddress(const std::string & address)
{
    address_ = address;
}

bool Person::checkPESEL(const std::string & PESEL) 
{
    if (PESEL.size() != 11) return false;
    int sum = 0;
    sum = (PESEL[0] - 48) * 9 +
          (PESEL[1] - 48) * 7 +
          (PESEL[2] - 48) * 3 +
          (PESEL[3] - 48) * 1 +
          (PESEL[4] - 48) * 9 +
          (PESEL[5] - 48) * 7 +
          (PESEL[6] - 48) * 3 +
          (PESEL[7] - 48) * 1 +
          (PESEL[8] - 48) * 9 +
          (PESEL[9] - 48) * 7;
    if (sum == 0) return false;
    if ((sum%10) == (PESEL[10] - 48)) return true;
    return false;
}

std::string Person::getAddress() const
{
    return address_;
}

char Person::getSex() const
{
    return sex_;
}

int Person::getIndex() const
{
    return std::numeric_limits<int>::max();
}

Person::~Person() {}

std::string Person::toString(char delimeter) const
{
    std::stringstream ss;
    ss << std::setw(14) << name_ << delimeter
       << std::setw(14) << surname_ << delimeter
       << std::setw(11) << PESEL_ << delimeter
       << std::setw(1) << static_cast<char>(sex_) << delimeter
       << std::setw(40) << address_ << delimeter;
    return ss.str();
}
