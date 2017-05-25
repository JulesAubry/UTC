#include <algorithm>
#include "computer.h"
#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"
#include "atome.h"
#include "controleur.h"
#include "litteral.h"



LitteralManager::Handler LitteralManager::handler=LitteralManager::Handler();


LitteralManager& LitteralManager::getInstance(){
    if (handler.instance==nullptr) handler.instance=new LitteralManager;
    return *handler.instance;
}

void LitteralManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}

void LitteralManager::agrandissementCapacite() {
    Litteral** newtab=new Litteral*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Litteral**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}

void LitteralManager::removeLitteral(Litteral& e){
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Litteral inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}

void LitteralManager::removeLastLitteral() {
    delete exps[--nb];
}


LitteralManager::~LitteralManager(){
    for(unsigned int i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

Litteral& Item::getLitteral() const {
    if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une Litteral inexistante");
    return *exp;
}


void Pile::agrandissementCapacite() {
    Item* newtab=new Item[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

void Pile::push(Litteral& e){
    if (nb==nbMax) agrandissementCapacite();
    items[nb].setLitteral(e);
    nb++;
    modificationEtat();
}

void Pile::pop(){
    if (nb==0) throw ComputerException("Aucune ou plus assez de litteral sur la pile");
    nb--;
    items[nb].raz();
    modificationEtat();
}

void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getLitteral().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}


Pile::~Pile(){
    delete[] items;
}

Litteral& Pile::top() const {
    if (nb==0) throw ComputerException("Aucune ou plus assez de litteral sur la pile.");
    return items[nb-1].getLitteral();
}



bool estUnOperateur(const QString s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}

bool estUnNombre(const QString s){
    bool ok=false;
    s.toInt(&ok);
    return ok;
}

Litteral& LitteralManager::getLastAdded() {
    return *exps[nb-1];
}


/***** ADDS *******/
Entier& LitteralManager::addEntier(int v) {
    if (nb == nbMax) agrandissementCapacite();
    Entier* tmp = new Entier(v);
    exps[nb++] = tmp;
    return *tmp;
}

Reel& LitteralManager::addReel(double v) {
    if (nb == nbMax) agrandissementCapacite();
    Reel* tmp = new Reel(v);
    exps[nb++] = tmp;
    return *tmp;
}

Rationnel & LitteralManager::addRationnel(QString v) {
    QRegExp rx("[/]");// match a comma or a space
    QStringList list = v.split(rx, QString::SkipEmptyParts);
    if(list.at(1).toInt() == 0) throw ComputerException("Impossible d'ajouter un rationnel avec 0 comme denominateur.");
    if (nb == nbMax) agrandissementCapacite();
    Rationnel* tmp = new Rationnel(list.at(0).toInt(), list.at(1).toInt());
    exps[nb++] = tmp;
    return *tmp;
}

Programme & LitteralManager::addProgramme(QString s) {
    if (nb == nbMax) agrandissementCapacite();
    Programme* tmp = new Programme(s);
    exps[nb++] = tmp;
    return *tmp;
}

Complexe& LitteralManager::addComplexe(Litteral& re, Litteral& im){
    if (nb == nbMax) agrandissementCapacite();
    Complexe* tmp = new Complexe(re, im);
    exps[nb++] = tmp;
    return *tmp;
}

Litteral& LitteralManager::addAlreadyExisting(Litteral& toAdd) {
    if (nb == nbMax) agrandissementCapacite();
    Litteral* tmp = toAdd.clone();
    exps[nb++] = tmp;
    return *tmp;
}
Expression& LitteralManager::addExpression(QString s){
    if (nb == nbMax) agrandissementCapacite();
    Expression* tmp = new Expression(s);
    exps[nb++] = tmp;
    return *tmp;
}
Atome& LitteralManager::addAtome(QString s,Litteral& l){
    //on vérifie si l'atome n'existe pas déjà dans la liste des atomes
    std::vector<Atome*>* listeProgrammes =  &Controleur::getInstance().getListeProgrammes();
    std::vector<Atome*>* listeAtomes =  &Controleur::getInstance().getListeAtomes();
    bool found = false;
    //on enlève les ""
    //s.remove(0,1);
    //s.remove(s.size()-1,s.size()-1);
    //On regarde si ça match un atome : programme
    for( std::vector<Atome*>::iterator it = listeProgrammes->begin(); it != listeProgrammes->end(); ++it){
        if(((*it)->getID() == s) && (found==false)){
            found =  true;
            //on le met à jour avec le nouveau litteral, et on retourne
            (*it)->editLitteral(&l);
            return *(*it);
        }
    }
    //On regarde si ça match un atome : autres que programme
    for( std::vector<Atome*>::iterator it = listeAtomes->begin(); it != listeAtomes->end(); ++it){
        if(((*it)->getID() == s) && (found==false)){
            found = true;
            //on le met à jour avec le nouveau litteral, et on retourne
            (*it)->editLitteral(&l);
            return *(*it);
        }
    }
    if(!found){
        if (nb == nbMax) agrandissementCapacite();
        Atome* tmp = new Atome(s,&l);
        exps[nb++] = tmp;
        //Il faut maintenant l'ajouter dans la bonne liste
        string s = static_cast<string>(typeid(l).name());
        s.erase(0,1);
        if (s == "Programme")
            Controleur::getInstance().getListeProgrammes().push_back(tmp);
        else
            Controleur::getInstance().getListeAtomes().push_back(tmp);

        return *tmp;
    }
}
Litteral& LitteralManager::dupplicate(Litteral& toCopy) {
    if (nb == nbMax) agrandissementCapacite();
    Litteral* tmp = toCopy.clone();
    exps[nb++] = tmp;
    return *tmp;
}

