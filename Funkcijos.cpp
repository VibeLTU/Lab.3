    #include "Struktura.h"
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <algorithm>
    #include <numeric>
    #include <chrono>
    #include <iomanip>
    #include <random>
    #include "Vector_template.h"

    using namespace std;

    double median( Vector<double>& arr) {
        Vector<double> temp = arr;
        sort(temp.begin(), temp.end());
        int size = temp.size();
        if (size % 2 == 0) {
            return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
        } else {
            return temp[size / 2];
        }
    }

    void generuotiBalus(Studentas& studentas) {
        int a;
        a=rand() % 10 + 1;
        for(int i = 0 ; i < a ; i++){
        studentas.addNd(rand() % 10 + 1);
    }
        studentas.setEg(rand() % 10 + 1);
    }

    void atspausdintiDuomenis( Vector<Studentas>& A, bool iFaila) {
        if (iFaila) {
            ofstream out("Isvedimas.txt");
            out << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
            out << "------------------------------------------------------------------------" << endl;
            for ( auto& studentas : A) {
                out << left << setw(15) << studentas.getVardas() << left << setw(15) << studentas.getPavarde() << left << setw(15) << setprecision(3) << studentas.getGalutinis() <<  "         " << left << setw(15) << setprecision(3) <<  studentas.getMediana() << endl;
            }
            out.close();
            cout << "Studentas irasyti i faila 'Isvedimas.txt'" << endl;
        } else {
            cout << "Vardas" << "         " << "Pavarde" << "        " << "Galutinis (Vid.)" << "        " << "Galutinis (Med.)" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            for ( auto& studentas : A) {
                cout << left << setw(15) << studentas.getVardas() << left << setw(15) << studentas.getPavarde() << left << setw(15) << setprecision(3) << studentas.getGalutinis() <<  "         " << left << setw(15) << setprecision(3) <<  studentas.getMediana() << endl;
            }
        }
    }

    void rikiuotiPagalVarda(Vector<Studentas>& A) {
        sort(A.begin(), A.end(), []( Studentas& a,  Studentas& b) {
            return a.getVardas() < b.getVardas();
        });
    }

    void rikiuotiPagalPavarde(Vector<Studentas>& A) {
        sort(A.begin(), A.end(), []( Studentas& a,  Studentas& b) {
            return a.getPavarde() < b.getPavarde();
        });
    }

    void rikiuotiPagalGalutiniVidurki(Vector<Studentas>& A) {
        sort(A.begin(), A.end(), []( Studentas& a,  Studentas& b) {
            return a.getGalutinis() < b.getGalutinis();
        });
    }

    void rikiuotiPagalMediana(Vector<Studentas>& A) {
        sort(A.begin(), A.end(), []( Studentas& a,  Studentas& b) {
            return a.getMediana() < b.getMediana();
        });
    }

    void skaitytiIsFailo(Vector<Studentas>& A,  string& failoPavadinimas) {
        ifstream failas(failoPavadinimas);

        if (!failas.is_open()) {
            throw runtime_error("Klaida: Nepavyko atidaryti failo " + failoPavadinimas);
        }

        string eilute, temp3, temp4;
        getline(failas, eilute); // Praleisti pirma eilute
        while (getline(failas, eilute)) {
            istringstream eilutesSrautas(eilute);
            Studentas naujas;
            eilutesSrautas >> temp3 >> temp4;
            naujas.setVardas(temp3);
            naujas.setPavarde(temp4);
            double pazymys;
            while (eilutesSrautas >> pazymys) {
                naujas.addNd(pazymys);
            }
            naujas.setEgzFromNd();
            Vector<double> visiRezultatai = naujas.getNd();
            naujas.setNdvid(accumulate(visiRezultatai.begin(), visiRezultatai.end(), 0.0) / visiRezultatai.size());
            visiRezultatai.push_back(naujas.getEg());
            naujas.setMediana(median(visiRezultatai));
            naujas.setGalutinis(0.4 * naujas.getNdvid() + 0.6 * naujas.getEg());
            A.push_back(naujas);
        }
        failas.close();



    }

    void generuotiFailaSuStudentais(int irasu_skaicius) {
        ofstream failas;
        string failo_pavadinimas = "Studentai_" + to_string(irasu_skaicius) + ".txt";
        failas.open(failo_pavadinimas);

        if (!failas.is_open()) {
            cout << "Klaida: Nepavyko sukurti failo " << failo_pavadinimas << endl;
            return;
        }

        failas << "Vardas              Pavarde             ND1       ND2       ND3       ND4       ND5       ND6       ND7       ND8       ND9      ND10      ND11      ND12      ND13      ND14      ND15      Egz." << endl;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> nd_distribution(1, 10);
        uniform_int_distribution<> eg_distribution(1, 10);

    for (int i = 0; i < irasu_skaicius; ++i) {
        failas << setw(20) << left << ("Vardas" + to_string(i + 1)) << setw(20) << left << ("Pavarde" + to_string(i + 1));
        for (int j = 0; j < 15; ++j) {
            failas << setw(10) << left << nd_distribution(gen);
        }
        failas << setw(10) << left << eg_distribution(gen) << endl;
    }

        failas.close();
        cout << "Failas " << failo_pavadinimas << " sukurtas sekmingai." << endl;
    }

    void rikiuotiStudentus(Vector<Studentas>& geri_studentai, Vector<Studentas>& blogi_studentai) {
        int rikiavimoPasirinkimas;
        cout << "Pasirinkite, kaip rikiuoti studentus:" << endl;
        cout << "1. Pagal varda" << endl;
        cout << "2. Pagal pavarde" << endl;
        cout << "3. Pagal galutini (vid.)" << endl;
        cout << "4. Pagal galutini (med.)" << endl;
        cout << "Jusu pasirinkimas: ";
        cin >> rikiavimoPasirinkimas;

        if (rikiavimoPasirinkimas == 1) {
            sort(geri_studentai.begin(), geri_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getVardas() < b.getVardas();
            });
            sort(blogi_studentai.begin(), blogi_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getVardas() < b.getVardas();
            });
        } else if (rikiavimoPasirinkimas == 2) {
            sort(geri_studentai.begin(), geri_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getPavarde() < b.getPavarde();
            });
            sort(blogi_studentai.begin(), blogi_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getPavarde() < b.getPavarde();
            });
        } else if (rikiavimoPasirinkimas == 3) {
            sort(geri_studentai.begin(), geri_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getGalutinis() > b.getGalutinis();
            });
            sort(blogi_studentai.begin(), blogi_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getGalutinis() > b.getGalutinis();
            });
        } else if (rikiavimoPasirinkimas == 4) {
            sort(geri_studentai.begin(), geri_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getMediana() > b.getMediana();
            });
            sort(blogi_studentai.begin(), blogi_studentai.end(), []( Studentas& a,  Studentas& b) {
                return a.getMediana() > b.getMediana();
            });
        } else {
            cout << "Netinkamas pasirinkimas!" << endl;
            return;
        }
        auto start = chrono::high_resolution_clock::now();
        // Išvesti gerus studentus į failą "Geri_studentai.txt"
        ofstream geri_failas("Geri_studentai.txt");
        if (!geri_failas.is_open()) {
            cout << "Klaida: Nepavyko sukurti failo Geri_studentai.txt" << endl;
            return;
        }
        geri_failas << "Geri studentai:" << endl;
        geri_failas << "Vardas         Pavarde       (Vid.)        (Med.)" << endl;
        for ( auto& studentas : geri_studentai) {
            geri_failas << left << setw(15) << studentas.getVardas() << setw(15) << studentas.getPavarde() << setw(15) << setprecision(3) << studentas.getGalutinis() << setw(15) << setprecision(3) << studentas.getMediana() << endl;
        }
        geri_failas.close();
        auto geri_end = chrono::high_resolution_clock::now();
        chrono::duration<double> geri_diff = geri_end - start;

        cout << "Geri studentai isvesti i faila Geri_studentai.txt" << endl;
        cout << "Tai uztruko: " << geri_diff.count() << " s" << endl;

        auto blogi_start = chrono::high_resolution_clock::now();

        // Isvesti blogus studentus į failą "Blogi_studentai.txt"
        ofstream blogi_failas("Blogi_studentai.txt");
        if (!blogi_failas.is_open()) {
        cout << "Klaida: Nepavyko sukurti failo Blogi_studentai.txt" << endl;
        return;
        }
        blogi_failas << "Blogi studentai:" << endl;
        blogi_failas << "Vardas         Pavarde       (Vid.)        (Med.)" << endl;
        for ( auto& studentas : blogi_studentai) {
        blogi_failas << left << setw(15) << studentas.getVardas() << setw(15) << studentas.getPavarde() << setw(15) << setprecision(3) << studentas.getGalutinis() << setw(15) << setprecision(3) << studentas.getMediana() << endl;
        }
        blogi_failas.close();
        auto blogi_end = chrono::high_resolution_clock::now();
        chrono::duration<double> blogi_diff = blogi_end - blogi_start;

        cout << "Blogi studentai isvesti i faila Blogi_studentai.txt" << endl;
        cout << "Tai uztruko: " << blogi_diff.count() << " s" << endl;
    }
        void testConstructor()
{
        Vector<double> temp{1, 2, 3, 4};
        Studentas mok("Vardenis", "Pavardenis", temp, 9, 8, 7);
        cout << ":" << endl;
        if (mok.getVardas() == "Vardenis")
        cout << "Vardas tinkamas!" << endl;
        else
        cout << "Vardas netinkamas!" << endl;
        if (mok.getPavarde() == "Pavardenis")
        cout << "Pavarde tinkama!" << endl;
        else
        cout << "Pavarde netinkama!" << endl;
        if (mok.getNd() == temp)
        cout << "Namu darbai tinkami!" << endl;
        else
        cout << "Namu darbai netinkami!" << endl;
        if (mok.getEg() == 9)
        cout << "Egzaminas tinkamas!" << endl;
        else
        cout << "Egzaminas netinkamas!" << endl;
        if (mok.getGalutinis() == 8)
        cout << "Vidurkis tinkamas!" << endl;
        else
        cout << "Vidurkis netinkamas!" << endl;
        if (mok.getMediana() == 7)
        cout << "Mediana tinkama!" << endl;
        else
        cout << "Mediana netinkama!" << endl;
}
    void testCopyConstructor()
{
        Vector<double> temp{1, 2, 3, 4};
        Studentas mok("Vardenis", "Pavardenis", temp, 9, 8, 7);
        Studentas mok1 = mok;
        if (mok1.getVardas() == "Vardenis")
        cout << "Vardas tinkamas!" << endl;
        else
        cout << "Vardas netinkamas!" << endl;
        if (mok1.getPavarde() == "Pavardenis")
        cout << "Pavarde tinkama!" << endl;
        else
        cout << "Pavarde netinkama!" << endl;
        if (mok1.getNd() == temp)
        cout << "Namu darbai tinkami!" << endl;
        else
        cout << "Namu darbai netinkami!" << endl;
        if (mok1.getEg() == 9)
        cout << "Egzaminas tinkamas!"<< endl;
        else
        cout << "Egzaminas netinkamas!" << endl;
        if (mok1.getGalutinis() == 8)
        cout << "Vidurkis tinkamas!" << endl;
        else
        cout << "Vidurkis netinkamas!" << endl;
        if (mok1.getMediana() == 7)
        cout << "Mediana tinkama!" << endl;
        else
        cout << "Mediana netinkama!" << endl;
}
    void testMoveConstructor()
{
        Vector<double> temp{1, 2, 3, 4};
        Studentas mok("Vardenis", "Pavardenis", temp, 9, 8, 7);
        Studentas mok1 = move(mok);
        if (mok1.getVardas() == "Vardenis")
        cout << "Vardas tinkamas!" << endl;
        else
        cout << "Vardas netinkamas!" << endl;
        if (mok1.getPavarde() == "Pavardenis")
        cout << "Pavarde tinkama!" << endl;
        else
        cout << "Pavarde netinkama!" << endl;
        if (mok1.getNd() == temp)
        cout << "Namu darbai tinkami!" << endl;
        else
        cout << "Namu darbai netinkami!" << endl;
        if (mok1.getEg() == 9)
        cout << "Egzaminas tinkamas!" << endl;
        else
        cout << "Egzaminas netinkamas!" << endl;
        if (mok1.getGalutinis() == 8)
        cout << "Vidurkis tinkamas!" << endl;
        else
        cout << "Vidurkis netinkamas!" << endl;
        if (mok1.getMediana() == 7)
        cout << "Mediana tinkama!" << endl;
        else
        cout << "Mediana netinkama!" << endl;
}
    void testCopyAssignment()
{
        Vector<double> temp{1, 2, 3, 4};
        Studentas mok("Vardenis", "Pavardenis", temp, 9, 8, 7);
        Studentas mok1;
        mok1 = mok;
        if (mok1.getVardas() == "Vardenis")
        cout << "Vardas tinkamas!" << endl;
        else
        cout << "Vardas netinkamas!" << endl;
        if (mok1.getPavarde() == "Pavardenis")
        cout << "Pavarde tinkama!" << endl;
        else
        cout << "Pavarde netinkama!" << endl;
        if (mok1.getNd() == temp)
        cout << "Namu darbai tinkami!" << endl;
        else
        cout << "Namu darbai netinkami!" << endl;
        if (mok1.getEg() == 9)
        cout << "Egzaminas tinkamas!" << endl;
        else
        cout << "Egzaminas netinkamas!" << endl;
        if (mok1.getGalutinis() == 8)
        cout << "Vidurkis tinkamas!" << endl;
        else
        cout << "Vidurkis netinkamas!" << endl;
        if (mok1.getMediana() == 7)
        cout << "Mediana tinkama!" << endl;
        else
        cout << "Mediana netinkama!" << endl;
}
    void testMoveAssignment()
{
        Vector<double> temp{1, 2, 3, 4};
        Studentas mok("Vardenis", "Pavardenis", temp, 9, 8, 7);
        Studentas mok1;
        mok1 = move(mok);
        if (mok1.getVardas() == "Vardenis")
        cout << "Vardas tinkamas!" << endl;
        else
        cout << "Vardas netinkamas!" << endl;
        if (mok1.getPavarde() == "Pavardenis")
        cout << "Pavarde tinkama!" << endl;
        else
        cout << "Pavarde netinkama!" << endl;
        if (mok1.getNd() == temp)
        cout << "Namu darbai tinkami!" << endl;
        else
        cout << "Namu darbai netinkami!" << endl;
        if (mok1.getEg() == 9)
        cout << "Egzaminas tinkamas!" << endl;
        else
        cout << "Egzaminas netinkamas!" << endl;
        if (mok1.getGalutinis() == 8)
        cout << "Vidurkis tinkamas!" << endl;
        else
        cout << "Vidurkis netinkamas!" << endl;
        if (mok1.getMediana() == 7)
        cout << "Mediana tinkama!" << endl;
        else
        cout << "Mediana netinkama!" << endl;
}
    void testInputOutput()
{
        istringstream mok("Vardenis pavardenis 1 2 3 4 5 9");
        Studentas mok2;
        mok >> mok2;
        cout << "Nuskaityta is srauto i mok1: " << mok2 << endl;
}
