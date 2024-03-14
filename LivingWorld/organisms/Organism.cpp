#include "Organism.h"
#include <iostream>
#include <utility>

using namespace std;

int Organism::getPower() {
    return this->power;
}

void Organism::setPower(int pow) {
    this->power = pow;
}

Position Organism::getPosition() {
    return this->position;
}

void Organism::setPosition(Position pos) {
    this->position = pos;
}

void Organism::move(int dx, int dy) {
    position.move(dx, dy);
}

string Organism::getSpecies() {
    return this->species;
}

void Organism::setSpecies(string spec) {
    this->species = std::move(spec);
}

int Organism::getInitiative() {
    return this->initiative;
}

void Organism::setInitiative(int init) {
    this->initiative = init;
}

int Organism::getLongevity() {
    return this->liveLength;
}

void Organism::setLongevity(int longev) {
    this->liveLength = longev;
}

int Organism::getTurnBorn() {
    return this->turnBorn;
}

int Organism::getTurnDied() {
    return this->turnDied;
}

void Organism::setTurnDied(int turnDed) {
    this->turnDied = turnDed;
}

int Organism::getPowerToReproduce() {
    return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToRepr) {
    this->powerToReproduce = powerToRepr;
}

int Organism::getDxy() {
    return this->dxy;
}

void Organism::setDxy(int dxdy) {
    this->dxy = dxdy;
}

vector<pair<shared_ptr<Organism>, pair<int, int>>> Organism::getAncestors() {
    return this->ancestors;
}

void Organism::addAncestor(shared_ptr<Organism> ancestor, int turnBorn, int turnDied) {
    this->ancestors.emplace_back(ancestor, make_pair(turnBorn, turnDied));
}

void Organism::setTurnBorn(int turnBorn) {
    this->turnBorn = turnBorn;
}

shared_ptr<Organism> Organism::reproduce(Position pos, int turn, shared_ptr<Organism> parent) {
    shared_ptr<Organism> child = clone(pos);
    child->setTurnBorn(turn);
    child->addAncestor(parent, parent->getTurnBorn(), parent->getTurnDied());
    cout <<  child->toString() << " was born" <<  endl;
    return child;
}


