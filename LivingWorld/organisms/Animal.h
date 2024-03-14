#pragma once

#include <utility>

#include "organisms/Organism.h"
#include "Position.h"

using namespace std;

class Animal : public Organism {
protected:
    Position lastPosition;
public:
    Animal(int power, Position position) : Organism(power, position), lastPosition(position) {};

    Animal(int power, Position position, int turnBorn, shared_ptr<Organism> parent,
           vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) : Organism(power, position, turnBorn, std::move(parent), std::move(ancestors)),
                                                                           lastPosition(position) {};

    Animal(shared_ptr<Organism> parent, Position position) : Organism(parent->getPower(), position, parent->getTurnBorn(), parent, parent->getAncestors()),
                                                             lastPosition(position) {};

    virtual ~Animal() = default;

    shared_ptr<Organism> clone(Position position) override = 0;

    string toString() override = 0;

    void move(int dx, int dy) override {
        Position position = this->getPosition();
        Position newPosition = Position(position.getX() + dx, position.getY() + dy);
        this->setPosition(newPosition);
    }

    // on collision, compare power
    void collision(shared_ptr<Organism> other, int turn) override {
        if (this->getPower() > other->getPower()) {
            other->setTurnDied(turn);
            other->setPosition(Position(-1, -1));
            other->die();
        } else {
            this->setTurnDied(turn);
            this->setPosition(Position(-1, -1));
            this->die();
        }
    }

    void moveBack() {
        this->setPosition(this->lastPosition);
    }

    void setLastPosition(Position position);

    Position getLastPosition();
};

class Sheep : public Animal {
public:
    Sheep(int power, Position position);
    Sheep(int power, Position position, int turnBorn, shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors);
    Sheep(shared_ptr<Organism> parent, Position position);
    ~Sheep() override;

    shared_ptr<Organism> clone(Position position) override;

    // define tostring
    string toString() override {
        string power = to_string(this->getPower());
        string position = this->getPosition().toString();
        return "S(power: " + power + ", position: " + position + ")";
    }
};

class Wolf : public Animal {
public:
    Wolf(int power, Position position);
    Wolf(int power, Position position, int turnBorn, shared_ptr<Organism> parent, vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors);
    Wolf(shared_ptr<Organism> parent, Position position);
    ~Wolf() override;

    virtual shared_ptr<Organism> clone(Position position1) override;

    // define tostring
    string toString() override {
        string power = to_string(this->getPower());
        string position = this->getPosition().toString();
        return "W(power: " + power + ", position: " + position + ")";
    }
};