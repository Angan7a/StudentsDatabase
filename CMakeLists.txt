cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(db.out)

set(SRC_LIST
    Database.cpp
    Database.hpp
    Person.cpp
    Person.hpp
    PeselValidation.cpp
    PeselValidation.hpp
    Student.cpp
    Student.hpp
    Worker.cpp
    Worker.hpp
)

add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} main.cpp)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

set(TEST_SRC_LIST
    test/old-tests.cpp
    test/tests-Database.cpp
    test/tests-main.cpp
)

add_executable(${PROJECT_NAME}-ut-catch ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}-ut-catch ${PROJECT_NAME}-lib)
