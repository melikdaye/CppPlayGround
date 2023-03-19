//
// Created by Administrator on 8.03.2023.
//

#include "singleton.h"

Singleton Singleton::p_instance;
Singleton & Singleton::instance(){
    return p_instance;
}
void Singleton::methodA(){

}
void Singleton::methodB(){

}


Logger Logger::pInstance;
Logger::Logger(){
    stream = fopen("log.txt","w");
}
Logger & Logger::instance() {
    return pInstance;
}

Logger::~Logger(){
        fclose(stream);
}
void Logger::writeLog(const char * message){
    fprintf(stream,"[%s] %s\n",tag.c_str(),message);
    fflush(stream);
}
void Logger::setTag(const char *tag){
    tag = tag;
}


LoggerLazy *LoggerLazy::pInstance;
std::mutex LoggerLazy::pMutex;
LoggerLazy::LoggerLazy(){
    stream = fopen("log.txt","w");
    atexit([](){
        delete pInstance;
    });
}
LoggerLazy & LoggerLazy::instance() {
    //Double-checked locking pattern
    if(pInstance == nullptr) {
        pMutex.lock();
        if (pInstance == nullptr) {
            //pInstance = new LoggerLazy{}; The generated instructions for this statement can be randomly ordered by compiler and it becomes non thread-safe
            void *p = operator new(sizeof(LoggerLazy));
            new(p)LoggerLazy();
            pInstance = static_cast<LoggerLazy *>(p);
        }
        pMutex.unlock();
    }
    return *pInstance;
}

//Meyer's Singleton, it returns instance that does not allocated on heap and its lifetime bound to program life and it is thread safe
LoggerLazy & LoggerLazy::instanceMeyer() {

    static LoggerLazy instance;
    return instance;
}

//init singleton with thread safe manner with std::call_once
std::once_flag flag;
LoggerLazy &LoggerLazy::instanceCallOnce() {
    std::call_once(flag,[](int){
        pInstance = new LoggerLazy{};
    },5);
    return *pInstance;
    //InitOnceExecuteOnce - Win32
    //pthread_once - Linux (POSIX)
}

LoggerLazy::~LoggerLazy(){
    fclose(stream);
}
void LoggerLazy::writeLog(const char * message){
    fprintf(stream,"[%s] %s\n",tag.c_str(),message);
    fflush(stream);
}
void LoggerLazy::setTag(const char *tag){
    tag = tag;
}




void basicExample(){
    Singleton &s = Singleton::instance();
    s.methodA();
    //Singleton s2; Default constructor is private so it cannot be compiled
}

void openConnection(){
    Logger &lg = Logger::instance();
    lg.writeLog("Open a connection");

    LoggerLazy &lgLazy = LoggerLazy::instance();
    lgLazy.writeLog("Open a connection");
}

void loggerExample(){
    Logger &logger = Logger::instance();
    //Logger logger = Logger::instance(); Use copy constructor it performs shallow copy and end of copy object is destroyed so connection is closed,deleting copy constructor is a solution
    logger.setTag("DEBUG");
    logger.writeLog("Application is started");
    openConnection();
    logger.writeLog("Application is shutting down");


    //Lazy instantiation
    LoggerLazy &loggerLazy = LoggerLazy::instance();
    loggerLazy.setTag("DEBUG");
    loggerLazy.writeLog("Application is started");
    openConnection();
    loggerLazy.writeLog("Application is shutting down");

    //Meyer's Instantiation
    LoggerLazy &meyerLog = LoggerLazy::instanceMeyer();


}