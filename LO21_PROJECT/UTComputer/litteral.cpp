#include "litteral.h"
#include "computer.h"
#include "regex.h"
#include <regex>
#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "atome.h"
#include "programme.h"
#include "expression.h"
#include "controleur.h"
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <iostream>

/*******************************************************************/
/************************* OPERATEUR FORGET ************************/
/*******************************************************************/

int Entier::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un entier.");
}
int Rationnel::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un rationnel.");
}
int Reel::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un reel.");
}
int Complexe::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un complexe.");
}
int Programme::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un programme.");
}
int Atome::operatorForget()  {
    throw UTComputerException("Impossible d'oublier un atome.");

}
int Expression::operatorForget()  {
    std::vector<Atome*>* listeProgrammes = &Controleur::getInstance().getListeProgrammes();
    std::vector<Atome*>* listeAtomes = &Controleur::getInstance().getListeAtomes();
    bool found = false;
    int cpt = 0;
    //On regarde si ça match un atome : programme
    for( std::vector<Atome*>::iterator it = listeProgrammes->begin(); it != listeProgrammes->end(); ++it){
        if(((*it)->getID() == toString()) && (found==false)){
            listeProgrammes->erase(listeProgrammes->begin()+cpt);
            found = true;
            LitteralManager::getInstance().removeLitteral(*(*it));
            return 1;
        }
        cpt++;

    }

    if(!found){
        cpt = 0;
        //On regarde si ça match un atome : autres que programme
        for( std::vector<Atome*>::iterator it = listeAtomes->begin(); it != listeAtomes->end(); ++it){
            if(((*it)->getID() == toString()) && (found==false)){
                listeAtomes->erase(listeAtomes->begin()+cpt);
                found = true;
                LitteralManager::getInstance().removeLitteral(*(*it));
                return 1;

            }
            cpt++;

        }
    }
    if(!found)
        throw UTComputerException("Cet n'est lie a aucun litteral");
}



/*******************************************************************/
/************************* OPERATEUR STO ***************************/
/*******************************************************************/

const Litteral& Entier::operatorSto() const  {
    throw UTComputerException("Impossible d'utiliser un entier comme identificateur.");
}
const Litteral& Rationnel::operatorSto()  const{
    throw UTComputerException("Impossible d'utiliser un rationnel comme identificateur.");
}
const Litteral& Reel::operatorSto() const {
    throw UTComputerException("Impossible d'utiliser un reel comme identificateur.");
}
const Litteral& Complexe::operatorSto() const {
    throw UTComputerException("Impossible d'utiliser un complexe comme identificateur.");
}
const Litteral& Programme::operatorSto() const {
    throw UTComputerException("Impossible d'utiliser un programme comme identificateur.");
}
const Litteral& Expression::operatorSto()const  {
    if(!regex_match(toString().toStdString(),regex("^[A-Z][a-zA-Z0-9]*")))
        throw UTComputerException("L'atome n'est pas correct (il ne faut pas d'espace/commencer par MAJ).");
    return *this;
}
const Litteral& Atome::operatorSto() const {
    throw UTComputerException("Impossible d'utiliser un atome déjà existant comme identificateur.");
}


/*******************************************************************/
/************************* OPERATEUR EDIT ***************************/
/*******************************************************************/
const Litteral &  Atome::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'un atome.");
}
const Litteral & Complexe::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'un complexe.");
}
const Litteral & Expression::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'une expression.");
}
const Litteral & Programme::operatorEdit() const {
    return * this;
}
const Litteral & Entier::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'un entier.");
}
const Litteral & Rationnel::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'un rationnel.");
}
const Litteral & Reel::operatorEdit() const {
    throw UTComputerException("Action non autorisee a partir d'un reel.");
}



/*******************************************************************/
/************************* OPERATEUR IFT ***************************/
/*******************************************************************/

int Entier::operatorIft() const  {
    if (getValue() > 0) return 1;
    return 0;}
int Rationnel::operatorIft()  const{
    if (getValue() > 0) return 1;
    return 0;}
int Reel::operatorIft() const {
    if (getValue() > 0) return 1;
    return 0;
}
int Complexe::operatorIft() const {
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if (((getReelle() <= zero).getValue() == 0) || ((getImaginaire() <= zero).getValue() == 0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return 1;
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return 0;
}
int Programme::operatorIft() const {
    throw UTComputerException("Impossible de faire un test logique a partir d'un programme.");
}
int Expression::operatorIft()const  {
    throw UTComputerException("Impossible de faire un test logique a partir d'une expression.");
}
int Atome::operatorIft() const {
    throw UTComputerException("Un atome est dans la pile. Ne devrait jamais arriver.");
}





/*******************************************************************/
/************************* OPERATEUR NEG ***************************/
/*******************************************************************/

Litteral& Entier::operatorNeg()  {
    return LitteralManager::getInstance().addEntier(-getValue());
}
Litteral& Rationnel::operatorNeg()  {
    QString retour;
    if (getNumerator() > 0)
         retour = "-"+QString::number(getNumerator())+"/"+QString::number(getDenominator());
    if (getNumerator() < 0 )
         retour = QString::number(-getNumerator())+"/"+QString::number(getDenominator());

    return LitteralManager::getInstance().addRationnel(retour);
}
Litteral& Reel::operatorNeg()  {
    return LitteralManager::getInstance().addReel(-getValue());
}
Litteral& Complexe::operatorNeg()  {
    Litteral& neg = getReelle().operatorNeg();
    Litteral& im = LitteralManager::getInstance().dupplicate(getImaginaire());
    return LitteralManager::getInstance().addComplexe(neg,im);
}
/*******************************************************************/
/************************* OPERATEUR NUM ***************************/
/*******************************************************************/

Litteral& Entier::operatorNum() const {
    return LitteralManager::getInstance().addEntier(getValue());
}
Litteral& Rationnel::operatorNum() const {
    return LitteralManager::getInstance().addEntier(getNumerator());
}
Litteral& Reel::operatorNum() const {
    throw UTComputerException("Il est impossible d'appliquer NUM sur un reel.");
}
Litteral& Complexe::operatorNum() const {
    throw UTComputerException("Il est impossible d'appliquer NUM sur un complexe.");
}

/*******************************************************************/
/************************* OPERATEUR DEN ***************************/
/*******************************************************************/

Litteral& Entier::operatorDen() const {
    return LitteralManager::getInstance().addEntier(1);
}
Litteral& Rationnel::operatorDen() const {
    return LitteralManager::getInstance().addEntier(getDenominator());
}
Litteral& Reel::operatorDen() const {
    throw UTComputerException("Il est impossible d'appliquer DEN sur un reel.");
}
Litteral& Complexe::operatorDen() const {
    throw UTComputerException("Il est impossible d'appliquer DEN sur un complexe.");
}

/*******************************************************************/
/************************* OPERATEUR RE ***************************/
/*******************************************************************/

Litteral& Entier::operatorRe() const {
    throw UTComputerException("Partie reelle d'un entier. N'a aucun effet.");
}
Litteral& Rationnel::operatorRe() const {
    throw UTComputerException("Partie reelle d'un rationnel. N'a aucun effet.");
}
Litteral& Reel::operatorRe() const {
    throw UTComputerException("Partie reelle d'un Reel. N'a aucun effet.");
}
Litteral& Complexe::operatorRe() const {
    return LitteralManager::getInstance().addAlreadyExisting(getReelle());
}

/*******************************************************************/
/************************* OPERATEUR IM ***************************/
/*******************************************************************/

Litteral& Entier::operatorIm() const {
    return LitteralManager::getInstance().addEntier(0);
}
Litteral& Rationnel::operatorIm() const {
    return LitteralManager::getInstance().addEntier(0);
}
Litteral& Reel::operatorIm() const {
    return LitteralManager::getInstance().addEntier(0);
}
Litteral& Complexe::operatorIm() const {
    return LitteralManager::getInstance().addAlreadyExisting(getImaginaire());
}
/*******************************************************************/
/************************* OPERATEUR NOT ***************************/
/*******************************************************************/

Entier& Entier::operatorNot() const {
    if(getValue()!=0)
        return LitteralManager::getInstance().addEntier(0);
    return LitteralManager::getInstance().addEntier(1);
}
Entier& Rationnel::operatorNot() const {
    if(getValue()!=0)
        return LitteralManager::getInstance().addEntier(0);
    return LitteralManager::getInstance().addEntier(1);
}
Entier& Reel::operatorNot() const {
    if(getValue()!=0)
        return LitteralManager::getInstance().addEntier(0);
    return LitteralManager::getInstance().addEntier(1);
}
Entier& Complexe::operatorNot() const {
    Litteral& zero = LitteralManager::getInstance().addEntier(0);
    //si une des deux n'est pas nulle alors le nombre complexe ne vaut pas 0, donc on renvoit
    if(((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(0);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(1);
}

/*******************************************************************/
/************************* OPERATEUR EVAL ***************************/
/*******************************************************************/

Litteral& Entier::operatorEval()  const {
    throw UTComputerException ("Impossible d'evaluer un entier.");
}
Litteral& Rationnel::operatorEval()  const {
    throw UTComputerException ("Impossible d'evaluer un rationnel.");
}
Litteral& Reel::operatorEval()  const {
    throw UTComputerException ("Impossible d'evaluer un reel.");
}
Litteral& Complexe::operatorEval()  const {
    throw UTComputerException ("Impossible d'evaluer un complexe.");
}
Litteral& Programme::operatorEval()  const {
    Controleur& controleur = Controleur::getInstance();
    int nbPush = 0;
    try {
        //on enlève le 1er [ et le dernier ]
        QString myProg = programme;
        myProg.remove(0,1);
        myProg.remove(myProg.size()-1,myProg.size()-1);
        QRegExp rx("[ ]");
        QStringList list = myProg.split(rx, QString::SkipEmptyParts);
        for(int i = 0; i < list.length(); i++) {
            controleur.commande(list.at(i));
            nbPush++;
        }

    } catch (UTComputerException e) {
        for(int i =0; i< nbPush; i++) controleur.getPile().pop();
        throw UTComputerException(e.what());
    }
}

Litteral& Expression::operatorEval()  const {
    int nbPush = 0;
    Controleur& controleur = Controleur::getInstance();
    try {
        std::vector<Regex*>& listeRegex = Controleur::getInstance().getListeRegex();
        std::vector<Operateur*>& listeOperateurs = Controleur::getInstance().getListeOperateurs();
        QString postfix = parse(this->toString(),listeOperateurs);
        QRegExp rx("[ ]");
        QStringList list = postfix.split(rx, QString::SkipEmptyParts);
        for(int i = 0; i < list.length(); i++) {
            controleur.commande(list.at(i));
            nbPush++;
        }
    } catch (UTComputerException e) {
        for(int i =0; i< nbPush; i++) controleur.getPile().pop();
        throw UTComputerException(e.what());
    }
}

























