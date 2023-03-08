cmake_minimum_required(VERSION 3.19)
project(CppPlayGround)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppPlayGround main.cpp OOP/Inheritance/Animal.h OOP/Polymorphism/Checking.cpp OOP/Polymorphism/Checking.h
        OOP/Polymorphism/Savings.cpp OOP/Polymorphism/Savings.h OOP/Polymorphism/Transaction.cpp OOP/Polymorphism/Transaction.h
        OOP/Polymorphism/Account.cpp OOP/Polymorphism/Account.h "OOP/Creational Design Patterns/singleton.h" "OOP/Creational Design Patterns/singleton.cpp")
