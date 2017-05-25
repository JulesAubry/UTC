#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <string>
#include <vector>
#include "operator.h"
class Operateur;

/*Transforme l'arg en chaine de caract�re. Regarde si apr�s le . il y a un 0.
Permet donc de savoir si le double peut �tre consid�r� comme un int.*/
bool isInt(double arg);

int precedence(char op);
QString parse(QString exp,const std::vector<Operateur*> listeOperateurs);


#endif // LIBRAIRIE_H
