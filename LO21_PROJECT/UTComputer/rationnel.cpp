#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"




QString  Rationnel::toString() const {
    QString s; s += QString::number(numerateur); s += QString("/"); s += QString::number(denominateur);
    return s;
}


/*******************************************************************/
/****************** OPERATIONS A PARTIR D'UN RATIONNEL *************/
/*******************************************************************/


/*** + ***/
Litteral& Rationnel::operator+(const Litteral & l) const {
    return l + *this;
}
Litteral& Rationnel::operator+(const Entier& l) const {
    QString s;
    s = QString("%1/%2").arg(getNumerator()+l.getValue()*getDenominator()).arg(getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}

Litteral& Rationnel::operator+(const Reel & l)  const {
    return LitteralManager::getInstance().addReel(getValue()+l.getValue());

}
Litteral& Rationnel::operator+(const Rationnel & l) const {
    //si le nouveau dénominateur vaut 1, alors on ajoute un entier
    double tmp = (getNumerator()*l.getDenominator()+l.getNumerator()*getDenominator())/(getDenominator()*l.getDenominator());
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on fait un rationnel
    QString s;
    s = QString("%1/%2").arg(getNumerator()*l.getDenominator()+l.getNumerator()*getDenominator()).arg(getDenominator()*l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator+(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()+*this,*l.getImaginaire().clone());
}

/*** - ***/
Litteral& Rationnel::operator-(const Litteral & l) const {
    return l - *this ;
}
Litteral& Rationnel::operator-(const Entier& l) const {
    QString s;
    s = QString("%1/%2").arg(l.getValue()*getDenominator()-getNumerator()).arg(getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator-(const Reel & l)  const {
    double d = getNumerator() / getDenominator();
    return LitteralManager::getInstance().addReel(l.getValue()-d);
}
Litteral& Rationnel::operator-(const Rationnel & l) const {
    //si le nouveau dénominateur vaut 1, alors on ajoute un entier
    double tmp = (l.getNumerator()*getDenominator()-getNumerator()*l.getDenominator())/(getDenominator()*l.getDenominator());
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on fait un rationnel
    QString s;
    s = QString("%1/%2").arg(-getNumerator()*l.getDenominator()+l.getNumerator()*getDenominator()).arg(getDenominator()*l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator-(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe(*this-l.getReelle(),*l.getImaginaire().clone());
}

/*** * ***/
Litteral& Rationnel::operator*(const Litteral & l) const {
    return l * *this;
}
Litteral& Rationnel::operator*(const Entier& l) const {
    double tmp = l.getValue()*getValue();
    //Si le double résultant n'a plus de partie décimale, alors on le transforme en entier
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on ajoute en tant que rationnel comme prévu
    QString s;
    s = QString("%1/%2").arg(l.getValue()*getNumerator()).arg(getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator*(const Reel & l)  const {
    return LitteralManager::getInstance().addReel(getValue()*l.getValue());

}
Litteral& Rationnel::operator*(const Rationnel & l) const {
    //si le nouveau dénominateur vaut 1, alors on ajoute un entier
    double tmp = (getNumerator()*l.getNumerator())/(getDenominator()*l.getDenominator());
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    //Sinon on fait un rationnel
    QString s;
    s = QString("%1/%2").arg(getNumerator()*l.getNumerator()).arg(getDenominator()*l.getDenominator());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator*(const Complexe & l) const {
    return LitteralManager::getInstance().addComplexe(l.getReelle()*(*this),l.getImaginaire()*(*this));
}

/*** / ***/
Litteral& Rationnel::operator/(const Litteral & l) const {
    return l / *this;
}
Litteral& Rationnel::operator/(const Entier& l) const {
    double tmp = l.getValue()/getValue();
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    QString s;
    s = QString("%1/%2").arg(getNumerator()).arg(getDenominator()*l.getValue());
    return LitteralManager::getInstance().addRationnel(s);
}
Litteral& Rationnel::operator/(const Reel & l)  const {
    return LitteralManager::getInstance().addReel(l.getValue()/getValue());
}
Litteral& Rationnel::operator/(const Rationnel & l) const {
    //diviser c'est multiplier par l'inverse
    double tmp = (getNumerator()*l.getDenominator())/(getDenominator()*l.getNumerator());
    if (isInt(tmp))
        return LitteralManager::getInstance().addEntier(static_cast<int>(tmp));
    QString s;
    s = QString("%1/%2").arg(getNumerator()*l.getDenominator()).arg(getDenominator()*l.getNumerator());
    return LitteralManager::getInstance().addRationnel(s);
}

Litteral& Rationnel::operator/(const Complexe& l) const {
    Litteral& a = l.getReelle();
    Litteral& b = l.getImaginaire();
    Litteral& reelle = (a*(*this))/((*this)*(*this));
    Litteral& imaginaire = b*(*this)/(*this)*(*this);
    //TODO : remove les résultats intermédiaires du litteral manager ? Ils sont stockés mais on s'en sert plus
    return LitteralManager::getInstance().addComplexe(reelle,imaginaire);
}


/*** DIVISION ENTIERE ***/

Litteral& Rationnel::operatorDivEntiere(const Litteral& l)  const {
    try {
        return l.operatorDivEntiere(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }}

Litteral& Rationnel::operatorDivEntiere(const Entier& l)  const{
  /*  double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un rationnel et un entier.");

}
Litteral& Rationnel::operatorDivEntiere(const Reel& l)  const{
   /* double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre un reel et un rationnel.");

}
Litteral& Rationnel::operatorDivEntiere(const Rationnel& l)  const{
  /*  double tmp = l.getValue() / getValue();
    //on prend la partie entière. floor retourne un double. conversion auto entre double et int.
    int res = floor(tmp);
    return LitteralManager::getInstance().addEntier(res);*/
    throw UTComputerException("Il est impossible d'appliquer DIV entre deux rationnels.");
}
Litteral& Rationnel::operatorDivEntiere(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer DIV entre un complexe et un rationnel.");
}

/*** MODULO ***/
Litteral& Rationnel::operator%(const Litteral& l) const{
    try {
        return l%*this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Rationnel::operator%(const Entier& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un entier et un rationnel.");
}

Litteral& Rationnel::operator%(const Reel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un reel et un rationnel.");
}
Litteral& Rationnel::operator%(const Rationnel& l) const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre deux rationnels.");
}
Litteral& Rationnel::operator%(const Complexe& l)  const{
    throw UTComputerException("Il est impossible d'appliquer MOD entre un complexe et un rationnel.");
}

/*** OPERATEUR $ ***/
Litteral& Rationnel::operator$(const Litteral& l) const{
    try {
        return l.operator$(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Litteral& Rationnel::operator$(const Entier& l)  const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}

Litteral& Rationnel::operator$(const Reel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());

}
Litteral& Rationnel::operator$(const Rationnel& l) const{
    return LitteralManager::getInstance().addComplexe(*l.clone(), *this->clone());
}
Litteral& Rationnel::operator$(const Complexe& l) const{
    throw UTComputerException("Impossible de creer un nombre complexe a partir d'un autre nombre complexe.");
}



/*** OPERATEUR EGAL ***/
Entier& Rationnel::operatorEgale(const Litteral& l) const{
    try {
        return l.operatorEgale(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Rationnel::operatorEgale(const Entier& l)  const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorEgale(const Reel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorEgale(const Rationnel& l) const{
    if(l.getValue() == getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorEgale(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");
}

/*** OPERATEUR <= ***/
Entier& Rationnel::operator<=(const Litteral& l) const{
    try {
        return l <= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Rationnel::operator<=(const Entier& l)  const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator<=(const Reel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator<=(const Rationnel& l) const{
    if(l.getValue() <= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator<=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");
}

/*** OPERATEUR >= ***/
Entier& Rationnel::operator>=(const Litteral& l) const{
    try {
        return l <= *this;
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Rationnel::operator>=(const Entier& l)  const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator>=(const Reel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator>=(const Rationnel& l) const{
    if(l.getValue() >= getValue())
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operator>=(const Complexe& l) const{
    throw UTComputerException("Impossible de comparer un rationnel et un complexe.");
}

/*** OPERATEUR AND ***/
Entier& Rationnel::operatorAnd(const Litteral& l) const{
    try {
        return l.operatorAnd(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Rationnel::operatorAnd(const Entier& l)  const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorAnd(const Reel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorAnd(const Rationnel& l) const{
    if((l.getValue() != 0) && (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorAnd(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle() <= zero).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) && (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}


/*** OPERATEUR OR ***/
Entier& Rationnel::operatorOr(const Litteral& l) const{
    try {
        return l.operatorOr(*this);
    } catch (UTComputerException e) {
        throw UTComputerException(e.what());
    }
}
Entier& Rationnel::operatorOr(const Entier& l)  const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorOr(const Reel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorOr(const Rationnel& l) const{
    if((l.getValue() != 0) || (getValue()!=0))
        return LitteralManager::getInstance().addEntier(1);
    return LitteralManager::getInstance().addEntier(0);
}
Entier& Rationnel::operatorOr(const Complexe& l) const{
    //si c'est pas inf ou egal, alors c'est sup donc c'est ok
    Litteral& zero = LitteralManager::getInstance().addEntier(0); //obligatoire à cause du double dispatch
    if((((l.getReelle().operatorEgale(zero)).getValue() == 0) || ((l.getImaginaire().operatorEgale(zero)).getValue() == 0)) || (getValue()!=0)){
        LitteralManager::getInstance().removeLitteral(zero);
        return LitteralManager::getInstance().addEntier(1);
    }
    LitteralManager::getInstance().removeLitteral(zero);
    return LitteralManager::getInstance().addEntier(0);
}
