//
// Created by Administrator on 9.03.2023.
//

#include "objectPool.h"

void SharedObject::methodA() {
    std::cout << __FUNCSIG__ << std::endl;
}

void SharedObject::methodB() {
    std::cout << __FUNCSIG__ << std::endl;
}

void SharedObject::reset() {
    std::cout << __FUNCSIG__ << std::endl;
}

SharedObject *ObjectPool::acquireObject() {
    for(auto& o : pooledObjects){
        if(!o->isUsed()){
            std::cout << "[POOL] Returning an existing object" << std::endl;
            o->setUsedState(true);
            o->reset();
            return o;
        }
    }
    std::cout << "[POOL] Creating a new object" << std::endl;
    SharedObject *o = new SharedObject{};
    pooledObjects.push_back(o);
    return o;
}

void ObjectPool::releaseObject(SharedObject *p) {
    for(auto& o : pooledObjects){
        if(o == p){
            o->setUsedState(false);
        }
    }
}


Missile::Missile() {
    std::cout << "Missile Created" << std::endl;
}

Missile::~Missile() {
    std::cout << "Missile Destroyed" << std::endl;
}

void Missile::update() {
    std::cout << "->" ;
}

std::vector<ActorPtr> actors{};
void fire(){
    actors.push_back(ActorPool::acquireActor("missile"));
    actors.push_back(ActorPool::acquireActor("alien"));
}
void animate(){
    for(auto &m: actors){
        m->update();
    }
}
void explode(){
    std::cout << "X" << std::endl;
    for(auto &m: actors){
        m->setVisibility(false);
    }
    actors.clear();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

void ObjectPoolMethod::executeSample(){
    auto s1 = ObjectPool::acquireObject();
    s1->methodA();
    s1->methodB();

    auto s2 = ObjectPool::acquireObject();
    s2->methodA();
    s2->methodB();

    ObjectPool::releaseObject(s1);
    auto s3 = ObjectPool::acquireObject();
    s3->methodA();
    s3->methodB();

    ActorPool::registerCreator("missile",[](){
       return std::make_shared<Missile>();
    });
    ActorPool::registerCreator("alien",[](){
        return std::make_shared<Alien>();
    });


    int loop{2};
    int counter{};
    while (loop != 0){
        ++counter;
        if(counter == 1){
            fire();
        }
        if(counter >=1 && counter <=5){
            animate();
        }
        if(counter > 5){
            explode();
            counter = 0;
            --loop;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }

//    using IntPool = ObjectPoolT<int>;
//    auto p1 = IntPool::acquire();
//    auto p2 = IntPool::acquire();
//    auto p3 = IntPool::acquire();
//
//    IntPool::release(p1);
//    auto p4 = IntPool::acquire();
//    IntPool::destroy();

    using TestPool = ObjectPoolT<Test,2,TestAllocator>;
    auto p1 = TestPool::acquire();
    auto p2 = TestPool::acquire();
    auto p3 = TestPool::acquire();

    TestPool::release(p1);
    auto p4 = TestPool::acquire();
    TestPool::destroy();

}

ActorPtr  ActorPool::acquireActor(const std::string &key) {
    ActorPtr actor{};
    if(auto it = actorPool.find(key); it == end(actorPool)){
            return internalCreate(key);
    }
    auto s_actors = actorPool[key].actors;
    actor = findActor(s_actors);
    if(!actor){
        actor = internalCreate(key);
    }
    else{
        std::cout << "[POOL] Returning existing actor of type : " << key << std::endl;
    }
    return  actor;
}

void ActorPool::releaseActor(const std::string &key, const ActorPtr & actor) {
    if(auto it = actorPool.find(key); it == end(actorPool)){
        throw std::runtime_error("Unknown key");
    }
    auto s_actors = actorPool[key].actors;
    for(auto &a:s_actors){
        a->setVisibility(false);
        break;
    }

}

std::shared_ptr <Actor> ActorPool::internalCreate(const std::string &key) {
    ActorPtr actor{};
    if(!actorPool[key].creator){
        std::cout << "Creator not registered" << std::endl;
        return actor;
    }
    actor = actorPool[key].creator();
    actorPool[key].actors.push_back(actor);
    std::cout << "[POOL] Creating new actor of type: " << key << std::endl;
    return actor;
}

ActorPtr ActorPool::findActor(const std::vector <ActorPtr> &actors) {
    auto itActor = std::find_if(begin(actors),end(actors),[](const auto &actor){
        return !static_cast<ActorPtr>(actor)->isVisible();
    });
    if(itActor != end(actors)){
        (*itActor)->setVisibility(true);
        return *itActor;
    }
    return nullptr;
}

void ActorPool::registerCreator(const std::string &key, Creator creator) {
        actorPool[key].creator = creator;
}

Alien::Alien() {
    std::cout << "Alien Created" << std::endl;
}

Alien::~Alien() {
    std::cout << "Alien Destroyed" << std::endl;
}

void Alien::update() {
    std::cout << "@" ;
}
