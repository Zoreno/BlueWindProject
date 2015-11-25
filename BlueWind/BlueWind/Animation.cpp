#include "Animation.h"
#include "Entity.h"
#include <iostream>
using namespace std;


Animation::Animation(Entity* entityPointer)
	: entityPtr_{entityPointer}
{
	loadTexture("SkeletonWalkUp0", "res/textures/player/SkeletonWalkUp0.png", idle_);
	loadTexture("SkeletonWalkUp1", "res/textures/player/SkeletonWalkUp1.png", walkingNorth_);
	loadTexture("SkeletonWalkUp2", "res/textures/player/SkeletonWalkUp2.png", walkingNorth_);
	loadTexture("SkeletonWalkUp3", "res/textures/player/SkeletonWalkUp3.png", walkingNorth_);
	loadTexture("SkeletonWalkUp4", "res/textures/player/SkeletonWalkUp4.png", walkingNorth_);
	loadTexture("SkeletonWalkUp5", "res/textures/player/SkeletonWalkUp5.png", walkingNorth_);
	loadTexture("SkeletonWalkUp6", "res/textures/player/SkeletonWalkUp6.png", walkingNorth_);
	loadTexture("SkeletonWalkUp7", "res/textures/player/SkeletonWalkUp7.png", walkingNorth_);
	loadTexture("SkeletonWalkUp8", "res/textures/player/SkeletonWalkUp8.png", walkingNorth_);
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

			/*case south:
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
				break;*/

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

		/*case south:
			currentSprite_.setTexture(*idle_[1]);

		case east:
			currentSprite_.setTexture(*idle_[2]);

		case west:
			currentSprite_.setTexture(*idle_[3]);*/
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
	//cout << "Nu är vi här" << endl;
	currentSprite_.setPosition(entityPtr_->getPosition());
	//cout << "Det gick bra!" << endl;
	window.draw(currentSprite_);
}

void Animation::loadTexture(const std::string& texName, const std::string& fileName, std::vector<sf::Texture*>& animVector)
{
	sf::Texture* tex = new sf::Texture;
	if (!tex->loadFromFile(fileName))
	{
		//TODO lägg till ex
		cout << "Kan inte ladda textur: " + texName << endl;
	}
	else
		animVector.push_back(tex);
}