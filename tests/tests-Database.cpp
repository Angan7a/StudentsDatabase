#include "catch.hpp"
#include "../inc/Database.hpp"
#include "../inc/Student.hpp"
#include "../inc/Worker.hpp"
    
SCENARIO("Find person by PESEL") {
    GIVEN("A empty database") {
        Database db;
        REQUIRE_THROWS_WITH(db.showDB(),"Database is empty");
        WHEN("Find person with wrong PESEL - 123 - in empty database") {
            THEN("Expect throw - bad PESEL")
            REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("123")),"Bad PESEL");
        }
        WHEN("Fill the database random data 5 students and 8 workers and finding person with PESEL - 66040170503 - not in the database") {
            db.fillDB(5, 8);
            THEN("Expect throw - There is no person with PESEL - 66040170503 in the database") 
                REQUIRE_THROWS_WITH(*(db.findPersonWithPESEL("66040170503")),"There is no person with PESEL - 66040170503 in the database");
        }
        WHEN("Added person to database and find this person in database") {
            std::shared_ptr<Person> student = std::make_shared<Student>("Katarzyna", "Nowak", "66040170503", 'W', "Wroclaw, Staszica 12", 99789);
            db.addPerson(student);
            THEN("Expect succes") {
                REQUIRE(*(db.findPersonWithPESEL("66040170503")) == student);
            }
        }
    }
}
