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

/*
 * Pros
 * Reduces coupling with concrete classes
 * Behaves like operator new , but is more flexible
 * Caching existing instances improves performance of the application
 * Reduces the overhead of heap allocation & deallocation
 * Reduces heap fragmentation
 *
 * Cons
 * Memory may be wasted on unused pooled objects
 * Pooled objects may remain in memory until the end of the program
 * Objects that are acquired from the pool must be reset prior to their use
 * ObjectPool class may get tightly coupled with the concrete classes
 *
 * When to use
 * When frequently create & destroy objects
 * Objects are expensive to create
 *
 *
 * */

#include <iostream>
#include <vector>
#include <thread>
#include <unordered_map>
#include <functional>

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
using Creator = std::function<ActorPtr()>;
class ActorPool{

    struct ActorInfo {
        std::vector<ActorPtr> actors{};
        Creator creator;
    };

    inline static std::unordered_map<std::string,ActorInfo> actorPool{};
    ActorPool() = default;
    static ActorPtr internalCreate(const std::string &key);
    static ActorPtr findActor(const std::vector<ActorPtr> &actors);
public:
    static void registerCreator(const std::string &key,Creator creator);
    static ActorPtr  acquireActor(const std::string &key);
    static void releaseActor(const std::string &key, const ActorPtr & actor);
};


template<typename T>
class DefaultAllocator{
public:
    T *operator()(){
        return new T{};
    }
    void operator()(T *p){
        delete p;
    }
    void reset(){

    }
};


template<typename T,size_t maxSize=std::numeric_limits<size_t>::max(),typename AllocatorT=DefaultAllocator<T>>
class ObjectPoolT{
    struct ObjectInfo{
        bool isUsed{};
        T *object{};
    };
    inline static std::vector<ObjectInfo> pooledObjects{};
    inline static AllocatorT allocator{};
public:
    [[nodiscard]] //If returned value will not be stored warning is raised by compiler
    static T * acquire(){
        for(auto &obj:pooledObjects){
            if(!obj.isUsed){
                obj.isUsed = true;
                std::cout << "[POOL] Returning an existing object" << std::endl;
                return obj.object;
            }
        }
        if(pooledObjects.size() == maxSize){
            std::cout << "[POOL] Pool is reached to the max size" << std::endl;
            return nullptr;
        }
        std::cout << "[POOL] Creating a new object" << std::endl;
        auto pObj = allocator();
        pooledObjects.push_back({true,pObj});
        return pObj;
    }
    static void release(const T *pObj){
        for(auto &obj:pooledObjects){
            if(obj.object == pObj){
                obj.isUsed = false;
                break;
            }
        }
    }
    static void destroy(){
        for(auto &obj: pooledObjects){
            if(obj.isUsed){
                std::cout << "WARNING Deleting an object still in use" << std::endl;
            }
            allocator(obj.object);
        }
        allocator.reset();
        pooledObjects.clear();
    }

};

class Test{
    Test(){

    }

public:
    void Foo(){

    }
    friend class TestAllocator;
};

class TestAllocator{
public:
    Test *operator()(){
        return new Test{};
    }
    void operator()(Test *p){
        delete p;
    }
    void reset(){

    }
};

namespace ObjectPoolMethod {

    void executeSample();

}


#endif //CPPPLAYGROUND_OBJECTPOOL_H
