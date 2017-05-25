#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <operator.h>
#include "utcomputerexception.h"
#include "librairie.h"



class Entier;
class Rationnel;
class Reel;
class Complexe;
class Regex;
class Operateur;
class Pile;
class Programme;
class Atome;

class Litteral {
public:
    virtual ~Litteral(){}
    virtual QString toString () const = 0;
    virtual Litteral& operator+(const Litteral & l) const = 0;
    virtual Litteral& operator+(const Entier& l) const = 0;
    virtual Litteral& operator+(const Reel & l)  const = 0;
    virtual Litteral& operator+(const Rationnel & l) const = 0;
    virtual Litteral& operator+(const Complexe & l) const = 0;
    virtual Litteral& operator+(const Programme & l) const = 0;
    virtual Litteral& operator+(const Atome & l) const = 0;

    virtual Litteral& operator-(const Litteral & l) const = 0;
    virtual Litteral& operator-(const Entier& l) const = 0;
    virtual Litteral& operator-(const Reel & l)  const = 0;
    virtual Litteral& operator-(const Rationnel & l) const = 0;
    virtual Litteral& operator-(const Complexe & l) const = 0;
    virtual Litteral& operator-(const Programme & l) const = 0;
    virtual Litteral& operator-(const Atome & l) const = 0;


    virtual Litteral& operator*(const Litteral & l) const = 0;
    virtual Litteral& operator*(const Entier& l) const = 0;
    virtual Litteral& operator*(const Reel & l)  const = 0;
    virtual Litteral& operator*(const Rationnel & l) const = 0;
    virtual Litteral& operator*(const Complexe & l) const = 0;
    virtual Litteral& operator*(const Programme & l) const = 0;
    virtual Litteral& operator*(const Atome & l) const = 0;

    virtual Litteral& operator/(const Litteral & l) const = 0;
    virtual Litteral& operator/(const Entier& l) const = 0;
    virtual Litteral& operator/(const Reel & l)  const = 0;
    virtual Litteral& operator/(const Rationnel & l) const = 0;
    virtual Litteral& operator/(const Complexe & l) const = 0;
    virtual Litteral& operator/(const Programme & l) const = 0;
    virtual Litteral& operator/(const Atome & l) const = 0;

    virtual Litteral& operatorNeg()  = 0;
    virtual Litteral& operatorDivEntiere(const Litteral& l) const = 0;
    virtual Litteral& operatorDivEntiere(const Entier& l) const = 0;
    virtual Litteral& operatorDivEntiere(const Reel& l) const = 0;
    virtual Litteral& operatorDivEntiere(const Rationnel& l) const = 0;
    virtual Litteral& operatorDivEntiere(const Complexe& l) const = 0;
    virtual Litteral& operatorDivEntiere(const Programme & l) const = 0;
    virtual Litteral& operatorDivEntiere(const Atome & l) const = 0;

    virtual Litteral& operator%(const Litteral & l) const = 0;
    virtual Litteral& operator%(const Entier& l) const = 0;
    virtual Litteral& operator%(const Reel & l)  const = 0;
    virtual Litteral& operator%(const Rationnel & l) const = 0;
    virtual Litteral& operator%(const Complexe & l) const = 0;
    virtual Litteral& operator%(const Programme & l) const = 0;
    virtual Litteral& operator%(const Atome & l) const = 0;

    virtual Litteral& operatorNum()  const = 0;
    virtual Litteral& operatorDen()  const = 0;
    virtual Litteral* clone() const = 0;
    virtual Litteral& operator$(const Litteral & l) const = 0;
    virtual Litteral& operator$(const Entier& l) const = 0;
    virtual Litteral& operator$(const Reel & l)  const = 0;
    virtual Litteral& operator$(const Rationnel & l) const = 0;
    virtual Litteral& operator$(const Complexe & l) const = 0;
    virtual Litteral& operator$(const Programme & l) const = 0;
    virtual Litteral& operator$(const Atome & l) const = 0;


    virtual Litteral& operatorRe()  const = 0;
    virtual Litteral& operatorIm()  const = 0;

    virtual Entier& operatorEgale(const Litteral& l) const = 0;
    virtual Entier& operatorEgale(const Entier& l) const = 0;
    virtual Entier& operatorEgale(const Reel& l) const = 0;
    virtual Entier& operatorEgale(const Rationnel& l) const = 0;
    virtual Entier& operatorEgale(const Complexe& l) const = 0;
    virtual Entier& operatorEgale(const Programme & l) const = 0;
    virtual Entier& operatorEgale(const Atome & l) const = 0;


    virtual Entier& operator<=(const Litteral& l) const = 0;
    virtual Entier& operator<=(const Entier& l) const = 0;
    virtual Entier& operator<=(const Reel& l) const = 0;
    virtual Entier& operator<=(const Rationnel& l) const = 0;
    virtual Entier& operator<=(const Complexe& l) const = 0;
    virtual Entier& operator<=(const Programme & l) const = 0;
    virtual Entier& operator<=(const Atome & l) const = 0;



    virtual Entier& operator>=(const Litteral& l) const = 0;
    virtual Entier& operator>=(const Entier& l) const = 0;
    virtual Entier& operator>=(const Reel& l) const = 0;
    virtual Entier& operator>=(const Rationnel& l) const = 0;
    virtual Entier& operator>=(const Complexe& l) const = 0;
    virtual Entier& operator>=(const Programme & l) const = 0;
    virtual Entier& operator>=(const Atome & l) const = 0;


    virtual Entier& operatorAnd(const Litteral& l) const = 0;
    virtual Entier& operatorAnd(const Entier& l) const = 0;
    virtual Entier& operatorAnd(const Reel& l) const = 0;
    virtual Entier& operatorAnd(const Rationnel& l) const = 0;
    virtual Entier& operatorAnd(const Complexe& l) const = 0;
    virtual Entier& operatorAnd(const Programme & l) const = 0;
    virtual Entier& operatorAnd(const Atome & l) const = 0;



    virtual Entier& operatorOr(const Litteral& l) const = 0;
    virtual Entier& operatorOr(const Entier& l) const = 0;
    virtual Entier& operatorOr(const Reel& l) const = 0;
    virtual Entier& operatorOr(const Rationnel& l) const = 0;
    virtual Entier& operatorOr(const Complexe& l) const = 0;
    virtual Entier& operatorOr(const Programme & l) const = 0;
    virtual Entier& operatorOr(const Atome & l) const = 0;

    virtual const Litteral & operatorSto() const = 0;


    virtual Entier& operatorNot() const = 0;
    virtual Litteral& operatorEval()   const = 0;

    virtual int operatorIft() const = 0;
    virtual int operatorForget()  = 0;

   virtual const Litteral &  operatorEdit() const = 0;


};









/*
class Atome  : public Litteral{


};*/





#endif // LITTERAL_H
