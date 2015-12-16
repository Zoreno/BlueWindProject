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

#include <Windows.h>
#include <fstream>
#include "Application.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	try
	{
		Application app;
		app.run();
	}
	catch (const exception& e)
	{
		ofstream crashLogStream;
		crashLogStream.open("crashlog.txt", std::ofstream::out);
		if (crashLogStream.is_open())
		{
			crashLogStream << e.what() << endl;
			crashLogStream.close();
		}
	}
	
	return 0;
}

/*
* SLUT PÅ FILEN Main.cpp
*/