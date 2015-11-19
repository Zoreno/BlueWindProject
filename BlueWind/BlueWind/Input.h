#pragma once

#include <map>

class Input
{
public:
	std::map<char, bool> pressedButtons_;

	Input();
	void update();

};