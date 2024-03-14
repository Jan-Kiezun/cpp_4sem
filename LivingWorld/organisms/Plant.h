#pragma once

#include <utility>

#include "organisms/Organism.h"

class Plant : public Organism {
public:
    explicit Plant(Position position) : Organism(0, position) {};

    Plant(Position position, int turnBorn,
          shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) :
            Organism(0, position, turnBorn, std::move(parent), std::move(ancestors)) {};

    Plant(shared_ptr<Organism> parent, Position position) : Organism(0, position, parent->getTurnBorn(), parent,
                                                                     parent->getAncestors()) {};

    ~Plant() override;

    shared_ptr<Organism> clone(Position position) override = 0;

    void move(int dx, int dy);

    void collision(shared_ptr<Organism> other, int turn) override {};

    string toString() override = 0;
};

class Grass : public Plant {
public:
    explicit Grass(Position position);
    Grass(Position position, int turnBorn, shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors);
    Grass(shared_ptr<Organism> parent, Position position);
    ~Grass() override;

    shared_ptr<Organism> clone(Position position) override;

    // define tostring
    string toString() override {
        string position = this->getPosition().toString();
        string power = to_string(this->getPower());
        return "G(position: " + position + ", power: " + power + ")";
    }
};

class Dandelion : public Plant {
public:
    explicit Dandelion(Position position);
    Dandelion(Position position, int turnBorn, shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors);
    Dandelion(shared_ptr<Organism> parent, Position position);
    ~Dandelion() override;

    shared_ptr<Organism> clone(Position position) override;

    // define tostring
    string toString() override {
        string position = this->getPosition().toString();
        string power = to_string(this->getPower());
        return "D(position: " + position + ", power: " + power + ")";
    }
};

class Toadstool : public Plant {
public:
    explicit Toadstool(Position position);
    Toadstool(Position position, int turnBorn, shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors);
    Toadstool(shared_ptr<Organism> parent, Position position);
    ~Toadstool() override;

    shared_ptr<Organism> clone(Position position) override;

    // define tostring
    string toString() override {
        string position = this->getPosition().toString();
        string power = to_string(this->getPower());
        return "T(position: " + position + ", power: " + power + ")";
    }
};