#include "Animal.h"
#include <iostream>

using namespace std;

void Animal::setLastPosition(Position position) {
    lastPosition = position;
}

Position Animal::getLastPosition() {
    return lastPosition;
}

Wolf::Wolf(int power, Position position) : Animal(power, position) {
    setSpecies("W");
    setInitiative(5);
    setLongevity(15);
    setPowerToReproduce(50);
    setDxy(2);
}

Wolf::Wolf(int power, Position position, int turnBorn, shared_ptr<Organism> parent,
           vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) : Animal(power, position, turnBorn, std::move(parent),
                                                            std::move(ancestors)) {
    setSpecies("W");
    setInitiative(5);
    setLongevity(10);
    setPowerToReproduce(25);
    setDxy(2);
}

Wolf::Wolf(shared_ptr<Organism> parent, Position position) : Animal(parent->getPower(), position, parent->getTurnBorn(),
                                                 parent, parent->getAncestors()) {
    setSpecies("W");
    setInitiative(5);
    setLongevity(10);
    setPowerToReproduce(25);
    setDxy(2);
}

Wolf::~Wolf() = default;

shared_ptr<Organism> Wolf::clone(Position position) {
    shared_ptr<Organism> parent = shared_from_this();
    shared_ptr<Organism> clone = make_shared<Wolf>(parent, position);
    return clone;
}

Sheep::Sheep(int power, Position position) : Animal(power, position) {
    setSpecies("S");
    setInitiative(3);
    setLongevity(10);
    setPowerToReproduce(70);
    setDxy(1);
}

Sheep::Sheep(int power, Position position, int turnBorn, shared_ptr<Organism> parent,
             vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) : Animal(power, position, turnBorn, std::move(parent),
                                                              std::move(ancestors)) {
    setSpecies("S");
    setInitiative(3);
    setLongevity(7);
    setPowerToReproduce(40);
    setDxy(1);
}

Sheep::Sheep(shared_ptr<Organism> parent, Position position) : Animal(parent->getPower(), position, parent->getTurnBorn(),
                                                   parent, parent->getAncestors()) {
    setSpecies("S");
    setInitiative(3);
    setLongevity(7);
    setPowerToReproduce(40);
    setDxy(1);
}

Sheep::~Sheep() = default;

shared_ptr<Organism> Sheep::clone(Position position) {
    shared_ptr<Organism> parent = shared_from_this();
    cout << parent->getPower() << endl;
    shared_ptr<Organism> clone = make_shared<Sheep>(parent, position);
    return clone;
}