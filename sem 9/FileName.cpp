#include<iostream>
using namespace std;

class Parinte {
	const string CNP;
	char* nume;
protected:
	double KG;
public:
	static string Tara;

	Parinte() :CNP("1111")
	{
		this->nume = new char[strlen("ceva") + 1];
		strcpy_s(this->nume, strlen("ceva") + 1, "ceva");
		this->KG = 0.0;
	}

	Parinte(string CNP, const char* nume, double KG) :CNP(CNP) {
		if (CNP.empty()) {
			throw new exception("cnp are dim 0");
		}
		if (nume == nullptr) {
			throw new exception("nume este nullptr");
		}
		if (KG == 0) {
			throw new exception("KG este 0");
		}

		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		this->KG = KG;
	}

	Parinte(Parinte& p) :CNP(p.CNP) {
		this->nume = new char[strlen(p.nume) + 1];
		strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
		this->KG = p.KG;
	}

	Parinte& operator=(const Parinte& p) {
		if (this != &p) {
			delete[]this->nume;

			this->nume = new char[strlen(p.nume) + 1];
			strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
			this->KG = p.KG;
		}

		return *this;
	}

	~Parinte() {
		delete[]this->nume;
	}

	friend ostream& operator<<(ostream& out, const Parinte& p);
	friend istream& operator>>(istream& in, Parinte& p);
};
string Parinte::Tara = "Romania";

ostream& operator<<(ostream& out, const Parinte& p) {
	out << "Nume: " << p.nume << " KG: " << p.KG << " Tara: " << p.Tara << " CNP: " << p.CNP << endl;
	return out;
}

istream& operator>>(istream& in, Parinte& p) {
	cout << "Nume: ";
	char aux[100];
	in.getline(aux, 100);

	delete[] p.nume;

	p.nume = new char[strlen(aux) + 1];
	strcpy_s(p.nume, strlen(aux) + 1, aux);

	cout << " KG: ";
	in >> p.KG;

	return in;
}

class Copil :protected  Parinte {
	string NumeScoala;
	int	NrMaterii;
	int* Absente;
public:

	Copil() :Parinte() {
		this->NumeScoala = "scoalaRandom";
		this->NrMaterii = 0;
		this->Absente = nullptr;
	}

	Copil(string CNP, const char* nume, double KG, string NumeScoala, int NrMaterii, int* Absente)
		:Parinte(CNP, nume, KG) {

		this->NumeScoala = NumeScoala;
		this->NrMaterii = NrMaterii;
		this->Absente = new int[NrMaterii];
		for (int i = 0; i < NrMaterii; i++) {
			this->Absente[i] = Absente[i];
		}
	}

	Copil(Copil& c) :Parinte(c) {
		this->NumeScoala = c.NumeScoala;
		this->NrMaterii = c.NrMaterii;
		this->Absente = new int[c.NrMaterii];
		for (int i = 0; i < c.NrMaterii; i++) {
			this->Absente[i] = c.Absente[i];
		}
	}

	Copil& operator=(const Copil& c) {
		if (this != &c) {
			Parinte::operator=(c);

			delete[]this->Absente;

			this->NumeScoala = c.NumeScoala;
			this->NrMaterii = c.NrMaterii;
			this->Absente = new int[c.NrMaterii];
			for (int i = 0; i < c.NrMaterii; i++) {
				this->Absente[i] = c.Absente[i];
			}
		}

		return *this;
	}

	~Copil() {
		delete[]this->Absente;
	}

	friend ostream& operator<<(ostream& out, const Copil& p);
	friend istream& operator>>(istream& in, Copil& p);
};

ostream& operator<<(ostream& out, const Copil& p) {
	out << (Parinte&)p << endl;

	out << " NumeScoala: " << p.NumeScoala << " Nr. Materii: " << p.NrMaterii << endl;
	for (int i = 0; i < p.NrMaterii; i++) {
		out << "Absente[" << i << "] = " << p.Absente[i];
	}
	out << endl;

	return out;
}
istream& operator>>(istream& in, Copil& p) {
	in >> (Parinte&)p;

	char aux[100];
	cout << "NumeScoala: ";  in >> aux;
	p.NumeScoala = aux;

	cout << "NrMaterii: ";
	in >> p.NrMaterii;

	delete[] p.Absente;

	p.Absente = new int[p.NrMaterii];

	for (int i = 0; i < p.NrMaterii; i++) {
		cout << "Absente[" << i << "] = ";
		in >> p.Absente[i];
	}

	return in;
}

class Biblioteca {
	int NrElevi;
	Copil* Elevi;
	string NumeBibliotecara;
	int varstaBibliotecara;
public:

	Biblioteca() {
		this->NrElevi = 0;
		Elevi = nullptr;
		this->NumeBibliotecara = "randomNUmeBibliotecara";
		this->varstaBibliotecara = 0;
	}

	Biblioteca(int NrElevi, Copil* Elevi, string NumeBibliotecara, int varstaBibliotecara) {
		this->NumeBibliotecara = NumeBibliotecara;
		this->varstaBibliotecara = varstaBibliotecara;

		this->NrElevi = NrElevi;
		this->Elevi = new Copil[NrElevi];
		for (int i = 0; i < NrElevi; i++) {
			this->Elevi[i] = Elevi[i];
		}
	}

	Biblioteca(Biblioteca& b) {
		this->NumeBibliotecara = b.NumeBibliotecara;
		this->varstaBibliotecara = b.varstaBibliotecara;

		this->NrElevi = b.NrElevi;
		this->Elevi = new Copil[b.NrElevi];
		for (int i = 0; i < b.NrElevi; i++) {
			this->Elevi[i] = b.Elevi[i];
		}
	}

	Biblioteca& operator=(const Biblioteca& b) {
		if (this != &b) {
			delete[] this->Elevi;

			this->NumeBibliotecara = b.NumeBibliotecara;
			this->varstaBibliotecara = b.varstaBibliotecara;

			this->NrElevi = b.NrElevi;
			this->Elevi = new Copil[b.NrElevi];
			for (int i = 0; i < b.NrElevi; i++) {
				this->Elevi[i] = b.Elevi[i];
			}
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Biblioteca& p);

	~Biblioteca() {
		delete[]this->Elevi;
	}

	int getVarsta() {
		return varstaBibliotecara;
	}

	string getNumeBibliotecara() {
		return this->NumeBibliotecara;
	}

	int getNrElevi() {
		return this->NrElevi;
	}

	Copil* getElevi() {
		return this->Elevi;
	}

	void setNumeBibliotecara(string NumeBibliotecara) {
		if (NumeBibliotecara.empty()) {
			throw new exception("NumeBibliotecara este empty.");
		}

		this->NumeBibliotecara = NumeBibliotecara;
	}

	void setNrElevi(int NrElevi) {
		if (NrElevi == 0) {
			throw new exception("NrElevi este 0.");
		}
		this->NrElevi = NrElevi;
	}

	void setElevi(Copil* Elevi, int NrElevi) {
		if (NrElevi == 0 || Elevi == nullptr) {
			throw new exception("NrElevi este 0 || Elevi == nullptr");
		}

		delete[] this->Elevi;
		this->NrElevi = NrElevi;
		this->Elevi = new Copil[NrElevi];
		for (int i = 0; i < NrElevi; i++) {
			this->Elevi[i] = Elevi[i];
		}
	}

	//operatori
	//op. unari 
	//op. ++ - pre-incrementare
	const Biblioteca& operator++() {
		this->varstaBibliotecara++;

		return *this;
	}

	//op. ++ - post-incrementare
	const Biblioteca operator++(int) { 
		//fara & la return -> este nevoie sa se returneze o copie a lui aux --> aux este distrus
		Biblioteca aux(*this);

		this->varstaBibliotecara++;

		return aux;
	}

	//op binari
	//op. + (ex: cout<<s5+2;)
	int operator+(int x) {
		return varstaBibliotecara + x;
	}

	//op. +  (ex: cout<<s4+s3;)
	Biblioteca operator+(Biblioteca& b) {
		Biblioteca aux(*this);

		aux.NrElevi = aux.NrElevi + b.NrElevi;

		delete[]aux.Elevi;
		aux.Elevi = new Copil[aux.NrElevi];

		int k = 0;
		for (int i = 0; i < this->NrElevi; i++) {
			aux.Elevi[k++] = this->Elevi[i];
		}

		for (int i = 0; i < b.NrElevi; i++) {
			aux.Elevi[k++] = b.Elevi[i];
		}
		return aux;
	}

	//op. + (ex: cout<<10+s3;)
	friend int operator+(int x, Biblioteca& student);

	//op += (s5+=3;)
	void operator+=(int x) {
		varstaBibliotecara += x;
	}

	//op !
	//if(!s4){//fa ceva};
	bool operator!() {
		return varstaBibliotecara > 0;
	}


	//op ==
	//if(b1==b2){..}
	//bool operator==(Biblioteca& s) {
	//	if (this == &s) {
	//		return true;
	//	}

	//	bool sameFields = strcmp(this->nume, s.nume) == 0 &&
	//		this->telefon == s.telefon &&
	//		this->varsta == s.varsta &&
	//		this->gen == s.gen &&
	//		this->nrNote == s.nrNote;

	//	if (sameFields == true) {
	//		for (int i = 0; i < nrNote; i++) {
	//			if (this->note[i] != s.note[i]) {
	//				return false;
	//			}
	//		}
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//}

	//op functie ()
	//void operator()(int valoare) {
	//	if (valoare >= 1 && valoare <= 3) {
	//		for (int i = 0; i < this->NrElevi; i++) {
	//			if (this->Elevi[i] + valoare <= 10) {
	//				this->Elevi[i] += valoare;
	//			}
	//		}
	//	}
	//	else {
	//		throw new exception("Eroare: valoare < 1 sau valoare >3");
	//	}
	//}

	//op index[]
	//cout<<s6[2];
	Copil& operator[](int index) {
		if (index >= 0 && index < NrElevi) {
			return this->Elevi[index];
		}
		else {
			throw new exception("Eroare: index < 0 sau index > nrNote");
		}
	}

	//operator cast - implicit sau explicit
	operator int() {
		return varstaBibliotecara;
	}

};
ostream& operator<<(ostream& out, const Biblioteca& p) {
	out << "NumeBibliotecara: " << p.NumeBibliotecara << " NrElevi: " << p.NrElevi
		<< " Varsta bibliotecara: " << p.varstaBibliotecara << endl;

	for (int i = 0; i < p.NrElevi; i++) {
		out << "Elevi[" << i << "] = " << p.Elevi[i];
	}
	out << endl;

	return out;
}

//op. + (ex: cout<<10+s3;)
int operator+(int x, Biblioteca& b) {
	return x + b.NrElevi;
}

//polimorfism => supraincarcare si suprascriere
//supraincarcare
int suma(int a, int b) {
	return a + b;
}

int suma(int a, int b, int c) {
	return a + b + c;
}

double suma(int a, double b) {
	return a + b;
}

void main() {
	Parinte p1;
	Parinte p2("2121", "Ion Popescu", 88.6);

	cout << p1 << endl << p2 << endl << endl;
	Copil c1;

	int absente[2] = { 4,6 };
	Copil c2("2121992", "Ion Popescu", 88.6, "Scoala 1", 2, absente);

	Copil copii[2] = { c1,c2 };
	Biblioteca b1(2, copii, "Maria Popescu", 54);
	cout << b1;

	//operatori 
	cout << endl << endl << "========op=====" << endl << endl;

	cout << ++b1 << endl;
	cout << b1++ << endl;
}

