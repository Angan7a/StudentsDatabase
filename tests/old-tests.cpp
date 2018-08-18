#include "../inc/Database.hpp"
#include "../inc/Student.hpp"
#include "../inc/Worker.hpp"
#include "../inc/PeselValidation.hpp"
#include <iostream>
#include "catch.hpp"


TEST_CASE("Testing find person")
{
    SECTION("Finding person by PESEL")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Finding person with wrong PESEL - 123 - in empty database")
            {
                REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("123")),"Bad PESEL");
            }
            WHEN("Finding person with wrong PESEL - 12345678901 - in empty database")
            {
                REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("12345678901")),"Bad PESEL");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Finding person with PESEL - 123 - no in the database")
                {
                    REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("123")),"Bad PESEL");
                }
                WHEN("Added person to database")
                {
                    std::shared_ptr<Person> student = std::make_shared<Student>("Katarzyna", "Nowak", "66040170503", 'W', "Wroclaw, Staszica 12", 99789);
                    db.addPerson(student);
                    THEN("Finding person with PESEL - 66040170503 - existe in the database")
                    {
                        REQUIRE(*(db.findPersonWithPESEL("66040170503")) == student);
                    }
                }
            }
        }
    }
    SECTION("Finding person by surname")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Finding person with surname - Kot - in empty database")
            {
                REQUIRE_THROWS_WITH(db.findPersonWithSurname("Kot"),"Database is empty!");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                std::shared_ptr<Person> worker = std::make_shared<Worker>("Katarzyna", "Lis", "44121786205", 'W', "Wroclaw, Staszica 12", 99789);
                db.addPerson(worker);
                THEN("Finding person with surname - Kot - no in the database")
                {
                    REQUIRE_THROWS_WITH(db.findPersonWithSurname("Kot"),"There isn't person with surname Kot");
                }
                THEN("Finding persons with surname - Lis  - existe in the database")
                {
                    std::vector<std::shared_ptr<Person>> personsWithSurnames = db.findPersonWithSurname("Lis");
                    for (auto person : personsWithSurnames)
                    {
                        REQUIRE(person->getSurname() == "Lis");
                    }
                }
            }
        }
    }
}

TEST_CASE("Testing sort")
{
    SECTION("Sorting persons by PESEL")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Sorting persons by PESEL in empty database")
            {
                REQUIRE_THROWS_WITH(db.sortByPESEL(), "Database is empty!");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Sort person by PESEL in database")
                {
                    db.sortByPESEL();
                    std::vector<std::shared_ptr<Person>>::iterator iter = db.getFirstIterOfPerson();
                    for (int i = 0; i < db.getNumberOfPersons()-1; i++)
                    {
                        REQUIRE((*iter)->getPESEL() < (*(iter+1))->getPESEL());
                        iter++;
                    }
                }
            }
        }
    }
    SECTION("Sorting persons by surname")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Sorting persons by surname in empty database")
            {
                REQUIRE_THROWS_WITH(db.sortBySurname(), "Database is empty!");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Sort person by surname in database")
                {
                    db.sortBySurname();
                    std::vector<std::shared_ptr<Person>>::iterator iter = db.getFirstIterOfPerson();
                    for (int i = 0; i < db.getNumberOfPersons()-1; i++)
                    {
                        REQUIRE((*iter)->getSurname() <= (*(iter+1))->getSurname());
                        iter++;
                    }
                }
            }
        }
    }
    SECTION("Sorting persons by payment")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Sorting persons by payment in empty database")
            {
                REQUIRE_THROWS_WITH(db.sortByPayment(), "Database is empty!");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Sort person by payment in database")
                {
                    db.sortByPayment();
                    std::vector<std::shared_ptr<Person>>::iterator iter = db.getFirstIterOfPerson();
                    for (int i = 0; i < db.getNumberOfPersons()-1; i++)
                    {
                        REQUIRE((*iter)->getPayment() <= (*(iter+1))->getPayment());
                        iter++;
                    }
                }
            }
        }
    }
}

TEST_CASE("Testing check PESEL")
{
    SECTION("Test bad PESEL")
    {
        GIVEN("A empty PESEL")
        {
            std::string PESEL;
            THEN("Check PESEL")
                REQUIRE(Person::checkPESEL(PESEL) == false);
            WHEN("PESEL is 00000000000")
            {
                PESEL = "00000000000";
                THEN("Check PESEL")
                    REQUIRE(Person::checkPESEL(PESEL) == false);
            }
            WHEN("PESEL is 12345678901")
            {
                PESEL = "12345678901";
                THEN("Check PESEL")
                    REQUIRE(Person::checkPESEL(PESEL) == false);
            }
            WHEN("PESEL is 123456789032")
            {
                PESEL = "123456789032";
                THEN("Check PESEL")
                    REQUIRE(Person::checkPESEL(PESEL) == false);
            }
        }
    }
    SECTION("Test correct PESEL")
    {
        WHEN("PESEL is 89121782400")
        {
            std::string PESEL = "89121782400";
            THEN("Check PESEL")
                REQUIRE(Person::checkPESEL(PESEL) == true);
        }
    }
}

TEST_CASE("Testing erase person with PESEL")
{
    SECTION("Erase person by PESEL")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Erase person with wrong PESEL - 123 - in empty database")
            {
                REQUIRE_THROWS_WITH(db.removePersonWithPESEL("123"),"Bad PESEL");
            }
            WHEN("Erase person with wrong PESEL - 12345678901 - in empty database")
            {
                REQUIRE_THROWS_WITH(db.removePersonWithPESEL("12345678901"),"Bad PESEL");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Erase person with PESEL - 123 - no in the database")
                {
                    REQUIRE_THROWS_WITH(db.removePersonWithPESEL("123"),"Bad PESEL");
                }
                WHEN("Added person to database")
                {
                    std::shared_ptr<Person> student = std::make_shared<Student>("Katarzyna", "Nowak", "89121782400", 'W', "Wroclaw, Staszica 12", 99789);
                    db.addPerson(student);
                    THEN("Erase person with PESEL - 8912178243400 - existe in the database")
                    {
                        db.removePersonWithPESEL("89121782400");
                        REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("89121782400")), "There is no person with PESEL - 89121782400 in the database");
                    }
                }
            }
        }
    }
}

TEST_CASE("Testing save and read file")
{
    SECTION("Save amd read file")
    {
        GIVEN("A empty database")
        {
            Database db;
            WHEN("Save empty database")
            {
                REQUIRE_THROWS_WITH(db.saveToFile(),"Database is empty");
            }
            GIVEN("Fill the database random data 15 students and 18 workers")
            {
                db.fillDB(5, 8);
                THEN("Save database to file")
                {
                    db.saveToFile();
                    REQUIRE_THROWS_WITH(db.showDB(),"Database is empty");
                }
                THEN("Read from file")
                {
                    REQUIRE_NOTHROW(db.readFromFile());
                }
            }
        }
    }
}



TEST_CASE("Change address and payment by PESEL")
{
    SECTION("Change address and payment worker")
    {
        GIVEN("A no empty database")
        {
            Database db;
            db.fillDB(5, 8);
            WHEN("Added worker to database")
            {
                std::shared_ptr<Person> worker = std::make_shared<Worker>("Katarzyna", "Nowak", "43061710615", 'W', "Wroclaw, Staszica 12", 3000);
                db.addPerson(worker);
                THEN("Change address and payment person with PESEL - 43061710615")
                {
                    db.changeAddressPaymentPersonWithPESEL("43061710615", "Londyn", 8000);
                    REQUIRE((*db.findPersonWithPESEL("43061710615"))->getAddress() == "Londyn");
                    REQUIRE((*db.findPersonWithPESEL("43061710615"))->getPayment() == 8000);
                }
            }
        }
    }
    SECTION("Change address and payment student")
    {
        GIVEN("A no empty database")
        {
            Database db;
            db.fillDB(5, 8);
            WHEN("Added student to database")
            {
                std::shared_ptr<Person> student = std::make_shared<Student>("Katarzyna", "Nowak", "49061785514", 'W', "Wroclaw, Staszica 12", 3000);
                db.addPerson(student);
                THEN("Change address and payment person with PESEL - 49061785514")
                {
                    REQUIRE_THROWS(db.changeAddressPaymentPersonWithPESEL("49061785514", "Londyn", 8000));
                }
            }
        }
    }
}
