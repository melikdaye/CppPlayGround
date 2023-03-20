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

std::vector<std::shared_ptr<Missile>> missiles{};
void fire(){
    missiles.push_back(ActorPool::acquireMissile());
    missiles.push_back(ActorPool::acquireMissile());
}
void animate(){
    for(auto &m: missiles){
        m->update();
    }
}
void explode(){
    std::cout << "X" << std::endl;
    for(auto &m: missiles){
        m->setVisible(false);
    }
    missiles.clear();
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

    int counter{};
    while (true){
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
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
}

ActorPtr  ActorPool::acquireActor(const std::string &key) {
    ActorPtr actor{};
    if(auto it = actorPool.find(key); it == end(actorPool)){
            actor = internalCreate(key);
            actorPool[key].push_back(actor);
            return actor;
    }
    auto actors = actorPool[key];

    for(auto &missile : missiles){
        if(!missile->isVisible()){
            missile->setVisible(true);
            std::cout << "[POOL] Returning an existing instance" << std::endl;
            return missile;
        }
    }
    std::cout << "[POOL] Creating a new instance" << std::endl;
    auto missile = std::make_shared<Missile>();
    missiles.push_back(missile);
    return missile;
}

void ActorPool::releaseActor(const std::string &key, const ActorPtr & actor) {
    for(auto &missile : missiles){
        if(missile == r_actor){
            missile->setVisible(false);
            std::cout << "[POOL] Releasing an existing instance" << std::endl;
        }
    }
}

std::shared_ptr <Actor> ActorPool::internalCreate(const std::string &key) {
    std::cout << "[POOL] Creating new actor of type: " << key << std::endl;
    if(key == "missile"){
        return std::make_shared<Missile>();
    }
    else if(key == "alien"){
        return std::make_shared<Alien>();
    }
    return nullptr;
}

std::shared_ptr <Actor> ActorPool::findActor(const std::vector <ActorPtr> &actors) {
    auto itActor = std::find_if(begin(actors),end(actors),[](const auto &actor){
        return !actor.isVisible();
    })
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
