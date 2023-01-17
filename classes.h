//
// Created by melik on 17.12.2022.
//

#ifndef CPPPLAYGROUND_CLASSES_H
#define CPPPLAYGROUND_CLASSES_H
#include "iostream"

using namespace  std;

class Car {
    private:
        float fuel{0};
        float speed{0};
        int passengers{0};
        static int totalCount; //Cannot be init in class, cannot be accessed by this pointer, it is invoked directly thorugh the class name
    public:

        Car()  = default; // If parameterized constructor declared compiler does not synthesize default constructor so you have to request like this

        Car(const Car &) = delete;  // Prevent compiler synthesize copy constructor so copy is prevented


        /*
        *
        * Delegate constructor allows constructor to invoke another constructor
        * Replacement for common initialization
        * Reduces duplicate init code in multiple constructor
        *
        *
        */
        Car(float amount):Car(amount,0) {
            cout << "Car(float)" << endl;
        }

        Car(float amount , int pass){
            ++totalCount;
            fuel = amount;
            speed = 0;
            passengers = pass;
            cout << "Car(float,int)" << endl;
        }

        void FillFuel(float  amount){
            fuel += amount;
        }

        ~Car(){
            --totalCount;
            cout << "~Car()" << endl;
        }

        static void showCount(){
            cout << "Total cars: " << totalCount << endl;
        };

        void Dashboard() const{
            cout << "Fuel: " << fuel << endl;
            cout << "Speed: " << speed << endl;
            cout << "Passengers: " << passengers << endl;
        }
};

int Car::totalCount = 0;


class Integer{
    int *m_pInt;
public:
    Integer(){
        m_pInt = new int(0);
    };

    explicit Integer(int value){
        m_pInt = new int(value);
    };


    Integer(const Integer &obj){ //Always pass by reference dont pass by value because each time new copy of object is created and copy constructor stuck in  a loop
        m_pInt = new int (*obj.m_pInt);
    };

    int getValue() const{
        return *m_pInt;
    }

    void setValue(int value){
        *m_pInt = value;
    }

    void setValue(float value) = delete; //Prevent auto type conversion and init with float;

    ~Integer(){
        delete m_pInt;
    };

};


#endif //CPPPLAYGROUND_CLASSES_H
