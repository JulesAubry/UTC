#include "operator.h"
#include "utcomputerexception.h"

void Operateur::execute() {
    try {
        strategie->execute();
    } catch (UTComputerException e) { throw e;}
}

OperateurPlus::OperateurPlus():Operateur("+",new StrategiePlus()){}
OperateurMoins::OperateurMoins():Operateur("-",new StrategieMoins()){}
OperateurMult::OperateurMult():Operateur("*",new StrategieMult()){}
OperateurDiv::OperateurDiv():Operateur("/",new StrategieDiv()){}
OperateurDivEntiere::OperateurDivEntiere():Operateur("DIV",new StrategieDivEntiere()){}
OperateurNeg::OperateurNeg():Operateur("NEG",new StrategieNeg()){}
OperateurMod::OperateurMod():Operateur("MOD",new StrategieMod()){}
OperateurNum::OperateurNum():Operateur("NUM",new StrategieNum()){}
OperateurDen::OperateurDen():Operateur("DEN",new StrategieDen()){}
OperateurComplexe::OperateurComplexe():Operateur("$",new StrategieComplexe()){}
OperateurRe::OperateurRe():Operateur("RE",new StrategieRe()){}
OperateurIm::OperateurIm():Operateur("IM",new StrategieIm()){}
OperateurEgal::OperateurEgal():Operateur("=",new StrategieEgal()){}
OperateurNonEgal::OperateurNonEgal():Operateur("!=",new StrategieNonEgal()){}
OperateurInfOuEgal::OperateurInfOuEgal():Operateur("<=",new StrategieInfOuEgal()){}
OperateurSup::OperateurSup():Operateur(">",new StrategieSup()){}
OperateurSupOuEgal::OperateurSupOuEgal():Operateur(">=",new StrategieSupOuEgal()){}
OperateurInf::OperateurInf():Operateur("<",new StrategieInf()){}
OperateurAnd::OperateurAnd():Operateur("AND",new StrategieAnd()){}
OperateurOr::OperateurOr():Operateur("OR",new StrategieOr()){}
OperateurNot::OperateurNot():Operateur("NOT",new StrategieNot()){}
OperateurEval::OperateurEval():Operateur("EVAL",new StrategieEval()){}
OperateurUndo::OperateurUndo():Operateur("UNDO",new StrategieUndo()){}
OperateurRedo::OperateurRedo():Operateur("REDO",new StrategieRedo()){}
OperateurIft::OperateurIft():Operateur("IFT",new StrategieIft()){}
OperateurSto::OperateurSto():Operateur("STO", new StrategieSto()){}
OperateurForget::OperateurForget():Operateur("FORGET", new StrategieForget()){}
OperateurEdit::OperateurEdit():Operateur("EDIT", new StrategieEdit()){}
OperateurLastOp::OperateurLastOp():Operateur("LASTOP", new StrategieLastOp()){}
OperateurLastArgs::OperateurLastArgs():Operateur("LASTARGS", new StrategieLastArgs()){}






/* Manipulation de la pile */
OperateurDup::OperateurDup():Operateur("DUP",new StrategieDup()){}
OperateurDrop::OperateurDrop():Operateur("DROP",new StrategieDrop()){}
OperateurSwap::OperateurSwap():Operateur("SWAP",new StrategieSwap()){}
OperateurClear::OperateurClear():Operateur("CLEAR",new StrategieClear()){}
