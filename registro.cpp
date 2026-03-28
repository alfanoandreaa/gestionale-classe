#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ordina(vector<string>& nomi, vector<string>& cognomi, vector<float>& voti_mat, vector<float>& voti_inf, vector<float>& voti_ita, vector<float>& medie) {
	for(int i = 0; i < cognomi.size(); i++) {
		for(int j = i + 1; j < cognomi.size(); j++) {
			if(cognomi[i] > cognomi[j] || (cognomi[i] == cognomi[j] && nomi[i] > nomi[j])) {
				string temp_nome = nomi[i];
				nomi[i] = nomi[j];
				nomi[j] = temp_nome;

				string temp_cogn = cognomi[i];
				cognomi[i] = cognomi[j];
				cognomi[j] = temp_cogn;

				float temp_mat = voti_mat[i];
				voti_mat[i] = voti_mat[j];
				voti_mat[j] = temp_mat;

				float temp_inf = voti_inf[i];
				voti_inf[i] = voti_inf[j];
				voti_inf[j] = temp_inf;

				float temp_ita = voti_ita[i];
				voti_ita[i] = voti_ita[j];
				voti_ita[j] = temp_ita;

				float temp_med = medie[i];
				medie[i] = medie[j];
				medie[j] = temp_med;
			}
		}
	}
}

int main() {
	vector<string> nomi;
	vector<string> cognomi;
	vector<float> voti_mat;
	vector<float> voti_inf;
	vector<float> voti_ita;
	vector<float> medie;
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
			string n_nome, n_cogn;
			float v_mat, v_inf, v_ita;
			cout << "inserisci nome: ";
			cin >> n_nome;
			cout << "inserisci cognome: ";
			cin >> n_cogn;
			cout << "voto matematica: ";
			cin >> v_mat;
			cout << "voto informatica: ";
			cin >> v_inf;
			cout << "voto italiano: ";
			cin >> v_ita;

			nomi.push_back(n_nome);
			cognomi.push_back(n_cogn);
			voti_mat.push_back(v_mat);
			voti_inf.push_back(v_inf);
			voti_ita.push_back(v_ita);
			medie.push_back((v_mat + v_inf + v_ita) / 3.0);

			ordina(nomi, cognomi, voti_mat, voti_inf, voti_ita, medie);
			cout << "alunno aggiunto e registro ordinato.\n";
		}
		else if(scelta == 2) {
			if(nomi.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				for(int i = 0; i < nomi.size(); i++) {
					cout << cognomi[i] << " " << nomi[i] << " - media: " << medie[i] << "\n";
				}
			}
		}
		else if(scelta == 3) {
			if(nomi.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float somma_tot = 0;
				for(int i = 0; i < nomi.size(); i++) {
					somma_tot += medie[i];
				}
				cout << "media della classe: " << somma_tot / nomi.size() << "\n";
			}
		}
		else if(scelta == 4) {
			if(nomi.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float somma_voti = 0;
				for(int i = 0; i < nomi.size(); i++) {
					somma_voti += medie[i];
				}
				float m_classe = somma_voti / nomi.size();
				cout << "media classe: " << m_classe << "\n\n";
				cout << "sopra la media:\n";
				for(int i = 0; i < nomi.size(); i++) {
					if(medie[i] >= m_classe) {
						cout << "- " << cognomi[i] << " " << nomi[i] << "\n";
					}
				}
				cout << "\nsotto la media:\n";
				for(int i = 0; i < nomi.size(); i++) {
					if(medie[i] < m_classe) {
						cout << "- " << cognomi[i] << " " << nomi[i] << "\n";
					}
				}
			}
		}
		else if(scelta == 5) {
			int mat_scelta;
			float v_cercato;
			cout << "scegli materia (1=matematica, 2=informatica, 3=italiano): ";
			cin >> mat_scelta;
			cout << "inserisci il voto da cercare: ";
			cin >> v_cercato;
			bool trovato = false;
			for(int i = 0; i < nomi.size(); i++) {
				float v_stud = 0;
				if(mat_scelta == 1) v_stud = voti_mat[i];
				else if(mat_scelta == 2) v_stud = voti_inf[i];
				else if(mat_scelta == 3) v_stud = voti_ita[i];

				if(v_stud == v_cercato) {
					cout << "- " << cognomi[i] << " " << nomi[i] << "\n";
					trovato = true;
				}
			}
			if(trovato == false) cout << "nessuno ha preso questo voto.\n";
		}
		else if(scelta == 6) {
			if(nomi.size() == 0) {
				cout << "registro vuoto.\n";
			} else {
				float max_m = 0, max_in = 0, max_it = 0;
				int id_m = 0, id_in = 0, id_it = 0;

				for(int i = 0; i < nomi.size(); i++) {
					if(voti_mat[i] > max_m) {
						max_m = voti_mat[i];
						id_m = i;
					}
					if(voti_inf[i] > max_in) {
						max_in = voti_inf[i];
						id_in = i;
					}
					if(voti_ita[i] > max_it) {
						max_it = voti_ita[i];
						id_it = i;
					}
				}
				cout << "migliore in matematica: " << cognomi[id_m] << " " << nomi[id_m] << " (" << max_m << ")\n";
				cout << "migliore in informatica: " << cognomi[id_in] << " " << nomi[id_in] << " (" << max_in << ")\n";
				cout << "migliore in italiano: " << cognomi[id_it] << " " << nomi[id_it] << " (" << max_it << ")\n";
			}
		}
		else if(scelta == 7) {
			string no_cerca, co_cerca;
			cout << "inserisci nome: ";
			cin >> no_cerca;
			cout << "inserisci cognome: ";
			cin >> co_cerca;
			bool trovato = false;
			for(int i = 0; i < nomi.size(); i++) {
				if(nomi[i] == no_cerca && cognomi[i] == co_cerca) {
					cout << "trovato: " << cognomi[i] << " " << nomi[i] << "\n";
					cout << "mate: " << voti_mat[i] << ", info: " << voti_inf[i] << ", ita: " << voti_ita[i] << "\n";
					cout << "media: " << medie[i] << "\n";
					trovato = true;
				}
			}
			if(trovato == false) cout << "alunno non trovato.\n";
		}
	}
	return 0;
}
