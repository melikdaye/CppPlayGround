//
// Created by Administrator on 20.03.2023.
//

#ifndef CPPPLAYGROUND_ABSTRACTFACTORY_H
#define CPPPLAYGROUND_ABSTRACTFACTORY_H
/*
 * An abstract factory defines the interface for creating different products(factory methods)
 * Factories are added for each context
 *
 * Pros
 * Promotes loose coupling
 * To support more configurations in future , you have to add the classes for a new set and corresponding factory class
 * It enforces consistency among products as the application can get instances of classes only from one set at a time
 *
 * Cons
 * Adding new products is difficult
 * Adding a new config causes class explosion
 * Entails modification of the abstract factory interface which in turn will force child classes to change
 *
 * When to use
 * Providing instances to client without exposing concrete classes
 * Configure system with one of multiple product configurations
 * Ensure that system use classes only from one family at a time
 *
 * */
#include "iostream"
#include "vector"

class AbstractProductA{
public:
    virtual void productA() = 0;
    virtual ~AbstractProductA() = default;
};

class AbstractProductB{
public:
    virtual void productB() = 0;
    virtual ~AbstractProductB() = default;
};

class ProductA1: public AbstractProductA{
public:
    void productA() override {
        std::cout << "[1] Product A" << std::endl;
    }
};

class ProductB1: public AbstractProductB{
public:
    void productB() override {
        std::cout << "[1] Product B" << std::endl;
    }
};

class ProductA2: public AbstractProductA{
public:
    void productA() override {
        std::cout << "[2] Product A" << std::endl;
    }
};

class ProductB2: public AbstractProductB{
public:
    void productB() override {
        std::cout << "[2] Product B" << std::endl;
    }
};

class AbstractFactory{
public:
    virtual AbstractProductA * createProductA() = 0;
    virtual AbstractProductB * createProductB() = 0;
    virtual ~AbstractFactory() = default;
};

class ConcreteFactory1 : public AbstractFactory{
    public:
    AbstractProductA * createProductA() override{
        return new ProductA1{};
    }
    AbstractProductB * createProductB() override{
        return  new ProductB1{};
    }
};

class ConcreteFactory2 : public AbstractFactory{
public:
    AbstractProductA * createProductA() override{
        return new ProductA2{};
    }
    AbstractProductB * createProductB() override{
        return  new ProductB2{};
    }
};

class Connection{
    std::string  connectionString;
public:
    void setConnectionString(const std::string &connStr){
        connectionString = connStr;
    }
    const std::string & getConnectionString()const{
        return  connectionString;
    }
    virtual void open() = 0;
    virtual ~Connection() = default;
};

class RecordSet{
public:
    virtual const std::string  & get() = 0;
    virtual bool hasNext() = 0;
    virtual ~RecordSet() = default;
};

class Command{
    std::string commandString;
protected:
    Connection * connection;
public:
    Connection * getConnection()const{
        return  connection;
    }
    const std::string & getCommandString()const{
        return  commandString;
    }
    void setCommand(const std::string & commandStr){
        commandString = commandStr;
    }
    void setConnection(Connection * pConn){
        connection = pConn;
    }

    virtual void executeCommand() = 0;
    virtual RecordSet * executeQuery() = 0;
    virtual ~Command() = default;
};

class SqlRecordSet:public RecordSet{
    const std::vector<std::string> db{
            "Terminator",
            "Predator",
            "Eraser",
            "Expendables",
            "The 6th Day",
            "End of Days"
    };
    std::vector<std::string>::const_iterator cursor;
public:
    SqlRecordSet();
    const std::string &get() override;
    bool hasNext() override;
};

class SqlCommand:public Command{
public:
    void executeCommand() override;
    SqlRecordSet *executeQuery() override;
};

class SqlConnection:public Connection{
public:
    void open() override;
};

class MySqlRecordSet:public RecordSet{
    const std::vector<std::string> db{
            "Escape Plan",
            "Rambo",
            "Demo Day",
            "Judge Dredd",
            "Demolition Man",
            "Cobra"
    };
    std::vector<std::string>::const_iterator cursor;
public:
    MySqlRecordSet();
    const std::string &get() override;
    bool hasNext() override;
};

class MySqlCommand:public Command{
public:
    void executeCommand() override;
    MySqlRecordSet *executeQuery() override;
};

class MySqlConnection:public Connection{
public:
    void open() override;
};

class DbFactory{
public:
    virtual Connection * createConnection() = 0;
    virtual Command * createCommand() = 0;
    virtual ~DbFactory()=default;
};

class SqlFactory:public DbFactory{
public:
    Connection *createConnection() override;

    Command *createCommand() override;
};

class MySqlFactory:public DbFactory{
public:
    Connection *createConnection() override;

    Command *createCommand() override;
};







namespace AbstractFactoryMethod {

    void executeBasicSample();
    void executeDatabaseSample();

}

#endif //CPPPLAYGROUND_ABSTRACTFACTORY_H
