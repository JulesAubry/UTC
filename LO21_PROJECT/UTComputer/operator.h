#ifndef OPERATOR_H
#define OPERATOR_H

#include "computer.h"
#include "strategie.h"


class Pile;
class StrategieOperateurs;
class Regex;

/******************************   OPERATEUR  *************************/
class Operateur {
    QString symbol;
    StrategieOperateurs* strategie;
public :
    Operateur(const QString& _symbol, StrategieOperateurs* _strategie):symbol(_symbol),strategie(_strategie){}
    virtual ~Operateur(){delete strategie;}
    QString toString() const { return symbol; }
    void execute();
    virtual QString getInfo() = 0;
};
class OperateurPlus : public Operateur{
public:
    OperateurPlus();
    QString getInfo() { return "Type : binaire\n Dépile 2 fois, fait une addition, et empile le résultat.";}
};
class OperateurMoins : public Operateur{
public:
    OperateurMoins();
    QString getInfo() { return "Type : binaire\n Dépile 2 fois, fait une soustraction, et empile le résultat.";}
};
class OperateurMult : public Operateur{
public:
    OperateurMult();
    QString getInfo() { return "Type : binaire\n Dépile 2 fois, fait une multiplication, et empile le résultat.";}
};
class OperateurDiv : public Operateur{
public:
    OperateurDiv();
    QString getInfo() { return "Type : binaire\n Dépile 2 fois, fait une division, et empile le résultat.";}
};
class OperateurDivEntiere : public Operateur{
public:
    OperateurDivEntiere();
    QString getInfo() { return "Type : binaire\n Dépile 2 fois, fait une division entiere, et empile le résultat.";}
};
class OperateurNeg : public Operateur{
public:
    OperateurNeg();
    QString getInfo() { return "Type : unaire.\n Dépile 1 fois, inverse le signe d'un litéral, et empile le résultat.";}
};
class OperateurMod : public Operateur{
public:
    OperateurMod();
    QString getInfo() { return "Type : binaire.\n Dépile 2 fois, fait une division, et empile le reste de la division.";}
};
class OperateurNum : public Operateur{
public:
    OperateurNum();
    QString getInfo() { return "Type : unaire.\n Dépile 1 fois, récupère le numérateur, et l'empile.";}
};
class OperateurDen : public Operateur{
public:
    OperateurDen();
    QString getInfo() { return "Type : unaire.\n Dépile 1 fois, récupère le numérateur, et l'empile.";}
};
class OperateurDup : public Operateur{
public:
    OperateurDup();
    QString getInfo() { return "Empile une nouvelle littérale identique à celle du sommet de la pile.";}
};
class OperateurDrop : public Operateur{
public:
    OperateurDrop();
    QString getInfo() { return "Dépile la littérale au sommet de la pile.";}
};
class OperateurSwap : public Operateur{
public:
    OperateurSwap();
    QString getInfo() { return "Opérateur binaire : intervertit les deux derniers éléments empilés dans la pile.";}
};
class OperateurClear : public Operateur{
public:
    OperateurClear();
    QString getInfo() { return "Vide tous les éléments de la pile.";}
};
class OperateurComplexe : public Operateur{
public:
    OperateurComplexe();
    QString getInfo() { return "Opérateur binaire : renvoie une littérale complexe constituée à partir des deux derniers éléments de la pile qui constitueront la partie réelle et la partie imaginaire du complexe.";}
};
class OperateurRe : public Operateur{
public:
    OperateurRe();
    QString getInfo() { return "Opérateur unaire :  renvoie la partie réelle d’une littérale complexe qui peut être une littérale entière,rationelle ou réelle. Appliqué à une littérale entière, rationelle ou réelle, cet opérateur renvoie la littérale inchangée.";}
};
class OperateurIm : public Operateur{
public:
    OperateurIm();
    QString getInfo() { return "opérateur unaire : renvoie la partie iméginaire d’une littérale complexe qui peut être une littérale entière, rationelle ou réelle. Appliqué à une littérale entière, rationelle ou réelle, cet opérateur renvoie la littérale entière 0";}
};
class OperateurEgal : public Operateur{
public:
    OperateurEgal();
    QString getInfo() { return "opérateur binaire : retourne 1 si égal, 0 si non égal.";}
};
class OperateurNonEgal : public Operateur{
public:
    OperateurNonEgal();
    QString getInfo() { return "opérateur binaire : retourne 1 si non égal, 0 si égal.";}
};
class OperateurInfOuEgal : public Operateur{
public:
    OperateurInfOuEgal();
    QString getInfo() { return "opérateur binaire : retourne 1 si <=, 0 sinon.";}
};
class OperateurSup : public Operateur{
public:
    OperateurSup();
    QString getInfo() { return "opérateur binaire : retourne 1 si >, 0 sinon.";}
};
class OperateurSupOuEgal : public Operateur{
public:
    OperateurSupOuEgal();
    QString getInfo() { return "opérateur binaire : retourne 1 si >=, 0 sinon.";}
};
class OperateurInf : public Operateur{
public:
    OperateurInf();
    QString getInfo() { return "opérateur binaire : retourne 1 si <, 0 sinon.";}
};
class OperateurAnd : public Operateur{
public:
    OperateurAnd();
    QString getInfo() { return "opérateur binaire : retourne 1 si les deux littérales dépilées sont > 0";}
};
class OperateurOr : public Operateur{
public:
    OperateurOr();
    QString getInfo() { return "opérateur binaire : retourne 1 si au moins une des deux littérales est > 0";}
};
class OperateurNot : public Operateur{
public:
    OperateurNot();
    QString getInfo() { return "opérateur unaire : inverse la valeur de vérité";}
};
class OperateurEval : public Operateur{
public:
    OperateurEval();
    QString getInfo() { return "opérateur unaire : evalue une expression ou un programme.";}
};
class OperateurIft : public Operateur{
public:
    OperateurIft();
    QString getInfo() { return "dépile 2 arguments. Le 1er (i.e. le dernier dépilé) est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.";}
};
class OperateurUndo : public Operateur{
public:
    OperateurUndo();
    QString getInfo() { return "retour à la pile précédente";}
};
class OperateurRedo : public Operateur{
public:
    OperateurRedo();
    QString getInfo() { return "annulation du undo";}
};

class OperateurSto : public Operateur{
public:
    OperateurSto();
    QString getInfo() { return "dépile 2, si premier expression et deuxième un littéral ok sinon réempile";}
};
class OperateurForget: public Operateur{
public:
    OperateurForget();
    QString getInfo() { return "Dépile et efface l'atome.";}
};
class OperateurEdit: public Operateur{
public:
    OperateurEdit();
    QString getInfo() { return "Affiche la fenetre d'edition d'une expression";}
};
class OperateurLastOp: public Operateur{
public:
    OperateurLastOp();
    QString getInfo() { return "applique le dernier opérateur utilisé";}
};
class OperateurLastArgs: public Operateur{
public:
    OperateurLastArgs();
    QString getInfo() { return "empile les derniers littéraux utilisés ";}
};
/*******************************************************************/

#endif // OPERATOR_H
