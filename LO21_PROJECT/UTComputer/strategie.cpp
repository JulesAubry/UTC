#include "strategie.h"
#include "litteral.h"
#include "utcomputerexception.h"
#include "entier.h"
#include "reel.h"
#include "atome.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"
#include "controleur.h"




/*Transforme l'arg en chaine de caractère. Regarde si après le . il y a un 0.
Permet donc de savoir si le double peut être considéré comme un int.*/
bool getInt(double arg) {
    ostringstream oss;
    oss << arg;
    string s = oss.str();
    regex reg = regex("[[:digit:]]+");
    bool test = regex_match(s,reg);
    return test;
}

/******************************   STRATEGIES OPERATEURS *************************/

void StrategieLastOp::execute() {
    try {
        Operateur& op = Controleur::getInstance().getLastOp();
        if(&op == 0)
            throw UTComputerException("Aucun operateur disponible.");
        Controleur::getInstance().commande(op.toString());
    } catch (UTComputerException e) { throw UTComputerException(e.what());}
}

void StrategieLastArgs::execute() {
    try {
        vector<QString>& op = Controleur::getInstance().getLastArgs();
        if(op.size() == 0)
            throw UTComputerException("Aucun litteral disponible.");
        for (vector<QString>::iterator it = op.begin(); it != op.end(); ++it)
            Controleur::getInstance().commande(*it);
    } catch (UTComputerException e) { throw UTComputerException(e.what());}
}

void StrategiePlus::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2+pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Addition effectuee !");
    }
    catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieMoins::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2-pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
    }
    catch(UTComputerException e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());

    }
}

void StrategieMult::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2*pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Multiplication effectuee !");
    }
    catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
    }
}

void StrategieDiv::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2/pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Division effectuee !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieDivEntiere::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2.operatorDivEntiere(pop1);
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Division entiere effectuee !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieMod::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2%pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Modulo effectuee !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieNeg::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorNeg();
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.push(toAdd);
        pile.setMessage("NEG effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}

void StrategieNum::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorNum();
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.setMessage("NUM effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}

void StrategieDen::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorDen();
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.setMessage("DEN effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}
void StrategieComplexe::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2.operator$(pop1);
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Complexe cree !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}
void StrategieRe::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorRe();
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.setMessage("RE effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}
void StrategieIm::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorIm();
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.setMessage("RE effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}
void StrategieEgal::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2.operatorEgale(pop1);
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test d'egalite effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieNonEgal::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Entier& toAdd = pop2.operatorEgale(pop1);
        if (toAdd.getValue() == 1) {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(0);
            pile.push(toReallyAdd);
        }
        else {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(1);
            pile.push(toReallyAdd);
        }
        LitteralManager::getInstance().removeLitteral(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test de non-egalite effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}
void StrategieInfOuEgal::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2<=pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test <= effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieSupOuEgal::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop2>=pop1;
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test >= effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieSup::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Entier& toAdd = pop2<=pop1;
        if (toAdd.getValue() == 1) {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(0);
            pile.push(toReallyAdd);
        }
        else {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(1);
            pile.push(toReallyAdd);
        }
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test > effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieInf::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Entier& toAdd = pop2>=pop1;
        if (toAdd.getValue() == 1) {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(0);
            pile.push(toReallyAdd);
        }
        else {
            Entier& toReallyAdd = LitteralManager::getInstance().addEntier(1);
            pile.push(toReallyAdd);
        }
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test < effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}
void StrategieAnd::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Entier& toAdd = pop2.operatorAnd(pop1);
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test AND effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}
void StrategieOr::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        Entier& toAdd = pop2.operatorOr(pop1);
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        LitteralManager::getInstance().removeLitteral(pop2);
        pile.setMessage("Test OR effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieNot::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorNot();
        pile.push(toAdd);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        LitteralManager::getInstance().removeLitteral(pop);
        pile.setMessage("NOT effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}

void StrategieEval::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Litteral& toAdd = pop.operatorEval();
        //Le push sera fait par les strategies dans le programme
        //pile.push(toAdd);
        pile.setMessage("EVAL effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
    catch(const exception e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}

void StrategieSto::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        //On vérifie que l'action soit possible
        Litteral const & toCreateAtomWith = pop1.operatorSto();
        Atome& a = LitteralManager::getInstance().addAtome(toCreateAtomWith.toString(), pop2);
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        LitteralManager::getInstance().removeLitteral(pop1);
        pile.setMessage("STO effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}

void StrategieIft::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(2))
        throw UTComputerException("Pas assez d'element dans la pile.");
    //dépiler deux de la pile
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    try {
        //On effectue un test logique sur l'argument.
        int retour = pop2.operatorIft();
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop2.toString());
        Controleur::getInstance().getLastArgs().push_back(pop1.toString());
        if (retour > 0){//Si retour > 0
            Litteral& toAdd = pop1.operatorEval();
            LitteralManager::getInstance().removeLitteral(pop1);
            LitteralManager::getInstance().removeLitteral(pop2);
            //pile.push(toAdd);
        }
        else { //sinon, ne fait rien
            //pile.push(pop1);
            LitteralManager::getInstance().removeLitteral(pop1);
            LitteralManager::getInstance().removeLitteral(pop2);
        }
        pile.setMessage("IFT effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop2);
        pile.push(pop1);
        throw UTComputerException(e.what());
    }
}
void StrategieForget::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    if(!pile.enough(1))
        throw UTComputerException("Pas assez d'element dans la pile.");
    Litteral& pop = pile.top();
    pile.pop();
    try {
        Controleur::getInstance().getLastArgs().clear();
        Controleur::getInstance().getLastArgs().push_back(pop.toString());
        pop.operatorForget();
        pile.setMessage("FORGET effectue !");
    } catch(const UTComputerException & e) {
        pile.push(pop);
        throw UTComputerException(e.what());
    }
}

/*******************************************************************/
/******************************  STRATEGIES LITTERAUX *************************/

void StrategieEntier::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    pile.push(LitteralManager::getInstance().addEntier(s.toInt()));
    pile.setMessage("Entier ajoute !");
}

void StrategieReel::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    pile.push(LitteralManager::getInstance().addReel(s.toDouble()));
    pile.setMessage("Reel ajoute !");
}

void StrategieRationnel::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    pile.push(LitteralManager::getInstance().addRationnel(s));
    pile.setMessage("Rationnel ajoute !");

}
void StrategieProgramme::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    pile.push(LitteralManager::getInstance().addProgramme(s));
    pile.setMessage("Programme ajoute !");

}
void StrategieExpression::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    QRegExp rx("[ ]");
    QStringList list = s.split(rx, QString::SkipEmptyParts);
    QString newExpression = list.join("");
    newExpression.remove(0,1);
    newExpression.remove(newExpression.size()-1,newExpression.size()-1);
    pile.push(LitteralManager::getInstance().addExpression(newExpression));
    pile.setMessage("Expression ajoutee !");

}
void StrategieAtome::execute(const QString& s) {
    Pile & pile = Controleur::getInstance().getPile();
    pile.push(LitteralManager::getInstance().addExpression(s));
    pile.setMessage("L'atome n'a pas ete reconnu. Ajout en tant qu'expression.");

}


void StrategieEdit::execute() {
    /* A FAIRE */
}




/*******************************************************************/
/******************  STRATEGIES MANIPULATION PILE ******************/

void StrategieDup::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    //Récupérer le sommet
    Litteral& pop = pile.top();
    Litteral& toAdd = LitteralManager::getInstance().dupplicate(pop);
    pile.push(toAdd);
    pile.setMessage("Dupplication effectuee !");
}

void StrategieDrop::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    //Récupérer le sommet
    Litteral& pop = pile.top();
    //L'enlever de la pile
    pile.pop();
    //Le supprimer du manager
    LitteralManager::getInstance().removeLitteral(pop);
    pile.setMessage("DROP effectue !");
}

void StrategieSwap::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    //Récupérer le sommet
    Litteral& pop1 = pile.top();
    pile.pop();
    Litteral& pop2 = pile.top();
    pile.pop();
    pile.push(pop1);
    pile.push(pop2);
}

void StrategieClear::execute() {
    Pile & pile = Controleur::getInstance().getPile();
    //clear la pile
    while(!pile.estVide()) pile.pop();

    //Clear le memento
    Controleur::getInstance().setState(-1);
    //qDebug() << "Avant : " << Controleur::getInstance().getMementoList().size() << "\n";
    for(int i = 0; i < Controleur::getInstance().getMementoList().size(); i++) {
        Controleur::getInstance().getMementoList().pop_back();
    }
    //clear le manager
    LitteralManager::libererInstance();
    pile.setMessage("CLEAR effectue !");
}


void StrategieUndo::execute() {
    int state = Controleur::getInstance().getState();
     if(state >= 1) {
        Controleur::getInstance().setState(state-1);
        state = Controleur::getInstance().getState();
        Pile & p = Controleur::getInstance().get(state).getState();
        Controleur::getInstance().getPile() = p;
    }
    else throw UTComputerException("Il n'est pas possible de UNDO");
}


void StrategieRedo::execute() {
    int state = Controleur::getInstance().getState();
    if(state >= 0 && state < Controleur::getInstance().getMementoList().size()-1
            ) {
        Controleur::getInstance().setState(state+1);
        state = Controleur::getInstance().getState();
        Pile & p = Controleur::getInstance().get(state).getState();
        Controleur::getInstance().getPile() = p;
    }
    else throw UTComputerException("Il n'est pas possible de REDO");
}



/*******************************************************************/
