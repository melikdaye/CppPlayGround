//
// Created by Administrator on 7.03.2023.
//

#ifndef CPPPLAYGROUND_ANIMAL_H
#define CPPPLAYGROUND_ANIMAL_H

#include <iostream>
using namespace std;
class Animal {
public:
    void eat(){
        cout << "Animal Eating" << endl;
    }
    void run(){
        cout << "Animal Run" << endl;
    }
    void speak(){
        cout << "Animal Speak" << endl;
    }
};

class Dog : public Animal {
public:
    using Animal::Animal; //C++11 Inheriting constructors
    void eat(){
        cout << "Dog eating meat" << endl;
    }
    void speak(){
        cout << "Dog Barking" << endl;
    }
};



#endif //CPPPLAYGROUND_ANIMAL_H
