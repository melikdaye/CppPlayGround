//
// Created by Administrator on 22.03.2023.
//

#include <thread>
#include "prototype.h"

void PrototypeMethod::executeBasicExample() {
    Client c;
    c.setPrototype(new ConcreteProtoType1{});
    c.operation();
}
void PrototypeMethod::executeGameExample() {
    VehiclePrototypes::registerPrototype("car",std::make_shared<Car>());
    VehiclePrototypes::registerPrototype("bus",std::make_shared<Bus>());
    GameManagerProto managerProto;
    managerProto.run();
}

Prototype *ConcreteProtoType1::clone() {
    std::cout << __FUNCSIG__ << std::endl;
    return new ConcreteProtoType1{*this};
}

Prototype *ConcreteProtoType2::clone() {
    std::cout << __FUNCSIG__ << std::endl;
    return new ConcreteProtoType2{*this};
}

Animation::Animation(std::string_view animFile) {
    std::cout << "[Animation] Loading: " << animFile << " ";
    for (int i = 0; i < 10; ++i) {
        std::cout << ".";
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
    }
    std::cout<<std::endl;
    animationData.assign("^^^^^^");
}

Vehicle::Vehicle(int speed, int hitPoints, const std::string &name, std::string_view  animFile, const Position &position,const std::string &color)
        : speed(speed), hitPoints(hitPoints), name(name), position(position),color(color) {
        animation = new Animation{animFile};
}

Vehicle::~Vehicle() {
    delete animation;
}

int Vehicle::getSpeed() const {
    return speed;
}

int Vehicle::getHitPoints() const {
    return hitPoints;
}

const std::string &Vehicle::getName() const {
    return name;
}

const Position &Vehicle::getPosition() const {
    return position;
}

void Vehicle::setSpeed(int speed) {
    Vehicle::speed = speed;
}

void Vehicle::setHitPoints(int hitPoints) {
    Vehicle::hitPoints = hitPoints;
}

void Vehicle::setName(const std::string &name) {
    Vehicle::name = name;
}

void Vehicle::setAnimationData(const std::string &animData) {
    animation->setAnimationData(animData);
}

void Vehicle::setPosition(const Position &position) {
    Vehicle::position = position;
}

const std::string &Vehicle::getAnimation() const {
    return animation->getAnimationData();
}

Vehicle::Vehicle(const Vehicle &other):speed{other.speed},name{other.name},hitPoints{other.hitPoints}, position{other.position},color{other.color} {
   animation = new Animation{};
   animation->setAnimationData(other.getAnimation());
}

Vehicle &Vehicle::operator=(const Vehicle &other) {
    if(this != &other){
        speed = other.speed;
        name = other.name;
        hitPoints = other.hitPoints;
        position = other.position;
        color = other.color;
        animation->setAnimationData(other.getAnimation());
    }
    return *this;
}

Vehicle::Vehicle(Vehicle &&other) noexcept :  speed{other.speed}, name{std::move(other.name)}, hitPoints{other.hitPoints},
                                              position{other.position},animation{other.animation},color{std::move(other.color)}{
    other.animation = nullptr;
    other.position = {0,0};
    other.hitPoints = 0;
    other.speed = 0;
    other.name.clear();
    other.color.clear();

}

Vehicle &Vehicle::operator=(Vehicle &&other) noexcept {
    if(this != &other){
        speed = other.speed;
        name = std::move(other.name);
        hitPoints = other.hitPoints;
        position = other.position;
        color = other.color;
        delete animation;
        animation = other.animation;

        other.animation = nullptr;
        other.position = {0,0};
        other.hitPoints = 0;
        other.speed = 0;
        other.name.clear();
        other.color.clear();

    }
    return *this;
}

const std::string &Vehicle::getColor() const {
    return color;
}

void Vehicle::setColor(const std::string &color) {
    Vehicle::color = color;
}

Vehicle::Vehicle() {
    animation = new Animation{};
}

Vehicle * create(std::string_view type,int speed, int hitPoints, const std::string &name,  std::string_view  animFile, const Position &position) {
        if(type == "redcar"){
            return new Car{speed,hitPoints,name,animFile,position,"Red"};
        }
        else if(type == "greencar"){
            return new Car{speed,hitPoints,name,animFile,position,"Green"};
        }
        else if(type == "yellowbus"){
            return new Bus{speed,hitPoints,name,animFile,position,"Yellow"};
        }
        else if(type == "bluebus"){
            return new Bus{speed,hitPoints,name,animFile,position,"Blue"};
        }
    return nullptr;
}


void Car::update() {

    std::cout << "[" << getColor() << getName() << "]" << std::endl;
    std::cout << "Animation: " << getAnimation() << std::endl;
    if(dist(engine) && getColor() == "Red"){
        std::cout << "Increase speed temporarily" << getSpeed()*speedFactor << std::endl;
    }else{
        std::cout << "Speed: " << getSpeed() <<  std::endl;
    }
    std::cout << "Hit points: " << getHitPoints() << std::endl;
    std::cout << "Position: " << getPosition() << std::endl;
}

VehiclePtr Car::clone() {
    std::cout << "Cloning->" << getName() << std::endl;
    return std::shared_ptr<Vehicle>{new Car{*this}};
}

void Bus::update() {
    std::cout << "[" << getColor() << getName() << "]" << std::endl;
    std::cout << "Animation: " << getAnimation() << std::endl;
    if(dist(engine)){
        std::cout << "Moving out of way" << std::endl;
    }
    std::cout << "Speed: " << getSpeed() <<  std::endl;
    std::cout << "Hit points: " << getHitPoints() << std::endl;
    std::cout << "Position: " << getPosition() << std::endl;
}

VehiclePtr Bus::clone() {
    std::cout << "Cloning->" << getName() << std::endl;
    return std::shared_ptr<Vehicle>{new Bus{*this}};
}

VehiclePtr getRedCar(){
    auto vehicle = VehiclePrototypes::getPrototype("car");
    vehicle->setColor("Red");
    vehicle->setHitPoints(10);
    vehicle->setSpeed(30);
    vehicle->setPosition({0,0});
    Animation anim{"red.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    return vehicle;
}

VehiclePtr getGreenCar(){
    auto vehicle = VehiclePrototypes::getPrototype("car");
    vehicle->setColor("Green");
    vehicle->setHitPoints(5);
    vehicle->setSpeed(30);
    vehicle->setPosition({100,0});
    Animation anim{"green.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    return vehicle;
}

VehiclePtr getYellowBus(){
    auto vehicle = VehiclePrototypes::getPrototype("bus");
    vehicle->setColor("Yellow");
    vehicle->setHitPoints(20);
    vehicle->setSpeed(25);
    vehicle->setPosition({100,200});
    Animation anim{"ybus.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    return vehicle;
}

VehiclePtr getBlueBus(){
    auto vehicle = VehiclePrototypes::getPrototype("bus");
    vehicle->setColor("Blue");
    vehicle->setHitPoints(25);
    vehicle->setSpeed(25);
    vehicle->setPosition({200,200});
    Animation anim{"bbus.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    return vehicle;
}
void GameManagerProto::run() {
    vehicles.push_back(getRedCar());
    vehicles.push_back(getGreenCar());
    vehicles.push_back(getYellowBus());
    vehicles.push_back(getBlueBus());
    
    int count{5};
    while (count != 0){
        using namespace std::chrono_literals;
        system("cls");
        std::this_thread::sleep_for(1s);
        for (auto vehicle:vehicles) {
                vehicle->update();
        }
        if(count == 2){
            auto vehicle = vehicles[0]->clone();
            vehicle->setPosition({50,50});
            vehicle->setHitPoints(15);
            vehicles.push_back(vehicle);
        }
        if(count == 3){
            auto vehicle = vehicles[2]->clone();
            vehicle->setPosition({150,250});
            vehicle->setSpeed(10);
            vehicles.push_back(vehicle);
        }
        --count;
    }
}

std::vector<std::string> VehiclePrototypes::getKeys() {
    std::vector<std::string> keys{};
    keys.reserve(prototypes.size());
    for (const auto &kv:prototypes) {
        keys.push_back(kv.first);
    }
    return keys;
}

void VehiclePrototypes::registerPrototype(const std::string &key, VehiclePtr prototype) {
    if(auto it = prototypes.find(key);it == end(prototypes)){
        prototypes[key] = prototype;
    }
    else{
        std::cout << "Key already exist" << std::endl;
    }
}

VehiclePtr VehiclePrototypes::deregisterPrototype(const std::string &key) {
    if(auto it = prototypes.find(key);it != end(prototypes)){
        auto vehicle = prototypes[key];
        prototypes.erase(key);
        return vehicle;
    }
    return nullptr;
}

VehiclePtr VehiclePrototypes::getPrototype(const std::string &key) {
    if(auto it = prototypes.find(key);it != end(prototypes)){
        return prototypes[key]->clone();
    }
    return nullptr;
}
