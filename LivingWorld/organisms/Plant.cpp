#include "Plant.h"

#include <utility>

void Plant::move(int dx, int dy)
{
	Organism::move(0, 0);
}

Plant::~Plant() = default;

Grass::Grass(Position position): Plant(position) {
    setSpecies("G");
    setPower(0);
    setInitiative(1);
    setLongevity(3);
    setPowerToReproduce(70);
    setDxy(1);
}

Grass::Grass(Position position, int turnBorn, shared_ptr<Organism> parent,
             vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) :
        Plant(position, turnBorn, std::move(parent), std::move(ancestors)) {
    setSpecies("G");
    setPower(0);
    setInitiative(1);
    setLongevity(3);
    setPowerToReproduce(70);
    setDxy(1);
}

Grass::Grass(shared_ptr<Organism> parent, Position position) : Plant(std::move(parent), position) {
    setSpecies("G");
    setPower(0);
    setInitiative(1);
    setLongevity(3);
    setPowerToReproduce(70);
    setDxy(1);
}

shared_ptr<Organism> Grass::clone(Position position) {
    shared_ptr<Organism> parent = shared_from_this();
    shared_ptr<Organism> clone = make_shared<Grass>(parent, position);
    return clone;
}

Grass::~Grass() = default;

Dandelion::Dandelion(Position position): Plant(position) {
    setSpecies("D");
    setPower(0);
    setInitiative(1);
    setLongevity(2);
    setPowerToReproduce(80);
    setDxy(1);
}

Dandelion::Dandelion(Position position, int turnBorn, shared_ptr<Organism> parent,
                     vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) :
        Plant(position, turnBorn, std::move(parent), std::move(ancestors)) {
    setSpecies("D");
    setPower(0);
    setInitiative(1);
    setLongevity(2);
    setPowerToReproduce(80);
    setDxy(1);
}

Dandelion::Dandelion(shared_ptr<Organism> parent, Position position) : Plant(std::move(parent), position) {
    setSpecies("D");
    setPower(0);
    setInitiative(1);
    setLongevity(2);
    setPowerToReproduce(80);
    setDxy(1);
}

shared_ptr<Organism> Dandelion::clone(Position position) {
    shared_ptr<Organism> parent = shared_from_this();
    shared_ptr<Organism> clone = make_shared<Dandelion>(parent, position);
    return clone;
}

Dandelion::~Dandelion() = default;

Toadstool::Toadstool(Position position) : Plant(position) {
    setSpecies("T");
    setPower(0);
    setInitiative(1);
    setLongevity(10);
    setPowerToReproduce(25);
    setDxy(1);
}

Toadstool::Toadstool(Position position, int turnBorn, shared_ptr<Organism> parent,
                     vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) :
        Plant(position, turnBorn, std::move(parent), std::move(ancestors)) {
    setSpecies("T");
    setPower(0);
    setInitiative(1);
    setLongevity(10);
    setPowerToReproduce(25);
    setDxy(1);
}

Toadstool::Toadstool(shared_ptr<Organism> parent, Position position) : Plant(std::move(parent), position) {
    setSpecies("T");
    setPower(0);
    setInitiative(1);
    setLongevity(10);
    setPowerToReproduce(25);
    setDxy(1);
}


shared_ptr<Organism> Toadstool::clone(Position position) {
    shared_ptr<Organism> parent = shared_from_this();
    shared_ptr<Organism> clone = make_shared<Toadstool>(parent, position);
    return clone;
}

Toadstool::~Toadstool() = default;

