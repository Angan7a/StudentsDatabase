cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(db.out)

set(SRC_LIST
    src/Database.cpp
    inc/Database.hpp
    src/Person.cpp
    inc/Person.hpp
    src/PeselValidation.cpp
    inc/PeselValidation.hpp
    src/Student.cpp
    inc/Student.hpp
    src/Worker.cpp
    inc/Worker.hpp
)

add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} src/main.cpp)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
endif (UNIX)

set(TEST_SRC_LIST
    tests/old-tests.cpp
    tests/tests-Database.cpp
    tests/tests-main.cpp
)

add_executable(${PROJECT_NAME}-ut-catch ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}-ut-catch ${PROJECT_NAME}-lib)
