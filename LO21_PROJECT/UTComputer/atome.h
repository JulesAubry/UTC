#ifndef ATOME_H
#define ATOME_H

#include "litteral.h"
class Atome : public Litteral {
    friend class LitteralManager;
    QString id;
    Litteral * value;
    Atome(QString s, Litteral * l) :id(s), value(l) {}
    Atome(const Atome & e) : id(e.id), value(e.value){}
public:
    void editLitteral(Litteral* l);
    QString getID() { return id;}
    Litteral& getValue() {return *value;}
    virtual QString toString () const;
    void editLitteral(const Litteral & l);
    Litteral& operator+(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator+(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator+(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator+(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator+(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator+(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator+(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Litteral& operator-(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator-(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator-(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator-(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator-(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator-(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator-(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}



    Litteral& operator*(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator*(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator*(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator*(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator*(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator*(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator*(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Litteral& operator/(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator/(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator/(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator/(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator/(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator/(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator/(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Litteral& operatorNeg() { throw UTComputerException("Action non autorisee a partir d'un atome.");}
    Litteral& operatorDivEntiere(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operatorDivEntiere(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operatorDivEntiere(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operatorDivEntiere(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operatorDivEntiere(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Litteral& operator%(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator%(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator%(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator%(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator%(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator%(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator%(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}

    Litteral& operatorNum()  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDen()  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Litteral* clone() const { return new Atome(*this); }

    Litteral& operator$(const Litteral & l) const{ throw UTComputerException("Action non autorisee a partir d'un Litteral.");}
    Litteral& operator$(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Litteral& operator$(const Reel & l)  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'un Reel.");}
    Litteral& operator$(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'un Complexe.");}
    Litteral& operator$(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Litteral& operator$(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Litteral& operator$(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}

    Litteral& operatorRe()  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorIm()  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}

    Entier& operatorEgale(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Entier& operatorEgale(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Entier& operatorEgale(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Entier& operatorEgale(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Entier& operator<=(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Entier& operator<=(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Entier& operator<=(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Entier& operator<=(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}

    Entier& operator>=(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Entier& operator>=(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un Programme.");}
    Entier& operator>=(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}
    Entier& operator>=(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une Expression.");}


    Entier& operatorAnd(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Entier& operatorAnd(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorOr(const Litteral& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Entier& l) const{ throw UTComputerException("Action non autorisee a partir d'un Entier.");}
    Entier& operatorOr(const Reel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Rationnel& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Complexe& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorNot()  const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorEval()   const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}

    const Litteral & operatorSto() const;
    int operatorIft() const;
    int operatorForget() ;

    const Litteral &  operatorEdit() const;




};

#endif // ATOME_H
