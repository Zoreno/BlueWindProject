#pragma once

#include <vector>
#include "Item.h"

class Player;
class Game;

class Inventory
{
public:
	Inventory() = delete;
	Inventory(Player*, Game*);
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	~Inventory();

	void addItem(int);
	void removeItem(int);
	bool hasItem(int);
	bool isFull();
	int getCount(int);

	Item* at(int);

	int getSize();
	const unsigned int getMaxSize();

	std::string toString();

private:
	std::vector<Item*> items_;
	const unsigned int maxSize_{8};
	Player* playerPointer_;
	Game* gamePointer_;

	void populateItemList();
	std::vector<Item*> allItems_;
};