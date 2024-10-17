#include<iostream>

using namespace std;

class Persoana {
	//private: by default zona asta e private
	string nume;
	string telefon;
	string CNP;
protected:
	int varsta;
	float kg;
private:
	bool gen;

public:

	Persoana() {
		this->nume = "numeDefault";
		this->telefon = "telefonUnknown";
		this->CNP = "randomCNP";
		this->varsta = 0;
		this->kg = 0;
		this->gen = false;
	}

	Persoana(string nume, string telefon, string CNP) {
		this->nume = nume;
		this->telefon = telefon;
		this->CNP = CNP;
	}

	Persoana(string nume, string telefon, string CNP, int varsta, float kg, bool gen) {
		this->nume = nume;
		this->telefon = telefon;
		this->CNP = CNP;
		this->varsta = varsta;
		this->kg = kg;
		this->gen = gen;
	}

	string getNume() {
		return this->nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	string getTelefon() {
		return this->telefon;
	}

	void setTelefon(string telefon) {
		this->telefon = telefon;
	}

	string getCNP() {
		return this->CNP;
	}

	void setCNP(string CNP) {
		this->CNP = CNP;
	}

	int getVarsta() {
		return this->varsta;
	}

	void setVarsta(int varsta) {
		this->varsta = varsta;
	}

	float getKg() {
		return this->kg;
	}

	void setKg(float kg) {
		this->kg = kg;
	}

	bool getGen() {
		return this->gen;
	}

	void setGen(bool gen) {
		this->gen = gen;
	}

	void afisare() {
		cout << "Nume: "<< this->nume << " , telefon: " << this->telefon << " , CNP:"
			<< this->CNP << " , varsta: " << this->varsta << " , kg: " << this->kg << " ,gen: " << this->gen<<endl<<endl;
	}
};

class Profesor : public Persoana {
	int aniVechime;
};


void main() {
	Persoana p;

	cout << p.getNume() << " " << p.getTelefon() << " "
		<< p.getCNP() << " " << p.getVarsta() << " " << p.getKg() << " " << p.getGen() << endl;

	Persoana p1("Popescu Ion", "0754353534", "124334563643");
	p1.afisare();


	Persoana p2("Popescu Maria", "0786664324", "5434343434", 30, 68, false);
	p2.afisare();
}