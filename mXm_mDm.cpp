// mXm_mDm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"pch.h"
#include <iostream>
#include<fstream>
#include <string>
#include "Song.h"
#include<vector>
#include<list>
static std::vector<std::string> DEFAULT_VECTOR;
static std::list<Song> DEFAULT_LIST;
bool es_separador(char lletra) {
	/*Pre:cert Post:retorna cert si lletra és un separador, fals altrament*/
	bool separador = true;
	if ((lletra >= 'a' and lletra <= 'z') or (lletra >= 'A' && lletra <= 'Z') or (lletra >= '0' and lletra <= '9') or lletra == '%' or lletra == ':')
		separador = false;
	else { //considerem els caràcters especials catalans i castellans
		/*
		switch (lletra) {
		case '·': case 'ç': case 'Ç': case 'ñ': case'Ñ': case 'à': case 'á':case 'è': case
		'é': case'í': case'ò': case 'ó': case 'ú': case 'ï': case 'ü': separador = false; break;
		}
		*/
	}
	return separador;
}
void passar_separadors(std::ifstream & fitxer) {
	/*Pre: fitxer obert
	Post: s’han llegit tots els separadors */
	char lletra = ' '; //es pot cridar havent llegit eof
	while (!fitxer.eof() && es_separador(lletra)) {
		//std::cout << lletra;
		fitxer.get(lletra);
	}
	if (!fitxer.eof()) fitxer.unget(); //pot no ser necessari
}
void llegeixIdxAndCnt(std::ifstream & fitxer,char lletra,ushort &tdx, ushort &cnt, bool &trobat) {
	//pre:cert
  //post:tracta paraula de una canso llegin el idx i cnt
	std::string _idx = "";
	std::string _cnt = "";
	bool fi = false;
	while (!fitxer.eof() && !fi)
	{
		trobat = false;

		std::cout << "[";
		while (not trobat)// llegeix caracters idx
		{
			if ((lletra >= 'A' and lletra <= 'Z')) { fi = true; break; }
			if (lletra == ':') { trobat = true; }
			else {
				if (lletra != ',')
					_idx += lletra;
				std::cout << lletra;
				fitxer.get(lletra);
			}
		}
		if (!fi) {
			std::cout << " , ";
			lletra = fitxer.get();
			while (!fitxer.eof() && not es_separador(lletra))// llegeix caracters idx
			{
				_cnt += lletra;
				std::cout << lletra;
				fitxer.get(lletra);
			}
			//std::cout << _cnt;
			std::cout << "]";
			std::cout << "_idx= " << _idx << "  _cnt= " << _cnt << "  ";
			_idx = _cnt = "";
			passar_separadors(fitxer);
		}
		trobat = true;
	}
}

void llegeixCodis(std::ifstream & fitxer,char lletra, std::string &tdxmXm, ushort & tid, bool &trobat) {
	//pre:cert
		//post:tracta Codis de una canso llegin el idxmxm i tid
	std::string _idx = "";
	std::string _cnt = "";
	passar_separadors(fitxer);
	std::cout << "-->  ";
	while (!es_separador(lletra))// llegeix caracters idx
	{
		_idx += lletra;
		std::cout << lletra;
		fitxer.get(lletra);
	}
	std::cout << " , ";
	passar_separadors(fitxer);
	lletra = fitxer.get();
	while (not es_separador(lletra))// llegeix caracters idx
	{
		_cnt += lletra;
		std::cout << lletra;
		fitxer.get(lletra);
	}
	passar_separadors(fitxer);
	trobat = true;
	std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
void passar_paraula_c_s(std::ifstream& fitxer, bool &trobat, char opcio, std::vector<std::string> &sacParaules = DEFAULT_VECTOR) {
	/*Pre: fitxer vàlid i apunt de llegir el 1r carácter d’una paraula
	Post: s’ha llegit tota una paraula */
	char lletra = fitxer.get(); //lletra=cin.get();
	std::string paraula = "";
	ushort _idx;
	ushort _cnt;

	char ant = ' ';
	while (!trobat && !fitxer.eof() && !es_separador(lletra)) {
		if (opcio == 'c') {
			if (ant == '%' && lletra == 'i') {
				trobat = true;
				std::cout << "----------------------------------TROBAT OCURRENCIA-------------------------------------------------------------" << std::endl;
				fitxer.get(lletra);
			}
			ant = lletra;
		}
		else //tracta sac de paraules 
		{
			if ((lletra >= 'A' && lletra <= 'Z'))
			{
				trobat = true;
				fitxer.unget();
			}
			else paraula += lletra;
		}
		if (!trobat) {
			std::cout << lletra;
			fitxer.get(lletra); //lletra=cin.get();
		}
	}
	if (opcio == 'p')sacParaules.push_back(paraula);
	if (!fitxer.eof()) fitxer.unget(); //pot no ser necessari
}

void passar_paraula(std::ifstream& fitxer, bool &trobat, char opcio) {
	/*Pre: fitxer vàlid i apunt de llegir el 1r carácter d’una paraula
	Post: s’ha llegit tota una paraula */
	char lletra = fitxer.get(); //lletra=cin.get();
	std::string paraula;
	ushort _idx;
	ushort _cnt;
	while (!trobat && !fitxer.eof() && !es_separador(lletra)) {

		if (opcio == 'x') {//tracta codi canso
			llegeixCodis(fitxer, lletra, paraula, _cnt, trobat);
			break;

		}
		else
		{//tracta histograma canso
			llegeixIdxAndCnt(fitxer, lletra, _idx, _cnt, trobat);
			break;
		}
		std::cout << lletra;
		fitxer.get(lletra); //lletra=cin.get();
	}
	if (!fitxer.eof()) fitxer.unget(); //pot no ser necessari
}
///////////////////////////////////////////////////////////////
void passarComentaris(std::ifstream &fitxer) {
	passar_separadors(fitxer);
	bool trobat = false;
	while (!trobat && !fitxer.eof())
	{
		passar_paraula_c_s(fitxer, trobat, 'c');
		//if(!trobat)
		passar_separadors(fitxer);
	}
}

void passarSacParaules(std::ifstream &fitxer, std::vector<std::string>& sacParaules) {
	passar_separadors(fitxer);
	bool trobat = false;
	while (!trobat && !fitxer.eof())
	{
		passar_paraula_c_s(fitxer, trobat, 'p', sacParaules);
		passar_separadors(fitxer);
	}
}

void passarCansoCodi(std::ifstream &fitxer) {
	passar_separadors(fitxer);
	bool trobat = false;
	while (!fitxer.eof() && !trobat)
	{
		passar_paraula(fitxer, trobat, 'x');
		//passar_separadors(fitxer);
	}
}
void passarCansolletres(std::ifstream &fitxer) {
	passar_separadors(fitxer);
	bool trobat = false;
	while (!trobat && !fitxer.eof())
	{
		passar_paraula(fitxer, trobat, 'h');
		passar_separadors(fitxer);
	}
}
typedef unsigned short ushort;
void passaCansoSencer(std::ifstream & fitxer) {
	while (!fitxer.eof())
	{
		passarCansoCodi(fitxer);
		passarCansolletres(fitxer);
	}
}
int main()
{

	std::list<Song> myPlayList;
	std::vector<std::string> sacParaules;
	std::cout << "Entra el nom del fitxer: ";
	std::string nom_fitxer;
	std::cin >> nom_fitxer;
	std::ifstream fentrada(nom_fitxer.c_str());
	//std::string tid, std::string MSD_artist_name, std::string MSD_title, std::string mXm_tid, std::string mXm_artist_name, std::string mXm_title)

	/*Song song("kkdksd", "sdsdkjsd", "ssdsdsd", "asasas", "asasasa", "sdsdsdsd");
	song.addWord(1, 23);
	song.addWord(2, 26);
	song.addWord(3, 26);
	song.addWord(4, 26);
	song.addWord(5, 26);
	song.addWord(6, 26);
	song.addWord(7, 26);
	song.addWord(8, 26);

	std::list<ushort> _list = song.mostFrequentWordsIdxs();
	for (auto l : _list) {
		std::cout << l << std::endl;
	}
	*/

	if (fentrada.is_open()) {
		passarComentaris(fentrada);
		passarSacParaules(fentrada, sacParaules);
		passaCansoSencer(fentrada);
		for (auto p : sacParaules) {
			std::cout << p << "-";
		}
	}
	else
	{
		std::cout << "no s'ha obert correctament el fitxer" << std::endl;
	}
	std::cout << "Hello World!\n";
	//TODO :FIX LEE UNA CANCION DE MAS 

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
