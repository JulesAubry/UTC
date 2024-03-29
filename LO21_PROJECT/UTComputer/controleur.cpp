#include "controleur.h"
#include "atome.h"

/******************************   CONTROLEUR *************************/

Controleur * Controleur::instance = nullptr;

void Controleur::commande(const QString& c){
    bool found = false;
    bool found_bis = false;

    //On regarde si c'est un litt�ral
    /*for( std::vector<Regex*>::iterator it = listeRegex.begin(); it != listeRegex.end(); ++it){
       if(regex_match(c.toStdString(),(*it)->getRegex())){
            (*it)->execute(expAff,c);
            found = true;
        }
    }
    if (!found){ //sinon c'est un op�rateur
        // On cherche l'op�rateur parmis la liste
        for( std::vector<Operateur*>::iterator it = listeOperateurs.begin(); it != listeOperateurs.end(); ++it){
            if ((*it)->toString() == c) {
                (*it)->execute(expAff);
                found = true;
            }
        }
    }
   if (!found)
        expAff.setMessage("Requete non implementee.");*/

    try {
        //on regarde si �a match un programme/expression/litteral unaire
        bool go = true;
        for( std::vector<Regex*>::iterator it = listeRegex->begin(); it != listeRegex->end(); ++it){
            if((regex_match(c.toStdString(),(*it)->getRegex())) && (found==false) && ((*it)->toString() != "Regex_atome")){
                (*it)->execute(c);
                found = true;
                found_bis = true;
                go = false;
            }
        }
        //sinon, on split tout
        if (go == true){
            found = false;
            QRegExp rx("[ ]");
            QStringList list = c.split(rx, QString::SkipEmptyParts);
            for(int i = 0; i < list.length(); i++) {
                //On regarde si c'est un operateur
                for( std::vector<Operateur*>::iterator it = listeOperateurs->begin(); it != listeOperateurs->end(); ++it){
                    if ((*it)->toString() == list.at(i)) {
                        (*it)->execute();
                        found = true;
                        lastOp = (*it);
                        found_bis = true;

                    }
                }
                if (!found){ // sinon c'est un litteral ?
                    for( std::vector<Regex*>::iterator it = listeRegex->begin(); it != listeRegex->end(); ++it){
                        if((regex_match(list.at(i).toStdString(),(*it)->getRegex())) && (found==false) && ((*it)->toString() != "Regex_atome")){
                            (*it)->execute(list.at(i));
                            found = true;
                              found_bis = true;
                        }
                    }
                }
                if (!found){ //sinon un atome ?
                    //On regarde si �a match un atome : programme
                    for( std::vector<Atome*>::iterator it = listeProgrammes->begin(); it != listeProgrammes->end(); ++it){
                        if(((*it)->getID() == list.at(i)) && (found==false)){
                            expAff->push((*it)->getValue());
                            commande("EVAL");
                            found = true;
                            found_bis = true;
                        }
                    }
                    //On regarde si �a match un atome : autres que programme
                    for( std::vector<Atome*>::iterator it = listeAtomes->begin(); it != listeAtomes->end(); ++it){
                        if(((*it)->getID() == list.at(i)) && (found==false)){
                            expAff->push((*it)->getValue());
                            found = true;
                            found_bis = true;
                        }
                    }
                }
                if (!found){ // sinon c'est peut un atome non reconnu, donc on l'ajoute en tant qu'expression
                    for( std::vector<Regex*>::iterator it = listeRegex->begin(); it != listeRegex->end(); ++it){
                        if((regex_match(list.at(i).toStdString(),(*it)->getRegex())) && (found==false)){
                            (*it)->execute(list.at(i));
                            found = true;
                        }
                    }
                }

                // sinon commande non reconnue
                if(!found) throw UTComputerException("Requete non implementee/erreur syntaxique.");
                found = false;
            }
        }
        if(c.toStdString() != "REDO" &&  c.toStdString() != "UNDO" && c.toStdString() != "CLEAR" && found_bis && c != ""){
                Pile * p = new Pile();
                for(int i = 0; i < expAff->taille(); i++) {
                    p->push(expAff->getItems()[i].getLitteral());
                }
                for(int i = state+1; i < mementoList.size(); i++) {
                    mementoList.pop_back();
                }
                add(Memento(*p));
                state = mementoList.size()-1;

                //qDebug() << state;
        }
    } catch(UTComputerException e){
        throw UTComputerException(e.what());
    }
}

/* if(c.toStdString() != "REDO" &&  c.toStdString() != "UNDO" && c != ""){
        Pile * p = new Pile();
        for(int i = 0; i < expAff->taille(); i++) {
            p->push(expAff->getItems()[i].getLitteral());
        }
        for(int i = state; i < mementoList.size(); i++) {
            mementoList.pop_back();
        }
        add(Memento(*p));
        state++;
        state = mementoList.size();
    }*/




Controleur& Controleur::getInstance() {
    if(Controleur::instance == nullptr) Controleur::instance = new Controleur(LitteralManager::getInstance(), nullptr, nullptr, nullptr);
    return *Controleur::instance;
}

void Controleur::libererInstance(){
    delete Controleur::instance;
}


void Controleur::init(Pile* v,  std::vector<Operateur*>* _listeOperateurs,std::vector<Regex*>* _listeRegex) {
    expAff = v;
    listeOperateurs = _listeOperateurs;
    listeRegex = _listeRegex;
}


/*******************************************************************/
