//
// Created by Administrator on 22.03.2023.
//

#ifndef CPPPLAYGROUND_PROTOTYPE_H
#define CPPPLAYGROUND_PROTOTYPE_H

#include <unordered_map>
#include "iostream"
#include "random"
class Prototype{
public:
    virtual Prototype * clone() = 0;
    virtual ~Prototype() = default;
};

class ConcreteProtoType1:public Prototype{
public:
    Prototype *clone() override;
};

class ConcreteProtoType2:public Prototype{
public:
    Prototype *clone() override;
};

class Client{
    Prototype *prototype;
public:
    void setPrototype(Prototype *p){
        prototype = p;
    }
    void operation(){
        auto p = prototype->clone();
    }
};

class Animation{
    std::string  animationData{};
public:
    Animation()=default;
    Animation(std::string_view animFile);
    const std::string & getAnimationData()const{
        return animationData;
    }
    void setAnimationData(const std::string &animData){
        animationData = animData;
    }
};

struct Position{
    int x;
    int y;
    friend std::ostream  &operator<<(std::ostream &out,Position p){
        return out << "(" << p.x << "," << p.y << ")" << std::endl;
    }
};
class Vehicle;
using VehiclePtr = std::shared_ptr<Vehicle>;
class Vehicle{
    int speed{};
    int hitPoints{};
    std::string name{};
    Animation * animation{};
    Position position{};
    std::string color{};
public:
    Vehicle();
    Vehicle(int speed, int hitPoints, const std::string &name,  std::string_view  animFile, const Position &position,const std::string &color);

    virtual ~Vehicle();

    Vehicle(const Vehicle &other);
    Vehicle & operator=(const Vehicle &other);

    Vehicle(Vehicle &&other)noexcept;
    Vehicle &operator=(Vehicle &&other)noexcept;

    int getSpeed() const;

    int getHitPoints() const;

    const std::string &getName() const;

    const Position &getPosition() const;

    const std::string & getAnimation()const;

    void setSpeed(int speed);

    void setHitPoints(int hitPoints);

    void setName(const std::string &name);

    void setAnimationData(const std::string &animData);

    void setPosition(const Position &position);

    const std::string &getColor() const;

    void setColor(const std::string &color);

    virtual void update() = 0;
    virtual VehiclePtr clone() = 0;
};


class Car: public Vehicle{
    using Vehicle::Vehicle;
    float speedFactor{1.5};
    std::default_random_engine engine{100};
    std::bernoulli_distribution dist{.5};
public:
    void setSpeedFactor(float factor){
        speedFactor = factor;
    }
    void update() override;
    VehiclePtr clone() override;
};



class Bus: public Vehicle{
    using Vehicle::Vehicle;
    std::default_random_engine engine{500};
    std::bernoulli_distribution dist{.5};
public:
    void update() override;
    VehiclePtr clone() override;
};

Vehicle * create(std::string_view type,int speed, int hitPoints, const std::string &name,  std::string_view  animFile, const Position &position);

class GameManagerProto{
    std::vector<VehiclePtr> vehicles{};
public:
    void run();
};


class VehiclePrototypes{
    inline static std::unordered_map<std::string , VehiclePtr> prototypes{};
    VehiclePrototypes()=default;
public:
    static std::vector<std::string> getKeys();
    static void registerPrototype(const std::string &key,VehiclePtr prototype);
    static VehiclePtr deregisterPrototype(const std::string &key);
    static VehiclePtr getPrototype(const std::string & key);
};

namespace PrototypeMethod{
    void executeBasicExample();
    void executeGameExample();
}

#endif //CPPPLAYGROUND_PROTOTYPE_H
