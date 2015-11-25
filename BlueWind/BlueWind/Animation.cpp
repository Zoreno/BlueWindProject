#include "Animation.h"
#include "Entity.h"
#include <iostream>
using namespace std;


Animation::Animation(Entity* entityPointer, const string& filename)
	: entityPtr_{entityPointer}
{
	loadTexture("WalkUp0", filename, idle_, 6);
	loadTexture("WalkUp1", filename, walkingNorth_, 6);
	loadTexture("WalkUp2", filename, walkingNorth_, 7);
	loadTexture("WalkDown0", filename, idle_, 0);
	loadTexture("WalkDown1", filename, walkingSouth_, 0);
	loadTexture("WalkDown2", filename, walkingSouth_, 1);
	loadTexture("WalkRight0", filename, idle_, 4);
	loadTexture("WalkRight1", filename, walkingEast_, 4);
	loadTexture("WalkRight2", filename, walkingEast_, 5);
	loadTexture("WalkDown0", filename, idle_, 2);
	loadTexture("WalkDown1", filename, walkingWest_, 2);
	loadTexture("WalkDown2", filename, walkingWest_, 3);
	currentSprite_.setTexture(*walkingSouth_[0]);
	//cout << walkingSouth_.size() << endl;
}

void Animation::update()
{
	switch (state_)
	{
	case Animation::walking:
		++cooldown;
		if (cooldown >= 3)
		{
			++it;
			switch (dir_)
			{
			case north:
				if (it > walkingNorth_.size())
					it = 1;
				currentSprite_.setTexture(*walkingNorth_[it - 1]);
				cooldown = 0;
				break;

			case south:
				if (it > walkingSouth_.size())
					it = 1;
				currentSprite_.setTexture(*walkingSouth_[it - 1]);
				cooldown = 0;
				break;

			case east:
				if (it > walkingEast_.size())
					it = 1;
				currentSprite_.setTexture(*walkingEast_[it - 1]);
				cooldown = 0;
				break;

			case west:
				if (it > walkingWest_.size())
					it = 1;
				currentSprite_.setTexture(*walkingWest_[it - 1]);
				cooldown = 0;
				break;

			default:
				break;
			}
		}
		break;

	case Animation::idle:
		switch (dir_)
		{
		case north:
			currentSprite_.setTexture(*idle_[0]);
			break;

		case south:
			currentSprite_.setTexture(*idle_[1]);
			break;

		case east:
			currentSprite_.setTexture(*idle_[2]);
			break;

		case west:
			currentSprite_.setTexture(*idle_[1]);
			break;

		default:
			break;
		}
		break;
	case Animation::attacking:
		break;
	default:
		break;
	}
}

void Animation::render(GameWindow& window)
{
	currentSprite_.setPosition(entityPtr_->getPosition());
	window.draw(currentSprite_);
}

void Animation::loadTexture(const std::string& texName, const std::string& fileName, std::vector<sf::Texture*>& animVector, int pos)
{
	sf::Texture* tex = new sf::Texture;
	sf::IntRect area(pos * 16, 0, 16, 16);
	tex->loadFromFile(fileName, area);
	animVector.push_back(tex);
}