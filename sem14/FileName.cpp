#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class Productie {


public:
	string nume;
	string tip;

	Productie() {
		this->nume = "unknownName";
		this->tip = "unknownType";
	}

	Productie(string nume, string tip) {
		this->nume = nume;
		this->tip = tip;
	}


	friend ostream& operator<<(ostream& out, const Productie& s) {
		out << "Nume: " << s.nume << " tip: " << s.tip << endl;
		return out;
	}
};

class Film :public Productie {
public:
	Film(string nume) :Productie(nume, "film") {

	}
};

class Serial :public Productie {
public:
	Serial(string nume) :Productie(nume, "serial") {

	}
};

class StreamingService {
	static string numeCompanie;

	double pretAbonament;
	int durataAbonament;

	int nrProductii;
	string* productii;
	double* minuteVizionate;

	Productie* productii2;
	int nrProductii2;

public:
	StreamingService() {
		this->pretAbonament = 0.0;
		this->durataAbonament = 0;

		this->minuteVizionate = nullptr;

		this->nrProductii = 0;
		this->productii = nullptr;

		this->nrProductii2 = 0;
		this->productii2 = nullptr;
	}

	StreamingService(
		double pretAbonament,
		int durataAbonament,
		int nrProductii,
		string* productii,
		int nrProductii2,
		Productie* productii2,
		double* minuteVizionate) {
		this->pretAbonament = pretAbonament;
		this->durataAbonament = durataAbonament;

		this->nrProductii = nrProductii;
		this->productii = new string[nrProductii];
		for (int i = 0; i < nrProductii; i++) {
			this->productii[i] = productii[i];
		}

		this->nrProductii2 = nrProductii2;
		this->productii2 = new Productie[nrProductii2];
		for (int i = 0; i < nrProductii2; i++) {
			this->productii2[i] = productii2[i];
		}

		this->minuteVizionate = new double[nrProductii];
		for (int i = 0; i < nrProductii; i++) {
			this->minuteVizionate[i] = minuteVizionate[i];
		}
	}

	StreamingService(const StreamingService& s) {
		this->pretAbonament = s.pretAbonament;
		this->durataAbonament = s.durataAbonament;

		this->nrProductii = s.nrProductii;
		this->productii = new string[s.nrProductii];
		for (int i = 0; i < s.nrProductii; i++) {
			this->productii[i] = s.productii[i];
		}

		this->nrProductii2 = s.nrProductii2;
		this->productii2 = new Productie[s.nrProductii2];
		for (int i = 0; i < s.nrProductii2; i++) {
			this->productii2[i] = s.productii2[i];
		}

		this->minuteVizionate = new double[s.nrProductii];
		for (int i = 0; i < s.nrProductii; i++) {
			this->minuteVizionate[i] = s.minuteVizionate[i];
		}
	}

	StreamingService& operator=(const StreamingService& s) {
		if (this != &s) {
			this->pretAbonament = s.pretAbonament;
			this->durataAbonament = s.durataAbonament;

			delete[] this->productii;
			this->nrProductii = s.nrProductii;
			this->productii = new string[s.nrProductii];
			for (int i = 0; i < s.nrProductii; i++) {
				this->productii[i] = s.productii[i];
			}

			delete[] this->minuteVizionate;

			this->minuteVizionate = new double[s.nrProductii];
			for (int i = 0; i < s.nrProductii; i++) {
				this->minuteVizionate[i] = s.minuteVizionate[i];
			}

			delete[] this->productii2;

			this->nrProductii2 = s.nrProductii2;
			this->productii2 = new Productie[s.nrProductii2];
			for (int i = 0; i < s.nrProductii2; i++) {
				this->productii2[i] = s.productii2[i];
			}
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const StreamingService& s) {
		out << "Pret abonament: " << s.pretAbonament << " durata abonament: " << s.durataAbonament << endl;

		out << s.nrProductii << " productii: " << endl;
		for (int i = 0; i < s.nrProductii; i++) {
			out << s.productii[i] << " ";
		}

		out << endl << s.nrProductii << " minute vizionate: " << endl;
		for (int i = 0; i < s.nrProductii; i++) {
			out << s.minuteVizionate[i] << " ";
		}

		out << s.nrProductii2 << " productii2: " << endl;
		for (int i = 0; i < s.nrProductii2; i++) {
			out << s.productii2[i] << " ";
		}

		return out;
	}

	~StreamingService() {
		delete[] this->productii;
		delete[] this->minuteVizionate;
		delete[] this->productii2;
	}

	//getter si setteri
	double getPretAbonament() {
		return pretAbonament;
	}

	void setPretAbonament(double pretAbonament) {
		this->pretAbonament = pretAbonament;
	}

	int getDurataAbonament() {
		return durataAbonament;
	}

	void setDurataAbonament(int durataAbonament) {
		this->durataAbonament = durataAbonament;
	}

	int getNrProductii() {
		return nrProductii;
	}

	void setNrProductii(int nrProductii) {
		this->nrProductii = nrProductii;
	}

	string* getProductii() {
		return productii;
	}

	void setProductii(int nrProductii, string* productii) {
		delete[] productii;

		this->nrProductii = nrProductii;
		this->productii = new string[this->nrProductii];
		for (int i = 0; i < nrProductii; i++) {
			this->productii[i] = productii[i];
		}
	}

	Productie* getProductii2() {
		return productii2;
	}

	void setProductii(int nrProductii2, Productie* productii2) {
		delete[] productii2;

		this->nrProductii = nrProductii2;
		this->productii2 = new Productie[this->nrProductii2];
		for (int i = 0; i < nrProductii2; i++) {
			this->productii2[i] = productii2[i];
		}
	}

	double* getMinuteVizionate() {
		return minuteVizionate;
	}

	void setMinuteVizionate(int nrProductii, double* minuteVizionate) {
		delete[] minuteVizionate;

		this->nrProductii = nrProductii;
		this->minuteVizionate = new double[this->nrProductii];
		for (int i = 0; i < nrProductii; i++) {
			this->minuteVizionate[i] = minuteVizionate[i];
		}
	}

	void operator+=(string numeProductie) {
		string* aux = new string[nrProductii + 1];
		double* aux2 = new double[nrProductii + 1];

		for (int i = 0; i < nrProductii; i++) {
			aux[i] = productii[i];
			aux2[i] = minuteVizionate[i];
		}

		aux[nrProductii] = numeProductie;
		aux2[nrProductii] = 0;

		delete[] productii;
		delete[] minuteVizionate;

		nrProductii++;

		productii = aux;
		minuteVizionate = aux2;
	}

	void operator-=(string numeProductie) {
		int index = -1;
		for (int i = 0; i < nrProductii; i++) {
			if (productii[i] == numeProductie) {
				index = i;
				break;
			}
		}

		if (index >= 0) {
			string* aux = new string[nrProductii - 1];
			double* aux2 = new double[nrProductii - 1];

			for (int i = 0; i < nrProductii; i++) {
				if (i != index) {
					aux[i] = productii[i];
					aux2[i] = minuteVizionate[i];
				}
			}

			delete[] productii;
			delete[] minuteVizionate;

			nrProductii--;

			productii = aux;
			minuteVizionate = aux2;
		}
	}

	operator double() {
		int max = -1;

		for (int i = 0; i < nrProductii; i++) {
			if (max < minuteVizionate[i]) {
				max = minuteVizionate[i];
			}
		}

		return max;
	}

	//primele 5 seriale si 5 filme...sortezi minuteVizionate cresc& desc => afisezi primele 5 valori

	void topFilmeSiSeriale() {
		Productie aux1;
		double aux2;

		for (int i = 0; i < nrProductii - 1; i++) {
			for (int j = 0; j < nrProductii; j++) {
				if (this->minuteVizionate[i] > this->minuteVizionate[j]) {
					aux1 = this->productii2[i];
					this->productii2[i] = this->productii2[j];
					this->productii2[j] = aux1;

					aux2 = this->minuteVizionate[i];
					this->minuteVizionate[i] = this->minuteVizionate[j];
					this->minuteVizionate[j] = aux2;
				}
			}
		}

		int nrFilme = 0, nrSeriale = 0;
		for (int i = 0; i < nrProductii; i++) {
			if (this->productii2[i].tip == "film" && nrFilme < 5) {
				nrFilme++;
				cout << this->productii2[i] << " min viz: " << this->minuteVizionate[i] << endl;
			}

			if (this->productii2[i].tip == "serial" && nrSeriale < 5) {

				nrSeriale++;
				cout << this->productii2[i] << " min viz: " << this->minuteVizionate[i] << endl;
			}
		}
	}
};

template <typename T, typename W> T suma(T a, W b) {
	return a + b;
}

string StreamingService::numeCompanie = "NETFLIX";

void main() {
	cout << suma(10, 33.44) << endl;
	cout << suma(19.44, 3123.44) << endl;
	cout << suma(22, 1) << endl;

}