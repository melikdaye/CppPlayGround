//
// Created by Administrator on 20.03.2023.
//

#include "abstractFactory.h"

void AbstractFactoryMethod::executeBasicSample() {
    AbstractFactory *pFactory = new ConcreteFactory2{};
    AbstractProductA  *pA = pFactory->createProductA();
    AbstractProductB  *pB = pFactory->createProductB();

    pA->productA();
    pB->productB();

    delete pA;
    delete pB;
}

void AbstractFactoryMethod::executeDatabaseSample() {


    DbFactory *dbFactory = new MySqlFactory{};
    Connection *pCon = dbFactory->createConnection();
    pCon->setConnectionString("uid=melik;db=movies;table=actors");
    pCon->open();

    Command *pCmd = dbFactory->createCommand();
    pCmd->setConnection(pCon);
    pCmd->setCommand("select * from actors");
    RecordSet *pRec = pCmd->executeQuery();
    while(pRec->hasNext()){
        std::cout << pRec->get() << std::endl;
    }
    delete pCmd;
    delete pCon;
    delete pRec;
}

void SqlCommand::executeCommand() {
    std::cout << "[SqlCommand] Executing command on" << connection->getConnectionString() << std::endl;
}

SqlRecordSet *SqlCommand::executeQuery() {
    std::cout << "[SqlCommand] Executing query " <<  std::endl;
    return new SqlRecordSet();
}

void SqlConnection::open() {
    std::cout << "[SqlConnection] Connection Opened" <<  std::endl;
}

SqlRecordSet::SqlRecordSet() {
    cursor = db.begin();
}

const std::string &SqlRecordSet::get() {
    return *cursor++;
}

bool SqlRecordSet::hasNext() {
    return cursor != db.end();
}


void MySqlConnection::open() {
    std::cout << "[MySqlConnection] Connection Opened" <<  std::endl;
}

void MySqlCommand::executeCommand() {
    std::cout << "[MySqlCommand] Executing command on" << connection->getConnectionString() << std::endl;
}

MySqlRecordSet *MySqlCommand::executeQuery() {
    std::cout << "[MySqlCommand] Executing query " <<  std::endl;
    return new MySqlRecordSet();
}

MySqlRecordSet::MySqlRecordSet() {
    cursor = db.begin();
}

const std::string &MySqlRecordSet::get() {
    return *cursor++;
}

bool MySqlRecordSet::hasNext() {
    return cursor != db.end();
}

Connection *SqlFactory::createConnection() {
    return new SqlConnection{};
}

Command *SqlFactory::createCommand() {
    return new SqlCommand{};
}

Connection *MySqlFactory::createConnection() {
    return new MySqlConnection{};
}

Command *MySqlFactory::createCommand() {
    return new MySqlCommand{};
}
