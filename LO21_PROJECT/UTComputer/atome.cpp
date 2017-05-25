#include "entier.h"
#include "reel.h"
#include "rationnel.h"
#include "complexe.h"
#include "programme.h"
#include "expression.h"
#include "atome.h"





QString Atome::toString() const {
    QString s;
    s+= id;
    s+= value->toString();
    return s;
}
/*
void Atome::editLitteral(const Litteral & l) {
    LitteralManager::getInstance().removeLitteral(value);
    value = l;
}*/

void Atome::editLitteral( Litteral* l) {
    LitteralManager::getInstance().removeLitteral(*value);
    this->value = l;
}
