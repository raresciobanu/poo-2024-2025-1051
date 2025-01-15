#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class StreamingService {
	static string numeCompanie;

	double pretAbonament;
	int durataAbonament;
	int nrFilme;
	string* filme;
	int nrSeriale;
	string* seriale;
	int minuteVizionate;
public:
	StreamingService() {
		this->pretAbonament = 0.0;
		this->durataAbonament = 0;

		this->nrFilme = 0;
		this->filme = nullptr;

		this->nrSeriale = 0;
		this->seriale = nullptr;

		this->minuteVizionate = 0;
	}

	StreamingService(
		double pretAbonament,
		int durataAbonament,
		int nrFilme,
		string* filme,
		int nrSeriale,
		string* seriale,
		int minuteVizionate) {
		this->pretAbonament = pretAbonament;
		this->durataAbonament = durataAbonament;

		this->nrFilme = nrFilme;
		this->filme = new string[nrFilme];
		for (int i = 0; i < nrFilme; i++) {
			this->filme[i] = filme[i];
		}

		this->nrSeriale = nrSeriale;
		this->seriale = new string[nrSeriale];
		for (int i = 0; i < nrSeriale; i++) {
			this->seriale[i] = seriale[i];
		}

		this->minuteVizionate = minuteVizionate;
	}

	StreamingService(const StreamingService& s) {
		this->pretAbonament = s.pretAbonament;
		this->durataAbonament = s.durataAbonament;

		this->nrFilme = s.nrFilme;
		this->filme = new string[s.nrFilme];
		for (int i = 0; i < s.nrFilme; i++) {
			this->filme[i] = s.filme[i];
		}

		this->nrSeriale = s.nrSeriale;
		this->seriale = new string[s.nrSeriale];
		for (int i = 0; i < s.nrSeriale; i++) {
			this->seriale[i] = s.seriale[i];
		}

		this->minuteVizionate = s.minuteVizionate;
	}

	StreamingService& operator=(const StreamingService& s) {
		if (this != &s) {
			this->pretAbonament = s.pretAbonament;
			this->durataAbonament = s.durataAbonament;

			delete[] this->filme;
			this->nrFilme = s.nrFilme;
			this->filme = new string[s.nrFilme];
			for (int i = 0; i < s.nrFilme; i++) {
				this->filme[i] = s.filme[i];
			}

			delete[] this->seriale;
			this->nrSeriale = s.nrSeriale;
			this->seriale = new string[s.nrSeriale];
			for (int i = 0; i < s.nrSeriale; i++) {
				this->seriale[i] = s.seriale[i];
			}

			this->minuteVizionate = s.minuteVizionate;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const StreamingService& s) {
		out << "Pret abonament: " << s.pretAbonament << " durata abonament: " << s.durataAbonament
			<< " minute vizionate: " << s.minuteVizionate << endl;
		out << s.nrFilme << " filme: " << endl;
		for (int i = 0; i < s.nrFilme; i++) {
			out << s.filme[i] << " ";
		}

		out << endl << s.nrFilme << " seriale: " << endl;
		for (int i = 0; i < s.nrSeriale; i++) {
			out << s.seriale[i] << " ";
		}

		return out;
	}

	~StreamingService() {
		delete[] this->filme;
		delete[] this->seriale;
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

	int getNrFilme() {
		return nrFilme;
	}

	void setNrFilme(int nrFilme) {
		this->nrFilme = nrFilme;
	}

	string* getFilme() {
		return filme;
	}

	void setFilme(int nrFilme, string* filme) {
		delete[] filme;

		this->nrFilme = nrFilme;
		this->filme = new string[this->nrFilme];
		for (int i = 0; i < nrFilme; i++) {
			this->filme[i] = filme[i];
		}
	}

	int getNrSeriale() {
		return nrSeriale;
	}

	void setNrSeriale(int nrSeriale) {
		this->nrSeriale = nrSeriale;
	}

	string* getSeriale() {
		return seriale;
	}

	void setSeriale(int nrSeriale, string* seriale) {
		delete[] seriale;

		this->nrSeriale = nrSeriale;
		this->seriale = new string[this->nrSeriale];
		for (int i = 0; i < nrSeriale; i++) {
			this->seriale[i] = seriale[i];
		}
	}

	int getMinuteVizionate() {
		return minuteVizionate;
	}

	void setMinuteVizionate(int minuteVizionate) {
		this->minuteVizionate = minuteVizionate;
	}
};

string StreamingService::numeCompanie = "NETFLIX";

void main() {

}