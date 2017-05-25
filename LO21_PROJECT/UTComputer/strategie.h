#ifndef STRATEGIE_H
#define STRATEGIE_H

#include "computer.h"
#include <typeinfo>
#include <cassert>
#include <math.h>

class Pile;
class Regex;
class Operateur;

/******************************   STRATEGIE *************************/
class StrategieOperateurs {
public:
    virtual void execute() = 0;
};

class StrategieLitteraux {
public:
    virtual void execute(const QString& s) = 0;
};
/*******************************************************************/
/******************************   STRATEGIES OPERATEURS  *************************/
class StrategiePlus : public StrategieOperateurs {
public:
    void execute();
};
class StrategieMoins : public StrategieOperateurs {
public:
    void execute();
};
class StrategieMult : public StrategieOperateurs {
public:
    void execute();
};
class StrategieDiv : public StrategieOperateurs {
public:
    void execute();
};
class StrategieDivEntiere : public StrategieOperateurs {
public:
    void execute();
};
class StrategieNeg: public StrategieOperateurs {
public:
    void execute();
};
class StrategieMod: public StrategieOperateurs {
public:
    void execute();
};
class StrategieNum: public StrategieOperateurs {
public:
    void execute();
};
class StrategieDen: public StrategieOperateurs {
public:
    void execute();
};
class StrategieDup: public StrategieOperateurs {
public:
    void execute();
};
class StrategieDrop: public StrategieOperateurs {
public:
    void execute();
};
class StrategieSwap: public StrategieOperateurs {
public:
    void execute();
};
class StrategieClear: public StrategieOperateurs {
public:
    void execute();
};
class StrategieComplexe: public StrategieOperateurs {
public:
    void execute();
};
class StrategieRe: public StrategieOperateurs {
public:
    void execute();
};
class StrategieIm: public StrategieOperateurs {
public:
    void execute();
};
class StrategieEgal: public StrategieOperateurs {
public:
    void execute();
};
class StrategieNonEgal: public StrategieOperateurs {
public:
    void execute();
};
class StrategieInfOuEgal: public StrategieOperateurs {
public:
    void execute();
};
class StrategieSup: public StrategieOperateurs {
public:
    void execute();
};
class StrategieSupOuEgal: public StrategieOperateurs {
public:
    void execute();
};
class StrategieInf: public StrategieOperateurs {
public:
    void execute();
};
class StrategieAnd: public StrategieOperateurs {
public:
    void execute();
};
class StrategieOr: public StrategieOperateurs {
public:
    void execute();
};
class StrategieNot: public StrategieOperateurs {
public:
    void execute();
};
class StrategieEval: public StrategieOperateurs {
public:
    void execute();
};

class StrategieIft: public StrategieOperateurs {
public:
    void execute();
};
class StrategieUndo: public StrategieOperateurs {
public:
    void execute();
};
class StrategieRedo: public StrategieOperateurs {
public:
    void execute();
};

class StrategieSto: public StrategieOperateurs {
public:
    void execute();
};
class StrategieForget: public StrategieOperateurs {
public:
    void execute();
};
class StrategieEdit: public StrategieOperateurs {
public:
    void execute();
};
class StrategieLastOp: public StrategieOperateurs {
public:
    void execute();
};
class StrategieLastArgs: public StrategieOperateurs {
public:
    void execute();
};




/*******************************************************************/
/******************************   STRATEGIES LITTERAUX  *************************/
class StrategieEntier : public StrategieLitteraux {
public:
    void execute(const QString& s);
};

class StrategieReel : public StrategieLitteraux {
public:
    void execute(const QString& s);
};

class StrategieRationnel : public StrategieLitteraux {
public:
    void execute(const QString& s);
};
class StrategieProgramme : public StrategieLitteraux {
public:
    void execute(const QString& s);
};
class StrategieExpression : public StrategieLitteraux {
public:
    void execute(const QString& s);
};
class StrategieAtome : public StrategieLitteraux {
public:
    void execute(const QString& s);
};
/*******************************************************************/

#endif // STRATEGIE_H
