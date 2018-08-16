#pragma once
#include "Person.hpp"
#include <vector>
#include <memory>

class Database
{
    std::vector<std::shared_ptr<Person>> persons_;
    int getRandom(int min, int max) const;
    void getData(std::string & name, std::string & surname, std::string & address, char & sex, std::string & PESEL) const;
public:
    void addPerson(std::shared_ptr<Person> person);
    void sortByPESEL();
    void sortBySurname();
    void sortByPayment();
    void removePersonWithPESEL(const std::string & PESEL);
    std::vector<std::shared_ptr<Person>>::iterator findPersonWithPESEL(const std::string & PESEL);
    std::vector<std::shared_ptr<Person>> findPersonWithSurname(const std::string & surname);
    void changeAddressPaymentPersonWithPESEL(const std::string & PESEL, const std::string & address, int payment);
    void showDB();
    void saveToFile();
    void readFromFile();
    void fillDB(int numberOfStudnets, int numberOfWorkers);
    int getNumberOfPersons() const;
    std::vector<std::shared_ptr<Person>>::iterator getFirstIterOfPerson();
    void sort(std::function<bool(std::shared_ptr<Person> &,std::shared_ptr<Person> &)> what);
    auto find(std::function<bool(std::shared_ptr<Person> &)> what,std::vector<std::shared_ptr<Person>>::iterator iter);
};
