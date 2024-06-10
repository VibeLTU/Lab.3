
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include "Struktura.h"

using namespace std;

int main() {
    // Bandymas sukurti abstrakciosios klases Zmogus objekta
    // Jeigu norite patestuoti, ar galima sukurti nauja zmogus klase, nuimkite "//" zenklus 16-oje eiluteje
    // Zmogus z("Jonas", "Jonaitis"); // Panaikinus šios eilutės komentarą, bus padaryta kompiliavimo klaida

    // Sekmingai sukurkite isvestinės klases Studentas objekta
    Studentas s("Petras", "Petraitis", {9.5, 8.5, 10}, 9.0, 9.1, 9.5);

    s.print();
    int choice;
    Vector<Studentas> A;
    while (true) {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1. Ivesti duomenis ranka" << endl;
        cout << "2. Generuoti pazymius" << endl;
        cout << "3. Generuoti pazymius ir studentu vardus, pavardes" << endl;
        cout << "4. Nuskaityti duomenis is failo" << endl;
        cout << "5. Rikiuoti duomenis" << endl;
        cout << "6. Isvesti duomenis" << endl;
        cout << "7. Generuoti faila su studentais" << endl;
        cout << "8. Kategorizuoti studentus pagal galutini bala" << endl;
        cout << "9. Patikrinti 1.2v" << endl;
        cout << "10. Patikrinti 3.0v std::vector" << endl;
        cout << "11. Patikrinti 3.0v Vector" << endl;
        cout << "12. Baigti darba" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Klaida: Netinkamas pasirinkimas. Prasome ivesti skaiciu nuo 1 iki 9." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            string temp, temp1;
            double temp2;
            Studentas naujas;
            cout << "Iveskite varda: ";
            cin >> temp;
            naujas.setVardas(temp);
            cout << "Iveskite pavarde: ";
            cin >> temp1;
            naujas.setPavarde(temp1);
            cout << "Iveskite kiek namu darbu rezultatu norite suvesti: ";
            int nd_sk;
            for (int i = 0; i < 1; ++i) {
                cin >> nd_sk;
                if (nd_sk < 1 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }
            cout << "Iveskite namu darbu rezultatus (nuo 1 iki 10): ";
            for (int i = 0; i < nd_sk; ++i) {
                cin >> temp2;
                if (temp2 < 1 || temp2 > 10 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
                else {naujas.addNd(temp2);
                }
            }

            for (int i = 0; i < 1; ++i) {
                    cout << "Iveskite egzamino rezultata: ";
                    cin >> temp2;
                    //cin >> a;
                    //naujas.setEg(a);
                if (temp2 < 1 || temp2 > 10 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu nuo 1 iki 10." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
                else {naujas.setEg(temp2);
                }
            }

            // Skaičiuojame namų darbų vidurkį
            naujas.calculateNdVid();

            // Skaičiuojame medianą iš visų rezultatų
            Vector<double> visiRezultatai = naujas.getNd();
            visiRezultatai.push_back(naujas.getEg());
            naujas.setMediana(median(visiRezultatai));
            // Skaičiuojame galutinį vidurkį
        naujas.setGalutinis(0.4 * naujas.getNdvid() + 0.6 * naujas.getEg());
        A.push_back(naujas);

        } else if (choice == 2) {
            cout << "Kiek mokiniu duomenis sugeneruoti: ";
            int n;
            for (int i = 0; i < 1; ++i) {
            cin >> n;
            if (n < 1 || n > 10 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }

            for (int i = 0; i < n; i++) {
            Studentas naujas;
            string temp, temp1;
            cout << "Iveskite varda: ";
            cin >> temp;
            naujas.setVardas(temp);
            cout << "Iveskite pavarde: ";
            cin >> temp1;
            naujas.setPavarde(temp1);
                cout << "Iveskite kiek namu darbu rezultatu norite sugeneruoti: ";
                int nd_sk;
                for (int i = 0; i < 1; ++i) {
                cin >> nd_sk;
                if (nd_sk < 1 || cin.fail()) {
                    cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    i--; // Pakartotinai įvedimas to paties elemento
                }
            }

                // Sugeneruojame atsitiktinius namų darbų rezultatus
                for (size_t j = 0; j < nd_sk; j++) {
                    naujas.addNd(rand() % 10 + 1);// Sugeneruojame rezultatus nuo 1 iki 10
                }

                // Sugeneruojame atsitiktinį egzamino rezultatą
                naujas.setEg(rand() % 10 + 1); // Sugeneruojame rezultatą nuo 1 iki 10

                // Skaičiuojame namų darbų vidurkį
                naujas.calculateNdVid();

                // Skaičiuojame medianą iš visų rezultatų
                Vector<double> visiRezultatai = naujas.getNd();
                visiRezultatai.push_back(naujas.getEg());
                naujas.setMediana(median(visiRezultatai));

                // Skaičiuojame galutinį vidurkį
                naujas.setGalutinis(0.4 * naujas.getNdvid() + 0.6 * naujas.getEg());

                A.push_back(naujas);
            }

        } else if (choice == 3) {
            cout << "Kiek mokiniu duomenis sugeneruoti: ";
            int n;
            for (int i = 0; i < 1; ++i) {
            cin >> n;
            if (n < 1 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }

            for (int i = 0; i < n; i++) {
                Studentas naujas;
                generuotiBalus(naujas); // Sugeneruoti atsitiktinius namų darbų ir egzamino rezultatus
                naujas.setVardas("Vardas" + to_string(i + 1)); // Sugeneruoti atsitiktinį vardą
                naujas.setPavarde("Pavarde" + to_string(i + 1)); // Sugeneruoti atsitiktinę pavardę

                // Skaičiuojame namų darbų vidurkį
                naujas.calculateNdVid();

                // Skaičiuojame medianą iš visų rezultatų
                Vector<double> visiRezultatai = naujas.getNd();
                visiRezultatai.push_back(naujas.getEg());
                naujas.setMediana(median(visiRezultatai));

                // Skaičiuojame galutinį vidurkį
                naujas.setGalutinis(0.4 * naujas.getNdvid() + 0.6 * naujas.getEg());

                A.push_back(naujas);
            }

        } else if (choice == 4) {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPavadinimas;

        try {
            auto start = chrono::high_resolution_clock::now();
            skaitytiIsFailo(A, failoPavadinimas);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Failo nuskaitymas uztruko: " << diff.count() << " s" << endl;
        } catch ( exception& e) {
            cout << e.what() << endl;
        }
        }else if (choice == 5) {
            int rikiavimoPasirinkimas;
            cout << "Pasirinkite, kaip rikiuoti duomenis:" << endl;
            cout << "1. Pagal varda" << endl;
            cout << "2. Pagal pavarde" << endl;
            cout << "3. Pagal galutini (vid.)" << endl;
            cout << "4. Pagal galutini (med.)" << endl;
            cout << "Jusu pasirinkimas: ";
                        int n;
            for (int i = 0; i < 1; ++i) {
            cin >> rikiavimoPasirinkimas;
            if (rikiavimoPasirinkimas < 1 || rikiavimoPasirinkimas > 4 || cin.fail()) {
            cout << "Klaida: Ivestas netinkamas skaicius. Prasome ivesti sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; // Pakartotinai įvedimas to paties elemento
            }
            }
            auto start = chrono::high_resolution_clock::now();
            if (rikiavimoPasirinkimas == 1) {
                rikiuotiPagalVarda(A);
            } else if (rikiavimoPasirinkimas == 2) {
                rikiuotiPagalPavarde(A);
            } else if (rikiavimoPasirinkimas == 3) {
                rikiuotiPagalGalutiniVidurki(A);
            } else if (rikiavimoPasirinkimas == 4) {
                rikiuotiPagalMediana(A);
            } else {
                cout << "Netinkamas pasirinkimas!" << endl;
            }
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Failo rusiavimas uztruko: " << diff.count() << " s" << endl;
        } else if (choice == 6) {
            int isvedimoPasirinkimas;
            cout << "Pasirinkite, kaip norite isvesti duomenis:" << endl;
            cout << "1. I konsole" << endl;
            cout << "2. I faila 'Isvedimas.txt'" << endl;
            cout << "Jusu pasirinkimas: ";
            cin >> isvedimoPasirinkimas;

            if (isvedimoPasirinkimas == 1) {
                atspausdintiDuomenis(A);
            } else if (isvedimoPasirinkimas == 2) {
                atspausdintiDuomenis(A, true);
            } else {
                cout << "Netinkamas pasirinkimas!" << endl;
            }
        } else if (choice == 7) {
            int irasu_skaicius;
            cout << "Iveskite studentu irasu skaiciu: ";
            cin >> irasu_skaicius;

            if (cin.fail() || irasu_skaicius < 1) {
                cout << "Klaida: Netinkamas studentu irasu skaicius. Iveskite teigiama skaiciu." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            auto start = chrono::high_resolution_clock::now();
            generuotiFailaSuStudentais(irasu_skaicius);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;

            cout << "Failo generavimas uztruko: " << diff.count() << " s" << endl;

        } else if (choice == 8) {
            Vector<Studentas> geri_studentai;
            Vector<Studentas> blogi_studentai;
            int choice1;
            cout << "Pasirinkiti 1, 2 arba 3 strategija:";
            cin >> choice1;
            auto start = chrono::high_resolution_clock::now();
            if(choice1 == 1){
            for ( auto& studentas : A) {
            if (studentas.getGalutinis() >= 5.0) {
            geri_studentai.push_back(studentas);
        } else {
            blogi_studentai.push_back(studentas);
        }
        }
        }
            if (choice1 == 2){
            for (auto it = A.begin(); it != A.end(); ) {
            if (it->getGalutinis() >= 5.0) {
            ++it;
            } else {
            blogi_studentai.push_back(*it);
            //it = A.erase(it);
            }
            }
            }
            if (choice1 == 3) {
    auto partition_point = std::partition(A.begin(), A.end(), []( auto& studentas) {
        return studentas.getGalutinis() >= 5.0;
    });

    std::copy(A.begin(), partition_point, std::back_inserter(geri_studentai));
    std::copy(partition_point, A.end(), std::back_inserter(blogi_studentai));
}
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Rusiavimas uztruko: " << diff.count() << " s" << endl;
    rikiuotiStudentus(geri_studentai, blogi_studentai);
        }
         else if (choice == 9){
    testConstructor();
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignment();
    testMoveAssignment();
    testInputOutput();
         }
         else if (choice == 10) {
            unsigned int sz = 100000000, x=0;  // 100000, 1000000, 10000000, 100000000
            std::vector<int> v1;
            auto start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i){
        v1.push_back(i);
        if(v1.capacity() == v1.size()){x++;}
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "std::vector testas uztruko: " << diff.count() << " s" << endl;
        cout << x << endl;
        }
         else if (choice == 11) {
            unsigned int sz = 100000000, x=0;  // 100000, 1000000, 10000000, 100000000
            Vector<int> v2;
            auto start = chrono::high_resolution_clock::now();
        for (int i = 1; i <= sz; ++i){
        v2.push_back(i);
        if(v2.capacity() == v2.size()){x++;}
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "std::vector testas uztruko: " << diff.count() << " s" << endl;
        cout << x << endl;
        }
        else if (choice == 12){
            break;
        }
         else {
            cout << "Pasirinkimas neteisingas. Bandykite dar karta." << endl;
        }
    }

    return 0;
}
