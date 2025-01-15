#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class Asigurare {
	const int ID;
	char* numeAsigurat;
	double sumaAsigurata;
	string tipulAsigurarii;
	int durataAsigurarii;
public:
	Asigurare() :ID(0) {
		this->numeAsigurat = new char[strlen("Anonim") + 1];
		strcpy_s(this->numeAsigurat, strlen("Anonim") + 1, "Anonim");

		this->sumaAsigurata = 0.0;
		this->tipulAsigurarii = "NN";
		this->durataAsigurarii = 0;
	}

	Asigurare(int ID, const char* numeAsigurat, double sumaAsigurata, string tipulAsigurarii,
		int durataAsigurarii) :ID(ID) {

		this->numeAsigurat = new char[strlen(numeAsigurat) + 1];
		strcpy_s(this->numeAsigurat, strlen(numeAsigurat) + 1, numeAsigurat);

		this->sumaAsigurata = sumaAsigurata;
		this->tipulAsigurarii = tipulAsigurarii;
		this->durataAsigurarii = durataAsigurarii;
	}

	Asigurare(const Asigurare& b) :ID(b.ID) {
		this->numeAsigurat = new char[strlen(b.numeAsigurat) + 1];
		strcpy_s(this->numeAsigurat, strlen(b.numeAsigurat) + 1, b.numeAsigurat);

		this->sumaAsigurata = b.sumaAsigurata;
		this->tipulAsigurarii = b.tipulAsigurarii;
		this->durataAsigurarii = b.durataAsigurarii;
	}

	~Asigurare() {
		delete[] this->numeAsigurat;
	}

	Asigurare& operator=(Asigurare& b) {
		if (this != &b) {
			delete[] numeAsigurat;

			this->numeAsigurat = new char[strlen(b.numeAsigurat) + 1];
			strcpy_s(this->numeAsigurat, strlen(b.numeAsigurat) + 1, b.numeAsigurat);

			this->sumaAsigurata = b.sumaAsigurata;
			this->tipulAsigurarii = b.tipulAsigurarii;
			this->durataAsigurarii = b.durataAsigurarii;
		}

		return *this;
	}

	friend istream& operator>>(istream& in, Asigurare& b) {
		cout << "Nume asigurat: ";
		char aux[100];
		in.getline(aux, 100);

		delete[] b.numeAsigurat;

		b.numeAsigurat = new char[strlen(aux) + 1];
		strcpy_s(b.numeAsigurat, strlen(aux) + 1, aux);

		cout << "Suma asigurata: ";
		in >> b.sumaAsigurata;

		cout << "Tipul asigurarii: ";
		in.ignore();
		in.getline(aux, 100);
		b.tipulAsigurarii = aux;

		cout << "Durata asigurarii: ";
		in >> b.durataAsigurarii;

		return in;
	}

	friend ostream& operator<<(ostream& out, const Asigurare& b) {
		out << "ID: " << b.ID << " Nume asigurat: " << b.numeAsigurat
			<< " suma asigurata: " << b.sumaAsigurata
			<< " tipul asigurarii: " << b.tipulAsigurarii 
			<< " durata asigurarii: " << b.durataAsigurarii << endl;

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Asigurare& b) {
		out << b.ID << endl << b.numeAsigurat << endl << b.sumaAsigurata << endl << b.tipulAsigurarii << endl << b.durataAsigurarii << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Asigurare& b) {
		int ID;
		in >> ID;

		in.ignore();

		char aux[100];
		in.getline(aux, 100);

		delete[] b.numeAsigurat;

		b.numeAsigurat = new char[strlen(aux) + 1];
		strcpy_s(b.numeAsigurat, strlen(aux) + 1, aux);

		in >> b.sumaAsigurata;

		in.ignore();

		in.getline(aux, 100);
		b.tipulAsigurarii = aux;

		in >> b.durataAsigurarii;

		return in;
	}

	void scrieInFisierBinar(ofstream& fisBinarOut) {
		fisBinarOut.write((char*)&ID, sizeof(ID));

		int dim = strlen(numeAsigurat) + 1; //+1 - pt '\0' de la finalul unui sir de caractere
		//fct write - compilatorul trebuie sa stie la CE adresa sa se uite in memorie si cat sa citeasca
		fisBinarOut.write((char*)&dim, sizeof(dim)); //tu ai un pointer de tip char CE are ca VALOARE adresa lui dim....
		fisBinarOut.write(numeAsigurat, dim); //aici nu mai e sizeof, pt ca ai calculat deja dimensiunea sirului de caractere

		fisBinarOut.write((char*)&sumaAsigurata, sizeof(sumaAsigurata));

		dim = tipulAsigurarii.size() + 1; //+1 - pt '\0' de la finalul unui sir de caractere
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(tipulAsigurarii.c_str(), dim);

		fisBinarOut.write((char*)&durataAsigurarii, sizeof(durataAsigurarii));
	}

	void citireDinFisierBinar(ifstream& fisBinarIn) {
		int ID = 0;
		fisBinarIn.read((char*)&ID, sizeof(ID));

		int dim = 0;
		fisBinarIn.read((char*)&dim, sizeof(dim));

		char aux[200];
		fisBinarIn.read(aux, dim);

		delete[] numeAsigurat;
		numeAsigurat = new char[strlen(aux) + 1];
		strcpy_s(numeAsigurat, strlen(aux) + 1, aux);

		fisBinarIn.read((char*)&sumaAsigurata, sizeof(sumaAsigurata));

		fisBinarIn.read((char*)&dim, sizeof(dim));
		fisBinarIn.read(aux, dim);
		this->tipulAsigurarii = aux;

		fisBinarIn.read((char*)&this->durataAsigurarii, sizeof(this->durataAsigurarii));
	}

	double operator()(double cursDeSchimb) {
		return sumaAsigurata / cursDeSchimb;
	}

	operator double() {
		return sumaAsigurata;
	}

	char* getNumeAsigurat() {
		return numeAsigurat;
	}

	void setNumeAsigurat(char* numeAsigurat) {
		delete[] this->numeAsigurat;

		this->numeAsigurat = new char[strlen(numeAsigurat) + 1];
		strcpy_s(this->numeAsigurat, strlen(numeAsigurat) + 1, numeAsigurat);
	}

	double getSumaAsigurata() {
		return sumaAsigurata;
	}

	void setSumaAsigurata(double sumaAsigurata) {
		this->sumaAsigurata = sumaAsigurata;
	}

	string getTipulAsigurarii() {
		return tipulAsigurarii;
	}

	void setTipulAsigurarii(string tipulAsigurarii) {
		this->tipulAsigurarii = tipulAsigurarii;
	}

	int getDurataAsigurarii() {
		return durataAsigurarii;
	}

	void setDurataAsigurarii(int durataAsigurarii) {
		this->durataAsigurarii = durataAsigurarii;
	}
};

class BrokerAsigurari {
	int dim;
	Asigurare* asigurari;
public:
	BrokerAsigurari() {
		this->dim = 0;
		this->asigurari = nullptr;
	}

	BrokerAsigurari(int dim, Asigurare* asigurari) {
		this->dim = dim;
		this->asigurari = new Asigurare[dim];
		for (int i = 0; i < dim; i++) {
			this->asigurari[i] = asigurari[i];
		}
	}

	BrokerAsigurari(const BrokerAsigurari& b) {
		this->dim = b.dim;
		this->asigurari = new Asigurare[b.dim];
		for (int i = 0; i < b.dim; i++) {
			this->asigurari[i] = b.asigurari[i];
		}
	}

	BrokerAsigurari& operator=(const BrokerAsigurari& b) {
		if (this != &b) {
			this->dim = b.dim;

			delete[] this->asigurari;
			this->asigurari = new Asigurare[b.dim];
			for (int i = 0; i < b.dim; i++) {
				this->asigurari[i] = b.asigurari[i];
			}
		}

		return *this;
	}

	double medie() {
		double sumaTotala = 0.0;

		for (int i = 0; i < dim; i++) {
			sumaTotala += this->asigurari[i].getSumaAsigurata();
		}

		return sumaTotala / dim;
	}

	~BrokerAsigurari() {
		delete[] asigurari;
	}
};
void main() {
	//fisiere text si binare

	//flag-uri
	//ios::app - adauga informatii la un fisier existent sau il va crea daca nu exista
	//ios::nocreate - deschide fisierul daca exista deja.
	//ios::in - pt citire dintr-un fisier
	//ios::out - scriere intr-un fisier
	//ios::truc - sterge tot din fisier inainte sa scrii in el 
	//ios::noreplace - doar pt a crea un nou fisier
	//ios::ate - deschide fisierul si merge la sfarsitul lui - fol pt adaugare informatii la final
	//ios::binary - fisierul deschis va contine doar informatii binare

	Asigurare a1;
	Asigurare a2(121, "Popescu Ion", 88000, "NN activ", 360);
	Asigurare a3(3331, "Ionescu Maria", 12000.99, "NN simplu", 200);

	ofstream asigurariOut("asigurariOut.txt", ios::out);
	if (asigurariOut.is_open()) {
		asigurariOut << a1;//nu merge inlantuirea la << ofstream
		asigurariOut << a2;//nu merge inlantuirea la << ofstream
		asigurariOut << a3;//nu merge inlantuirea la << ofstream

		asigurariOut.close();
	}
	else {
		cout << "Fisierul asigurariOut.txt nu poate fi deschis pentru scriere.\n";
	}

	cout << endl << endl << "FISIERE" << endl << endl;

	ifstream asigurariIn("asigurariOut.txt", ios::in);
	if (asigurariIn.is_open()) {
		Asigurare temp;

		asigurariIn >> temp;//a1
		cout << temp << endl;

		asigurariIn >> temp;//a2
		cout << temp << endl;

		asigurariIn >> temp;//a3
		cout << temp << endl;

		asigurariIn.close();
	}
	else {
		cout << "Fisierul asigurariOut.txt nu poate fi deschis pentru citire.\n";
	}

	cout << "\n\n\n=========BINARE=========\n\n\n";
	ofstream fisBinarOut("wwww.bin", ios::out | ios::binary);
	if (fisBinarOut.is_open()) {
		a2.scrieInFisierBinar(fisBinarOut);
		a3.scrieInFisierBinar(fisBinarOut);

		fisBinarOut.close();
	}
	else {
		cout << "Fisierul wwww.dat nu poate fi deschis pentru scriere.\n";
	}

	ifstream fisBinarIn("wwww.bin", ios::in | ios::binary);
	if (fisBinarIn.is_open()) {
		Asigurare temp;
		temp.citireDinFisierBinar(fisBinarIn);
		cout << "temp din fisier binar:   " << temp << endl;

		temp.citireDinFisierBinar(fisBinarIn);
		cout << "temp din fisier binar:   " << temp << endl;

		fisBinarIn.close();
	}
	else {
		cout << "Fisierul wwww.bin nu poate fi deschis pentru citire.\n";
	}

	BrokerAsigurari b1(2, new Asigurare[2]{ a2,a3 });
	cout << "\nMEDIE: " << b1.medie();

	vector<Asigurare> vectorAsigurari;
	vectorAsigurari.push_back(a1);
	vectorAsigurari.push_back(a2);
	vectorAsigurari.push_back(a3);

	double total = 0.0;
	for (int i = 0; i < vectorAsigurari.size(); i++) {
		total += vectorAsigurari[i].getSumaAsigurata();
	}

	cout << "\nTOTAL: " << total;
}