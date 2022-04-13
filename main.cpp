#include <iostream>
#include <cstring>
#include <string>
using namespace std;
/*Departamentul „Salarizare” al firmei X actualizează fișele întregului personal
utilizând o aplicație OOP. În acest scop se vor implementa clasele:
-Data (int zi, char *luna, int an);
-Angajat (string nume, string prenume, float salariu, Data data_angajare);
-Part_Time (int nr_ore_zi, Data final_contract) : Angajat
-Permanent (int nr_minori_intretinere) :Angajat
De sărbători fiecare angajat va primi o primă. Angajatul permanent va primi pe lângă
suma standard și un spor calculat ca un procent din prima fixă, egal cu vechimea lui în
firmă, calculată până la 31 decembrie 2020 (de exemplu: dacă vechimea lui în firmă este
de 12 ani, atunci va primi pentru pentru fiecare copil minor 12% * suma standard
stabilită de firmă, etc), iar angajații part-time vor primi suma standard stabilită dacă
contractul lor nu se termină până la sfârșitul lunii curente, altfel, primesc doar 75% din
suma standard prevăzută.*/

int lunaNumber (char *luna){
    if (strcmp(luna, "ianuarie") == 0)
        return 1;
    if (strcmp(luna, "februarie") == 0)
        return 2;
    if (strcmp(luna, "martie") == 0)
        return 3;
    if (strcmp(luna, "aprilie") == 0)
        return 4;
    if (strcmp(luna, "mai") == 0)
        return 5;
    if (strcmp(luna, "iunie") == 0)
        return 6;
    if (strcmp(luna, "iulie") == 0)
        return 7;
    if (strcmp(luna, "august") == 0)
        return 8;
    if (strcmp(luna, "septembrie") == 0)
        return 9;
    if (strcmp(luna, "octombrie") == 0)
        return 10;
    if (strcmp(luna, "noiembrie") == 0)
        return 11;
    if (strcmp(luna, "decembrie") == 0)
        return 12;
    return 0;
}

class MyOutOfBoundsException : public exception{
public:
    MyOutOfBoundsException() = default;

    const char* what() const noexcept override{
        return "Angajat permanent sau part-time?";
    }
};

class Data{
private:
    int zi;
    char *luna = nullptr;
    int an;
public:
    void setZi(int zi_){
        zi = zi_;
    }
    int getZi() const {
        return zi;
    }
    void setAn(int an_){
        an = an_;
    }
    int getAn() const {
        return an;
    }
    void setLuna(char *luna_){
        delete[] luna;

        size_t len = strlen(luna_);
        luna = new char[len];
        strcpy(luna, luna_);
    }
    char *getLuna() const {
        return luna;
    }
    Data(){ }
    Data(int zi_, const char* luna_, int an_){
        size_t len = strlen(luna_);
        luna = new char[len];
        strcpy(luna, luna_);
        zi = zi_;
        an = an_;
    }
    ~Data(){
        delete[] luna;
    }
    Data(const Data &date){
        size_t len = strlen(date.luna);
        luna = new char[len];
        strcpy(luna, date.luna);
        zi = date.zi;
        an = date.an;
    }
    Data& operator=(const Data &newData) {
        this->setLuna(newData.getLuna());
        this->an = newData.an;
        this->zi = newData.zi;
        return *this;
    }
    bool operator==(const Data &rhs) const {
        return zi == rhs.zi &&
               strcmp(luna, rhs.luna) == 0 &&
               an == rhs.an;
    }
    bool operator!=(const Data &rhs) const {
        return !(rhs == *this);
    }
    friend ostream &operator<<(ostream &os, const Data &data) {
        os << "Zi: " << data.zi << " Luna: " << data.luna << " An: " << data.an;
        return os;
    }
    friend istream &operator>>(istream &is, Data &data) {
        is >> data.zi;
        char buf[100];
        is >> buf;
        data.setLuna(buf);
        is >> data.an;
        return is;
    }
};

class Angajat{
protected:
    string nume;
    string prenume;
    float salariu;
    Data data_angajare;
public:
    void setNume(string nume_){
        nume = nume_;
    }
    string getNume(){
        return nume;
    }
    void setPrenume(string prenume_){
        prenume = prenume_;
    }
    string getPrenume(){
        return prenume;
    }
    void setSalariu(float salariu_){
        salariu = salariu_;
    }
    float getSalariu(){
        return salariu;
    }
    void setData_Angajare(Data const data_angajare_){
        data_angajare = data_angajare_;
    }
    Data getData_Angajare(){
        return data_angajare;
    }
    virtual ~Angajat(){
    };
    Angajat(string nume_, string prenume_, float salariu_, Data data_angajare_){
        nume = nume_;
        prenume = prenume_;
        salariu = salariu_;
        data_angajare = data_angajare_;
    }
    Angajat(const Angajat &a){
        nume = a.nume;
        prenume = a.prenume;
        salariu = a.salariu;
        data_angajare = a.data_angajare;
    }
    Angajat& operator=(const Angajat &newAng) {
        this->nume = newAng.nume;
        this->prenume = newAng.prenume;
        this->salariu = newAng.salariu;
        this->data_angajare = newAng.data_angajare;
        return *this;
    }
    bool operator==(const Angajat &rhs) const {
        return nume == rhs.nume &&
               prenume == rhs.prenume &&
               salariu == rhs.salariu &&
               data_angajare == rhs.data_angajare;
    }
    bool operator!=(const Angajat &rhs) const {
        return !(rhs == *this);
    }
    friend ostream &operator<<(ostream &os, const Angajat &angajat) {
        os << "Nume: " << angajat.nume << " Prenume: " << angajat.prenume << " Salariu: " << angajat.salariu
           << " Data_angajare: " << angajat.data_angajare;
        return os;
    }
    friend istream &operator>>(istream &is, Angajat &a) {
        is >> a.nume;
        is >> a.prenume;
        is >> a.salariu;
        Data d = Data();
        is >> d;
        a.data_angajare = d;
        return is;
    }
    virtual int CalculPrima(){
        throw MyOutOfBoundsException();
    };
};

class Part_Time:public Angajat{
private:
    int nr_ore_zi;
    Data final_contract;
public:
    void setNr_ore_zi(int nr_ore_zi_){
        nr_ore_zi = nr_ore_zi_;
    }
    int getNr_ore_zi(){
        return nr_ore_zi;
    }
    void setFinal_contract(Data const final_contract_){
        final_contract = final_contract_;
    }
    Data getFinal_contract(){
        return final_contract;
    }
    ~Part_Time(){
    }
    Part_Time(string nume_, string prenume_, float salariu_, Data const data_angajare_, int nr_ore_zi_, Data const final_contract_):
    Angajat(nume_, prenume_, salariu_, data_angajare_){
        nr_ore_zi = nr_ore_zi_;
        final_contract = final_contract_;
    }
    Part_Time(const Part_Time &p):Angajat(p){
        nr_ore_zi = p.nr_ore_zi;
        final_contract = p.final_contract;
    }
    Part_Time& operator=(const Part_Time &newPart) {
        this->nume = newPart.nume;
        this->prenume = newPart.prenume;
        this->salariu = newPart.salariu;
        this->data_angajare = newPart.data_angajare;
        this->nr_ore_zi = newPart.nr_ore_zi;
        this->final_contract = newPart.final_contract;
        return *this;
    }
    bool operator==(const Part_Time &rhs) const {
        return static_cast<const Angajat &>(*this) == static_cast<const Angajat &>(rhs) &&
               nr_ore_zi == rhs.nr_ore_zi &&
               final_contract == rhs.final_contract;
    }
    bool operator!=(const Part_Time &rhs) const {
        return !(rhs == *this);
    }
    friend ostream &operator<<(ostream &os, const Part_Time &time) {
        os << static_cast<const Angajat &>(time) << " Nr_ore_zi: " << time.nr_ore_zi << " Final_contract: "
           << time.final_contract;
        return os;
    }
    friend istream &operator>>(istream &is, Part_Time &p) {
        is >> static_cast<Angajat &>(p);
        is >> p.nr_ore_zi;
        is >> p.final_contract;
        return is;
    }
    int CalculPrima() override {
        Data data_curenta;
        cout << "Care este data de astazi? " << endl;
        cin >> data_curenta;
        if (final_contract.getAn() <= data_curenta.getAn())
            if (lunaNumber(final_contract.getLuna()) <= lunaNumber(data_curenta.getLuna()))
                return salariu;
        return salariu * 75 / 100;
    }
};

class Permanent:Angajat{
private:
    int nr_minori_intretinere;
public:
    void setNr_minori(int nr_minori_intretinere_){
        nr_minori_intretinere = nr_minori_intretinere_;
    }
    int getNr_minori(){
        return nr_minori_intretinere;
    }
    ~Permanent(){

    };
    Permanent(string nume_, string prenume_, float salariu_, Data data_angajare_, int nr_minori_intretinere_)
    :Angajat(nume_, prenume_, salariu_, data_angajare_){
        nr_minori_intretinere = nr_minori_intretinere_;
    }
    Permanent(const Permanent &p):Angajat(p){
        nr_minori_intretinere = p.nr_minori_intretinere;
    }
    Permanent& operator=(const Permanent &newPerm) {
        this->nume = newPerm.nume;
        this->prenume = newPerm.prenume;
        this->salariu = newPerm.salariu;
        this->data_angajare = newPerm.data_angajare;
        this->nr_minori_intretinere = newPerm.nr_minori_intretinere;
        return *this;
    }
    bool operator==(const Permanent &rhs) const {
        return static_cast<const Angajat &>(*this) == static_cast<const Angajat &>(rhs) &&
               nr_minori_intretinere == rhs.nr_minori_intretinere;
    }
    bool operator!=(const Permanent &rhs) const {
        return !(rhs == *this);
    }
    friend ostream &operator<<(ostream &os, const Permanent &p) {
        os << static_cast<const Angajat &>(p);
        os << " Nr minori intretinere: " << p.nr_minori_intretinere;
        return os;
    }
    friend istream &operator>>(istream &is, Permanent &p) {
        is >> static_cast<Angajat &>(p);
        is >> p.nr_minori_intretinere;
        return is;
    }
    int CalculPrima() override{
        return float(nr_minori_intretinere) * float((2020 - data_angajare.getAn())) * salariu + salariu;
    }
};
int main() {
    Data d1 = Data(10, "octombrie", 2021);
    Data data_curenta = Data(11, "aprilie", 2021);
    Angajat a1 = Angajat("Andrei", "Mario", 100, d1);
    Permanent b1 = Permanent ("Andrei", "Andrei" , 100, d1, 2);
    //cout << b1.CalculPrima();
    Part_Time p1 = Part_Time("Velciu", "razvan", 100, d1, 5, d1);
    //cout << p1.CalculPrima(data_curenta);
    //cin >> d1;
    //cin >> a1;
    //cin >> b1;
    //cin >> p1;
    //cout << d1 << endl;
    //cout << a1 << endl;
    //cout << b1 << endl;
    //cout << p1 << endl;
    /*try{
        a1.CalculPrima();
    }
    catch (const MyOutOfBoundsException &e){
        cout << e.what() << endl;
    }*/
    return 0;
}
