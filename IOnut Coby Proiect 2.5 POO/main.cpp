#include <iostream>
#include <cstring>
using namespace std;
/*
Cobianu Ionut Adrian - Grupa 141
Tema 4. liste de numere întregi (implementate dinamic)

Se dau urmatoarele clase:
	- Nod (char info, nod*next)
	- Nod_dublu:Nod {nod * ante;};
	- Nod_prioritate:Nod_dublu {int prio;}

Să se implementeze clasa Coada_prioritati care sa aibă elemente de tip
Nod_prioritate. Clasele derivate trebuie sa contina cel puțin constructori
parametrizati prin care sa se evidentieze transmiterea parametrilor către
constructorul din clasa de baza si destructorI.
*/

template <class T> class nod
{
protected:
    T informatie;
    nod * next;
public:
    nod(T arg1, nod* arg2)
    {
        informatie=arg1;
        next=arg2;
        //cout << "Nod initializat. \n";
    };

    nod()
    {
        informatie=0;
        this->next=NULL;
        //cout << "Nod initializat. \n";
    };

    nod(nod*p)
    {
        this->informatie=p->informatie;
        this->next=p->next;
        //cout << "Nod initializat. \n";
    }
    void setNext(nod*);
    void setInfo(T x);
    T returneazaInfo()
    {
        return informatie;
    }
    nod* returneazaNext()
    {
        return next;
    }
    friend istream& operator>>(istream& stream, nod& p1);
    friend istream& operator>>(istream& stream, nod* p1);
    friend ostream& operator<<(ostream &stream, nod &p11);
    nod& operator=(nod &p2);
    virtual int asd(){};
};

template <class T>
void nod<T>::setNext(nod* p)
{
    this->next = p;
}

template <class T>
void nod<T>::setInfo(T x)
{
    informatie = x;
}

template <class T>
istream& operator>>(istream& stream,nod<T> &i1)
{
    cout << "\n Introduceti informatia din nod \n";
    stream >> i1.informatie;
    return stream;
}
template <class T>
istream& operator>>(istream& stream,nod<T>* p1)
{
    stream >> p1;
    return stream;
}
template <class T>
ostream& operator<<(ostream &stream,nod<T> &i1)
{
    stream<<i1.returneazaInfo()<<endl;
    return stream;
}
template <class T>
nod<T>& nod<T>::operator=(nod<T> &p1)
{
    this->informatie=p1.informatie;
}
/// CLASA NOUA
template <class T>
class Nod_dublu: public nod<T>
{
protected:
    nod<T>* prev;

public:
    void setPrev(nod<T>*p)
    {
    this->prev=p;
    };
    nod<T>* returneazaPrev()
    {
        return prev;
    }
    Nod_dublu():nod<T>()
    {
        this->prev=NULL;
        //cout << "Nod dublu initializat. \n";
    }
    Nod_dublu(nod<T>* arg3):nod<T>()
    {
        prev=arg3;
        //cout << "Nod dublu initializat. \n";
    }
    Nod_dublu(Nod_dublu* p):nod<T>()
    {
        this->prev=p->prev;
    }
    friend istream& operator>>(istream& stream,Nod_dublu<T>& p1);
    //friend ostream& operator<<(ostream& stream,Nod_dublu& p1);

};
template <class T>
istream& operator>>(istream &stream,Nod_dublu<T> &i1)
{
    operator>>(stream,i1);
    stream >> i1.prev;
    return stream;
}

template <class T>
class Nod_prioritate: public Nod_dublu<T>
{
    int prioritate;

public:
    void set_prioritate(int num)
    {
        prioritate=num;
    }
    int returneazaPrioritate()
    {
        return prioritate;
    }
    Nod_prioritate():Nod_dublu<T>()
    {
        set_prioritate(0);
        //cout << "\n Prioritate initializata. \n";
    }
    Nod_prioritate(int prioritate):Nod_dublu<T>()
    {
        this->set_prioritate(prioritate);
        //cout << "Prioritate initializata. \n";
    }
    Nod_prioritate(Nod_prioritate *p):Nod_dublu<T>()
    {
        this->prioritate=p->prioritate;
        //cout << "Prioritate initializata. \n";
    }
    friend istream& operator>>(istream &stream,Nod_prioritate &i1);
    friend ostream& operator<<(ostream &stream,Nod_prioritate &i1);
    Nod_prioritate& operator=(Nod_prioritate &p2);
    Nod_prioritate& operator=(nod<T>* n);
    Nod_prioritate* trecere()
    {

        Nod_prioritate<T>* J = dynamic_cast<Nod_prioritate<T>*>(this->returneazaNext());
        //cout << J << " ";
        return J;
    }
    Nod_prioritate* trecereI()
    {
        Nod_prioritate<T>* J = dynamic_cast<Nod_prioritate<T>*>(this->returneazaPrev());
        //cout << J << " ";
        return J;
    }
};
template <class T>
istream& operator>>(istream &stream, Nod_prioritate<T> &i1)
{
    cout << "\n Introduceti prioritatea nodului \n";
    stream >> i1.prioritate;
    int temp;
    cout << "\n Introduceti valoarea nodului \n";
    stream >> temp;
    i1.setInfo(temp);
    return stream;
}
template <class T>
ostream& operator<<(ostream &stream, Nod_prioritate<T> &i1)
{
    stream<<i1.returneazaPrioritate()<<endl;
    return stream;
}
template <class T>
Nod_prioritate<T>& Nod_prioritate<T>::operator=(Nod_prioritate<T> &p1)
{
    this->prioritate=p1.prioritate;
}
// Tu pentru coada tre sa ai ceva de genul
// O coada este formata din mai multe noduri de prioritate
template <class T>class Coada_prioritati: public Nod_prioritate<T>
{
    Nod_prioritate<T>* prim;
    Nod_prioritate<T>* ultim;
public:
    Coada_prioritati()
    {
        prim=ultim=NULL;
        //cout << "Coada initializata. \n";
    }
    void distrugere(Nod_prioritate<T>* prim)
    {
       if(prim)
        {
        Nod_prioritate<T>* p = prim;
        prim=prim->trecere();
        distrugere(prim);
        delete p;
        }
    }
    ~Coada_prioritati()
    {
        distrugere(prim);
        //cout << "Coada distrusa. \n";
    }
    void adaugare_element(T x,int prioritate)
    {
        int valid = 0;
        try{
            if(prioritate < 0)
                throw 42;
        }
        catch(int )
        {
            cout << "throw scaun \n";
            valid = 1;
        }
        if(valid != 0 )
        {
        Nod_prioritate<T> *p=new Nod_prioritate<T>;
        p->setInfo(x);
        p->set_prioritate(prioritate);
        p->setPrev(NULL);
        p->setNext(NULL);
        if(prim==NULL)
        {
            prim=ultim=p;
        }
        else
            if(p->returneazaPrioritate() < prim->returneazaPrioritate())
        {
            //cout << "hahaha \n";
            p->setNext(prim);
                prim->setPrev(p);
                prim=p;
        }
        else
        {
            Nod_prioritate<T>* r = prim;
            while(r!= NULL)
                {
                if (p->returneazaPrioritate() <= r->returneazaPrioritate())
                        break;
                r = r->trecere();
                }
            if(r == NULL)
                {
                    p->setPrev(ultim);
                    ultim->setNext(p);
                    ultim=p;
                }
            else
                if(r->returneazaPrioritate() == p->returneazaPrioritate())
                    {

                            Nod_prioritate<T>* l = r->trecereI();

                             while(r != NULL && r->returneazaInfo() <= p->returneazaInfo() && p->returneazaPrioritate() == r->returneazaPrioritate())
                                {
                                    if(r->trecereI() == NULL)
                                        l = r;
                                    else
                                        l = r->trecereI();
                                    r = r->trecere();
                                }
                            if(r == prim)
                            {
                                prim->setPrev(p);
                                p->setNext(prim);
                                prim = p;
                            }
                            else
                            if(r == NULL)
                            {
                                if(l->trecere() == ultim)
                                {
                                    l->trecere()->setNext(p);
                                    p->setPrev(l->trecere());
                                }
                                else
                                {
                                    l->setNext(p);
                                    p->setPrev(l);
                                }
                                ultim = p;
                            }
                            else
                                if(r->returneazaPrioritate()>p->returneazaPrioritate())
                                {
                                //cout << "Ia zi bai, intrii aici\n?";
                                l->trecere()->setNext(p);
                                p->setPrev(l->trecere());
                                r->setPrev(p);
                                p->setNext(r);
                                }
                            else
                            {
                                l->setNext(p);
                                p->setPrev(l);
                                r->setPrev(p);
                                p->setNext(r);
                            }
                           // if(p == ultim && r!=NULL)
                             //   ultim = r;
                    }

            else
            {
                Nod_prioritate<T>* t = r->trecereI();
                t->setNext(p);
                p->setPrev(t);
                p->setNext(r);
                r->setPrev(p);
            }


        }
        }
}
    void afisare1()
    {
        Nod_prioritate<T>* p= prim;
        while(p)
        {
            cout << p->returneazaInfo() << '|' << p->returneazaPrioritate() << '\n';
            //Nod_prioritate *temp = (Nod_prioritate)*p->returneazaNext();
            p = p->trecere();
            //p = p->returneazaNext();
        }
    }
    void afisare2()
    {
        Nod_prioritate<T>* p= ultim;
        while(p)
        {
            cout << p->returneazaInfo() << '|' << p->returneazaPrioritate() << '\n';
            //Nod_prioritate *temp = (Nod_prioritate)*p->returneazaNext();
            p = p->trecereI();
            //p = p->returneazaNext();
        }
    }
    void stergere(T x,int y)
    {
        Nod_prioritate<T>* p = prim;
        int ok = 0;
        while(p!= NULL)
        {
            if(p->returneazaInfo() == x && p->returneazaPrioritate()== y)
            {
                Nod_prioritate<T>* q = p->trecereI();
                if(q != NULL)
                q->setNext(p->returneazaNext());
                Nod_prioritate<T>* s = p->trecere();
                if(s != NULL)
                s->setPrev(p->returneazaPrev());
                if(p == prim && s==NULL && q == NULL)
                {
                    prim = NULL;
                    //cout << "OK1 \n";
                }
                else
                    if(q != NULL)
                    prim = q;
                else
                    if(s != NULL)
                    prim = s;
                delete p;
                ok = 1;
                if(q!=NULL)
                {
                    p = q;
                    //cout << "OK2 \n";
                }
                else
                if(s!=NULL)
                {
                    p = s;
                    //cout << "OK3 \n";
                }
            }
            p = p->trecere();
        }
    }
    template <class U>
    friend istream& operator>>(istream &stream,Coada_prioritati<U>& coada);
    template <class U>
    friend ostream& operator<<(ostream &stream,Coada_prioritati<U>& coada);
};

template <class T>
istream& operator>>(istream &stream,Coada_prioritati<T>& coada)
{
    cout << "Introduceti numarul de elemente :\n";
    int nr_elemente;
    cin >> nr_elemente;
    for(int i = 0; i < nr_elemente; i++)
    {
        cout << "Numar = ";
        T x;
        cin >> x;
        cout << endl;
        cout << "Prioritate = ";
        int y;
        cin >> y;
        cout << endl;
        coada.adaugare_element(x,y);
    }
}

template <class T>
ostream& operator<<(ostream &stream,Coada_prioritati<T> &coada)
{
    cout << "Coada este : \n";
    coada.afisare1();
}
void meniu()
{
    cout << "Introduceti 1 pentru a adauga elemente. \n";
    cout << "Introduceti 2 pentru a sterge un element dupa valoare si prioritate. \n";
    cout << "Introduceti 3 pentru a afisa lista crescator dupa prioritate. \n";
    cout << "Introduceti 4 pentru a afisa lista descrescator dupa prioritate. \n";
    cout << "Introduceti 5 pentru a oprii programul. \n";
}
int main()
{
    meniu();
    int x,y;
    int ok,optiune;
    Coada_prioritati<double> a;
    while(ok!=0)
    {
        cout << "Optiune = ";
        cin >> optiune;
        cout << endl;
        if(optiune == 1)
        {
        cin >> a;
        }
        else
            if(optiune == 2)
        {
            cout << "Numar = ";
            cin >> x;
            cout << endl;
            cout << "Prioritate = ";
            cin >> y;
            cout << endl;
            a.stergere(x,y);
        }
        else
            if(optiune == 3)
        {
            cout << a;
        }
        else
            if(optiune == 4)
        {
            a.afisare2();
        }
        else
            if(optiune == 5)
            ok=0;
        else
        {
            cout << "Optiune invalida! \n";
            return 0;
        }
    }
    return 0;
}
