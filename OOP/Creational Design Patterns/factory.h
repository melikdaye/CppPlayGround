//
// Created by Administrator on 9.03.2023.
//

#ifndef CPPPLAYGROUND_FACTORY_H
#define CPPPLAYGROUND_FACTORY_H

#include <iostream>


/*
 * Factory method create new type of instances that inherit from base class without break open close and dependency inversion principle
 * The creation process of inherited classes depends on virtual factory classes rather than concrete class instances
 *
 * ---- PROS ----
 * Instances can be created at run time
 * Promotes loose coupling
 * Construction becomes simpler due to abstraction
 * Construction process is encapsulated
 * May not return a new instance every time
 *
 * ---- CONS ----
 * Every new product class may require a corresponding factory class but it can be avoided with parameterised factory method
 *
 * --- WHEN TO USE ---
 *
 * A class does not know which instance it needs at runtime
 * A class does not want to depend on the concrete classes that it uses
 * You want to encapsulate the creation process
 * Clients implement the classes that you use - you need to create instances of such classes
 *
 * */

class Document{
public:
    virtual void write()=0;
    virtual void read()=0;
};

class TextDocument : public Document{
public:
    void write() override;
    void read() override;
};

class SpreadSheetDocument:public Document{
public:
    void write() override;

    void read() override;

};

using DocumentPtr = std::unique_ptr<Document>;
class Application{
    DocumentPtr pDocument;
public:
    void create();
    void open();
    void save();
    virtual DocumentPtr createDoc(){return nullptr;};
};

class TextApplication:public Application{
public:
    DocumentPtr createDoc() override;
};

class SpreadSheetApplication:public Application{
public:
    DocumentPtr createDoc() override;
};

namespace Factory{
    void executeSample();
}


#endif //CPPPLAYGROUND_FACTORY_H
