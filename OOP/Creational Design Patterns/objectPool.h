//
// Created by Administrator on 9.03.2023.
//

#ifndef CPPPLAYGROUND_OBJECTPOOL_H
#define CPPPLAYGROUND_OBJECTPOOL_H

/*
 * Object pool is not official pattern
 * The main goal of this pattern is improving performance and memory use by reusing objects from a fixed pool instead of allocating and freeing them respectively
 * Object pool maintains an array or a list of shared object instances that created by object pool not the client
 * Objects constructed when on start,empty pool state or an existing shared object is not available
 * Pool can be grow automatically or fixed size
 * Object pool can be implemented as a singleton or monostate
 * To avoid tight coupling with concrete pooled objects , for creating objects factory method can be used
 *
 * */

#include <iostream>
#include <vector>
#include <thread>
#include <unordered_map>

class SharedObject{
    bool m_isUsed{true};
public:
    void methodA();
    void methodB();
    void reset();
    bool isUsed()const{return m_isUsed;};
    void setUsedState(bool state){m_isUsed = state;};
};

class ObjectPool{
    ObjectPool()=default;
    inline static std::vector<SharedObject*> pooledObjects{};
public:
    static SharedObject * acquireObject();
    static void releaseObject(SharedObject *p);
};


class Actor{
    bool m_isVisible{true};
public:
    void setVisibility(bool visible){
        m_isVisible = visible;
    };
    bool isVisible()const {
        return m_isVisible;
    }
    virtual void update() = 0;
    virtual ~Actor()=default;
};

class Missile:public Actor{
public:
    Missile();
    ~Missile();
    void update() override;
};


class Alien:public Actor{
public:
    Alien();
    ~Alien();
    void update() override;
};


using ActorPtr = std::shared_ptr<Actor>;
class ActorPool{
    inline static std::unordered_map<std::string,std::vector<ActorPtr>> actorPool{};
    ActorPool() = default;
    static ActorPtr internalCreate(const std::string &key);
    static ActorPtr findActor(const std::vector<ActorPtr> &actors);
public:
    static ActorPtr  acquireActor(const std::string &key);
    static void releaseActor(const std::string &key, const ActorPtr & actor);
};



namespace ObjectPoolMethod {

    void executeSample();

}


#endif //CPPPLAYGROUND_OBJECTPOOL_H
