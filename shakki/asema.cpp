#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_lauta[i][j] = NULL;

	_lauta[0][0] = vt;
	_lauta[1][0] = vr;
	_lauta[2][0] = vl;
	_lauta[3][0] = vd;
	_lauta[4][0] = vk;
	_lauta[5][0] = vl;
	_lauta[6][0] = vr;
	_lauta[7][0] = vt;

	//Sotilaat
	for (int i = 0; i < 8; i++)
	{
		_lauta[i][1] = vs;
		_lauta[i][6] = ms;
	}

	_lauta[0][7] = mt;
	_lauta[1][7] = mr;
	_lauta[2][7] = ml;
	_lauta[3][7] = md;
	_lauta[4][7] = mk;
	_lauta[5][7] = ml;
	_lauta[6][7] = mr;
	_lauta[7][7] = mt;
}


void Asema::paivitaAsema(Siirto* siirto)
{
	if (siirto->onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL;
			_lauta[6][0] = vk;
			_lauta[7][0] = NULL;
			_lauta[5][0] = vt;
		}
		if (_siirtovuoro == 1) {
			_lauta[4][7] = NULL;
			_lauta[6][7] = mk;
			_lauta[7][7] = NULL;
			_lauta[5][7] = mt;
		}
	}
	else if (siirto->onkoPitkälinna()) {
		if (_siirtovuoro == 0) {
			_lauta[4][0] = NULL;
			_lauta[2][0] = vk;
			_lauta[0][0] = NULL;
			_lauta[3][0] = vt;

			if (_siirtovuoro == 1) {
				_lauta[4][7] = NULL;
				_lauta[2][7] = mk;
				_lauta[0][7] = NULL;
				_lauta[3][7] = mt;
			}
		}
		else {
			int alkuRiviInt;
			int alkuSarakeInt;
			int loppuRiviInt;
			int loppuSarakeInt;
			
			alkuRiviInt = siirto->getAlkuruutu().getRivi();
			alkuSarakeInt = siirto->getAlkuruutu().getSarake();
			Nappula* nappula = _lauta[alkuSarakeInt][alkuRiviInt];

			loppuRiviInt = siirto->getLoppuruutu().getRivi();
			loppuSarakeInt = siirto->getLoppuruutu().getSarake();

			_lauta[alkuSarakeInt][alkuRiviInt] = NULL;
			_lauta[loppuSarakeInt][loppuRiviInt] = nappula;

			if (siirto->_miksikorotetaan != NULL)
				_lauta[loppuSarakeInt][loppuRiviInt] = siirto->_miksikorotetaan;

			if (nappula->getKoodi() == VK) {
				_onkoValkeaKuningasLiikkunut = true;
			}
			if (nappula->getKoodi() == MK) {
				_onkoMustaKuningasLiikkunut = true;
			}

			if (nappula->getKoodi() == VT && alkuSarakeInt == 7 && alkuRiviInt == 0) {
				_onkoValkeaKTliikkunut = true;
			}
			if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 0) {
				_onkoValkeaDTliikkunut = true;
			}
			if (nappula->getKoodi() == MT && alkuSarakeInt == 7 && alkuRiviInt == 7) {
				_onkoMustaKTliikkunut = true;
			}
			if (nappula->getKoodi() == VT && alkuSarakeInt == 0 && alkuRiviInt == 7) {
				_onkoMustaDTliikkunut = true;
			}
		}
		if (_siirtovuoro == 0)
			_siirtovuoro = 1;
		else
			_siirtovuoro = 0;
	}
}



int Asema::getSiirtovuoro() 
{
	return 0;
}


void Asema::setSiirtovuoro(int vuoro) 
{
	
}


bool Asema::getOnkoValkeaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKuningasLiikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoValkeaKTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaDTliikkunut() 
{
	return false;
}


bool Asema::getOnkoMustaKTliikkunut() 
{
	return false;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
Lähetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla estämässä vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitkiä linjoja daami, torni ja lähetti
*/
double Asema::evaluoi() 
{
	return 0;

	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
{
	return 0;
	
}


bool Asema::onkoAvausTaiKeskipeli(int vari) 
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä
	
	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1
	

}


double Asema::nappuloitaKeskella(int vari) 
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa
	
	//valkeille ydinkeskusta

	
	
	//valkeille laitakeskusta
	


	//mustille ydinkeskusta
	
	//mustille laitakeskusta
	
}


double Asema::linjat(int vari) 
{
	return 0;
	
	//valkoiset
	
	//mustat
	
}


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lisäsin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydessä
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
}
