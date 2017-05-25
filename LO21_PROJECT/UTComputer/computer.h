#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <sstream>
#include <regex>

using namespace std;
class Litteral;
class Entier;
class Reel;
class Operateur;
class Rationnel;
class Complexe;
class Programme;
class Expression;
class Atome;

class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

class LitteralManager {
    Litteral** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    LitteralManager():exps(nullptr),nb(0),nbMax(0){}
    ~LitteralManager();
    LitteralManager(const LitteralManager& m);
    LitteralManager& operator=(const LitteralManager& m);

    struct Handler{
        LitteralManager* instance;
        Handler():instance(nullptr){}
        // destructeur appel? ? la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    Entier& addEntier(int v);
    Reel & addReel(double v);
    Rationnel& addRationnel(QString v);
    Complexe& addComplexe(Litteral& re,Litteral& im);
    Programme& addProgramme(QString s);
    Expression& addExpression(QString s);
    Atome& addAtome(QString s,Litteral& l );
    Litteral& addAlreadyExisting(Litteral& toAdd);
    Litteral& getLastAdded();
    void removeLitteral(Litteral& e);
    void removeLastLitteral();
    Litteral& dupplicate(Litteral& toCopy);
    static LitteralManager& getInstance();
    static void libererInstance();
    class Iterator {
        friend class LitteralManager;
        Litteral** currentExp;
        unsigned int nbRemain;
        Iterator(Litteral** u, unsigned nb):currentExp(u),nbRemain(nb){}
    public:
        Iterator():currentExp(nullptr),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        Litteral& current() const {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    Iterator getIterator() {
        return Iterator(exps,nb);
    }
    class iterator {
        Litteral** current;
        iterator(Litteral** u):current(u){}
        friend class LitteralManager;
    public:
        iterator():current(0){}
        Litteral& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(exps); }
    iterator end() { return iterator(exps+nb); }

    class const_iterator {
        Litteral** current;
        const_iterator(Litteral** u):current(u){}
        friend class LitteralManager;
    public:
        const_iterator():current(0){}
        Litteral& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps); }
    const_iterator end() const { return const_iterator(exps+nb); }
};


class Item {
    Litteral* exp;
public:
    Item():exp(nullptr){}
    void setLitteral(Litteral& e) { exp=&e; }
    void raz() { exp=0; }
    Litteral& getLitteral() const;
};

class Pile : public QObject {
    Q_OBJECT

    Item* items;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();
    void push(Litteral& e);
    void pop();
    Item * getItems() const {return items;};
    void setNbMax(unsigned int nb) {nbMax = nb;}
    unsigned int getNbMax() const {return nbMax;}
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Litteral& top() const;
    void setNbItemsToAffiche(unsigned int n) { nb=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }
    bool enough(int nbToPop) { return nbToPop <= nb;}
    Pile & operator=(const Pile & p) {
         delete items;
         items = new Item[p.nb];
         nb = 0;
         nbMax = p.nbMax;
         nbAffiche = p.nbAffiche;
         for(int i = 0; i < p.taille(); i++) {
             Litteral & l = p.getItems()[i].getLitteral();
             push(p.getItems()[i].getLitteral());
         }
         return * this;
    }
    class iterator {
        Item* current;
        iterator(Item* u):current(u){}
        friend class Pile;
        friend class QComputer;
    public:

        iterator():current(nullptr){}
        Litteral& operator*() const { return current->getLitteral(); }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(items+nb-1); }
    iterator end() { return iterator(items-1); }

    class const_iterator {
        Item* current;
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const Litteral& operator*() const { return current->getLitteral(); }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(items+nb-1); }
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);

#endif
