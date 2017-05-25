#ifndef PROGRAMME_H
#define PROGRAMME_H

#include "litteral.h"
class Programme : public Litteral {
    friend class LitteralManager;
    QString programme;
    Programme(QString _programme) :programme(_programme) {}
    Programme(const Programme& e) { programme = e.programme; }
public:

    virtual QString toString () const;
    Litteral& getValue() const { throw UTComputerException("getValue n'est pas implementee pour les programmes.");}
    Litteral& operator+(const Litteral & l) const { try { l+*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator+(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}


    Litteral& operator-(const Litteral & l) const { try { l-*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator-(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator*(const Litteral & l) const { try { l * *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator*(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator/(const Litteral & l) const { try { l / *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator/(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorNeg() { throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Litteral& operatorDivEntiere(const Litteral& l) const { try { l.operatorDivEntiere(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operatorDivEntiere(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Reel& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Rationnel& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Complexe& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Programme& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Expression& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Atome& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator%(const Litteral & l) const { try { l%*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator%(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Rationnel & l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Complexe & l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Programme & l) const { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Expression & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Atome & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorNum()  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDen()  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Litteral* clone() const { return new Programme(*this); }
    Litteral& operator$(const Litteral & l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Reel & l)  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Rationnel & l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Complexe & l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Programme & l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Expression & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Atome & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorRe()  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorIm()  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Entier& operatorEgale(const Litteral& l) const { try { l.operatorEgale(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorEgale(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Expression& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Atome& a) const  { throw UTComputerException("Action non autorisee a partir d'un' atome.");}

    Entier& operator<=(const Litteral& l) const { try { l <= *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operator<=(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Expression& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operator>=(const Litteral& l) const { try { l >= *this ; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operator>=(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Expression& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Entier& operatorAnd(const Litteral& l) const  { try { l.operatorAnd(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorAnd(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Expression& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorOr(const Litteral& l) const { try { l.operatorOr(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorOr(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Expression& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorNot()  const  { throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorEval()   const;
    const Litteral & operatorSto() const;
    int operatorIft() const;
    int operatorForget() ;
    const Litteral &  operatorEdit() const;



};


#endif // PROGRAMME_H
