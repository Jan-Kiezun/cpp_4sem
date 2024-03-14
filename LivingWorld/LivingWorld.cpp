#include <iostream>
#include <memory>
#include "Position.h"
#include "organisms/Organism.h"
#include "organisms/Plant.h"
#include "organisms/Animal.h"
#include "World.h"

using namespace std;

int main() {
    // Position
    Position p1;
    Position p2{1, 1};
    Position p3{-3, -5};

    //cout << p1.toString() << endl;
    //cout << p2.toString() << endl;
    //cout << p3.toString() << endl;
    //cout << p1.distance(p2) << endl;
    //p2.move(4, 6);
    //cout << p2.toString() << endl;

    // Organism
    //Organism org1;
    //Organism org2{ 10, p2 };

    //cout << org1.toString() << endl;
    //cout << org2.toString() << endl;
    //org1.move(2, 3);
    //cout << org1.toString() << endl;

    // Plant & Animal
//	Plant plant{ 3, p3 };
//	Animal animal{ 5, p2 };
//
//    Plant grass{ 3, p3 };

    Sheep sheep{5, p2};
    Grass grass{p3};

    cout << grass.toString() << endl;
    cout << sheep.toString() << endl;
    cout << grass.toString() << endl;
    cout << sheep.toString() << endl;
    grass.move(3, 4);
    cout << grass.toString() << endl;
    sheep.move(1, 2);
    cout << sheep.toString() << endl;

    // World test
    World world;
    Position posP1{4, 5};
    shared_ptr<Organism> grassW1 = make_shared<Grass>(posP1);
    Position posP2{5, 4};
    shared_ptr<Organism> dandelionW1 = make_shared<Dandelion>(posP2);

    Position posW2{3, 2};
    shared_ptr<Organism> sheepW1 = make_shared<Sheep>(5, posW2);
    Position posW3{2, 3};
    shared_ptr<Organism> wolfW1 = make_shared<Wolf>(9, posW3);

    world.addOrganism(grassW1);
    world.addOrganism(dandelionW1);
    world.addOrganism(sheepW1);
    world.addOrganism(wolfW1);

//    auto positions = world.getVectorOfPositionsAround(Position(5, 5));

//    for (auto pos: positions)
//        cout << pos.toString() << endl;


    int turns = 20;
    cout << world.toString() << endl;

    Sheep sheep2{5, p2};
    world.addOrganism(make_shared<Sheep>(sheep2));

//	world.writeWorld("world.bin");

    for (int i = 0; i < turns; i++) {
        world.makeTurn();
        cout << world.toString() << endl;
        world.printOrganisms();
    }

    // powrot do Tury 2
//    world.readWorld("world.bin");
//    cout << world.toString() << endl;


//    exit(0);
    return 0;
}
