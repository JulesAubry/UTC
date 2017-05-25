#include <sstream>
#include <regex>
#include "librairie.h"
#include "utcomputerexception.h"

using namespace std;

/*Transforme l'arg en chaine de caractère. Regarde si après le . il y a un 0.
Permet donc de savoir si le double peut être considéré comme un int.*/
bool isInt(double arg) {
    ostringstream oss;
    oss << arg;
    string s = oss.str();
    regex reg = regex("[[:digit:]]+");
    bool test = regex_match(s,reg);
    return test;
}


int precedence(char op) {
    switch(op) {
    case '-': case '+':
        return 1;
    case '*': case '/':
        return 2;
    default:
        return 0;
    }
}

QString parse(QString toParse,const vector<Operateur*> listeOperateurs) {
    string output;
    stack<string> operators;
    string symbols = "+*-/";
    string exp = toParse.toStdString();

    vector<string> availableFunctions;
    for (vector<Operateur *>::const_iterator it = listeOperateurs.begin(); it != listeOperateurs.end(); ++it)
        availableFunctions.push_back((*it)->toString().toStdString());

    while(!exp.empty()) {
        char c = exp[0];
        exp.erase(0, 1);

        string token;
        token += c;

        // 1. Si c'est un nombre on l'ajoute dans la file
        if(isdigit(c)) {
            // On récupère la suite du nombre
            while(!exp.empty() && (c = exp[0]) && (isdigit(c) || c == '.' || c == '$')) {
                token += c;
                exp.erase(0, 1);
            }
            output.append(token + ' ');
            // 2. Si c'est un operateur
        } else if(symbols.find(c) != string::npos) {
            // while there is an operator token at the top of the operator stack
            while(!operators.empty() && (precedence(c) <= precedence(operators.top()[0]))) {
                //pop o2 off the operator stack, onto the output queue;
                output.append(operators.top() + ' ');
                operators.pop();
            }
            // at the end of iteration push o1 onto the operator stack.
            operators.push(token);
            //4. If the token is a left parenthesis '(', then push it onto the stack
        } else if(c == '(') {
            operators.push(token);
            // 5. If the token is a right parenthesis ')'
        } else if(c == ')') {
            // Until the token at the top of the stack is a left parenthesis, pop operators off the stack onto the output queue.
            while(!operators.empty() && operators.top() != "(") {
                output.append(operators.top() + ' ');
                operators.pop();
            }
            if(operators.empty() || operators.top() != "(")
                throw UTComputerException("Parenthèses dépareillées.");

            // Pop the left parenthesis from the stack, but not onto the output queue.
            operators.pop();
            // If the token at the top of the stack is a function token, pop it onto the output queue.
            if(!operators.empty()) {
                string fun = operators.top();
                if(fun != "(") {
                    if(find(availableFunctions.begin(), availableFunctions.end(), operators.top()) != availableFunctions.end()) {
                        output.append(fun + ' ');
                        operators.pop();
                    }
                    // TODO : regarder aussi la chaine des variables

                    else
                        //throw exception("Pas d'opérateurs disponibles avec le nom : '+ fun +'");
                        throw UTComputerException("Pas d'opérateurs disponibles avec ce nom");
                }
            }
            // 3. Sinon c'est une fonction (ou une variable)
        } else {
            // TODO traiter variable connues
            while(!exp.empty() && (c = exp[0]) && (isalpha(c) || isdigit(c))) {
                token += c;
                exp.erase(0, 1);
            }
            operators.push(token);
        }
    }
    while(!operators.empty()) {
        if(operators.top() == "(" || operators.top() == ")")
            throw UTComputerException("Parenthèses dépareillées");
        else {
            output.append(operators.top() + ' ');
            operators.pop();
        }
    }

    return QString::fromStdString(output);
}


