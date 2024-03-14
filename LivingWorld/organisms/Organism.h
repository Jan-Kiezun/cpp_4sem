#pragma once

#include <string>
#include "Position.h"
#include <vector>
#include "memory"

using namespace std;

class Organism: public std::enable_shared_from_this<Organism> {
protected:
    bool alive = true;
    int power;
    Position position;
    string species;
    int turnBorn;
    int turnDied;
    int liveLength;
    int initiative;
    int powerToReproduce;
    int dxy = 1;
    vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors;
    shared_ptr<Organism> parent;
public:
    Organism(int power, Position position, int turnBorn, shared_ptr<Organism> parent,
             vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors) :
            power(power),
            position(position),
            species("O"),
            initiative(0),
            liveLength(2),
            turnBorn(turnBorn),
            powerToReproduce(0),
            turnDied(-1) {
        this -> parent = parent;
//        this->ancestors.push_back(make_pair(parent, make_pair(turnBorn, turnDied)));
        for (auto &ancestor: ancestors) {
            this->ancestors.push_back(ancestor);
        }
    };

    Organism(int power, Position position) :
            power(power),
            position(position),
            species("O"),
            initiative(0),
            liveLength(2),
            turnBorn(0),
            powerToReproduce(0),
            turnDied(-1) {};
    Organism() {};

    virtual ~Organism() = default;
    virtual shared_ptr<Organism> clone(Position position) = 0;
    virtual void collision(shared_ptr<Organism> other, int turn) = 0;

//    virtual void action(Position pos, World world) = 0;

    int getPower();

    void setPower(int power);

    Position getPosition();

    void setPosition(Position position);

    string getSpecies();

    void setSpecies(string spec);

    int getInitiative();

    void setInitiative(int initiative);

    int getLongevity();

    void setLongevity(int longevity);

    int getTurnBorn();

    int getTurnDied();

    void setTurnDied(int turnDied);

    void setTurnBorn(int turnBorn);

    int getPowerToReproduce();

    void setPowerToReproduce(int powerToReproduce);

    int getDxy();

    void setDxy(int dxy);

    vector<pair<shared_ptr<Organism>, pair<int, int>>> getAncestors();

    void addAncestor(shared_ptr<Organism> ancestor, int turnBorn, int turnDied);

    virtual string toString() = 0;

    virtual void move(int dx, int dy);

    void die(){
        this->alive = false;
    };

    void age(){
        this->liveLength--;
    };

    bool isAlive(){
        return this->alive;
    };

    bool childrenMade(){
        bool childrenMade = rand() % 100 < this->powerToReproduce;
        if (childrenMade) {
            this->power = this->power - 1;
        }
    };

    shared_ptr<Organism> reproduce(Position pos, int turn, shared_ptr<Organism> parent);

    // convert this to shared_ptr<Organism> this function
    shared_ptr<Organism> getParent(){
        return this->parent;
    };

    // define operator assignment operator
    Organism& operator=(const Organism& other ) {
        this->alive = other.alive;
        this->power = other.power;
        this->position = other.position;
        this->species = other.species;
        this->turnBorn = other.turnBorn;
        this->turnDied = other.turnDied;
        this->liveLength = other.liveLength;
        this->initiative = other.initiative;
        this->powerToReproduce = other.powerToReproduce;
        this->dxy = other.dxy;
        this->ancestors = other.ancestors;
        this->parent = other.parent;
        return *this;
    }
};