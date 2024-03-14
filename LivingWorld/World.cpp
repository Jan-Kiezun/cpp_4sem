#include "World.h"
#include <fstream>
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std;

string World::getOrganismFromPosition(int x, int y) {
    for (auto &org: organisms)
        if (org != nullptr && org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

vector<shared_ptr<Organism>> World::getOrganisms() {
    return organisms;
}

bool World::isPositionOnWorld(int x, int y) {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfPositionsAround(shared_ptr<Organism> organism) {
    Position position = organism->getPosition();
    int pos_x = position.getX(), pos_y = position.getY();
    int dxy = organism->getDxy();

    vector<Position> result;
    for (int x = -dxy; x < dxy + 1; ++x)
        for (int y = -dxy; y < dxy + 1; ++y)
            if ((x != 0 || y != 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                result.push_back(Position(pos_x + x, pos_y + y));
            }
    return result;
}

int World::getWorldX() {
    return this->worldX;
}

void World::setWorldX(int world_X) {
    this->worldX = world_X;
}

int World::getWorldY() {
    return this->worldY;
}

void World::setWorldY(int worldY) {
    this->worldY = worldY;
}

int World::getTurn() {
    return this->turn;
}

void World::addOrganism(shared_ptr<Organism> organism) {
    auto iter = organisms.begin();
    while (iter != organisms.end() && (*iter)->getInitiative() > organism->getInitiative())
        iter++;
    organisms.insert(iter, organism);
}

void World::killOrganism(shared_ptr<Organism> organism) {
    auto iter = remove_if(organisms.begin(), organisms.end(),
                          [organism](shared_ptr<Organism> org) { return org == organism; });
    organism -> setTurnDied(turn);
    organism -> die();
    organisms.erase(iter, organisms.end());
}


void World::printOrganisms() {
    cout << "organisms: " << endl;
    for (shared_ptr<Organism> org: organisms) {
        cout << org->toString() << " Ancestors: (";

        vector<pair<shared_ptr<Organism>, pair<int, int>>> ancestors = org->getAncestors();
        for (auto &ancestor: ancestors) {
            cout << "Born: " << ancestor.first->getTurnBorn() << " Dead: " << ancestor.first->getTurnDied() << ", ";
        }
        cout << ")" << endl;

    }
}

void World::actionOnEmptyField(shared_ptr<Organism> org, Position pos) {
    if (org->childrenMade()) {
        shared_ptr<Organism> child = org->reproduce(pos, turn, org);
        addOrganism(child);
    } else {
        org->setPosition(pos);
        cout << org->getSpecies() << " moved" << endl;
    }
}

void World::actionOnOrganism(shared_ptr<Organism> org, Position pos) {
    shared_ptr<Organism> other = nullptr;
    for (auto &org2: organisms) {
        if (org2->getPosition() == pos) {
            other = org2;
            break;
        }
    }
    org->collision(other, turn);
    if (!org->isAlive()) {
        cout << other->getSpecies() << " killed " << org->getSpecies() << endl;
        killOrganism(org);
    } else {
        cout << org->getSpecies() << " killed " << other->getSpecies() << endl;
        org->age();
        killOrganism(other);
    }
}

void World::makeTurn() {
    vector<Position> newPositions;
    int numberOfNewPositions;
    int randomIndex;

    srand(time(0));
    for (auto org: organisms) {
        if (org == nullptr || !org->isAlive())
            continue;

        if (org->getLongevity() == 0) {
            killOrganism(org);
            cout << org->getSpecies() << " died of old age" << endl;
            continue;
        }
        newPositions = getVectorOfPositionsAround(org);
        numberOfNewPositions = newPositions.size();

        if (numberOfNewPositions > 0) {
            randomIndex = rand() % numberOfNewPositions;
            Position pos = newPositions[randomIndex];

            if (isPositionFree(pos)) {
                org->age();
                actionOnEmptyField(org, pos);
            } else {
                actionOnOrganism(org, pos);
            }
        }
    }
    turn++;
}

void World::writeWorld(string fileName) {
    fstream my_file;
    my_file.open(fileName, ios::out | ios::binary);
    if (my_file.is_open()) {
        my_file.write((char *) &this->worldX, sizeof(int));
        my_file.write((char *) &this->worldY, sizeof(int));
        my_file.write((char *) &this->turn, sizeof(int));
        int orgs_size = this->organisms.size();
        my_file.write((char *) &orgs_size, sizeof(int));
        for (int i = 0; i < orgs_size; i++) {
            int data;
            data = this->organisms[i]->getPower();
            my_file.write((char *) &data, sizeof(int));
            data = this->organisms[i]->getPosition().getX();
            my_file.write((char *) &data, sizeof(int));
            data = this->organisms[i]->getPosition().getY();
            my_file.write((char *) &data, sizeof(int));
            string s_data = this->organisms[i]->getSpecies();
            int s_size = s_data.size();
            my_file.write((char *) &s_size, sizeof(int));
            my_file.write(s_data.data(), s_data.size());
        }
        my_file.close();
    }
}

void World::readWorld(string fileName) {
    fstream my_file;
    my_file.open(fileName, ios::in | ios::binary);
    if (my_file.is_open()) {
        int result;
        my_file.read((char *) &result, sizeof(int));
        this->worldX = (int) result;
        my_file.read((char *) &result, sizeof(int));
        this->worldY = (int) result;
        my_file.read((char *) &result, sizeof(int));
        this->turn = (int) result;
        my_file.read((char *) &result, sizeof(int));
        int orgs_size = (int) result;
        vector<shared_ptr<Organism>> new_organisms;
        for (int i = 0; i < orgs_size; i++) {
            int power;
            my_file.read((char *) &result, sizeof(int));
            power = (int) result;

            int pos_x;
            my_file.read((char *) &result, sizeof(int));
            pos_x = (int) result;
            int pos_y;
            my_file.read((char *) &result, sizeof(int));
            pos_y = (int) result;
            Position pos{pos_x, pos_y};

            int s_size;
            my_file.read((char *) &result, sizeof(int));
            s_size = (int) result;

            string species;
            species.resize(s_size);
            my_file.read((char *) &species[0], s_size);
        }
        this->organisms = std::move(new_organisms);
        my_file.close();
    }
}

string World::toString() {
    string result = "\nturn: " + to_string(getTurn()) + "\n";
    string spec;

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            if (spec != "")
                result += spec;
            else
                result += separator;
        };
        result += "\n";
    }
    return result;
}

