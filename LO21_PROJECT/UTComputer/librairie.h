#ifndef LIBRAIRIE_H
#define LIBRAIRIE_H

#include <string>
#include <vector>
#include "operator.h"
class Operateur;

/*Transforme l'arg en chaine de caractère. Regarde si après le . il y a un 0.
Permet donc de savoir si le double peut être considéré comme un int.*/
bool isInt(double arg);

int precedence(char op);
QString parse(QString exp,const std::vector<Operateur*> listeOperateurs);


#endif // LIBRAIRIE_H
