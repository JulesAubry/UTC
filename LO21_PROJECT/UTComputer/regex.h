#ifndef REGEX_H
#define REGEX_H

#include <regex>
#include "strategie.h"

/******************************  REGEX  *************************/
class Regex {
 regex reg;
 StrategieLitteraux* strategie;

public :
 Regex(regex _reg, StrategieLitteraux* _strategie) : reg(_reg), strategie(_strategie) {}
 virtual ~Regex() {}
 void execute(const QString& s) { strategie->execute(s); }
 regex getRegex() const {return reg;}
 virtual string toString() const = 0;

};

class Regex_entier : public Regex {
public :
 Regex_entier(): Regex(regex("-*[[:digit:]]+"), new StrategieEntier()) {}
 string toString() const{ return "Regex_entier";}
};
class Regex_reel : public Regex {
public:
    Regex_reel() : Regex(regex("-*[[:digit:]]+\\.[[:digit:]]+"), new StrategieReel()) {}
    string toString() const{ return "Regex_reel";}

};
class Regex_rationnel : public Regex {
public:
    Regex_rationnel() : Regex(regex("-*[[:digit:]]+\/[[:digit:]]+"), new StrategieRationnel()) {}
    string toString() const{ return "Regex_rationnel";}

};
class Regex_programme : public Regex {
public:
    Regex_programme() : Regex(regex("^\\[.+\\]$"), new StrategieProgramme()) {}
    string toString() const{ return "Regex_programme";}

};
class Regex_expression : public Regex {
public:
    Regex_expression() : Regex(regex("^\".+\"$"), new StrategieExpression()) {}
    string toString() const{ return "Regex_expression";}

};
class Regex_atome : public Regex {
public:
    Regex_atome() : Regex(regex("^[A-Z][a-zA-Z0-9]*"), new StrategieAtome()) {}
    string toString() const{ return "Regex_atome";}

};
/*******************************************************************/
#endif // REGEX_H
