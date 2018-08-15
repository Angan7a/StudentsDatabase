#include "Database.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <stdexcept> 
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include "Student.hpp"
#include "Worker.hpp"

void Database::addPerson(std::shared_ptr<Person> person)
{
    try
    {
        findPersonWithPESEL(person->getPESEL());
        std::string message = "I can't add person with PESEL - " + person->getPESEL() + ". This person exists in database";
        throw std::out_of_range(message);
    }
    catch (const std::invalid_argument & exc)
    {
        persons_.push_back(person);
    }
    catch (const std::out_of_range & exc)
    {
        std::cout << exc.what() << std::endl;
    }
}

void Database::sort(std::function<bool(std::shared_ptr<Person> &,std::shared_ptr<Person> &)> what)
{
        std::sort(persons_.begin(), persons_.end(), what);
}

void Database::sortByPayment()
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty!");
    sort([](const auto & person1, const auto & person2){return person1->getPayment() < person2->getPayment();});
}

void Database::sortByPESEL()
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty!");
    sort([](const auto & person1, const auto & person2){return person1->getPESEL() < person2->getPESEL();});
} 

void Database::sortBySurname()
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty!");
    sort([](const auto & person1, const auto & person2){return person1->getSurname() < person2->getSurname();});
}

auto Database::find(std::function<bool(std::shared_ptr<Person> &)> what, std::vector<std::shared_ptr<Person>>::iterator iter)
{
    return std::find_if(iter, end(persons_), what);
}

void Database::removePersonWithPESEL(const std::string & PESEL)
{ 
    persons_.erase(findPersonWithPESEL(PESEL));
}

std::vector<std::shared_ptr<Person>>::iterator Database::findPersonWithPESEL(const std::string & PESEL)
{
    if (!Person::checkPESEL(PESEL)) throw std::invalid_argument("Bad PESEL");
    if (persons_.empty()) throw std::invalid_argument("Database is empty!");
    auto iter = find([PESEL](const auto & person_){return person_->getPESEL() == PESEL;}, begin(persons_));
    std::string message = "There is no person with PESEL - " + PESEL + " in the database";
    if (iter == end(persons_)) throw std::invalid_argument(message);
    return iter;
}

std::vector<std::shared_ptr<Person>> Database::findPersonWithSurname(const std::string & surname)
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty!");
    std::vector<std::shared_ptr<Person>> personsWithSurname;
    auto iter = begin(persons_);
    while (iter != end(persons_))
    {
        iter = find([surname](const auto & person_){return person_->getSurname() == surname;}, iter);
        if (iter != end(persons_))
        {
            personsWithSurname.push_back(*iter);
            iter++;
        }
    }
    std::string message = "There isn't person with surname " + surname;
    if (personsWithSurname.empty()) throw std::invalid_argument(message);
    return personsWithSurname;
}
    
void Database::changeAddressPaymentPersonWithPESEL(const std::string & PESEL, const std::string & address, int payment)
{
    auto person = *findPersonWithPESEL(PESEL);
    person -> setAddress(address);
    person -> setPayment(payment);
}
    
void Database::showDB()
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty");
    printNamesTable();
    for ( auto singlePerson : persons_ )
    {
        printDataPerson(singlePerson);
    }
}

void Database::saveToFile()
{
    if (persons_.empty()) throw std::invalid_argument("Database is empty");
    std::fstream file;
    file.open ("data_base.txt", std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("unable to open file");
    else
    {
        for (auto person : persons_)
        {
            file << person->toString();
        }
        file.close();
        persons_.clear();
    }
}

void Database::readFromFile()
{
    std::fstream file;
    file.open ("data_base.txt", std::ios::in);
    if(!file.good())
        throw std::runtime_error("unable to open file");
    else
    {
        std::string line;
        while(std::getline(file, line))
        {
              if (std::stoi(line.substr(140,10)))
              {
                  std::shared_ptr<Person> worker = std::make_shared<Worker>(line);
                  addPerson(worker);
              } else
              {
                  std::shared_ptr<Person> student = std::make_shared<Student>(line);
                  addPerson(student);
              }
        }
        file.close();
    }
}
    
void Database::fillDB(int numberOfStudnets, int numberOfWorkers)
{
    std::string name, surname, address, PESEL;
    char sex;
    while (numberOfStudnets--)
    {
        getData(name, surname, address, sex, PESEL); 
        int index = getRandom(10000, 100000);
        std::shared_ptr<Person> student = std::make_shared<Student>(name, surname, PESEL, sex, address, index);
        addPerson(student);
    }
    while (numberOfWorkers--)
    {
        getData(name, surname, address, sex, PESEL); 
        int payment = getRandom(3000, 15000);
        std::shared_ptr<Person> worker = std::make_shared<Worker>(name, surname, PESEL, sex, address, payment);
        addPerson(worker);
    }
}

int Database::getRandom(int min, int max) const
{
    std::random_device rd;
    std::mt19937_64  mersenne(rd());                   
    std::uniform_int_distribution<> die(min, max);
    return die(mersenne);
}

void Database::getData(std::string & name, 
                       std::string & surname, 
                       std::string & address, 
                       char & sex, 
                       std::string & PESEL) const 
{
    std::vector<std::string> names = {"Anna", "Kasia", "Marek", 
                                      "Zuzanna", "Tomek", "Malgorzata", 
                                      "Kamil", "Jan", "Marta", 
                                      "Piotr", "Bogdan"};
    std::vector<std::string> surnames = {"Nowak", "Dudzik", 
                                         "Jakimiszyn", "Adamczyk", 
                                         "Jackiewicz", "Lis", 
                                         "Owczarek", "Borowek"};
    std::vector<std::string> cities = {"Krakow", "Wroclaw", 
                                       "Poznan", "Szczecin", 
                                       "Warszawa", "Opole", 
                                       "Lodz"};
    std::vector<std::string> streets = {"Ciepla", "Krakowska", 
                                        "Piekna", "Opolska", 
                                        "Dluga", "Zielinskiego", 
                                        "Borowska"};
    PESEL = std::to_string(getRandom(100000, 999999));
    PESEL += std::to_string(getRandom(10000, 99999));
    for (int i = 0; i < 10; i++)
    {
        PESEL.pop_back();
        PESEL += std::to_string(i);
        if (Person::checkPESEL(PESEL)) break;
    }
    name = names[getRandom(0, names.size() - 1)];
    surname = surnames[getRandom(0, surnames.size() - 1)];
    address = cities[getRandom(0, cities.size() - 1)] + ", " 
            + streets[getRandom(0, streets.size() - 1)] + " " 
            + std::to_string(getRandom(1,100));
    sex = name.back() == 'a'? 'W' : 'M';
}

void Database::printNamesTable() const
{
    std::cout << std::left << std::setw(20)
              << "PESEL" << std::setw(20)
              << "Name" << std::setw(20)
              << "Surname" << std::setw(20)
              << "Sex" << std::setw(40)
              << "Address" << std::setw(20)
              << "Index number" << std::setw(20)
              << "Payment" << std::endl;
    std::cout.fill('=');
    std::cout << std::setw(150) << "=" << std::endl;
    std::cout.fill(' ');
}

void Database::printDataPerson(std::shared_ptr<Person> person) const
{
    std::cout << person->toString();
}

int Database::getNumberOfPersons() const
{
    return persons_.size();
}

std::vector<std::shared_ptr<Person>>::iterator Database::getFirstIterOfPerson()
{
    return begin(persons_);
}
