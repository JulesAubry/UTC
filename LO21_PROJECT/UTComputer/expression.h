#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "litteral.h"
class Expression : public Litteral {
    friend class LitteralManager;
    QString expression;
    Expression(QString _expression) :expression(_expression) {}
    Expression(const Expression& e) { expression = e.expression; }
public:

    virtual QString toString () const;
    Litteral& getValue() const { throw UTComputerException("getValue n'est pas implementee pour les expressions.");}
    Litteral& operator+(const Litteral & l) const { try { l+*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator+(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator+(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}


    Litteral& operator-(const Litteral & l) const { try { l-*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator-(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator-(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator*(const Litteral & l) const { try { l * *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator*(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator*(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator/(const Litteral & l) const { try { l / *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator/(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Rationnel & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Complexe & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Programme & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator/(const Atome & l) const{ throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorNeg() { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorDivEntiere(const Litteral& l) const { try { l.operatorDivEntiere(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operatorDivEntiere(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Reel& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Rationnel& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Complexe& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Programme& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDivEntiere(const Atome& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operator%(const Litteral & l) const { try { l%*this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Litteral& operator%(const Entier& l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Reel & l)  const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Rationnel & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Complexe & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Programme & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator%(const Atome & l) const { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorNum()  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorDen()  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral* clone() const { return new Expression(*this); }
    Litteral& operator$(const Litteral & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Reel & l)  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Rationnel & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Complexe & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Programme & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operator$(const Atome & l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Litteral& operatorRe()  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorIm()  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorEgale(const Litteral& l) const { try { l.operatorEgale(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorEgale(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorEgale(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operator<=(const Litteral& l) const { try { l <= *this; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operator<=(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator<=(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operator>=(const Litteral& l) const { try { l >= *this ; } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operator>=(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operator>=(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorAnd(const Litteral& l) const  { try { l.operatorAnd(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorAnd(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorAnd(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorOr(const Litteral& l) const { try { l.operatorOr(*this); } catch (UTComputerException e) { throw UTComputerException(e.what());}}
    Entier& operatorOr(const Entier& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Reel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Rationnel& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Complexe& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Programme& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Entier& operatorOr(const Atome& l) const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}

    Entier& operatorNot()  const  { throw UTComputerException("Action non autorisee a partir d'une expression.");}
    Litteral& operatorEval()  const;
    const Litteral& operatorSto() const;
    int operatorIft() const;
   int  operatorForget() ;
   const Litteral &  operatorEdit() const;





};






#endif // EXPRESSION_H
