//
// Created by Administrator on 8.03.2023.
//

#ifndef CPPPLAYGROUND_SINGLETON_H
#define CPPPLAYGROUND_SINGLETON_H

#include <cstdio>
#include <string>
#include <memory>
#include <mutex>

/*
 * Ensure a class only has one instance, and provide a global point of access to it
 * The class is made responsible for its own instance
 * It intercepts the call for construction and returns a single instance
 * Direct construction of object is disabled
 *
 * */

class Singleton{
    Singleton()=default;
    static Singleton p_instance;
public:

    static Singleton & instance();
    void methodA();
    void methodB();
};



class Logger{
    FILE * stream;
    std::string tag;
    Logger();
    static Logger pInstance; //Eager instance
public:
    static Logger & instance();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger & operator=(const Logger &) = delete;
    void writeLog(const char * message);
    void setTag(const char *tag);
};


//Lazy Instantiation with thread-safe init
class LoggerLazy{
    FILE * stream;
    std::string tag;
    LoggerLazy();
//    struct Deleter{
//        void operator()(Logger *p){
//            delete p;
//        }
//    };
    static LoggerLazy *pInstance; //Lazy instance
    static std::mutex pMutex;
//    inline static std::unique_ptr<LoggerLazy,Deleter> pInstance{};
public:
    static LoggerLazy & instance();
    static LoggerLazy & instanceMeyer();
    static LoggerLazy & instanceCallOnce();
    ~LoggerLazy();
    LoggerLazy(const Logger &) = delete;
    LoggerLazy & operator=(const Logger &) = delete;
    void writeLog(const char * message);
    void setTag(const char *tag);
};

///CRTP IDIOM
template<typename T>
class BaseSingleton{
protected:
    BaseSingleton() = default;
    BaseSingleton(const BaseSingleton &)=delete;
    BaseSingleton & operator=(const BaseSingleton &)=delete;

public:
    static T & instance(){
        static T pInstance;
        return pInstance;
    }
};

class GameManager : public BaseSingleton<GameManager>{
private:
    GameManager() = default;
    friend class BaseSingleton<GameManager>;

public:
    void loadAssets(){

    }
    void run(){

    }
};


void basicExample();
void loggerExample();




#endif //CPPPLAYGROUND_SINGLETON_H
