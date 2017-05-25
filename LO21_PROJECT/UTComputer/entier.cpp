#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"





QString  Entier::toString() const {
    return QString::number(value);
}

/*******************************************************************/
/********************** OPERATIONS A PARTIR D'UN ENTIER ************/
/*******************************************************************/


/*** + ***/
Litteral& Entier::operator+(const Litteral & l) const {
    return l + *this;
}
Litteral& Entier::operator+(const Entier& l) const {
    return LitteralManager::getInstance().addEntier(getValue()+l.getValue());
}
Litteral& Entier::operator+(const Reel & l)  const {
    return LitteralManager::getInstance().addReel(getValue()+l.getValue());
}
Litteral& Entier::operator+(const Rationnel & l) const {
    QString s;
    s = QString("%1/%2").arg(getValue()*l.getDenominator()+l.getNumerator()).arg(l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Entier::operator+(const Complexe & l)  const {
    return LitteralManager::getInstance().addComplexe((l.getReelle()+*this),*l.getImaginaire().clone());
}


/*** - ***/
Litteral& Entier::operator-(const Litteral & l) const {
    return l - *this;
}
Litteral& Entier::operator-(const Entier& l) const {
    return LitteralManager::getInstance().addEntier(l.getValue()-getValue());
}
Litteral& Entier::operator-(const Reel & l)  const {
    return LitteralManager::getInstance().addReel(l.getValue()-getValue());
}
Litteral& Entier::operator-(const Rationnel & l) const {
    QString s;
    s = QString("%1/%2").arg(l.getNumerator()-getValue()*l.getDenominator()).arg(l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Entier::operator-(const Complexe & l)  const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()-*this,*l.getImaginaire().clone());
}



/*** * ***/
Litteral& Entier::operator*(const Litteral & l) const {
    return l * (*this);
}
Litteral& Entier::operator*(const Entier& l) const {
    return LitteralManager::getInstance().addEntier(l.getValue()*getValue());
}
Litteral& Entier::operator*(const Reel& l) const {
    return LitteralManager::getInstance().addReel(l.getValue()*getValue());
}
Litteral& Entier::operator*(const Rationnel& l) const {
    double tmp = getValue()*l.getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que rationnel comme prévu
    QString s;
    s = QString("%1/%2").arg(getValue()*l.getNumerator()).arg(l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Entier::operator*(const Complexe& l) const {
    return LitteralManager::getInstance().addComplexe(*this*l.getReelle(),l.getImaginaire()*(*this));
}

/*** DIVISION ***/
Litteral& Entier::operator/(const Litteral & l) const {
    try {
        return l / (*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Entier::operator/(const Entier& l) const {
    if (getValue() == 0) throw UTComputerException("Il est impossible de diviser par zero.");
    double res = static_cast<double>(l.getValue())/getValue();
    if(isInt(res))
       return LitteralManager::getInstance().addEntier(l.getValue()/getValue());
    return LitteralManager::getInstance().addReel(res);
}
Litteral& Entier::operator/(const Reel& l) const {
    if (getValue() == 0) throw UTComputerException("Il est impossible de diviser par zero.");
    return LitteralManager::getInstance().addReel(l.getValue()/getValue());
}
Litteral& Entier::operator/(const Rationnel& l) const {
    if (getValue() == 0) throw UTComputerException("Il est impossible de diviser par zero.");
    double tmp = l.getValue()/getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que rationnel comme prévu
    QString s;
    s = QString("%1/%2").arg(l.getNumerator()).arg(l.getDenominator()*getValue());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Entier::operator/(const Complexe& l) const {
    Litteral& a = l.getReelle();
    Litteral& b = l.getImaginaire();
    Litteral& reelle = (a*(*this))/((*this)*(*this));
    Litteral& imaginaire = b*(*this)/(*this)*(*this);
    //TODO : remove les résultats intermédiaires du litteral manager ? Ils sont stockés mais on s'en sert plus
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}

/*** DIVISION ENTIERE ***/

Litteral& Entier::operatorDivEntiere(const Litteral& l) const{
    try {
        return l.operatorDivEntiere(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}

Litteral& Entier::operatorDivEntiere(const Entier& l)  const{
    return LitteralManager::getInstance().addEntier(l.getValue() / getValue());
}

Litteral& Entier::operatorDivEntiere(const Reel& l) const{
    /*if (getValue() == 0) throw UTComputerException("Il est impossible de diviser par zero.");
    double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un reel et un entier.");
}
Litteral& Entier::operatorDivEntiere(const Rationnel& l) const{
   /* if (getValue() == 0) throw UTComputerException("Il est impossible de diviser par zero.");
    double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un rationnel et un entier.");

}
Litteral& Entier::operatorDivEntiere(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un entier.");
}

/*** MODULO ***/
Litteral& Entier::operator%(const Litteral& l) const{
    try {
        return l%*this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Entier::operator%(const Entier& l)  const{
    return LitteralManager::getInstance().addEntier(l.getValue() % getValue());
}

Litteral& Entier::operator%(const Reel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un entier et un reel.");

}
Litteral& Entier::operator%(const Rationnel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un entier et un rationnel.");

}
Litteral& Entier::operator%(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un entier.");
}

/*** OPERATEUR $ ***/
Litteral& Entier::operator$(const Litteral& l) const{
    try {
        return l.operator$(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Entier::operator$(const Entier& l)  const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}

Litteral& Entier::operator$(const Reel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());

}
Litteral& Entier::operator$(const Rationnel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}
Litteral& Entier::operator$(const Complexe& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}

/*** OPERATEUR EGAL ***/
Entier& Entier::operatorEgale(const Litteral& l) const{
    try {
        return l.operatorEgale(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Entier::operatorEgale(const Entier& l)  const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorEgale(const Reel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorEgale(const Rationnel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorEgale(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");
}

/*** OPERATEUR <= ***/
Entier& Entier::operator<=(const Litteral& l) const{
    try {
        return l <= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Entier::operator<=(const Entier& l)  const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator<=(const Reel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator<=(const Rationnel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator<=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");
}


/*** OPERATEUR >= ***/
Entier& Entier::operator>=(const Litteral& l) const{
    try {
        return l >= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Entier::operator>=(const Entier& l)  const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator>=(const Reel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator>=(const Rationnel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operator>=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un entier et un complexe.");
}


/*** OPERATEUR AND ***/
Entier& Entier::operatorAnd(const Litteral& l) const{
    try {
        return l.operatorAnd(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Entier::operatorAnd(const Entier& l)  const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorAnd(const Reel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorAnd(const Rationnel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorAnd(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) && (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}

/*** OPERATEUR Or ***/
Entier& Entier::operatorOr(const Litteral& l) const{
    try {
        return l.operatorOr(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Entier::operatorOr(const Entier& l)  const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorOr(const Reel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorOr(const Rationnel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Entier::operatorOr(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) || (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
