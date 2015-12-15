/*
* IDENTIFIERING
*
* Filnamn:    Main.cpp
* Enhetsnamn: Main
* Typ:        Utgångspunkt för körning av programmet.
* Revision:   1
* Skriven av: Joakim Bertils
*
*
* BESKRIVNING
*
* Denna fil kör applikationen som tillhandahåller spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151112  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include "Application.h"

using namespace std;

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
	

	return 0;
}

/*
* SLUT PÅ FILEN Main.cpp
*/