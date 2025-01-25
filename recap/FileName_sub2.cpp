#include<iostream>
#include<map>
#include<vector>

using namespace std;

class Joc {
public:
	string titlu;
	int varstaMinima;
	double pret;

	Joc() {
		this->titlu = "random game";
		this->varstaMinima = 5;
		this->pret = 0.0;
	}

	Joc(string titlu, int varstaMinima, double pret) {
		this->titlu = titlu;
		this->varstaMinima = varstaMinima;
		this->pret = pret;

	}

	friend ostream& operator<<(ostream& consolaOut, const Joc& j) {
		consolaOut << "Titlu: " << j.titlu << " varsta minima: " << j.varstaMinima << " pret: " << j.pret << endl;
		return consolaOut;
	}

	virtual void exempluVirtualizare() {
		cout << "sunt in clasa Joc" << endl;
	}
};

class Joc3D :public Joc {

public:

	void exempluVirtualizare() override {
		cout << "sunt in clasa Joc3D" << endl;
	}

};
class Magazin {
	const int ID;

	string nume;
	int nrJocuri;
	Joc* jocuri;

public:
	Magazin() :ID(0) {
		this->nrJocuri = 0;
		this->jocuri = nullptr;
		this->nume = "random Magazin";
	}

	Magazin(int ID, string nume, int nrJocuri, Joc* jocuri) :ID(ID) {
		this->nume = nume;
		this->nrJocuri = nrJocuri;

		this->jocuri = new Joc[nrJocuri];
		for (int i = 0; i < nrJocuri; i++) {
			this->jocuri[i] = jocuri[i];
		}
	}

	Magazin(const Magazin& m) :ID(m.ID) {
		this->nume = m.nume;

		this->nrJocuri = m.nrJocuri;

		this->jocuri = new Joc[m.nrJocuri];
		for (int i = 0; i < m.nrJocuri; i++) {
			this->jocuri[i] = m.jocuri[i];
		}
	}

	Magazin& operator=(const Magazin& m) {
		if (this != &m) {
			this->nume = m.nume;

			this->nrJocuri = m.nrJocuri;

			delete[] jocuri; //evitare memory leaks

			this->jocuri = new Joc[m.nrJocuri];
			for (int i = 0; i < m.nrJocuri; i++) {
				this->jocuri[i] = m.jocuri[i];
			}
		}

		return *this;
	}

	~Magazin() {
		delete[] jocuri;
	}

	friend ostream& operator<<(ostream& consolaOut, const Magazin& m) {
		consolaOut << "Nume: " << m.nume << " ID: " << m.ID << " " << m.nrJocuri << " jocuri: " << endl;

		for (int i = 0; i < m.nrJocuri; i++) {
			consolaOut << m.jocuri[i];
		}

		return consolaOut;
	}

	int getID() {
		return this->ID;
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	int getNrJocuri() {
		return this->nrJocuri;
	}

	void setNrJocuri(int nrJocuri) {
		this->nrJocuri = nrJocuri;
	}

	Joc* getJocuri() {
		return this->jocuri;
	}

	void setJocuri(int nrJocuri, Joc* jocuri) {
		this->nrJocuri = nrJocuri;

		delete[] this->jocuri;//evitare memory leaks;

		this->jocuri = new Joc[nrJocuri];
		for (int i = 0; i < nrJocuri; i++) {
			this->jocuri[i] = jocuri[i];
		}
	}

	Joc operator[](int index) {
		if (index >= 0 && index < this->nrJocuri) {
			return this->jocuri[index];
		}
		else {
			throw new exception("bad index provided");
		}
	}

	void operator+=(Joc j) {
		Joc* aux = new Joc[nrJocuri + 1];

		for (int i = 0; i < nrJocuri; i++) {
			aux[i] = jocuri[i];
		}

		aux[nrJocuri] = j;

		delete[] jocuri;//evitare memory leaks

		this->jocuri = aux;

		this->nrJocuri++;
	}

	void operator-=(Joc j) {
		int index = -1;
		for (int i = 0; i < nrJocuri; i++) {
			if (this->jocuri[i].titlu == j.titlu) {
				index = i;
				break;
			}
		}

		if (index > 0) {
			Joc* aux = new Joc[nrJocuri - 1];

			for (int i = 0; i < nrJocuri; i++) {
				if (i != index) {
					aux[i] = jocuri[i];
				}
			}

			delete[] jocuri;//evitare memory leaks

			this->jocuri = aux;

			this->nrJocuri--;
		}
	}

	void sumaTotala() {
		double total = 0.0;

		for (int i = 0; i < this->nrJocuri; i++) {
			total += this->jocuri[i].pret;
		}

		cout << total << endl;
	}


};

void main() {
	Joc j2("joc1", 5, 22.99);
	Joc j3("joc2", 5, 12.99);
	Joc j4("joc3", 12, 122.99);
	Joc j5("joc4", 12, 422.99);

	//virtualizare
	Joc j1;
	Joc3D j3d1;

	Joc** vectorDePointeri = new Joc * [2];
	vectorDePointeri[0] = &j1;
	vectorDePointeri[1] = &j3d1;

	for (int i = 0; i < 2; i++) {
		vectorDePointeri[i]->exempluVirtualizare();
	}



	//pereche(cheie, valoare)
	vector<Joc> v1;
	v1.push_back(j1);
	v1.push_back(j2);
	v1.push_back(j3);

	vector<Joc> v2;
	v2.push_back(j4);
	v2.push_back(j5);

	map<int, vector<Joc>> mapJocuriPerVarsta;
	map<int, vector<Joc>>::iterator iteratormapJocuriPerVarsta;

	mapJocuriPerVarsta.insert(pair<int, vector<Joc>>(5, v1));
	mapJocuriPerVarsta.insert(pair<int, vector<Joc>>(12, v2));

	for (iteratormapJocuriPerVarsta = mapJocuriPerVarsta.begin(); iteratormapJocuriPerVarsta != mapJocuriPerVarsta.end(); iteratormapJocuriPerVarsta++) {
		cout << "Pentru varsta: " << (*iteratormapJocuriPerVarsta).first << " se pot vinde jocurile: " << endl;
		
		for (int i = 0; i < (*iteratormapJocuriPerVarsta).second.size(); i++) {
			cout << (*iteratormapJocuriPerVarsta).second[i];
		}

		cout << endl;
	}
}