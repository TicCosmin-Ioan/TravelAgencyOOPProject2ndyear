#include <iostream>
#include <vector>
using namespace std;

class Reducere
{
private:

public:

    virtual ostream& afisare(ostream& os)const
    {

        return os;

    }

};

class redM : public Reducere
{

private:

    float vald1 = 40;

public:

    void setredM(int x)
    {

        vald1 = x;

    }

    float getRedM()
    {

        return vald1;

    };

};

class redI : public Reducere
{

private:

    float vald2 = 50;

public:

    void setredI(int x)
    {

        vald2 = x;

    }

    float getRedI()
    {

        return vald2;

    };
};

class redP : public Reducere
{

private:

    float valdp = 15;

public:

    void setP(int x)
    {

        valdp = x;

    }

    float getRedP()
    {

        return valdp;

    };

};

class Recenzie
{

private:

    string nClient;
    int pdt;
    float nota;

public:

    Recenzie(string NClient = "", int Pdt = 0, int Nota = 0) : nClient(NClient), pdt(Pdt), nota(Nota)
    {}

    friend ostream& operator<<(ostream& os, const Recenzie& r)
    {

        os << "Client: " << r.nClient << endl;
        os << "Durata sederii sale: " << r.pdt << endl;
        os << "Nota acordata: " << r.nota;
        os << endl;

        return os;

    }

    friend istream& operator>>(istream& is, Recenzie& r)
    {

        cout << "Client: ";
        is >> r.nClient;
        cout << "Durata sederii sale: ";
        is >> r.pdt;
        cout << "Nota acordata: ";
        is >> r.nota;
        cout << endl;

        return is;

    }

};

vector<Recenzie> v;

class Destinatie
{

protected:

    vector<Recenzie> lista;
    string tara, oras, nume;
    float pret;

public:

    Destinatie(const vector<Recenzie> lista = v, string tara = "", string oras = "", string nume = "", float pret = 0) :
        lista(lista), tara(tara), oras(oras), nume(nume), pret(pret)
    {}

    float getpret()
    {

        return pret;

    }

    virtual istream& citire(istream& is)
    {
        int n;

        cout << "Tara: ";
        is >> tara;
        cout << "Oras: ";
        is >> oras;
        cout << "Numele locatiei: ";
        is >> nume;
        cout << "Pret: ";
        is >> pret;
        cout << "Numarul de recenzii: ";

        is >> n;

        if (n != 0)cout << endl;


        for (int i = 0; i < n; i++)
        {

            Recenzie r;
            cout << "Recenzie " << i + 1 << " :" << endl;
            cout << endl;
            is >> r;
            lista.push_back(r);

        }

        return is;

    }

    virtual ostream& afisare(ostream& os)
    {

        int i;

        os << "Tara: " << tara << endl;
        os << "Oras: " << oras << endl;
        os << "Numele locatiei: " << nume << endl;
        os << "Pret: " << pret;

        cout << endl;

        for (i = 0; i < lista.size(); i++)
        {
            os << "Recenzie " << i + 1 << " :";
            os << lista[i];
        }

        return os;

    }

    friend istream& operator>>(istream& is, Destinatie& d)
    {

        d.citire(is);
        return is;

    }

    friend ostream& operator<<(ostream& os, Destinatie& d)
    {

        d.afisare(os);
        return os;

    }

};

class DestinatieMontana : public Destinatie
{

private:

    float ivm;
    float dist;
    int nrt;

public:

    DestinatieMontana(const vector<Recenzie> lista = v, string tara = "", string oras = "", string nume = "", float pret = 0, float ivm = 0, float dist = 0, int nrt = 0) :
        Destinatie(lista, tara, oras, nume, pret), ivm(ivm), dist(dist), nrt(nrt)
    {}

    istream& citire(istream& is)
    {

        Destinatie::citire(is);

        cout << "Inaltimea celui mai apropiat varf montan: ";
        is >> ivm;
        cout << "Distanta pana la acesta: ";
        is >> dist;
        cout << "Numarul de trasee special amenajate din zona: ";
        is >> nrt;

        cout << endl;

        return is;

    }

    ostream& afisare(ostream& os)
    {

        Destinatie::afisare(os);

        os << "Inaltimea celui mai apropiat varf montan: " << ivm << endl;
        os << "Distanta pana la acesta: " << dist << endl;
        os << "Numarul de trasee special amenajate din zona: " << nrt;

        return os;

    }
};

class DestinatieInsulara : public Destinatie
{

private:

    int nriap;
    bool iesire;

public:

    DestinatieInsulara(const vector<Recenzie> lista = v, string tara = "", string oras = "", string nume = "", float pret = 0, int nriap = 0, bool iesire = 0) :
        Destinatie(lista, tara, oras, nume, pret), nriap(nriap), iesire(iesire)
    {}

    istream& citire(istream& is)
    {

        Destinatie::citire(is);

        cout << "Insula cu iesire la: (0 pentru mare, 1 pentru ocean): ";
        is >> iesire;

        cout << "Numarul de insule din apropiere: ";

        is >> nriap;

        cout << endl;

        return is;

    }

    ostream& afisare(ostream& os)
    {
        Destinatie::afisare(os);

        os << "Insula cu iesire la: (0 pentru mare, 1 pentru ocean) " << iesire << endl;

        os << "Numarul de insule din apropiere: " << nriap;

        return os;

    }
};

vector<Destinatie*> d;

class TravelAgency
{

private:

    vector<Destinatie*> destinatii;
    vector<Reducere*> reduceri;

public:

    int getNrDest()
    {
        return destinatii.size();
    }

    void stergeDest(int n)
    {
        destinatii.erase(destinatii.begin() + n - 1);
    }

    template<class Destinatie>void adaugaDest(Destinatie d)
    {

        Destinatie* nd;
        nd = new Destinatie;
        *nd = d;
        destinatii.push_back(nd);

    }

    friend ostream& operator<<(ostream& os, const TravelAgency& travelAgency)
    {
        int ct = 1;
        for (auto i : travelAgency.destinatii)
        {
            os << endl;
            os << "Destinatie " << ct << ": " << endl;
            os << endl;
            os << *i << endl;
            ct++;
        }

        os << endl;

        return os;

    }

    void run()
    {
        int var1;

        cout << "Selectati cerinta: " << endl;
        cout << "1: Adauga o destinatie. " << endl;
        cout << "2: Sterge o destinatie. " << endl;
        cout << "3: Afiseaza toate destinatiile disponibile. " << endl;
        cout << "4: Exit. " << endl;

        TravelAgency Agentie;

        do
        {

            cin >> var1;
            cout << endl;

            if (var1 < 1 || var1>4)
            {

                cout << "Operatiune nereusita." << endl;

            }

            else if (var1 == 1)
            {
                int var2;

                cout << "Tipul destinatiei: " << endl;
                cout << "1: Destinatie montana. " << endl;
                cout << "2: Destinatie insulara. " << endl;

                cin >> var2;
                cout << endl;

                if (var2 < 1 || var2 > 2)
                {

                    cout << "Operatiune nereusita." << endl;

                }

                else if (var2 == 1)
                {

                    DestinatieMontana dM;
                    cin >> dM;
                    Agentie.adaugaDest(dM);

                }

                else if (var2 == 2)
                {
                    DestinatieInsulara dM;
                    cin >> dM;
                    Agentie.adaugaDest(dM);

                }
            }

            else if (var1 == 2)
            {
                if (Agentie.getNrDest() != 0)
                {

                    cout << Agentie << endl;

                }

                if (Agentie.getNrDest() == 0)
                {

                    cout << "Nu avem nicio destinatie." << endl;

                }

                else
                {
                    int var2;

                    cout << "Introduceti numarul destinatiei pe care doriti sa o stergeti:" << endl;

                    cin >> var2;
                    cout << endl;

                    if (var2 >= 1 && var2 <= Agentie.getNrDest())
                    {

                        Agentie.stergeDest(var2);

                    }

                    else
                    {

                        cout << "Nu exista destinatia cu numarul " << var2 << "." << endl;

                    }
                }
            }

            else if (var1 == 3)
            {
                if (Agentie.getNrDest() == 0)
                {

                    cout << "Nu avem nicio destinatie." << endl;

                }

                else
                {
                    cout << Agentie;
                }
            }

            else if (var1 == 4)
            {
                break;
            }

            cout << endl;

            cout << "Selectati cerinta: " << endl;
            cout << "1: Adauga o destinatie. " << endl;
            cout << "2: Sterge o destinatie. " << endl;
            cout << "3: Afiseaza toate destinatiile disponibile. " << endl;
            cout << "4: Exit. " << endl;

        } while (var1 != 4);
    }

//metoda ce seteaza discount
    void setReducere(Reducere& r, int x)
    {
        try
        {
            dynamic_cast<redM&>(r).setredM(x);

        }
        catch (bad_cast&) {};

        try
        {
            dynamic_cast<redI&>(r).setredI(x);

        }
        catch (bad_cast&) {};

        try
        {
            dynamic_cast<redP&>(r).setP(x);

        }
        catch (bad_cast&) {};
    }

//metoda ce afisaza date despre destinatie si pretul dupa ce s-a aplicat discountul maxim
    void afisDesti(Destinatie& d)
    {
        cout << d;

        int i, valM = 0;

        for (i = 0; i < reduceri.size(); i++)
        {


            if (dynamic_cast<redM*>(reduceri[i]) != nullptr)
            {

                if (dynamic_cast<redM*>(reduceri[i])->getRedM() > valM)
                {

                    valM = dynamic_cast<redM*>(reduceri[i])->getRedM();


                }

            }

            else if (dynamic_cast<redI*>(reduceri[i]) != nullptr)
            {

                if (dynamic_cast<redI*>(reduceri[i])->getRedI() > valM)
                {

                    valM = dynamic_cast<redI*>(reduceri[i])->getRedI();

                }

            }

            else if (dynamic_cast<redP*>(reduceri[i]) != nullptr)
            {

                if ((dynamic_cast<redP*>(reduceri[i])->getRedP() / 100) * d.getpret() > valM)
                {

                    valM = (dynamic_cast<redP*>(reduceri[i])->getRedP() / 100) * d.getpret();

                }

            }



        }

        cout << d.getpret() - valM;

    }

};

int main()
{

    TravelAgency Agentie2;

    Agentie2.run(); 


    return 0;
}
