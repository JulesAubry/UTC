#ifndef MEMENTO_H
#define MEMENTO_H

#include "computer.h"

class Memento {
   Pile & pile;

public :
    Memento(Pile & p) : pile(p) {}

    Pile & getState(){
          return pile;
    }
};

#endif // MEMENTO_H
