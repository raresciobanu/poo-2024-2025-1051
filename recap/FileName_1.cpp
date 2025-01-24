#include<iostream>
#include<map>
#include<fstream>

using namespace std;

enum TipFrizerie {
	salon,
	clasica,
	barberShop
};

class Serviciu {

public:

	string denumireServiciu = "serviciu_default";

	Serviciu(string denumireServiciu) {
		this->denumireServiciu = denumireServiciu;
	}

	virtual double calculPret() = 0;

	friend ostream& operator<<(ostream& consolaOut, const Serviciu& s) {
		consolaOut << "Denumire serviciu: " << s.denumireServiciu;
		return consolaOut;
	}

	friend ofstream& operator<<(ofstream& fisOut, const Serviciu& s) {
		fisOut << s.denumireServiciu;
		return fisOut;
	}
};

class Tuns :public Serviciu {
public:
	Tuns() :Serviciu("tuns") {
	}

	double calculPret() {
		return 50;
	}
};

class Frezat :public Serviciu {
public:
	Frezat() :Serviciu("frezat") {
	}

	double calculPret() {
		return 66.5;
	}
};

class Barbierit :public Serviciu {
public:
	Barbierit() :Serviciu("barbierit") {
	}

	double calculPret() {
		return 30.5;
	}
};


class Frizerie {
	Serviciu** servicii;
	int nrServicii;
private:
	const int ID;
	TipFrizerie tipFrizerie;
protected:
	char* denumire;
	int nrFrizeri;
public:
	static int lungimeMinimaDenumire;


	Frizerie() :ID(0) {
		this->tipFrizerie = salon;

		this->nrFrizeri = 0;

		this->denumire = new char[strlen("denumireRandom") + 1];
		strcpy_s(this->denumire, strlen("denumireRandom") + 1, "denumireRandom");

		this->nrServicii = 0;
		this->servicii = nullptr;
	}

	Frizerie(const char* denumire, TipFrizerie tipFrizerie, int nrFrizeri) :ID(98765) {
		this->tipFrizerie = tipFrizerie;

		this->nrFrizeri = nrFrizeri;

		this->denumire = new char[strlen(denumire) + 1];
		strcpy_s(this->denumire, strlen(denumire) + 1, denumire);


		//initializati ce nu vi se da ca input
		this->nrServicii = 0;
		this->servicii = nullptr;
	}

	Frizerie(int ID, const char* denumire, TipFrizerie tipFrizerie, int nrFrizeri, int nrServicii, Serviciu** servicii) :ID(ID) {
		this->tipFrizerie = tipFrizerie;

		this->nrFrizeri = nrFrizeri;

		this->denumire = new char[strlen(denumire) + 1];
		strcpy_s(this->denumire, strlen(denumire) + 1, denumire);


		//initializati ce nu vi se da ca input
		this->nrServicii = nrServicii;
		this->servicii = new Serviciu * [nrServicii];
		for (int i = 0; i < nrServicii; i++) {
			this->servicii[i] = servicii[i];
		}
	}

	Frizerie(const Frizerie& f) :ID(f.ID) {
		this->tipFrizerie = f.tipFrizerie;

		this->nrFrizeri = f.nrFrizeri;

		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy_s(this->denumire, strlen(f.denumire) + 1, f.denumire);

		this->nrServicii = f.nrServicii;
		this->servicii = new Serviciu * [f.nrServicii];
		for (int i = 0; i < f.nrServicii; i++) {
			this->servicii[i] = f.servicii[i];
		}
	}

	Frizerie& operator=(const Frizerie& f) {
		if (this != &f) {
			this->tipFrizerie = f.tipFrizerie;

			this->nrFrizeri = f.nrFrizeri;

			delete[] this->denumire; //evitare memory leaks;

			this->denumire = new char[strlen(f.denumire) + 1];
			strcpy_s(this->denumire, strlen(f.denumire) + 1, f.denumire);


			delete[] this->servicii; //evitare memory leaks;

			this->nrServicii = f.nrServicii;
			this->servicii = new Serviciu * [f.nrServicii];
			for (int i = 0; i < f.nrServicii; i++) {
				this->servicii[i] = f.servicii[i];
			}
		}

		return *this;
	}

	~Frizerie() {
		delete[] this->denumire;
		delete[] this->servicii;
	}

	static void setLungimeMinimaDenumire(int lungime) {
		lungimeMinimaDenumire = lungime;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(const char* denumire) {
		if (strlen(denumire) > lungimeMinimaDenumire) {
			delete[] this->denumire; //evitare memory leaks;

			this->denumire = new char[strlen(denumire) + 1];
			strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		}
		else {
			throw new exception("denumirea nu are lungimea minima: " + lungimeMinimaDenumire);
		}

	}

	friend ostream& operator<<(ostream& consolaOut, const Frizerie& f) {
		consolaOut << "ID: " << f.ID << " denumire: " << f.denumire << " nrFrizeri: " << f.nrFrizeri << " TIP frizerie: " << f.tipFrizerie
			<< " lungimeMinima: " << f.lungimeMinimaDenumire << endl;

		consolaOut << "nrServicii: " << f.nrServicii << endl;
		for (int i = 0; i < f.nrServicii; i++) {
			consolaOut << *f.servicii[i] << endl;
		}

		return consolaOut;
	}

	friend ofstream& operator<<(ofstream& fisOut, const Frizerie& f) {
		fisOut << f.ID << endl;

		fisOut << f.denumire << endl;

		fisOut << f.nrFrizeri << endl;

		fisOut << f.tipFrizerie << endl;

		fisOut << f.nrServicii << endl;

		for (int i = 0; i < f.nrServicii; i++) {
			fisOut << *f.servicii[i] << endl;
		}

		return fisOut;
	}

	friend istream& operator>>(istream& consolaIn, Frizerie& f) {
		cout << "NrFrizeri: "; consolaIn >> f.nrFrizeri;

		int tipFrizerie;
		cout << "TIP frizerie: "; consolaIn >> tipFrizerie;
		switch (tipFrizerie)
		{
		case clasica:
		{
			f.tipFrizerie = clasica;
			break;
		}
		case salon:
		{
			f.tipFrizerie = salon;
			break;
		}
		case barberShop:
		{
			f.tipFrizerie = barberShop;
			break;
		}
		default:
			break;
		}


		cout << "Lungime minima: "; consolaIn >> f.lungimeMinimaDenumire; //optional-nu e nevoie sa schimbati var. statica

		char aux[100];
		consolaIn.ignore();
		cout << "Denumire: ";
		consolaIn.getline(aux, 100);

		delete[] f.denumire; //evitare memory leaks;

		f.denumire = new char[strlen(aux) + 1];
		strcpy_s(f.denumire, strlen(aux) + 1, aux);

		return consolaIn;
	}

	friend ifstream& operator>>(ifstream& fisIn, Frizerie& f) {
		int ID;
		fisIn >> ID;

		char aux[100];
		fisIn.ignore();

		fisIn.getline(aux, 100);

		delete[] f.denumire; //evitare memory leaks;

		f.denumire = new char[strlen(aux) + 1];
		strcpy_s(f.denumire, strlen(aux) + 1, aux);

		fisIn >> f.nrFrizeri;

		int tipFrizerie;
		fisIn >> tipFrizerie;
		switch (tipFrizerie)
		{
		case clasica:
		{
			f.tipFrizerie = clasica;
			break;
		}
		case salon:
		{
			f.tipFrizerie = salon;
			break;
		}
		case barberShop:
		{
			f.tipFrizerie = barberShop;
			break;
		}
		default:
			break;
		}

		fisIn >> f.nrServicii;

		delete[] f.servicii;

		f.servicii = new Serviciu * [f.nrServicii];

		string aux2;
		for (int i = 0; i < f.nrServicii; i++) {
			fisIn >> aux2;

			if (aux2 == "tuns") {
				f.servicii[i] = new Tuns();
			}
			else if (aux2 == "frezat") {
				f.servicii[i] = new Frezat();
			}
			else {
				f.servicii[i] = new Barbierit();
			}
		}

		return fisIn;
	}

	void serviciiSolicitate() {
		double total = 0.0;
		for (int i = 0; i < nrServicii; i++) {
			total += this->servicii[i]->calculPret();
		}

		cout << "serviciiSolicitate: " << total << endl;
	}

	void operator+=(Serviciu& s) {
		Serviciu** aux = new Serviciu * [nrServicii + 1]; //N+1 Serviciu()

		for (int i = 0; i < nrServicii; i++) {
			aux[i] = servicii[i];
		}

		aux[nrServicii] = &s;

		delete[] servicii;

		nrServicii++;

		servicii = aux;
	}

	void operator-=(Serviciu& s) {
		int count = 0;
		for (int i = 0; i < nrServicii; i++) {
			if (servicii[i]->denumireServiciu == s.denumireServiciu) {
				count++;
			}
		}

		if (count >= 0) {
			Serviciu** aux = new Serviciu * [nrServicii - count];

			int k = 0;
			for (int i = 0; i < nrServicii; i++) {
				if (servicii[i]->denumireServiciu != s.denumireServiciu) {
					aux[k++] = servicii[i];
				}
			}

			delete[] servicii;

			nrServicii -= count;

			servicii = aux;
		}
	}
};

int Frizerie::lungimeMinimaDenumire = 4;

void main() {
	Frizerie f1;
	Frizerie f2("La Mihai", TipFrizerie::barberShop, 3);
	Frizerie f3 = f2;
	Frizerie::setLungimeMinimaDenumire(5);
	f3.setDenumire("El Saloon");
	cout << f3.getDenumire() << endl;

	Tuns t1, t2, t3;
	Barbierit b1, b2, b3;
	Frezat fr1, fr2, fr3;

	f3 += t1;
	f3 += t2;
	f3 += t3;
	f3 += b1;
	f3 += b2;
	f3 += b3;
	f3 += fr1;
	f3 += fr2;
	f3 += fr3;

	cout << f3 << endl;
	f3.serviciiSolicitate();

	//Frizerie f4;
	//cin >> f4;
	//cout << f4 << endl;

	cout << "\nmap STL\n";

	//pereche(cheie, valoare)
	map<string, double> mapServiciuPret;
	map<string, double>::iterator iteratorServiciuPret;

	mapServiciuPret.insert(pair<string, double>("tuns", 50));
	mapServiciuPret.insert(pair<string, double>("frezat", 66.5));
	mapServiciuPret.insert(pair<string, double>("barbierit", 30.5));

	for (iteratorServiciuPret = mapServiciuPret.begin(); iteratorServiciuPret != mapServiciuPret.end(); iteratorServiciuPret++) {
		cout << "La cheia: " << (*iteratorServiciuPret).first << " se afla valoarea: " << (*iteratorServiciuPret).second << endl;
	}

	ofstream frizeriiOut("frizerii.txt", ios::out);
	if (frizeriiOut.is_open()) {
		frizeriiOut << f1;
		frizeriiOut << f2;
		frizeriiOut << f3;

		frizeriiOut.close();
	}
	else {
		cout << "Fisierul frizerii.txt nu poate fi deschis pentru scriere.\n";
	}

	cout << endl << endl << "FISIERE" << endl << endl;

	ifstream frizeriiIn("frizerii.txt", ios::in);
	if (frizeriiIn.is_open()) {
		Frizerie temp;

		frizeriiIn >> temp;
		cout << temp << endl;

		frizeriiIn >> temp;
		cout << temp << endl;

		frizeriiIn >> temp;
		cout << temp << endl;

		frizeriiIn.close();
	}
	else {
		cout << "Fisierul frizerii.txt nu poate fi deschis pentru citire.\n";
	}

}