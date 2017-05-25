#ifndef QCOMPUTER_H
#define QCOMPUTER_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QDebug>
#include <QSound>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QEvent>
#include <QSignalMapper>
#include <iostream>
#include "computer.h"
#include "controleur.h"

class QComputer : public QWidget{
    Q_OBJECT

    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
    QLineEdit* listeCommandes; //Affichage de la liste des commandes
    QPushButton* options; //PushButton qui affiche le widget
    QPushButton* voirProgrammes; //PushButton qui affiche les programmes
    QPushButton* voirVariables; //PushButton qui affiche les variables
    QWidget* optionsWidget; //Pour dire si l'on veut un clavier ou non, changer la valeur dans la pile et le bip lors du message
    QWidget* programmesWidget; //Pour dire si l'on veut un clavier ou non, changer la valeur dans la pile et le bip lors du message
    QLineEdit * programmeLine;
    QLineEdit * programmeIdLine;
    QTableWidget* vueProgrammes;
    QWidget* editProgrammesWidget;
    QTextEdit* editProgrammesTextEdit;

    QWidget* variablesWidget; //Pour dire si l'on veut un clavier ou non, changer la valeur dans la pile et le bip lors du message
    QLineEdit * variableLine;
    QLineEdit * variableIdLine;
    QTableWidget* vueVariables;
    QWidget* editVariablesWidget;
    QTextEdit* editVariablesTextEdit;

    QWidget * clavierWidget; //Widget pour le clavier sinon on ne peut pas le hide ou show

    Pile* pile;
    Controleur* controleur;
public:
    explicit QComputer(QWidget *parent = 0);
public slots:
    void refresh();
    void getNextCommande();
    void stateChangedBipOptions(int);
    void playBipOptions();
    void stateChangedOptionClavier(int);
    void buttonTriggered(int);

            //Widget programme//
            void addProgramme();
            void deleteProgramme();
            void updateProgrammes();
            void editerProgrammeFunc();
            void lancerEditionProgramme();

            //Widget variable//
            void addVariable();
            void deleteVariable();
            void updateVariables();
            void editerVariableFunc();
            void lancerEditionVariable();


};
#endif // QCOMPUTER_H
