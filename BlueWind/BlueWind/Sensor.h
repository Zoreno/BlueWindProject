/* IDENTIFIERING
*
* Filnamn:    Sensor.h
* Enhetsnamn: Sensor
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en sensor i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include "Entity.h"
#include "GameWindow.h"
#include <functional>

/*
* KLASS SoundHandler
*
* BASKLASSER
*
* Entity
*
* BESKRIVNING
*
* Klassen representerar sensorer i spelet. Sensorer triggar callbackfunktioner när spelaren närmar sig.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Sensor(int, std::string, sf::Vector2f, World*, std::function<void(World*)>, sf::Texture&)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* callback_:		Callbackfunktion som triggas av sensorn.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Game;

class Sensor : public Entity
{
public:
	Sensor(int, std::string, sf::Vector2f, World*, std::function<void(World*)>, sf::Texture&);
	Sensor() = delete;
	Sensor(const Sensor&) = delete;
	Sensor& operator=(const Sensor&) = delete;

	void update() override;
	void render(GameWindow&) override;
	void trigger();

	void die() override;
private:
	std::function<void(World*)> callback_;
};//class Sensor

   /*
   * SLUT PÅ FILEN Sensor.h
   */