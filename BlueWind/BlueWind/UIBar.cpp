/*
* IDENTIFIERING
*
* Filnamn:    UIBar.cpp
* Enhetsnamn: UIBar
* Typ:        Definitioner hörande till klass UIBar
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UIBar.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <string>
#include "UIBar.h"

using namespace std;

/*
* KONSTRUKTOR UIBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& postfix, UserInterface* uiPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en mätare.
*
* INDATA
*
* position:		Plats på skärm där mätaren ska ritas.
* size:			Storlek på mätaren.
* color:		Färg på mätaren.
* postfix:		Text som ska skrivas sist på mätaren.
* uiPtr:		Pekare till användargränssnittet som mätaren är en del av.
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
* 
*/

UIBar::UIBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, const std::string& postfix, UserInterface* uiPtr)
	:fillLevel_{ 1 }, 
	position_ {position}, 
	size_ {size}, 
	color_{color}, 
	postfix_ {postfix}, 
	ui_{uiPtr}
{}

/*
* FUNKTION UIBar::update(int current, int max)
*
* BESKRIVNING
*
* Uppdaterar mätaren.
*
* INDATA
*
* current:		Nuvarande värdet på representerad storhet.
* max:			Maximala värdet på representerad storhet.
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: std::string
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UIBar::update(int current, int max)
{
	text_ = to_string(current) + '/' + to_string(max);
	if (max != 0 && current > 0)
	{
		fillLevel_ = static_cast<float>(current) / static_cast<float>(max);
		return;
	}
	fillLevel_ = 0;
}

/*
* FUNKTION UIBar::render(GameWindow& window)
*
* BESKRIVNING
*
* Ritar mätaren.
*
* INDATA
*
* window:		Fönster som mätaren ska ritas på.
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: sfml-grafik
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UIBar::render(GameWindow & window)
{
	sf::RectangleShape border{ size_ };
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::White);
	border.setOutlineThickness(2.0f);

	sf::RectangleShape fill{ sf::Vector2f(size_.x * fillLevel_, size_.y) };
	fill.setOutlineColor(sf::Color::Transparent);
	fill.setFillColor(color_);

	border.setPosition(position_);
	fill.setPosition(position_);

	window.draw(border);
	window.draw(fill);

	sf::Text text{ text_ + postfix_, ui_->getFont(), 16 };
	text.setPosition(position_ + sf::Vector2f(2, 0));
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	window.draw(text);
}

/*
* SLUT PÅ FILEN UIBar.cpp
*/