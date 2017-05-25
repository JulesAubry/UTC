#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "expression.h"
#include "programme.h"



QString  Reel::toString() const {
    return QString::number(value);
}

/*******************************************************************/
/********************** OPERATIONS A PARTIR D'UN REEL ************/
/*******************************************************************/

/*** + ***/
Litteral& Reel::operator+(const Litteral & l) const {
    return l + *this;
}
Litteral& Reel::operator+(const Entier& l) const {
    return LitteralManager::getInstance().addReel(getValue()+l.getValue());
}
Litteral& Reel::operator+(const Reel & l)  const {
    double tmp = getValue()+l.getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que réél comme prévu
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator+(const Rationnel & l) const {
    return LitteralManager::getInstance().addReel(getValue()+l.getValue());
}
Litteral& Reel::operator+(const Complexe & l)  const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()+*this,*l.getImaginaire().clone());
}


/*** - ***/
Litteral& Reel::operator-(const Litteral & l) const {
    return l - *this;
}
Litteral& Reel::operator-(const Entier& l) const {
    return LitteralManager::getInstance().addReel(l.getValue()-getValue());
}
Litteral& Reel::operator-(const Reel & l)  const {
    double tmp = l.getValue() - getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que réél comme prévu
     return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator-(const Rationnel & l) const {
    double tmp = l.getValue() - getValue();
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator-(const Complexe & l)  const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()-*this,*l.getImaginaire().clone());
}

/*** * ***/
Litteral& Reel::operator*(const Litteral & l) const {
    return l * *this;
}
Litteral& Reel::operator*(const Entier& l) const {
    return LitteralManager::getInstance().addReel(getValue()*l.getValue());
}
Litteral& Reel::operator*(const Reel & l)  const {
    double tmp = getValue()*l.getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que réél comme prévu
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator*(const Rationnel & l) const {
    double tmp = getValue()*l.getValue();
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator*(const Complexe & l)  const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()*(*this),l.getImaginaire()*(*this));
}

/*** / ***/
Litteral& Reel::operator/(const Litteral & l) const {
    return l / *this;
}
Litteral& Reel::operator/(const Entier& l) const {
    return LitteralManager::getInstance().addReel(l.getValue()/getValue());
}
Litteral& Reel::operator/(const Reel & l)  const {
    double tmp = l.getValue()/getValue();
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator/(const Rationnel & l) const {
    double tmp = l.getValue()/getValue();
    return LitteralManager::getInstance().addReel(tmp);
}
Litteral& Reel::operator/(const Complexe& l) const {
    Litteral& a = l.getReelle();
    Litteral& b = l.getImaginaire();
    Litteral& reelle = (a*(*this))/((*this)*(*this));
    Litteral& imaginaire = b*(*this)/(*this)*(*this);
    //TODO : remove les résultats intermédiaires du litteral manager ? Ils sont stockés mais on s'en sert plus
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}


/*** DIVISION ENTIERE ***/

Litteral& Reel::operatorDivEntiere(const Litteral& l)  const{
    try {
        return l.operatorDivEntiere(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}

Litteral& Reel::operatorDivEntiere(const Entier& l)  const{
    /*double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un reel et un entier.");

}

Litteral& Reel::operatorDivEntiere(const Reel& l)  const{
   /* double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre deux reels.");

}
Litteral& Reel::operatorDivEntiere(const Rationnel& l)  const{
   /* double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un reel et un rationnel.");

}

Litteral& Reel::operatorDivEntiere(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un reel.");

}

/*** MODULO ***/
Litteral& Reel::operator%(const Litteral& l) const{
    try {
        return l%*this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Reel::operator%(const Entier& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un reel et un entier.");
}

Litteral& Reel::operator%(const Reel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre deux reels.");
}
Litteral& Reel::operator%(const Rationnel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un reel et un rationnel.");
}
Litteral& Reel::operator%(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un reel.");

}

/*** OPERATEUR $ ***/
Litteral& Reel::operator$(const Litteral& l) const{
    try {
        return l.operator$(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Reel::operator$(const Entier& l)  const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}

Litteral& Reel::operator$(const Reel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());

}
Litteral& Reel::operator$(const Rationnel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}
Litteral& Reel::operator$(const Complexe& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}



/*** OPERATEUR EGAL ***/
Entier& Reel::operatorEgale(const Litteral& l) const{
    try {
        return l.operatorEgale(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Reel::operatorEgale(const Entier& l)  const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorEgale(const Reel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorEgale(const Rationnel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorEgale(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");
}


/*** OPERATEUR <= ***/
Entier& Reel::operator<=(const Litteral& l) const{
    try {
        return l <= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Reel::operator<=(const Entier& l)  const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator<=(const Reel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator<=(const Rationnel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator<=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");
}

/*** OPERATEUR >= ***/
Entier& Reel::operator>=(const Litteral& l) const{
    try {
        return l >= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Reel::operator>=(const Entier& l)  const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator>=(const Reel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator>=(const Rationnel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operator>=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un reel et un complexe.");
}

/*** OPERATEUR AND ***/
Entier& Reel::operatorAnd(const Litteral& l) const{
    try {
        return l.operatorAnd(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Reel::operatorAnd(const Entier& l)  const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorAnd(const Reel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorAnd(const Rationnel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorAnd(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) && (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}

/*** OPERATEUR OR ***/
Entier& Reel::operatorOr(const Litteral& l) const{
    try {
        return l.operatorOr(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Reel::operatorOr(const Entier& l)  const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorOr(const Reel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorOr(const Rationnel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Reel::operatorOr(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) || (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
