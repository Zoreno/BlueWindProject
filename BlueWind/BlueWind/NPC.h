#pragma once

#include "Entity.h"
#include "GameWindow.h"


class NPC : public Entity
{
public:
	//TODO lägg till interactfunktionen
	NPC(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&, std::string);
	NPC() = delete;
	NPC(const NPC&) = delete;
	NPC& operator=(const NPC&) = delete;

	void update() override;
	void render(GameWindow&) override;
	void talk() const;
private:
	sf::Sprite sprite_;
	std::string conversation_;
};
