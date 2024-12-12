#include<iostream>

using namespace std;

//interfete -> o clasa ce contine DOAR functii virtuale pure si trebuie neaparat implementate aceste metode in toti copiii

//clase abstracte -> clase ce contin cel PUTIN 1 fct. virtuala pura; clasele abstracte NU pot fi instantiate;

class Vietate {
	string taraOrigine;
public:
	Vietate() {
		this->taraOrigine = "unknownCountry";
	}

	Vietate(string taraOrigine) {
		this->taraOrigine = taraOrigine;
	}

	virtual string ceMananca() = 0; 	//functie virtuala pura;
};

//interfata
class IProprietar {
	virtual void numeProprietar() = 0;
};

class Animal : public Vietate, IProprietar {
	const string identificator;
	double KG;
	string culoare; 
	int varsta;

public:
	Animal() :identificator("323223232332"), Vietate() {
		this->KG = 0.0;
		this->culoare = "unknown";
		this->varsta = 0;
	}

	Animal(const string identificator, double KG, string culoare, int varsta, string taraOrigine) :identificator(identificator), Vietate(taraOrigine) {
		this->KG = KG;
		this->culoare = culoare;
		this->varsta = varsta;
	}

	friend ostream& operator<<(ostream& out, const Animal& a) {
		out << "Identificator: " << a.identificator << " KG: " << a.KG << " culoare: " << a.culoare << " varsta: " << a.varsta << endl;

		return out;
	}

	virtual void scoateSunet() //virtual ne ajuta sa SUPRASCRIEM o functie in copii
	{
		cout << "sunet animal" << endl;
	}

	string ceMananca() override {
		return "mancare";
	}

	void numeProprietar() override {
		cout << "Unknown" << endl;
	}
};


class Pisica : public Animal {
public:
	Pisica() :Animal() {

	}

	Pisica(const string identificator, double KG, string culoare, int varsta, string taraOrigine)
		:Animal(identificator, KG, culoare, varsta, taraOrigine) {
	}

	void scoateSunet() override {
		cout << "miau miau" << endl;
	}

	string ceMananca() override {
		return "boabe";
	}

	void numeProprietar() override {
		cout << "Maria" << endl;
	}
};

class Caine : public Animal {
public:
	Caine() :Animal() {

	}

	Caine(const string identificator, double KG, string culoare, int varsta, string taraOrigine)
		:Animal(identificator, KG, culoare, varsta, taraOrigine) {
	}

	void scoateSunet() override {
		cout << "ham ham" << endl;
	}

	string ceMananca() override {
		return "mamaliga";
	}

	void numeProprietar() override {
		cout << "Ion" << endl;
	}
};

class Cal : public Animal {
public:
	Cal() :Animal() {

	}

	Cal(const string identificator, double KG, string culoare, int varsta, string taraOrigine)
		:Animal(identificator, KG, culoare, varsta, taraOrigine) {
	}

	void scoateSunet() override {
		cout << "Iiii-ho-ho" << endl;
	}

	string ceMananca() override {
		return "fan";
	}

	void numeProprietar() override {
		cout << "Vasile" << endl;
	}
};

void main() {
	//polimorfism
	//supraincarcare 
	// => doar numele functiei este la fel si parametrii pot fi in orice ordine si de orice tip
	//suprascriere - se aplica la mostenire - 
	// => antetul functiei trebuie sa fie acelasi mereu...diferenta este in ce o sa faca metoda
	//(ai nevoie de functii virtuale)

	Animal animal("121", 335.55, "rosu", 3, "ROU");
	Pisica pisica("56565", 5.66, "negru", 1, "ROU");
	Caine caine("112111", 11.3, "alb", 2, "ROU");
	Cal cal("67777", 1200.88, "maro", 5, "USA");

	//early-binding - stii de la compilare ce se afiseaza
	pisica.scoateSunet();

	Animal animal2 = pisica;
	cout << animal2;
	animal2.scoateSunet();
	cout << endl;

	//late-binding -  stii abia la runtime ce se afiseaza - te fol. de pointeri!!!!!!!!
	Animal** panimale = new Animal * [4];
	panimale[0] = &animal;
	panimale[1] = &pisica;
	panimale[2] = &caine;
	panimale[3] = &cal;

	cout << "\n\n=======\n\n";
	for (int i = 0; i < 4; i++) {
		(*panimale[i]).scoateSunet();

		cout << (*panimale[i]).ceMananca() << endl;

		(*panimale[i]).numeProprietar();
		cout << "\n\n=======\n\n";
	}
}