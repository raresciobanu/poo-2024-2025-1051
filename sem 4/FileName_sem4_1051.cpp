#include<iostream>

using namespace std;

enum GEN {
	FEMEIE = 2,
	BARBAT
};

class Persoana {
	//private: by default zona asta e private
	string nume = "numeDefault";
	string telefon;
	string CNP;
protected:
	int varsta;
	float kg;
private:
	GEN gen;

public:

	Persoana() {
		this->telefon = "telefonUnknown";
		this->CNP = "randomCNP";
		this->varsta = 0;
		this->kg = 0;
		this->gen = BARBAT;
	}

	Persoana(string nume, string telefon, string CNP) {
		this->nume = nume;
		this->telefon = telefon;
		this->CNP = CNP;

		this->varsta = 0;
		this->kg = 0;
		this->gen = BARBAT;
	}

	Persoana(string nume, string telefon, string CNP, int varsta, float kg, GEN gen) {
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

	GEN getGen() {
		return this->gen;
	}

	void setGen(GEN gen) {
		this->gen = gen;
	}

	void afisare() {
		cout << "Nume: " << this->nume << " , telefon: " << this->telefon << " , CNP:"
			<< this->CNP << " , varsta: " << this->varsta << " , kg: " << this->kg << " ,gen: "
			<< this->genToString(this->gen) << endl << endl;
	}

	string genToString(GEN gen) {
		switch (gen)
		{
		case FEMEIE:
			return "Femeie";
		case BARBAT:
			return "Barbat";
		}
	}

	GEN stringToGEN(string value) {
		if (value == "Femeie") {
			return FEMEIE;
		}
		else {
			return BARBAT;
		}
	}

	Persoana& operator=(const Persoana& p) {
		if (this != &p) {
			this->nume = p.nume;
			this->telefon = p.telefon;
			this->CNP = p.CNP;
			this->varsta = p.varsta;
			this->kg = p.kg;
			this->gen = p.gen;
		}

		return *this;
	}
};

class Profesor : public Persoana {
	int aniVechime;

public:
	Profesor() : Persoana() {
		this->aniVechime = 0;
	}

	Profesor(string nume, string telefon, string CNP, int varsta, float kg, GEN gen, int aniVechime)
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

	int nrNote;
	double* note;
	char* nivelStudii;//licenta/master/doctorat...etc

public:
	Student() : Persoana() {
		this->exmatriculat = false;
		this->aniStudii = 0;

		this->nrNote = 0;
		this->note = nullptr;

		this->nivelStudii = new char[strlen("licenta") + 1];
		strcpy_s(this->nivelStudii, strlen("licenta") + 1, "licenta");
	}

	Student(string nume, string telefon, string CNP, int varsta, float kg, GEN gen, bool exmatriculat, int aniStudii)
		: Persoana(nume, telefon, CNP, varsta, kg, gen) {
		this->exmatriculat = exmatriculat;
		this->aniStudii = aniStudii;

		this->nrNote = 0;
		this->note = nullptr;

		this->nivelStudii = new char[strlen("licenta") + 1];
		strcpy_s(this->nivelStudii, strlen("licenta") + 1, "licenta");
	}

	Student(string nume, string telefon, string CNP, int varsta, float kg, GEN gen, bool exmatriculat, int aniStudii, int nrNote, double* note, const char* nivelStudii)
		: Persoana(nume, telefon, CNP, varsta, kg, gen) {
		this->exmatriculat = exmatriculat;
		this->aniStudii = aniStudii;

		this->nrNote = nrNote;
		this->note = new double[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}

		this->nivelStudii = new char[strlen(nivelStudii) + 1];
		strcpy_s(this->nivelStudii, strlen(nivelStudii) + 1, nivelStudii);
	}

	void afisareStudent() {
		cout << "Studentul are: " << this->aniStudii << " ani de studii si este exmatriculat: "
			<< (this->exmatriculat ? " DA " : " NU ") << endl;
		cout << "Nr note: " << this->nrNote << endl;
		for (int i = 0; i < this->nrNote; i++) {
			cout << "nota[" << i << "] = " << this->note[i] << " ";
		}
		cout << endl << "Nivel studii: " << this->nivelStudii << endl;

		this->afisare();
	}

	~Student() {
		cout << "Destructor student: " << this->getNume() << endl;
		delete[] this->note;
		delete[] this->nivelStudii;
	}

	Student& operator=(const Student& s) {
		if (this != &s) {
			Persoana::operator=(s);

			this->exmatriculat = s.exmatriculat;
			this->aniStudii = s.aniStudii;

			delete[] this->note;
			delete[] this->nivelStudii;

			this->nrNote = s.nrNote;
			this->note = new double[s.nrNote];
			for (int i = 0; i < s.nrNote; i++) {
				this->note[i] = s.note[i];
			}

			this->nivelStudii = new char[strlen(s.nivelStudii) + 1];
			strcpy_s(this->nivelStudii, strlen(s.nivelStudii) + 1, s.nivelStudii);
		}

		return *this;
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
		delete[] this->studenti;//ca sa nu avem memory leaks
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


	Persoana p2("Popescu Maria", "0786664324", "5434343434", 30, 68, FEMEIE);
	p2.afisare();


	Profesor prof1;
	prof1.afisareProfesor();

	Profesor prof2("Madalin Ion", "0777448663", "1221212121", 40, 93.7, BARBAT, 20);
	prof2.afisareProfesor();

	Student stud1;
	stud1.afisareStudent();

	Student stud2("Vasile Popescu", "0777555555", "199999999", 20, 77.7, BARBAT, false, 3);
	stud2.afisareStudent();

	Student stud3("Maria Raluca", "0753533333", "223333333", 21, 57.7, FEMEIE, false, 2);
	stud3.afisareStudent();

	double note1[5] = { 10, 9, 7.5, 8, 5.6 };
	Student stud4("Ioana Maria", "077444444", "100000111", 30, 51.7, FEMEIE, false, 1, 5, note1, "master");
	stud4.afisareStudent();

	double note2[5] = { 8, 9.4 , 5.5, 6, 7 };
	Student stud5("Marius Georgescu", "071111111", "200000011", 33, 89.7, BARBAT, false, 2, 5, note2,
		"doctorat");
	stud5.afisareStudent();

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

	delete[] studenti;//ca sa nu avem memory leak in main
}