#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	bool vari = false;

	for (int i = 7; i >= 0; i--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		wcout << i + 1;

		for (int j = 0; j < 8; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vari ? 96 : 240);

			if (_asema->_lauta[j][i] != NULL)
			{
				wcout << " " << _asema->_lauta[j][i]->getUnicode() << " ";
			}
			else
			{
				wcout << "   ";
			}

			if (j < 7)
				vari = !vari;
		}

		wcout << "\n";
	}

	wcout << "  a  b  c  d  e  f  g  h ";
}

Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;

	int koneenVari;

	wcout << "\nSiirto: ";
	string komento;
	cin >> komento;

	if (komento == siirto.onkoLyhytLinna())
	{
		siirto = Siirto(true, false);
	}
	else if (komento == "0-0-0")
	{
		siirto = Siirto(false, true);
	}
	else
	{
		int i = 0;

		Ruutu ruudut[2];

		for (int j = 0; j < 2; i += 3, j++)
		{
			int sarakeInt = komento[i] - 'a';
			int riviInt = komento[i + 1] - '1';

			//riviInt = koneenVari ? riviInt : 7 - riviInt;

			if (riviInt < 0 || riviInt > 7 || sarakeInt < 0 || sarakeInt > 7)
				return siirto;

			ruudut[j] = Ruutu(riviInt, sarakeInt);
		}

		int miksikorotetaan = 0;
		
		if (komento.length() == 6)
		{
			// T/R/L/D/K
			char a = komento[5];
			switch (a)
			{
			case 'r':
				miksikorotetaan = 0;
				break;
			case 'h':
				miksikorotetaan = 1;
				break;
			case 'b':
				miksikorotetaan = 2;
				break;
			case 'q':
				miksikorotetaan = 3;
				break;
			case 'k':
				miksikorotetaan = 4;
				break;
			}

		}

		siirto = Siirto(ruudut[0], ruudut[1]);
	}

	return siirto;
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
