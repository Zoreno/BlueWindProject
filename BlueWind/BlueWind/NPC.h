#pragma once

#include "Entity.h"
#include "GameWindow.h"
#include <functional>

class Game;

class NPC : public Entity
{
public:
	NPC(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&, std::string, std::function<void(NPC*)>);
	NPC() = delete;
	NPC(const NPC&) = delete;
	NPC& operator=(const NPC&) = delete;

	void update() override;
	void render(GameWindow&) override;
	void talk() const;
	void interact();

	void die() override;
private:
	sf::Sprite sprite_;
	std::string conversation_;
	std::function<void(NPC*)> callback_;
	bool talkedTo{ false };
};
