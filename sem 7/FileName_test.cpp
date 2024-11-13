#include<iostream>

using namespace std;

class Vehicul {
	const int ID;
	char* marca;
	int anFabricatie;
	string culoare;

public:
	Vehicul() : ID(0) {
		this->marca = new char[strlen("marcaUnknown") + 1];
		strcpy_s(this->marca, strlen("marcaUnknown") + 1, "marcaUnknown");

		this->anFabricatie = 0;

		this->culoare = "unknownColor";
	}

	Vehicul(int ID, const char* marca, int anFabricatie, string culoare) :ID(ID) {
		this->marca = new char[strlen(marca) + 1];
		strcpy_s(this->marca, strlen(marca) + 1, marca);

		this->anFabricatie = anFabricatie;

		this->culoare = culoare;
	}

	Vehicul(int anFabricatie, string culoare) :ID(98) {
		if (anFabricatie < 1900) {
			throw new exception("anFabricatie>1900");
		}
		if (culoare.empty()) {
			throw new exception("culoare nu este definita");
		}

		this->anFabricatie = anFabricatie;

		this->culoare = culoare;

		this->marca = new char[strlen("marcaUnknown") + 1];
		strcpy_s(this->marca, strlen("marcaUnknown") + 1, "marcaUnknown");
	}

	Vehicul(const Vehicul& v) :ID(v.ID) {
		this->marca = new char[strlen(v.marca) + 1];
		strcpy_s(this->marca, strlen(v.marca) + 1, v.marca);

		this->anFabricatie = v.anFabricatie;

		this->culoare = v.culoare;
	}

	Vehicul& operator=(const Vehicul& v) {
		if (this != &v) {
			delete[] this->marca;//evitare memory leaks

			this->marca = new char[strlen(v.marca) + 1];
			strcpy_s(this->marca, strlen(v.marca) + 1, v.marca);

			this->anFabricatie = v.anFabricatie;

			this->culoare = v.culoare;
		}

		return *this;
	}

	~Vehicul() {
		delete[] this->marca;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v);
};

ostream& operator<<(ostream& out, const Vehicul& v) {
	out << "ID: " << v.ID << " MARCA: " << v.marca << " AN FABRICATIE: " << v.anFabricatie
		<< " CULOARE: " << v.culoare << endl;

	return out;
}

class Masina : public Vehicul {
	bool areAC;
	int nrDotari;
	string* dotari;

public:

	Masina(int ID, const char* marca, int anFabricatie, string culoare,
		bool areAC, int nrDotari, string* dotari) :Vehicul(ID, marca, anFabricatie, culoare) {

		this->areAC = areAC;
		this->nrDotari = nrDotari;

		this->dotari = new string[nrDotari];
		for (int i = 0; i < nrDotari; i++) {
			this->dotari[i] = dotari[i];
		}
	}

	Masina(const Masina& m) : Vehicul(m) {
		this->areAC = m.areAC;
		this->nrDotari = m.nrDotari;

		this->dotari = new string[m.nrDotari];
		for (int i = 0; i < m.nrDotari; i++) {
			this->dotari[i] = m.dotari[i];
		}
	}

	Masina& operator=(const Masina& m) {
		if (this != &m) {
			Vehicul::operator=(m);

			this->areAC = m.areAC;
			this->nrDotari = m.nrDotari;

			delete[] this->dotari; //evitam memory leaks
			this->dotari = new string[m.nrDotari];
			for (int i = 0; i < m.nrDotari; i++) {
				this->dotari[i] = m.dotari[i];
			}
		}

		return *this;
	}

	~Masina() {
		delete[] dotari;
	}

	friend ostream& operator<<(ostream& out, const Masina& m);
};

ostream& operator<<(ostream& out, const Masina& m) {
	out << (Vehicul)m;

	out << "Are AC: " << m.areAC << " NR dotari: " << m.nrDotari << " DOTARI: \n";
	for (int i = 0; i < m.nrDotari; i++) {
		out << m.dotari[i] << " ";
	}

	out << endl << "============" << endl;
	return out;
}

class Moto : public Vehicul {
	bool areAtas;

public:
	Moto(int ID, char* marca, int anFabricatie, string culoare,
		bool areAtas) :Vehicul(ID, marca, anFabricatie, culoare) {
		this->areAtas = areAtas;
	}

	friend ostream& operator<<(ostream& out, const Moto& m);
};

ostream& operator<<(ostream& out, const Moto& m) {
	out << (Vehicul)m;

	out << "Are atas: " << m.areAtas << endl;

	return out;
}

class Persoana {
	string nume;

public:
	Persoana() {
		this->nume = "Unknown name";
	}

	Persoana(string nume) {
		this->nume = nume;
	}

	friend ostream& operator<<(ostream& out, const Persoana& p);
	friend istream& operator>>(istream& in, Persoana& p);

};

ostream& operator<<(ostream& out, const Persoana& p) {
	out << p.nume << endl;

	return out;
}

istream& operator>>(istream& in, Persoana& p) {
	char aux[100];
	cout << "Nume persoana: "; in.getline(aux, 100);
	p.nume = aux;

	return in;
}

class GrupMasini {
	string nume;
	int nrPersoane;
	Persoana* pointerPersoane;

public:
	GrupMasini(string nume, int nrPersoane, Persoana* pointerPersoane) {
		this->nume = nume;
		this->nrPersoane = nrPersoane;

		this->pointerPersoane = new Persoana[this->nrPersoane];
		for (int i = 0; i < this->nrPersoane; i++) {
			this->pointerPersoane[i] = pointerPersoane[i];
		}
	}

	GrupMasini(const GrupMasini& g) {
		this->nume = g.nume;
		this->nrPersoane = g.nrPersoane;

		this->pointerPersoane = new Persoana[g.nrPersoane];
		for (int i = 0; i < g.nrPersoane; i++) {
			this->pointerPersoane[i] = g.pointerPersoane[i];
		}
	}

	GrupMasini& operator=(const GrupMasini& g) {
		if (this != &g) {
			this->nume = g.nume;
			this->nrPersoane = g.nrPersoane;

			delete[] this->pointerPersoane;//evitare memory leaks
			this->pointerPersoane = new Persoana[g.nrPersoane];
			for (int i = 0; i < g.nrPersoane; i++) {
				this->pointerPersoane[i] = g.pointerPersoane[i];
			}
		}

		return *this;
	}

	~GrupMasini() {
		delete[] this->pointerPersoane;
	}

	int getNrPersoane() {
		return this->nrPersoane;
	}

	Persoana* getPointerPersoane() {
		return this->pointerPersoane;
	}

	void setPersoane(Persoana* pointerPersoane, int nrPersoane) {
		if (pointerPersoane == nullptr) {
			throw new exception("pointerul e null");
		}
		else {
			delete[] this->pointerPersoane;//evitare memory leaks

			this->nrPersoane = nrPersoane;
			this->pointerPersoane = new Persoana[nrPersoane];
			for (int i = 0; i < nrPersoane; i++) {
				this->pointerPersoane[i] = pointerPersoane[i];
			}
		}
	}

	friend ostream& operator<<(ostream& out, const GrupMasini& g);
	friend istream& operator>>(istream& in, GrupMasini& g);
};

ostream& operator<<(ostream& out, const GrupMasini& g) {
	out << "======\n";
	out << "Nume grup: " << g.nume << " Nr Persoane: " << g.nrPersoane << "\nPersoane:\n";
	for (int i = 0; i < g.nrPersoane; i++) {
		out << g.pointerPersoane[i];
	}
	out << "======";
	return out;
}

istream& operator>>(istream& in, GrupMasini& g) {
	char aux[100];
	cout << "Nume grup: "; in.getline(aux, 100);
	g.nume = aux;

	cout << "Nr Persoane: "; in >> g.nrPersoane;
	in.ignore();

	cout << "Persoane:\n";
	delete[] g.pointerPersoane;//evitare memory leaks

	g.pointerPersoane = new Persoana[g.nrPersoane];
	for (int i = 0; i < g.nrPersoane; i++) {
		cout << "Persoana[" << i << "]\n"; in >> g.pointerPersoane[i];
	}

	return in;
}


void main() {
	string* dotari = new string[3];
	dotari[0] = "dotare1";
	dotari[1] = "dotare2";
	dotari[2] = "dotare3";

	Masina m1(1, "Audi", 2020, "negru", true, 3, dotari);
	cout << m1;

	Masina m2(2, "BMW", 2021, "gri", true, 3, dotari);
	cout << m2;

	m1 = m2;
	cout << m1;

	try {
		//Vehicul v1(1880, "negru");
		Vehicul v2(2000, "");
	}
	catch (exception* e) {
		cout << endl << endl << "EROARE: " << e->what() << endl << endl;
	}

	Persoana p1("Vasile");
	Persoana p2("Ion");
	Persoana persoane[2] = { p1,p2 };

	GrupMasini grup1("Grupul1", 2, persoane);
	cout << grup1 << endl << endl;

	cin >> grup1;
	cout << endl << endl << grup1;
}