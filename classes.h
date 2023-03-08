//
// Created by melik on 17.12.2022.
//

#ifndef CPPPLAYGROUND_CLASSES_H
#define CPPPLAYGROUND_CLASSES_H
#include "iostream"
#include <memory>

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
        cout <<  "Integer()" << endl;
    };

    Integer(int value){
        m_pInt = new int(value);
        cout <<  "Integer(int value)" << endl;
    };


    Integer(const Integer &obj){ //Always pass by reference dont pass by value because each time new copy of object is created and copy constructor stuck in  a loop
        m_pInt = new int (*obj.m_pInt);
        cout <<  "Integer(const Integer &obj)" << endl;
    };

    Integer(Integer &&obj){
        m_pInt = obj.m_pInt;
        obj.m_pInt = nullptr;
        cout <<  "Integer(Integer &&obj)" << endl;
    }

    Integer operator +(const Integer & a)const{
        Integer temp;
        *temp.m_pInt = *m_pInt + *a.m_pInt;
        return temp;
    }

    Integer & operator ++(){
        ++(*m_pInt);
        return *this;
    }

    Integer operator ++(int){
        Integer temp(*this);
        ++(*m_pInt);
        return temp;
    }

    bool  operator==(const Integer &a) const {
        return *m_pInt == *a.m_pInt;
    }

    Integer & operator=(const Integer &a){
        if(this != &a){
            delete m_pInt;
            m_pInt = new int(*a.m_pInt);
        }
        return *this;
    }

    Integer & operator=(Integer &&a){
        if(this != &a){
            delete m_pInt;
            m_pInt = a.m_pInt;
            a.m_pInt = nullptr;
        }
        return *this;
    }

    int getValue() const{
        return *m_pInt;
    }

    void setValue(int value){
        if(m_pInt == nullptr)
            m_pInt = new int{};
        *m_pInt = value;
    }

    void setValue(float value) = delete; //Prevent auto type conversion and init with float;

    ~Integer(){
        delete m_pInt;
        cout <<  "~Integer()" << endl;
    };

    operator int(){
        return *m_pInt;
    }

    friend class Printer; //friend keyword allows to function or class
};

class Printer{
    std::weak_ptr<int > m_pValue{};
    public:
        void setValue(std::weak_ptr<int> p){
            m_pValue = p;
        }
        void print(){
            cout << "Ref count:" << m_pValue.use_count() << endl;
            if(m_pValue.expired()){
                cout << "Resource is no longer available" << endl;
                return;
             }
            auto sp = m_pValue.lock();
            cout << "Value is: " << *sp << endl;
            cout << "Ref count:" << sp.use_count() << endl;
        }

};

class Product{
    Integer m_Id;
    std::string pName;
public:
    Product(const Integer &id):m_Id(id){
        cout << "Product(Const Integer &)" << endl;
    }

    template<typename T1,typename T2>
    Product(T1 && name, T2 && id):
        pName{std::forward<T1>(name)},
        m_Id{std::forward<T2>(id)}
    {

    }
    ~Product(){
        cout << "~" << endl;
    }
    const Integer & GetInteger()const{
        return  m_Id;
    }
    operator Integer(){
        return  m_Id;
    }
};

class Project {
    std::string m_Name;
    public:
        void setName(const std::string &name){
            m_Name = name;
        }
        void showProjectDetails(){
            cout << "Project Name" << m_Name.data() << endl;
        }
};

class Employee{
    std::shared_ptr<Project> m_project{};
    public:
        void setProject(std::shared_ptr<Project> &project){
            m_project = project;
        }
        const std::shared_ptr<Project> & getProject()const {
            return m_project;
        }

};


#endif //CPPPLAYGROUND_CLASSES_H
