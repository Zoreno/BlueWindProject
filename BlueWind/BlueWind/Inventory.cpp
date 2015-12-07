#include "Inventory.h"
#include "Player.h"
#include <iostream>
#include "Game.h"

using namespace std;

Inventory::Inventory(Player * player, Game* game)
	: playerPointer_{ player }, 
	gamePointer_{game}
{
	items_.reserve(maxSize_);
	populateItemList();
}

Inventory::~Inventory()
{
	while (!allItems_.empty())
	{
		delete allItems_.back();
		allItems_.pop_back();
	}
	items_.clear();
}

void Inventory::addItem(int ID)
{
	if (isFull())
	{
		cout << "Inventory is full" << endl;
		return;
	}
	for (auto it : allItems_)
	{
		if (it->getID() == ID)
		{
			items_.push_back(it);
		}
	}
}

void Inventory::removeItem(int ID)
{
	auto it = items_.begin();

	while (it != items_.end())
	{
		if ((*it)->getID() == ID)
		{
			items_.erase(it);
			break;
		}
	}
}

bool Inventory::hasItem(int ID)
{
	for (auto it : items_)
	{
		if (it->getID() == ID)
		{
			return true;
		}
	}
	return false;
}

bool Inventory::isFull()
{
	return (items_.size() >= maxSize_);
}

int Inventory::getCount(int ID)
{
	int count;

	for (auto it : items_)
	{
		if (it->getID() == ID)
		{
			count++;
		}
	}

	return count;
}

Item * Inventory::at(int pos)
{
	return items_.at(pos);
}

int Inventory::getSize()
{
	return items_.size();
}

const unsigned int Inventory::getMaxSize()
{
	return maxSize_;
}

std::string Inventory::toString()
{
	string s;
	for (auto it : items_)
	{
		s = s + to_string(it->getID()) + " ";
	}
	return s;
}

void Inventory::populateItemList()
{
	//							ID	Namn		Textur
	allItems_.push_back(new Item{ 0,"Tree",gamePointer_->getTexture("grassTree") });
}
