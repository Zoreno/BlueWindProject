#include <fstream>
#include <sstream>
#include "Game.h"
#include "Application.h"
#include "Universe.h"

using namespace std;

string GameState::toString()
{
	string s;
	s.append(to_string(bridge1Built) + " ");
	s.append(to_string(minotaurDead) + " ");
	s.append(to_string(bridge2Built));
	return s;
}

Game::Game(Application * appPtr, bool loadSave)
	:Frame{appPtr}, 
	universe_{this}, 
	player_{universe_.getCurrentWorld(), textureHandler_.getTextureRef("player"), this }, 
	ui_{&player_}
{
	if (loadSave)
	{
		loadGame();
	}
	else
		appPtr->getSoundHandler().playMusic("world0Music");
}

void Game::update()
{
	universe_.update();
	player_.update();
	ui_.update();
}

void Game::render(GameWindow & window)
{
	sf::View camera = window.getView();
	camera.setCenter(player_.getPosition());
	window.setView(camera);
	universe_.render(window);
	player_.render(window);
	ui_.render(window);
}

void Game::handleKeyEvent(sf::Event event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Space:
		player_.swordAttack(universe_.getCurrentWorld()->getEnemyVector());
		break;
	case sf::Keyboard::J:
		player_.fireballAttack(universe_.getCurrentWorld()->getEnemyVector());
		break;
	case sf::Keyboard::K:
		player_.interact(universe_.getCurrentWorld()->getNPCVector());
		break;
	case sf::Keyboard::L:
		ui_.handleKeyEvent(event);
		break;
	default:
		break;
	}
}

void Game::handleMouseEvent(sf::Event)
{
}

vector<int> splitString(string s)
{
	stringstream ss(s);
	vector<int> IDs;
	string sub;

	while (ss >> sub)
		IDs.push_back(stoi(sub));
	return IDs;
}

void Game::saveGame()
{
	ofstream saveStream;
	saveStream.open("savefile.txt", std::ofstream::out | std::ofstream::trunc);
	if (saveStream.is_open())
	{
		saveStream << player_.getName() << endl;
		saveStream << player_.getMaxHealth() << endl;
		saveStream << player_.getMaxMana() << endl;
		saveStream << player_.getDamage() << endl;
		saveStream << player_.getLevel() << endl;
		saveStream << player_.getExperience() << endl;
		saveStream << universe_.getCurrentWorld()->getID() << endl;
		saveStream << player_.getPosition().x << endl;
		saveStream << player_.getPosition().y << endl;
		saveStream << player_.getInventory()->toString() << endl;
		saveStream << gameState_.toString() << endl;
		saveStream.close();
	}
	else
		throw FrameException("Kunde inte spara data till savefile.txt");
}

void Game::loadGame()
{
	string line;
	ifstream saveStream("savefile.txt");
	if (saveStream.is_open())
	{
		getline(saveStream, line); //name
		player_.setName(line);
		getline(saveStream, line); //maxHealth
		player_.setMaxHealth(stoi(line));
		getline(saveStream, line); //maxMana
		player_.setMaxMana(stoi(line));
		getline(saveStream, line); //damage
		player_.setDamage(stoi(line));
		getline(saveStream, line); //level
		player_.setLevel(stoi(line));
		getline(saveStream, line); //experience
		player_.setExperience(stoi(line));
		getline(saveStream, line); //currWorld
		int worldID = stoi(line);
		getline(saveStream, line); //pos x
		int posX = stoi(line);
		getline(saveStream, line); //pos y
		int posY = stoi(line);
		universe_.switchWorld(worldID, posX, posY);
		getline(saveStream, line); //inv
		vector<int> items = splitString(line);
		for (auto it : items)
		{
			player_.getInventory()->addItem(it);
		}
		getline(saveStream, line); //Gamestate
		if (line.at(0) == '1') //Bridge1
		{
			int startposition{ 13 * universe_.getWorld(0)->getMapWidth() + 40 };
			for (int i{ 0 }; i < 10; ++i)
			{
				universe_.getWorld(0)->changeTile(startposition + i, 2);
			}
			gameState_.bridge1Built = true;
		}

		if (line.at(2) == '1') //Minotaur
		{
			universe_.populateCity();
			gameState_.minotaurDead = true;
		}

		if (line.at(4) == '1') // Bridge2
		{
			int startposition{ 17 * universe_.getWorld(2)->getMapWidth() + 63 };

			for (int i{ 0 }; i < 2; ++i)
			{
				universe_.getWorld(2)->changeTile(startposition + i, 2);
			}
			gameState_.bridge2Built = true;
		}
		saveStream.close();
	}
	else
		throw FrameException("Kunde inte ladda data från savefile.txt");
}

Player * Game::getPlayer()
{
	return &player_;
}

Application * Game::getApp()
{
	return appPointer_;
}

UserInterface * Game::getUserInterface()
{
	return &ui_;
}

GameState * Game::getGameState()
{
	return &gameState_;
}

sf::Texture & Game::getTexture(const std::string& ref)
{
	return textureHandler_.getTextureRef(ref);
}

