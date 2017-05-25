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
    QString getInfo() { return "Type : binaire\n D�pile 2 fois, fait une addition, et empile le r�sultat.";}
};
class OperateurMoins : public Operateur{
public:
    OperateurMoins();
    QString getInfo() { return "Type : binaire\n D�pile 2 fois, fait une soustraction, et empile le r�sultat.";}
};
class OperateurMult : public Operateur{
public:
    OperateurMult();
    QString getInfo() { return "Type : binaire\n D�pile 2 fois, fait une multiplication, et empile le r�sultat.";}
};
class OperateurDiv : public Operateur{
public:
    OperateurDiv();
    QString getInfo() { return "Type : binaire\n D�pile 2 fois, fait une division, et empile le r�sultat.";}
};
class OperateurDivEntiere : public Operateur{
public:
    OperateurDivEntiere();
    QString getInfo() { return "Type : binaire\n D�pile 2 fois, fait une division entiere, et empile le r�sultat.";}
};
class OperateurNeg : public Operateur{
public:
    OperateurNeg();
    QString getInfo() { return "Type : unaire.\n D�pile 1 fois, inverse le signe d'un lit�ral, et empile le r�sultat.";}
};
class OperateurMod : public Operateur{
public:
    OperateurMod();
    QString getInfo() { return "Type : binaire.\n D�pile 2 fois, fait une division, et empile le reste de la division.";}
};
class OperateurNum : public Operateur{
public:
    OperateurNum();
    QString getInfo() { return "Type : unaire.\n D�pile 1 fois, r�cup�re le num�rateur, et l'empile.";}
};
class OperateurDen : public Operateur{
public:
    OperateurDen();
    QString getInfo() { return "Type : unaire.\n D�pile 1 fois, r�cup�re le num�rateur, et l'empile.";}
};
class OperateurDup : public Operateur{
public:
    OperateurDup();
    QString getInfo() { return "Empile une nouvelle litt�rale identique � celle du sommet de la pile.";}
};
class OperateurDrop : public Operateur{
public:
    OperateurDrop();
    QString getInfo() { return "D�pile la litt�rale au sommet de la pile.";}
};
class OperateurSwap : public Operateur{
public:
    OperateurSwap();
    QString getInfo() { return "Op�rateur binaire : intervertit les deux derniers �l�ments empil�s dans la pile.";}
};
class OperateurClear : public Operateur{
public:
    OperateurClear();
    QString getInfo() { return "Vide tous les �l�ments de la pile.";}
};
class OperateurComplexe : public Operateur{
public:
    OperateurComplexe();
    QString getInfo() { return "Op�rateur binaire : renvoie une litt�rale complexe constitu�e � partir des deux derniers �l�ments de la pile qui constitueront la partie r�elle et la partie imaginaire du complexe.";}
};
class OperateurRe : public Operateur{
public:
    OperateurRe();
    QString getInfo() { return "Op�rateur unaire :  renvoie la partie r�elle d�une litt�rale complexe qui peut �tre une litt�rale enti�re,rationelle ou r�elle. Appliqu� � une litt�rale enti�re, rationelle ou r�elle, cet op�rateur renvoie la litt�rale inchang�e.";}
};
class OperateurIm : public Operateur{
public:
    OperateurIm();
    QString getInfo() { return "op�rateur unaire : renvoie la partie im�ginaire d�une litt�rale complexe qui peut �tre une litt�rale enti�re, rationelle ou r�elle. Appliqu� � une litt�rale enti�re, rationelle ou r�elle, cet op�rateur renvoie la litt�rale enti�re 0";}
};
class OperateurEgal : public Operateur{
public:
    OperateurEgal();
    QString getInfo() { return "op�rateur binaire : retourne 1 si �gal, 0 si non �gal.";}
};
class OperateurNonEgal : public Operateur{
public:
    OperateurNonEgal();
    QString getInfo() { return "op�rateur binaire : retourne 1 si non �gal, 0 si �gal.";}
};
class OperateurInfOuEgal : public Operateur{
public:
    OperateurInfOuEgal();
    QString getInfo() { return "op�rateur binaire : retourne 1 si <=, 0 sinon.";}
};
class OperateurSup : public Operateur{
public:
    OperateurSup();
    QString getInfo() { return "op�rateur binaire : retourne 1 si >, 0 sinon.";}
};
class OperateurSupOuEgal : public Operateur{
public:
    OperateurSupOuEgal();
    QString getInfo() { return "op�rateur binaire : retourne 1 si >=, 0 sinon.";}
};
class OperateurInf : public Operateur{
public:
    OperateurInf();
    QString getInfo() { return "op�rateur binaire : retourne 1 si <, 0 sinon.";}
};
class OperateurAnd : public Operateur{
public:
    OperateurAnd();
    QString getInfo() { return "op�rateur binaire : retourne 1 si les deux litt�rales d�pil�es sont > 0";}
};
class OperateurOr : public Operateur{
public:
    OperateurOr();
    QString getInfo() { return "op�rateur binaire : retourne 1 si au moins une des deux litt�rales est > 0";}
};
class OperateurNot : public Operateur{
public:
    OperateurNot();
    QString getInfo() { return "op�rateur unaire : inverse la valeur de v�rit�";}
};
class OperateurEval : public Operateur{
public:
    OperateurEval();
    QString getInfo() { return "op�rateur unaire : evalue une expression ou un programme.";}
};
class OperateurIft : public Operateur{
public:
    OperateurIft();
    QString getInfo() { return "d�pile 2 arguments. Le 1er (i.e. le dernier d�pil�) est un test logique. Si la valeur de ce test est vrai, le 2e argument est �valu� sinon il est abandonn�.";}
};
class OperateurUndo : public Operateur{
public:
    OperateurUndo();
    QString getInfo() { return "retour � la pile pr�c�dente";}
};
class OperateurRedo : public Operateur{
public:
    OperateurRedo();
    QString getInfo() { return "annulation du undo";}
};

class OperateurSto : public Operateur{
public:
    OperateurSto();
    QString getInfo() { return "d�pile 2, si premier expression et deuxi�me un litt�ral ok sinon r�empile";}
};
class OperateurForget: public Operateur{
public:
    OperateurForget();
    QString getInfo() { return "D�pile et efface l'atome.";}
};
class OperateurEdit: public Operateur{
public:
    OperateurEdit();
    QString getInfo() { return "Affiche la fenetre d'edition d'une expression";}
};
class OperateurLastOp: public Operateur{
public:
    OperateurLastOp();
    QString getInfo() { return "applique le dernier op�rateur utilis�";}
};
class OperateurLastArgs: public Operateur{
public:
    OperateurLastArgs();
    QString getInfo() { return "empile les derniers litt�raux utilis�s ";}
};
/*******************************************************************/

#endif // OPERATOR_H
