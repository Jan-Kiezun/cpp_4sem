#pragma once

#include <vector>
#include <ctime>
#include "organisms/Organism.h"
#include "memory"


using namespace std;


class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
    vector<shared_ptr<Organism>> organisms;

	char separator = '.';

	string getOrganismFromPosition(int x, int y);
	bool isPositionOnWorld(int x, int y);
	bool isPositionFree(Position position);

public:
	World(int worldX, int worldY): worldX(worldX), worldY(worldY) {};
	World() : World(6, 6) {};

	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);

	int getTurn();

    vector<shared_ptr<Organism>> getOrganisms();
	void addOrganism( shared_ptr<Organism> organism);
    void killOrganism(shared_ptr<Organism> organism);
	vector<Position> getVectorOfPositionsAround(shared_ptr<Organism> organism);
	void makeTurn();
    void actionOnEmptyField(shared_ptr<Organism> organism, Position position);
    void actionOnOrganism(shared_ptr<Organism> organism, Position position);

	void writeWorld(string fileName);
	void readWorld(string fileName);

	string toString();

    void printOrganisms();


};

