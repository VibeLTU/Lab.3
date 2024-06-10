#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <initializer_list>
#include <iterator>
#include "Vector_template.h"

// Abstract base class for a person
class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;

public:
    Zmogus() = default;
    Zmogus(std::string vardas1, std::string pavarde1) : vardas(vardas1), pavarde(pavarde1) {}

    virtual ~Zmogus() = default;

    void setVardas(std::string vardas1) {
        vardas = vardas1;
    }
    std::string getVardas() const {
        return vardas;
    }

    void setPavarde(std::string pavarde1) {
        pavarde = pavarde1;
    }
    std::string getPavarde() const {
        return pavarde;
    }

    // Pure virtual functions making this class abstract
    virtual void print() const = 0;
};

// Derived class for a student
class Studentas : public Zmogus {
private:
    Vector<double> nd;
    double eg;
    double ndvid;
    double galutinis;
    double mediana;

public:
    // Constructors
    Studentas() = default;
    Studentas(std::string vardas1, std::string pavarde1, Vector<double> nd1, double eg1, double galutinis1, double median1)
        : Zmogus(vardas1, pavarde1), nd(nd1), eg(eg1), ndvid(0), galutinis(galutinis1), mediana(median1) {}

    // Destructor
    ~Studentas() = default;

    // Copy Constructor
    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde), nd(other.nd), eg(other.eg), ndvid(other.ndvid), galutinis(other.galutinis), mediana(other.mediana) {}

    // Copy Assignment Operator
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            Zmogus::operator=(other);
            nd = other.nd;
            eg = other.eg;
            ndvid = other.ndvid;
            galutinis = other.galutinis;
            mediana = other.mediana;
        }
        return *this;
    }

    // Move Constructor
    Studentas(Studentas&& other) noexcept
        : Zmogus(std::move(other)), nd(std::move(other.nd)), eg(other.eg), ndvid(other.ndvid), galutinis(other.galutinis), mediana(other.mediana) {}

    // Move Assignment Operator
    Studentas& operator=(Studentas&& other) noexcept {
        if (this != &other) {
            Zmogus::operator=(std::move(other));
            nd = std::move(other.nd);
            eg = other.eg;
            ndvid = other.ndvid;
            galutinis = other.galutinis;
            mediana = other.mediana;
        }
        return *this;
    }

    void setNd(Vector<double> nd1) {
        nd = nd1;
    }
    Vector<double> getNd() const {
        return nd;
    }

    void addNd(double nd1) {
        nd.push_back(nd1);
    }

    void setEg(double eg1) {
        eg = eg1;
    }
    double getEg() const {
        return eg;
    }

    void setNdvid(double ndvid1) {
        ndvid = ndvid1;
    }
    double getNdvid() const {
        return ndvid;
    }

    void setGalutinis(double galutinis1) {
        galutinis = galutinis1;
    }
    double getGalutinis() const {
        return galutinis;
    }

    void setMediana(double mediana1) {
        mediana = mediana1;
    }
    double getMediana() const {
        return mediana;
    }

    void setEgzFromNd() {
        if (!nd.empty()) {
            eg = nd.back();
            nd.pop_back();
        }
    }

    void calculateNdVid() {
        ndvid = 0;
        for (size_t j = 0; j < nd.size(); j++) {
            ndvid += nd[j];
        }
        ndvid /= nd.size();
    }

    // Input and Output Operators
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
        os << studentas.vardas << ' ' << studentas.pavarde << ' ';
        for (auto& grade : studentas.nd) {
            os << grade << ' ';
        }
        os << studentas.eg;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Studentas& studentas) {
        is >> studentas.vardas >> studentas.pavarde;
        double grade;
        while (is >> grade) {
            studentas.nd.push_back(grade);
        }
        return is;
    }

    void print() const override {
        std::cout << vardas << " " << pavarde << std::endl;
    }
};

// Function declarations
void testInputOutput();
void testConstructor();
void testCopyConstructor();
void testMoveConstructor();
void testCopyAssignment();
void testMoveAssignment();
double median(Vector<double>& arr);
void generuotiBalus(Studentas& studentas);
void skaitytiIsFailo(Vector<Studentas>& A, std::string& failoPavadinimas);
void rikiuotiPagalVarda(Vector<Studentas>& A);
void rikiuotiPagalPavarde(Vector<Studentas>& A);
void rikiuotiPagalGalutiniVidurki(Vector<Studentas>& A);
void rikiuotiPagalMediana(Vector<Studentas>& A);
void atspausdintiDuomenis(Vector<Studentas>& A, bool iFaila = false);
void generuotiFailaSuStudentais(int irasuSkaicius);
void rikiuotiStudentus(Vector<Studentas>& geri_studentai, Vector<Studentas>& blogi_studentai);

#endif // STRUKTURA_H_INCLUDED
