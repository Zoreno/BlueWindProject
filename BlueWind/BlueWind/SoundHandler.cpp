/* 
* IDENTIFIERING
*
* Filnamn:    SoundHandler.cpp
* Enhetsnamn: SoundHandler
* Typ:        Definitioner hörande till klass SoundHandler
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen SoundHandler.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include "SoundHandler.h"

using namespace std;

/*
* KONSTRUKTOR SoundHandler()
*
* BESKRIVNING
*
* Denna konstruktor skapar en ljudhanterare genom anrop av loadMusic och loadSound.
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

SoundHandler::SoundHandler()
{
	loadMusic("menuMusic", "res/sounds/menuMusic.ogg");
	loadMusic("gameOverMusic", "res/sounds/gameOverMusic.ogg");
	loadMusic("gameWonMusic", "res/sounds/gameWonMusic.ogg");
	loadMusic("world0Music", "res/sounds/world0Music.ogg");
	loadMusic("world1Music", "res/sounds/world1Music.ogg");
	loadMusic("world2Music", "res/sounds/world2Music.ogg");
	loadMusic("world3Music", "res/sounds/world3Music.ogg");
	loadMusic("world4Music", "res/sounds/world4Music.ogg");

	loadSound("itemAdded", "res/sounds/itemAdded.ogg");
	loadSound("menuClick", "res/sounds/menuClick.ogg");
}

/*
* DESTRUKTOR SoundHandler::~SoundHandler()
*
* BESKRIVNING
*
* Destruerar ljudhanteraren.
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

SoundHandler::~SoundHandler()
{
	while (!sounds_.empty())
	{
		auto it = sounds_.begin();
		delete it->second;
		sounds_.erase(it);
	}

	while (!music_.empty())
	{
		auto it = music_.begin();
		delete it->second;
		music_.erase(it);
	}
}

/*
* FUNKTION SoundHandler::playSound(const std::string& soundName)
*
* BESKRIVNING
*
* Spelar upp aktuell ljudeffekt.
*
* INDATA
*
* soundName:	Namn på ljudet som ska spelas upp.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void SoundHandler::playSound(const std::string& soundName)
{
	currentSound_.setBuffer(*sounds_.find(soundName)->second);
	currentSound_.play();
}

/*
* FUNKTION SoundHandler::playMusic(const std::string& musicName)
*
* BESKRIVNING
*
* Spelar upp aktuellt musikspår.
*
* INDATA
*
* musicName:	Namn på musikslingan som ska spelas upp.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void SoundHandler::playMusic(const std::string& musicName)
{
	if (currentMusic_ != musicName)
	{
		stopMusic();
		music_.find(musicName)->second->play();
		music_.find(musicName)->second->setLoop(true);
		currentMusic_ = musicName;
	}
}

/*
* FUNKTION SoundHandler::stopMusic()
*
* BESKRIVNING
*
* Stoppar uppspelning av aktuell musikspår.
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void SoundHandler::stopMusic()
{
	for (auto it : music_)
	{
		it.second->stop();
	}
	
}

/*
* FUNKTION SoundHandler::loadSound(const std::string& soundName, const std::string& fileName)
*
* BESKRIVNING
*
* Laddar in en ljudeffekt från fil.
*
* INDATA
*
* soundName:	Namn på ljudeffekten som ska laddas in.
* fileName:		Namn på filen som slingan ska läsas in från.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void SoundHandler::loadSound(const std::string& soundName, const std::string& fileName)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile(fileName))
	{
		throw SoundException("Kunde inte ladda in ljud från fil:" + fileName);
	}
	sounds_.emplace(soundName, soundBuffer);
}

/*
* FUNKTION SoundHandler::loadMusic(const std::string& musicName, const std::string& fileName)
*
* BESKRIVNING
*
* Laddar in en ljudslinga från fil.
*
* INDATA
*
* musikName:	Namn på musikslingan som ska laddas in.
* fileName:		Namn på filen som slingan ska läsas in från.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void SoundHandler::loadMusic(const std::string& musicName, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile(fileName))
	{
		throw SoundException("Kunde inte ladda in musik från fil:" + fileName);
	}
	music_.emplace(musicName, music);
}

/*
* SLUT PÅ FILEN SoundHandler.cpp
*/