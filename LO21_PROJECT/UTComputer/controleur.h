#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "regex.h"
#include "memento.h"

/******************************  CONTROLEUR  *************************/
class Controleur {
    friend class QComputer;
    LitteralManager& expMng;
    Pile* expAff;
    std::vector<Operateur*>* listeOperateurs;
    std::vector<Regex*>* listeRegex;
    std::vector<Atome*>* listeProgrammes;
    std::vector<Atome*>* listeAtomes;
    Operateur* lastOp;
    std::vector<QString>* lastArgs;
    int state;
    std::vector<Memento> mementoList = std::vector<Memento>();
    static Controleur* instance;
    Controleur(LitteralManager& m, Pile* v,  std::vector<Operateur*>* _listeOperateurs,std::vector<Regex*>* _listeRegex):
        expMng(m), expAff(v),listeOperateurs(_listeOperateurs),listeRegex(_listeRegex), state(-1),
        listeAtomes(new std::vector<Atome*>),listeProgrammes(new std::vector<Atome*>),lastOp(0),lastArgs(new std::vector<QString>){}
    void init(Pile* v,  std::vector<Operateur*>* _listeOperateurs,std::vector<Regex*>* _listeRegex);
public:
    Pile & getPile() const {return * expAff;}
    std::vector<Operateur*> & getListeOperateurs() const {return * listeOperateurs;}
    std::vector<Regex*> & getListeRegex() const {return * listeRegex;}
    std::vector<Atome*> & getListeProgrammes()  {return * listeProgrammes;}
    std::vector<Atome*> & getListeAtomes()  {return * listeAtomes;}
    std::vector<Memento> & getMementoList()  {return mementoList;}
    Operateur& getLastOp() const { return *lastOp;}
    std::vector<QString>& getLastArgs() const { return *lastArgs;}
    void commande(const QString& c);
    void add(Memento m){mementoList.push_back(m);}
    Memento get(int index){return mementoList.at(index);}
    int getState() const{return state;}
    void setState(int s) {state = s;}
    static Controleur& getInstance();
    static void libererInstance();
};
/*******************************************************************/

#endif // CONTROLEUR_H
