#pragma once

#include "Entity.h"
#include "GameWindow.h"
#include <functional>

class Game;

class Sensor : public Entity
{
public:
	Sensor(int, std::string, sf::Vector2f, World*, std::function<void(World*)>, const std::string&);
	Sensor() = delete;
	Sensor(const Sensor&) = delete;
	Sensor& operator=(const Sensor&) = delete;

	void update() override;
	void render(GameWindow&) override;
	void trigger();

	void die() override;
private:
	std::function<void(World*)> callback_;
};
