#include "../inc/Database.hpp"
#include "../inc/Person.hpp"
#include "../inc/Worker.hpp"
#include "../inc/PeselValidation.hpp"
#include <iostream>

int main()
{
    Database db;
  
    std::cout << "===== Try find person with PESEL - 123 - in empty database" << std::endl;
    try
    {
        db.findPersonWithPESEL("123");
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cin.get();
    
    try
    {
        db.fillDB(5, 8);
        std::shared_ptr<Person> worker = std::make_shared<Worker>("Katarzyna", "Nowak", "85091205707", 'W', "Wroclaw, Staszica 12", 99789);
        db.addPerson(worker);
        std::cout << "===== Show database" << std::endl;
        db.showDB();
        std::cin.get();
        std::cout << "===== Find data person with PESEL - 85091205707" << std::endl;
        std::shared_ptr<Person> foundPerson = *(db.findPersonWithPESEL("85091205707"));
        std::cout << foundPerson->toString();
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cin.get();
    
    try
    {
        std::cout << "===== Find persons with surname - Lis" << std::endl;                
        std::vector<std::shared_ptr<Person>> personsWithSurnames = db.findPersonWithSurname("Lis");
        for (auto person : personsWithSurnames)
        {
            std::cout << person->toString();
        }
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cin.get();

    try
    {
        std::cout << "===== Sort person by payment" << std::endl;
        db.sortByPayment();
        db.showDB();
        std::cin.get();

        std::cout << "===== Sort person by surname" << std::endl;
        db.sortBySurname();
        db.showDB();
        std::cin.get();

        std::cout << "===== Sort person by PESEL" << std::endl;
        db.sortByPESEL();
        db.showDB();
        std::cin.get();
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }

    try
    {
        std::cout << "===== Save to file and 2 x read database" << std::endl;
        db.saveToFile();
        db.readFromFile();
        db.readFromFile();
        db.showDB();
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cin.get();

    try
    {
        std::cout << "===== Change address and paymnet person with PESEL - 85091205707" << std::endl;
        db.changeAddressPaymentPersonWithPESEL("85091205707","Berlin",9000);
        db.showDB();
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }
    std::cin.get();

    try
    {
        std::cout << "===== Erase person with PESEL - 85091205707" << std::endl;
        db.removePersonWithPESEL("85091205707");
        db.showDB();
    }
    catch(const std::exception & exc)
    {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}
