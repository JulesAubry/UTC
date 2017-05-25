#ifndef RATIONNEL_H
#define RATIONNEL_H

#include "litteral.h"

class Rationnel : public Litteral {
    friend class LitteralManager;
    int numerateur;
    int denominateur;
    Rationnel(int n, int d) :numerateur(n), denominateur(d) {}
    Rationnel(const Rationnel& e) {
        numerateur = e.getNumerator();
        denominateur = e.getDenominator();
    };
public:

    QString toString() const;
    //static_cast pour forcer le résultat en double, sinon le résultat est tronqué partie entière
    double getValue() const {return static_cast<double>(numerateur)/denominateur; }
    double getNumerator() const { return numerateur; }
    double getDenominator() const { return denominateur; }
    Litteral& operator+(const Litteral & l) const;
    Litteral& operator+(const Entier& l) const;
    Litteral& operator+(const Reel & l)  const;
    Litteral& operator+(const Rationnel & l) const;
    Litteral& operator+(const Complexe & l) const;
    Litteral& operator+(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator+(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operator-(const Litteral & l) const;
    Litteral& operator-(const Entier& l) const;
    Litteral& operator-(const Reel & l)  const;
    Litteral& operator-(const Rationnel & l) const;
    Litteral& operator-(const Complexe & l) const;
    Litteral& operator-(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator-(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operator*(const Litteral & l) const;
    Litteral& operator*(const Entier& l) const;
    Litteral& operator*(const Reel & l)  const;
    Litteral& operator*(const Rationnel & l) const;
    Litteral& operator*(const Complexe & l) const;
    Litteral& operator*(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator*(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operator/(const Litteral & l) const;
    Litteral& operator/(const Entier& l) const;
    Litteral& operator/(const Reel & l)  const;
    Litteral& operator/(const Rationnel & l) const;
    Litteral& operator/(const Complexe & l) const;
    Litteral& operator/(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator/(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operatorNeg() ;
    Litteral& operatorDivEntiere(const Litteral& l) const;
    Litteral& operatorDivEntiere(const Entier& l) const;
    Litteral& operatorDivEntiere(const Reel& l) const;
    Litteral& operatorDivEntiere(const Rationnel& l)  const;
    Litteral& operatorDivEntiere(const Complexe& l)  const;
    Litteral& operatorDivEntiere(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operatorDivEntiere(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operator%(const Litteral & l) const;
    Litteral& operator%(const Entier& l) const;
    Litteral& operator%(const Reel & l)  const;
    Litteral& operator%(const Rationnel & l) const;
    Litteral& operator%(const Complexe & l) const;
    Litteral& operator%(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator%(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Litteral& operatorNum()  const;
    Litteral& operatorDen()  const;
    Litteral* clone() const { return new Rationnel(*this); }
    Litteral& operator$(const Litteral & l) const;
    Litteral& operator$(const Entier& l) const;
    Litteral& operator$(const Reel & l)  const;
    Litteral& operator$(const Rationnel & l) const;
    Litteral& operator$(const Complexe & l) const;
    Litteral& operator$(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Litteral& operator$(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}

    Litteral& operatorRe()  const;
    Litteral& operatorIm()  const;

    Entier& operatorEgale(const Litteral& l) const;
    Entier& operatorEgale(const Entier& l) const;
    Entier& operatorEgale(const Reel& l) const;
    Entier& operatorEgale(const Rationnel& l) const;
    Entier& operatorEgale(const Complexe& l) const;
    Entier& operatorEgale(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorEgale(const Expression & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Entier& operator<=(const Litteral& l) const;
    Entier& operator<=(const Entier& l) const;
    Entier& operator<=(const Reel& l) const;
    Entier& operator<=(const Rationnel& l) const;
    Entier& operator<=(const Complexe& l) const;
    Entier& operator<=(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator<=(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Entier& operator>=(const Litteral& l) const;
    Entier& operator>=(const Entier& l) const;
    Entier& operator>=(const Reel& l) const;
    Entier& operator>=(const Rationnel& l) const;
    Entier& operator>=(const Complexe& l) const;
    Entier& operator>=(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operator>=(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Entier& operatorAnd(const Litteral& l) const;
    Entier& operatorAnd(const Entier& l) const;
    Entier& operatorAnd(const Reel& l) const;
    Entier& operatorAnd(const Rationnel& l) const;
    Entier& operatorAnd(const Complexe& l) const;
    Entier& operatorAnd(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorAnd(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Entier& operatorOr(const Litteral& l) const;
    Entier& operatorOr(const Entier& l) const;
    Entier& operatorOr(const Reel& l) const;
    Entier& operatorOr(const Rationnel& l) const;
    Entier& operatorOr(const Complexe& l) const;
    Entier& operatorOr(const Programme& l) const{ throw UTComputerException("Action non autorisee a partir d'un programme.");}
    Entier& operatorOr(const Expression& l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Atome& l) const{ throw UTComputerException("Action non autorisee a partir d'un atome.");}


    Entier& operatorNot()  const;
    Litteral& operatorEval()   const;
    const Litteral & operatorSto() const;
    int operatorIft() const;
    int operatorForget() ;
    const Litteral &  operatorEdit() const;



};


#endif // RATIONNEL_H
