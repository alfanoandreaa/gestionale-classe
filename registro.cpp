#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ordina(vector<string>& nome, vector<string>& cognome, vector<float>& votomat, vector<float>& votoinf, vector<float>& votoita, vector<float>& media) {
	for(int i = 0; i < cognome.size(); i++) {
		for(int j = i + 1; j < cognome.size(); j++) {
			if(cognome[i] > cognome[j] || (cognome[i] == cognome[j] && nome[i] > nome[j])) {
				string tnome = nome[i];
				nome[i] = nome[j];
				nome[j] = tnome;

				string tcogn = cognome[i];
				cognome[i] = cognome[j];
				cognome[j] = tcogn;

				float tmat = votomat[i];
				votomat[i] = votomat[j];
				votomat[j] = tmat;

				float tinf = votoinf[i];
				votoinf[i] = votoinf[j];
				votoinf[j] = tinf;

				float tita = votoita[i];
				votoita[i] = votoita[j];
				votoita[j] = tita;

				float tmedia = media[i];
				media[i] = media[j];
				media[j] = tmedia;
			}
		}
	}
}

int main() {
	vector<string> nome;
	vector<string> cognome;
	vector<float> votomat;
	vector<float> votoinf;
	vector<float> votoita;
	vector<float> media;
	int scelta = -1;

	while(scelta != 0) {
		cout << "\n--- menu gestionale ---\n";
		cout << "1. aggiungi alunno\n";
		cout << "2. mostra media singoli alunni\n";
		cout << "3. mostra media della classe\n";
		cout << "4. mostra alunni sopra e sotto la media della classe\n";
		cout << "5. cerca alunni per voto e materia\n";
		cout << "6. mostra il migliore per ogni materia\n";
		cout << "7. cerca alunno per nome e cognome\n";
		cout << "0. esci\n";
		cout << "scelta: ";
		cin >> scelta;

		if(scelta == 1) {
			string n, c;
			float m, inf, ita;
			cout << "inserisci nome: ";
			cin >> n;
			cout << "inserisci cognome: ";
			cin >> c;
			cout << "voto matematica: ";
			cin >> m;
			cout << "voto informatica: ";
			cin >> inf;
			cout << "voto italiano: ";
			cin >> ita;

			nome.push_back(n);
			cognome.push_back(c);
			votomat.push_back(m);
			votoinf.push_back(inf);
			votoita.push_back(ita);
			media.push_back((m + inf + ita) / 3.0);

			ordina(nome, cognome, votomat, votoinf, votoita, media);
			cout << "alunno aggiunto e registro ordinato.\n";
		}
		else if(scelta == 2) {
			if(nome.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				for(int i = 0; i < nome.size(); i++) {
					cout << cognome[i] << " " << nome[i] << " - media: " << media[i] << "\n";
				}
			}
		}
		else if(scelta == 3) {
			if(nome.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float sommatot = 0;
				for(int i = 0; i < nome.size(); i++) {
					sommatot += media[i];
				}
				cout << "media della classe: " << sommatot / nome.size() << "\n";
			}
		}
		else if(scelta == 4) {
			if(nome.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float somma = 0;
				for(int i = 0; i < nome.size(); i++) {
					somma += media[i];
				}
				float mediaclasse = somma / nome.size();
				cout << "media classe: " << mediaclasse << "\n\n";
				cout << "sopra la media:\n";
				for(int i = 0; i < nome.size(); i++) {
					if(media[i] >= mediaclasse) {
						cout << "- " << cognome[i] << " " << nome[i] << "\n";
					}
				}
				cout << "\nsotto la media:\n";
				for(int i = 0; i < nome.size(); i++) {
					if(media[i] < mediaclasse) {
						cout << "- " << cognome[i] << " " << nome[i] << "\n";
					}
				}
			}
		}
		else if(scelta == 5) {
			int mat;
			float votocerc;
			cout << "scegli materia (1=matematica, 2=informatica, 3=italiano): ";
			cin >> mat;
			cout << "inserisci il voto da cercare: ";
			cin >> votocerc;
			bool trovato = false;
			for(int i = 0; i < nome.size(); i++) {
				float votostud = 0;
				if(mat == 1) votostud = votomat[i];
				else if(mat == 2) votostud = votoinf[i];
				else if(mat == 3) votostud = votoita[i];

				if(votostud == votocerc) {
					cout << "- " << cognome[i] << " " << nome[i] << "\n";
					trovato = true;
				}
			}
			if(trovato == false) cout << "nessuno ha preso questo voto.\n";
		}
		else if(scelta == 6) {
			if(nome.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float maxmat = 0, maxinf = 0, maxita = 0;
				int idmat = 0, idinf = 0, idita = 0;

				for(int i = 0; i < nome.size(); i++) {
					if(votomat[i] > maxmat) {
						maxmat = votomat[i];
						idmat = i;
					}
					if(votoinf[i] > maxinf) {
						maxinf = votoinf[i];
						idinf = i;
					}
					if(votoita[i] > maxita) {
						maxita = votoita[i];
						idita = i;
					}
				}
				cout << "migliore in matematica: " << cognome[idmat] << " " << nome[idmat] << " (" << maxmat << ")\n";
				cout << "migliore in informatica: " << cognome[idinf] << " " << nome[idinf] << " (" << maxinf << ")\n";
				cout << "migliore in italiano: " << cognome[idita] << " " << nome[idita] << " (" << maxita << ")\n";
			}
		}
		else if(scelta == 7) {
			string nomecerc, cogncerc;
			cout << "inserisci nome: ";
			cin >> nomecerc;
			cout << "inserisci cognome: ";
			cin >> cogncerc;
			bool trovato = false;
			for(int i = 0; i < nome.size(); i++) {
				if(nome[i] == nomecerc && cognome[i] == cogncerc) {
					cout << "trovato: " << cognome[i] << " " << nome[i] << "\n";
					cout << "mate: " << votomat[i] << ", info: " << votoinf[i] << ", ita: " << votoita[i] << "\n";
					cout << "media: " << media[i] << "\n";
					trovato = true;
				}
			}
			if(trovato == false) cout << "alunno non trovato.\n";
		}
	}
	return 0;
}
