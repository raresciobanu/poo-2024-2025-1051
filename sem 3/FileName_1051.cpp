#include<iostream>

using namespace std;

class Persoana {
	//private: by default zona asta e private
	string nume = "numeDefault";
	string telefon;
	string CNP;
protected:
	int varsta;
	float kg;
private:
	bool gen;

public:

	Persoana() {
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

		this->varsta = 0;
		this->kg = 0;
		this->gen = false;
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
		cout << "Nume: " << this->nume << " , telefon: " << this->telefon << " , CNP:"
			<< this->CNP << " , varsta: " << this->varsta << " , kg: " << this->kg << " ,gen: " << this->gen << endl << endl;
	}
};

class Profesor : public Persoana {
	int aniVechime;

public:
	Profesor() : Persoana() {
		this->aniVechime = 0;
	}

	Profesor(string nume, string telefon, string CNP, int varsta, float kg, bool gen, int aniVechime)
		: Persoana(nume, telefon, CNP, varsta, kg, gen) {
		this->aniVechime = aniVechime;
	}

	void afisareProfesor() {
		cout << "Profesor vechime: " << this->aniVechime << endl;
		this->afisare();
	}
};

class Student : public Persoana {
	bool exmatriculat;
	int aniStudii;

public:
	Student() : Persoana() {
		this->exmatriculat = false;
		this->aniStudii = 0;
	}

	Student(string nume, string telefon, string CNP, int varsta, float kg, bool gen, bool exmatriculat, int aniStudii)
		: Persoana(nume, telefon, CNP, varsta, kg, gen) {
		this->exmatriculat = exmatriculat;
		this->aniStudii = aniStudii;
	}

	void afisareStudent() {
		cout << "Studentul are: " << this->aniStudii << " ani de studii si este exmatriculat: "
			<< (this->exmatriculat ? " DA " : " NU ") << endl;
		this->afisare();
	}
};

//has a
class Curs {
	string nume;

	Student* studenti;
	int nrStudenti;

	Profesor profesor;

public:

	Curs() {
		this->nume = "Curs inexistent";

		this->studenti = nullptr;
		this->nrStudenti = 0;

		this->profesor = Profesor();
	}

	Curs(string nume, Student* studenti, int nrStudenti, Profesor prof) {
		this->nume = nume;

		this->studenti = new Student[nrStudenti];
		for (int i = 0; i < nrStudenti; i++) {
			this->studenti[i] = studenti[i];
		}

		this->nrStudenti = nrStudenti;

		this->profesor = prof;
	}

	~Curs() {
		delete[] this->studenti;
		cout << "s a distrus cursul: " << this->nume << endl;
	}

	void afisare() {
		cout << "Curs nume: " << this->nume << endl;

		profesor.afisareProfesor();

		cout << "Nr studenti: " << nrStudenti << ". Studentii: " << endl;

		for (int i = 0; i < nrStudenti; i++) {
			this->studenti[i].afisareStudent();
		}
	}
};

void main() {
	Persoana p;

	cout << p.getNume() << " " << p.getTelefon() << " "
		<< p.getCNP() << " " << p.getVarsta() << " " << p.getKg() << " " << p.getGen() << endl;

	Persoana p1("Popescu Ion", "0754353534", "124334563643");
	p1.afisare();


	Persoana p2("Popescu Maria", "0786664324", "5434343434", 30, 68, false);
	p2.afisare();


	Profesor prof1;
	prof1.afisareProfesor();

	Profesor prof2("Madalin Ion", "0777448663", "1221212121", 40, 93.7, true, 20);
	prof2.afisareProfesor();

	Student stud1;
	stud1.afisareStudent();

	Student stud2("Vasile Popescu", "0777555555", "199999999", 20, 77.7, true, false, 3);
	stud2.afisareStudent();

	Student stud3("Maria Raluca", "0753533333", "223333333", 21, 57.7, false, false, 2);
	stud3.afisareStudent();

	cout << endl << endl << "==========CURSURI============" << endl << endl;

	Student* studenti = new Student[5];
	studenti[0] = stud1;
	studenti[1] = stud2;
	studenti[2] = stud3;

	Curs curs1;
	curs1.afisare();

	Curs curs2("POO", studenti, 3, prof2);
	curs2.afisare();

	Curs curs3("ATP", studenti, 3, prof2);
	curs3.afisare();
}