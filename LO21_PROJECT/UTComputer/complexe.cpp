#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"

QString  Complexe::toString() const {
    QString s; s += getReelle().toString(); s += QString("$"); s += getImaginaire().toString();
    return s;
}



/*******************************************************************/
/********************** OPERATIONS A PARTIR D'UN COMPLEXE ************/
/*******************************************************************/

/*** + ***/
Litteral& Complexe::operator+(const Litteral & l) const {
    return l + *this;
}
Litteral& Complexe::operator+(const Entier& l) const {
    //le + nous retourne un nouvel objet donc on est fine
    //on clone car on remove dans la stratégie
    return LitteralManager::getInstance().addComplexe(getReelle()+l,*getImaginaire().clone());
}
Litteral& Complexe::operator+(const Reel & l)  const {
    return LitteralManager::getInstance().addComplexe(getReelle()+l,*getImaginaire().clone());
}
Litteral& Complexe::operator+(const Rationnel & l) const {
    return LitteralManager::getInstance().addComplexe(getReelle()+l,*getImaginaire().clone());
}
Litteral& Complexe::operator+(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()+getReelle(),l.getImaginaire()+getImaginaire());
}


/*** - ***/
Litteral& Complexe::operator-(const Litteral & l) const {
    return l - *this;
}
Litteral& Complexe::operator-(const Entier& l) const {
    return LitteralManager::getInstance().addComplexe(l-getReelle(),*getImaginaire().clone());
}
Litteral& Complexe::operator-(const Reel & l)  const {
    return LitteralManager::getInstance().addComplexe(l-getReelle(),*getImaginaire().clone());
}
Litteral& Complexe::operator-(const Rationnel & l) const {
    return LitteralManager::getInstance().addComplexe(l-getReelle(),*getImaginaire().clone());
}
Litteral& Complexe::operator-(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()-getReelle(),l.getImaginaire()-getImaginaire());
}

/*** * ***/
Litteral& Complexe::operator*(const Litteral & l) const {
    return l * *this;
}
Litteral& Complexe::operator*(const Entier& l) const {
    return LitteralManager::getInstance().addComplexe(getReelle()*l,getImaginaire()*l);
}
Litteral& Complexe::operator*(const Reel & l)  const {
    return LitteralManager::getInstance().addComplexe(getReelle()*l,getImaginaire()*l);
}
Litteral& Complexe::operator*(const Rationnel & l) const {
    return LitteralManager::getInstance().addComplexe(getReelle()*l,getImaginaire()*l);
}
Litteral& Complexe::operator*(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe((l.getReelle()-getReelle())-(l.getImaginaire()*getImaginaire()),(l.getReelle()-getReelle())+(l.getImaginaire()*getImaginaire()));
}

/*** / ***/
Litteral& Complexe::operator/(const Litteral & l) const {
    return l / *this;
}
Litteral& Complexe::operator/(const Entier& a) const {
    Litteral& aP = getReelle();
    Litteral& bP = getImaginaire();
    Litteral& reelle = a*aP / (aP*aP + bP*bP);
    Litteral& nega = a.clone()->operatorNeg();
    Litteral& imaginaire = nega*bP/(aP*aP + bP *bP);
    delete &nega;
    //TODO : remove les résultats intermédiaires du litteral manager ? Ils sont stockés mais on s'en sert plus
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}
Litteral& Complexe::operator/(const Reel & a)  const {
    Litteral& aP = getReelle();
    Litteral& bP = getImaginaire();
    Litteral& reelle = a*aP / (aP*aP + bP*bP);
    Litteral& nega = a.clone()->operatorNeg();
    Litteral& imaginaire = nega*bP/(aP*aP + bP *bP);
    delete &nega;
    //TODO : remove les résultats intermédiaires du litteral manager ? Ils sont stockés mais on s'en sert plus
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}
Litteral& Complexe::operator/(const Rationnel & a) const {
    Litteral& aP = getReelle();
    Litteral& bP = getImaginaire();
    Litteral& reelle = a*aP / (aP*aP + bP*bP);
    Litteral& nega = a.clone()->operatorNeg();
    Litteral& imaginaire = nega*bP/(aP*aP + bP *bP);
    delete &nega;
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}
Litteral& Complexe::operator/(const Complexe & l) const {
    Litteral& a = l.getReelle();
    Litteral& b = l.getImaginaire();
    Litteral& aP = getReelle();
    Litteral& bP = getImaginaire();
    Litteral& reelle = (a*aP + b*bP) / (aP*aP + bP *bP);
    Litteral& imaginaire = ((b*aP)-(a*bP))/(aP*aP + bP *bP);
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}

/*** DIVISION ENTIERE ***/

Litteral& Complexe::operatorDivEntiere(const Litteral& l)  const{
    try {
        return l.operatorDivEntiere(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }}

Litteral& Complexe::operatorDivEntiere(const Entier& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un entier.");
}

Litteral& Complexe::operatorDivEntiere(const Reel& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un reel.");

}
Litteral& Complexe::operatorDivEntiere(const Rationnel& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un rationnel.");
}
Litteral& Complexe::operatorDivEntiere(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre deux complexes.");
}

/*** MODULO ***/
Litteral& Complexe::operator%(const Litteral& l) const{
    try {
        return l%*this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Complexe::operator%(const Entier& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un entier.");
}

Litteral& Complexe::operator%(const Reel& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un reel.");

}
Litteral& Complexe::operator%(const Rationnel& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un rationnel.");
}
Litteral& Complexe::operator%(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre deux complexes.");
}

/*** OPERATEUR $ ***/
Litteral& Complexe::operator$(const Litteral& l) const{
    try {
        return l.operator$(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Complexe::operator$(const Entier& l)  const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}

Litteral& Complexe::operator$(const Reel& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");

}
Litteral& Complexe::operator$(const Rationnel& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}
Litteral& Complexe::operator$(const Complexe& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}

/*** OPERATEUR EGAL ***/
Entier& Complexe::operatorEgale(const Litteral& l) const{
    try {
        return l.operatorEgale(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Complexe::operatorEgale(const Entier& l)  const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");

}
Entier& Complexe::operatorEgale(const Reel& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");

}
Entier& Complexe::operatorEgale(const Rationnel& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");

}
Entier& Complexe::operatorEgale(const Complexe& l) const{
    if ((l.getReelle().operatorEgale(getReelle()).getValue() == 1) && (l.getReelle().operatorEgale(getReelle()).getValue()) == 1)
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}

/*** OPERATEUR <= ***/
Entier& Complexe::operator<=(const Litteral& l) const{
    try {
        return l <= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Complexe::operator<=(const Entier& l)  const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");
}
Entier& Complexe::operator<=(const Reel& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");
}
Entier& Complexe::operator<=(const Rationnel& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");
}
Entier& Complexe::operator<=(const Complexe& l) const{
   /* if ((((l.getReelle() <= getReelle()).getValue() == 1) && ((l.getReelle() <= getReelle()).getValue() == 1)) || ((l.getReelle() <= getReelle()).getValue() == 1))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);*/
    throw UTComputerException("Impossible de comparer deux complexes.");
}

/*** OPERATEUR >= ***/
Entier& Complexe::operator>=(const Litteral& l) const{
    try {
        return l >= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Complexe::operator>=(const Entier& l)  const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");
}
Entier& Complexe::operator>=(const Reel& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");
}
Entier& Complexe::operator>=(const Rationnel& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");
}
Entier& Complexe::operator>=(const Complexe& l) const{
   /* if ((((l.getReelle() <= getReelle()).getValue() == 1) && ((l.getReelle() <= getReelle()).getValue() == 1)) || ((l.getReelle() <= getReelle()).getValue() == 1))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);*/
    throw UTComputerException("Impossible de comparer deux complexes.");
}

/*** OPERATEUR AND ***/
Entier& Complexe::operatorAnd(const Litteral& l) const{
    try {
        return l.operatorAnd(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Complexe::operatorAnd(const Entier& l)  const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) && (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorAnd(const Reel& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) && (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorAnd(const Rationnel& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) && (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorAnd(const Complexe& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0)) && (((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}

/*** OPERATEUR OR ***/
Entier& Complexe::operatorOr(const Litteral& l) const{
    try {
        return l.operatorOr(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Complexe::operatorOr(const Entier& l)  const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) || (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorOr(const Reel& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) || (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorOr(const Rationnel& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((l.getValue() != 0) || (((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Complexe::operatorOr(const Complexe& l) const{
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((getReelle().operatorEgale(zero)).getValue() == 0) || ((getImaginaire().operatorEgale(zero)).getValue() == 0)) || (((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0))){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
