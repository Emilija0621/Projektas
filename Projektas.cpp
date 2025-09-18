#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<random>
#include<cctype>
#include<fstream>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::sort;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::invalid_argument;
using std::ifstream;
using std::getline;
using std::istringstream;


struct studentas{
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzamino_pazymys;
    double galutinis_vidurkis;
    double galutinis_mediana;
};


studentas studentas_ivestis(bool atsitiktiniai_balai);
double skaiciuoti_galutinis_pazymys(const vector<int>& pazymiai, int egzaminas, bool naudoti_mediana = false);
double skaiciuoti_mediana(vector<int> pazymiai);
double skaiciuoti_vidurki(const vector<int>& pazymiai);
int generuoti_atsitiktini_bala();
void nuskaityti_duomenis_is_failo(const string& failo_pavadinimas, vector<studentas>& grupe);
int galutiniai_pazymiai(vector<studentas>& grupe);
void spausdinti_studentus(const vector<studentas>& grupe, int pasirinkimas);


int main() {
    vector<studentas> grupe;
    int pasirinkimas1;

    while (true) {
        while (true) {
            cout << "Pasirinkite veiksmą: " << endl;
            cout << "1 - Įvesti studentą su turimais duomenimis" << endl;
            cout << "2 - Įvesti vardą ir pavardę, bet pažymius generuoti atsitiktinai" << endl;
            cout << "3 - Spausdinti studentų rezultatus" << endl;
            cout << "4 - Nuskaityti studentų duomenis iš failo" << endl;
            cout << "5 - Išeiti" << endl;

            string ivestis;
            cin >> ivestis;

            try {
                pasirinkimas1 = stoi(ivestis);
                if (pasirinkimas1 < 1 || pasirinkimas1 > 5) {
                    cout << "Neteisingas pasirinkimas. Įveskite skaičių nuo 1 iki 5." << endl;
                    continue;
                }
                break;
            } catch (const invalid_argument&) {
                cout << "Įvesta netinkama reikšmė. Įveskite skaičių nuo 1 iki 5." << endl;
            }
        }

        if (pasirinkimas1 == 1) {
            grupe.push_back(studentas_ivestis(false));

        } else if (pasirinkimas1 == 2) {
            grupe.push_back(studentas_ivestis(true));

        } else if (pasirinkimas1 == 3) {
            
            int pasirinkimas = galutiniai_pazymiai(grupe);
            spausdinti_studentus(grupe, pasirinkimas);

        } else if (pasirinkimas1 == 4) {
            cout << "Įveskite failo pavadinimą: ";
            string failas;
            cin >> failas;
            nuskaityti_duomenis_is_failo(failas, grupe);

        } else if (pasirinkimas1 == 5) {
            cout << "Programa baigta." << endl;
            break;
            
        } else {
            cout << "Neteisingas pasirinkimas." << endl;
        }
    }
}


void spausdinti_studentus(const vector<studentas>& grupe, int pasirinkimas) {
    vector<studentas> surusiuota = grupe;
    sort(surusiuota.begin(), surusiuota.end(), [](auto &a, auto &b){
        return a.vardas < b.vardas;
    });

    if (pasirinkimas == 1){
        cout << setw(12) << left << "Vardas" << "|" << setw(15) << left << "Pavardė" << "|" << setw(5) << left << "Galutinis (Vid.)" << endl;
        cout << string(46, '-') << endl;
        for (auto past: surusiuota){
            cout << setw(12) << left << past.vardas << "|" << setw(15) << left << past.pavarde << "|";
            cout << setw(15) << fixed << setprecision(2) << past.galutinis_vidurkis << endl;
        }
        
    } else if (pasirinkimas == 2) {
        cout << setw(12) << left << "Vardas" << "|" << setw(15) << left << "Pavardė" << "|" << setw(5) << left << "Galutinis (Med.)" << endl;
        cout << string(46, '-') << endl;
        for (auto past: surusiuota){
            cout << setw(12) << left << past.vardas << "|" << setw(15) << left << past.pavarde << "|";
            cout << setw(15) << fixed << setprecision(2) << past.galutinis_mediana << endl;
        }
        
    } else if (pasirinkimas == 3){
        cout << setw(12) << left << "Vardas" << "|" << setw(15) << left << "Pavardė" << "|" << setw(5) << left << "Galutinis (Vid.)" << "|" << setw(5) << left << "Galutinis (Med.)" << endl;
        cout << string(55, '-') << endl;
        for (auto past: surusiuota){
            cout << setw(12) << left << past.vardas << "|" << setw(15) << left << past.pavarde << "|";
            cout << setw(15) << fixed << setprecision(2) << past.galutinis_vidurkis << "|" << setw(15) << fixed << setprecision(2) << past.galutinis_mediana << endl;
        }
    }
}


int galutiniai_pazymiai(vector<studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Studentų duomenų dar nėra." << endl;
        return 0;
    }

    int pasirinkimas;
    while (true) {
        cout << "Pasirinkite kaip norėsite skaičiuoti galutinį įvertinimą" << endl;
        cout << "1 - su vidurkiu\n2 - su mediana\n3 - noriu gauti abejais būdais suskaičiuotus įvertinimus" << endl;

        string ivestis;
        cin >> ivestis;

        try {
            pasirinkimas = stoi(ivestis);
            if (pasirinkimas < 1 || pasirinkimas > 3) {
                cout << "Neteisingas pasirinkimas. Įveskite skaičių nuo 1 iki 3." << endl;
                continue;
            }
            break;
        } catch (const invalid_argument&) {
            cout << "Įvesta netinkama reikšmė. Įveskite skaičių nuo 1 iki 3." << endl;
        }
    }

    for (auto &s : grupe) {
        s.galutinis_vidurkis = skaiciuoti_galutinis_pazymys(s.pazymiai, s.egzamino_pazymys, false);
        s.galutinis_mediana = skaiciuoti_galutinis_pazymys(s.pazymiai, s.egzamino_pazymys, true);
    }

    return pasirinkimas;
}


studentas studentas_ivestis(bool atsitiktiniai_balai){
    
    string ivestis;
    studentas pirmas;
    cout << "Įveskite studento duomenis." << endl;
    
    while (true){
        cout << "Vardas: "; cin >> pirmas.vardas;
        bool tikriname = true;
        for (char c: pirmas.vardas){
            if(!isalpha(c)){
                tikriname = false;
                break;
            }
        }
        if(tikriname) break;
                cout << "Vardas turi būti sudarytas tik iš raidžių." << endl;
    }
    
    while (true){
        cout << "Pavardė: "; cin >> pirmas.pavarde;
        bool tikriname = true;
        for (char c: pirmas.pavarde){
            if(!isalpha(c)){
                tikriname = false;
                break;
            }
        }
        if(tikriname) break;
                cout << "Pavardė turi būti sudarytas tik iš raidžių." << endl;
    }

    if (atsitiktiniai_balai){
        
        int kiek;
        while (true) {
            cout << "Kiek norite sugeneruoti pažymių? ";
            string ivestis;
            cin >> ivestis;

            try {
                kiek = stoi(ivestis);
                if (kiek < 1) {
                    cout << "Turi būti teigiamas skaičius. Bandykite dar kartą." << endl;
                    continue;
                }
                break;
            } catch (const invalid_argument&) {
                cout << "Įvesta netinkama reikšmė. Įveskite skaičių." << endl;
            }
        }
        
            for (int i=0; i<kiek; i++){
                pirmas.pazymiai.push_back(generuoti_atsitiktini_bala());
            }
        
            pirmas.egzamino_pazymys = generuoti_atsitiktini_bala();
        
        } else {
            cout << "įveskite studento pažymius (parašykite baigta, kai baigėte)"<< endl;
            
            while (true){
                cout << pirmas.pazymiai.size() + 1 << ". ";
                cin >> ivestis;
                if (ivestis == "baigta"){
                    break;
                }
                try {
                    int konvertuota = stoi(ivestis);
                    if (konvertuota < 1 || konvertuota > 10) {
                        cout << "Balas turi būti nuo 1 iki 10. Bandykite dar kartą." << endl;
                        continue;
                    }
                    pirmas.pazymiai.push_back(konvertuota);
                } catch (const invalid_argument&) {
                    cout << "Įvesta netinkama reikšmė. Įveskite skaičių nuo 1 iki 10 arba 'baigta'." << endl;
                }
            }
            
            while (true) {
                cout << "Įveskite egzamino pažymį: ";
                string ivestis;
                cin >> ivestis;

                try {
                    int egzaminas = stoi(ivestis);
                    if (egzaminas < 1 || egzaminas > 10) {
                        cout << "Egzamino pažymys turi būti nuo 1 iki 10. Bandykite dar kartą." << endl;
                        continue;
                    }
                    pirmas.egzamino_pazymys = egzaminas;
                    break;
                } catch (const invalid_argument&) {
                    cout << "Įvesta netinkama reikšmė. Įveskite skaičių nuo 1 iki 10." << endl;
                }
            }
        }
        return pirmas;
}


double skaiciuoti_vidurki(const vector<int>& pazymiai){
    if (pazymiai.empty()) return 0;
    double suma = 0;
    for (auto paz: pazymiai){
        suma += paz;
    }
    return suma / pazymiai.size();
}


double skaiciuoti_mediana(vector<int> pazymiai){
    if (pazymiai.empty()) return 0;
    sort(pazymiai.begin(), pazymiai.end());
    auto n = pazymiai.size();
    
    if (n % 2 == 1) {
            return pazymiai[n / 2];
        } else {
            return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
        }
}


double skaiciuoti_galutinis_pazymys(const vector<int>& pazymiai, int egzaminas, bool naudoti_mediana){
    double galutinis = 0;
    
    if (naudoti_mediana){
        galutinis = skaiciuoti_mediana(pazymiai) * 0.4 + egzaminas * 0.6;
    } else {
        galutinis = skaiciuoti_vidurki(pazymiai) * 0.4 + egzaminas * 0.6;
    }
    return galutinis;
}


int generuoti_atsitiktini_bala(){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

void nuskaityti_duomenis_is_failo(const string& failo_pavadinimas, vector<studentas>& grupe){
    ifstream in(failo_pavadinimas);
    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
        return;
    }

    string eilute;
    if (!getline(in, eilute)) {
        cout << "Failas " << failo_pavadinimas << " tuščias arba netinkamas." << endl;
        return;
    }

    size_t eil_nr = 1;

    istringstream antraste(eilute);
    vector<string> stulpeliai;
    string stulp;
    while (antraste >> stulp) stulpeliai.push_back(stulp);
    size_t nd_kiekis = stulpeliai.size() - 3;

    while (getline(in, eilute)) {
        ++eil_nr;
        if (eilute.empty()) continue;

        istringstream iss(eilute);
        studentas duomenys;

        if (!(iss >> duomenys.vardas >> duomenys.pavarde)) {
            cout << "Praleista eilutė " << eil_nr << "." << " (nerastas vardas/pavardė): " << eilute << endl;
            continue;
        }

        bool klaida = false;
        duomenys.pazymiai.clear();

        for (size_t i = 0; i < nd_kiekis; i++) {
            int nd;
            if (!(iss >> nd) || nd < 1 || nd > 10) {
                cout << "Praleista eilutė " << eil_nr << "." << " (netinkamai įvesti studento duomenys): " << eilute << endl;
                klaida = true;
                break;
            }
            duomenys.pazymiai.push_back(nd);
        }

        if (klaida) continue;

        int egz;
        if (!(iss >> egz) || egz < 1 || egz > 10) {
            cout << "Praleista eilutė " << eil_nr << "." << " (netinkamai įvesti studento duomenys): " << eilute << endl;
            continue;
        }
        duomenys.egzamino_pazymys = egz;

        grupe.push_back(duomenys);
    }

    cout << "Duomenų nuskaitymas baigtas." << endl;
}
