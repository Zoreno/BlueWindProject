/*
* IDENTIFIERING
*
* Filnamn:    Game.h
* Enhetsnamn: Game
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar ett spel
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/
#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <string>
#include "Frame.h"
#include "GameWindow.h"
#include "TextureHandler.h"
#include "Universe.h"
#include "Player.h"
#include "UserInterface.h"

/*
* KLASS GameState
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Sparar viktiga framsteg i spelet
*
* KONSTRUKTORER
*
* GameState() = default
*
* DATAMEDLEMMAR
*
* bridge1Built : Anger om första bron är byggd
* bridge2Built : Anger om andra bron är byggd
* minotaurDead : Anger om minotauren i andra världen är dödad
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class GameState
{
public:
	GameState() = default;
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;
	bool bridge1Built{ false };
	bool minotaurDead{ false };
	bool bridge2Built{ false };

	std::string toString();
}; //Class GameState


/*
   * KLASS Game
   *
   * BASKLASSER
   *
   * Frame
   *
   * BESKRIVNING
   *
   * En klass som representerar många viktiga funktionaliteter i spelet.
   *
   * KONSTRUKTORER
   *
   * Game(Application*, bool = false)
   *
   * DATAMEDLEMMAR
   *
   * textureHandler_ :	Spelets texturhanterare
   * universe_ :		Bygger upp spelaruniversum
   * player_ :			Spelaren skapas
   * ui_ :				User interface skapas
   * gameState_ :		Tillståndet för spelet lagras här
   *
   * REVISIONSBERÄTTELSE
   *
   * Revision     Datum   Förändringar
   *
   * 1            151120  Ursprungsversion
   *
   */

class Game : public Frame
{
public:
	Game(Application*, bool = false);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void update() override;
	void render(GameWindow&) override;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void saveGame();
	void loadGame();

	Player* getPlayer();
	Application* getApp();
	UserInterface* getUserInterface();
	GameState* getGameState();
	sf::Texture& getTexture(const std::string&);
private:
	TextureHandler textureHandler_;
	Universe universe_;
	Player player_;
	UserInterface ui_;
	GameState gameState_;
};