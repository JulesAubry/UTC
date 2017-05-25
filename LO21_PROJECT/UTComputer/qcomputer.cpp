#include "qcomputer.h"
#include "atome.h"
#include "programme.h"
#include "expression.h"

void QComputer::refresh() {
    int row = 0;
    commande->clear();
    vuePile->clear();

    /*
       for(Pile::iterator it =  pile->begin(); it!=pile->end(); ++it) {
         qDebug() << row << " : " << (*it).getValue();
       }
*/
    for(Pile::iterator it =  pile->begin(); it!=pile->end(); ++it) {
        vuePile->setItem(row, 0, new QTableWidgetItem((*it).toString()));
        row++;
    }
}

void QComputer::getNextCommande() {
    QString s = commande->text();
    QString nouveauMessage = (QString(listeCommandes->text())) + s;
    if (nouveauMessage.length() > 41) listeCommandes->setText(QString(""));
    else listeCommandes->setText(nouveauMessage);
    try {
        controleur->commande(s);
        message->setText(QString(pile->getMessage()));
    }
    catch (UTComputerException e) { message->setText(e.what());}
    catch (ComputerException e) { message->setText(e.getInfo());}

}

void QComputer::stateChangedBipOptions(int i) {
    if (i == 0) { //non cochÃ©
        message->blockSignals(true);
    }
    else { //cochÃ©
        message->blockSignals(false);
        QObject::connect(message, SIGNAL(textChanged(const QString)),
                         this, SLOT(playBipOptions()));
    }
}

void QComputer::playBipOptions() {
    QSound::play(":/beep.wav");
}

void QComputer::stateChangedOptionClavier(int i) {
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    if (i == 0) { //non cochÃ©
        clavierWidget->hide();
        setGeometry((width-300)/ 2, (height - 300) / 2,300,300);
    }
    else { //cochÃ©
        clavierWidget->show();
        setGeometry((width - 300)/ 2,( height - 400) / 2, 300, 400);
    }
}

void QComputer::buttonTriggered(int i) {
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
    QString s = commande->text();
    switch (i) {
    case 0:
        s += QString("7");
        break;
    case 1:
        s += QString("8");
        break;
    case 2:
        s += QString("9");
        break;
    case 3:
        s += QString("+");
        break;
    case 4:
        s += QString("4");
        break;
    case 5:
        s += QString("5");
        break;
    case 6:
        s += QString("6");
        break;
    case 7:
        s += QString("-");
        break;
    case 8:
        s += QString("1");
        break;
    case 9:
        s += QString("2");
        break;
    case 10:
        s += QString("3");
        break;
    case 11:
        s += QString("*");
        break;
    case 12:
        s += QString("0");
        break;
    case 13:
        s += QString(" ");
        break;
    case 14:
        QCoreApplication::postEvent(commande, event);
        break;
    case 15:
        s += QString("/");
        break;
    default:
        break;

    }
    commande->setText(s);
}

///////////SLOTS PROGRAMME////////////
void QComputer::addProgramme() {
    if(programmeLine->text() != "" && programmeIdLine->text() != "") {
        QString programmeLineText = programmeLine->text();
        QString programmeLineIdText = programmeIdLine->text();
        /*
        vueProgrammes->insertRow(vueProgrammes->rowCount());
        vueProgrammes->setRowCount(vueProgrammes->rowCount());
        int rowCount = vueProgrammes->rowCount();
        QTableWidgetItem *item = new QTableWidgetItem(programmeLineIdText);
        vueProgrammes->setItem(rowCount-1,0, item);
        vueProgrammes->setItem(rowCount-1,1, new QTableWidgetItem(programmeLineText));
        vueProgrammes->setColumnCount(2);*/

        QString id = QString("\"%1\"").arg(programmeLineIdText);
        try {
            controleur->commande(programmeLineText);
            controleur->commande(id);
            controleur->commande(QString("STO"));
        }
        catch (UTComputerException e) { message->setText(e.what());}
        catch (ComputerException e) { message->setText(e.getInfo());}

    }
    updateProgrammes();
}

void QComputer::deleteProgramme() {
    int iRows = vueProgrammes->rowCount();
    for(int i = iRows-1; i >= 0; i--) {
        if(vueProgrammes->item(i,0)->isSelected() || vueProgrammes->item(i,1)->isSelected()) {
            controleur->getListeProgrammes().erase(controleur->getListeProgrammes().begin()+i);
        }
    }
    updateProgrammes();
}

void QComputer::editerProgrammeFunc() {
    if(vueProgrammes->selectedItems().size()>0)  {
        QList<QTableWidgetItem *> list = vueProgrammes->selectedItems();
        int row = list.at(0)->row();
        editProgrammesTextEdit->setText(vueProgrammes->item(row,1)->text());

        editProgrammesWidget->setWindowModality(Qt::ApplicationModal);
        editProgrammesWidget->show();
    }
}

void QComputer::lancerEditionProgramme() {
    QString str = editProgrammesTextEdit->toPlainText();

    QList<QTableWidgetItem *> list = vueProgrammes->selectedItems();
    int row = list.at(0)->row();
    QString programmeLineIdText = vueProgrammes->item(row,0)->text();

    QString id = QString("\"%1\"").arg(programmeLineIdText);
    try {
        controleur->commande(str);
        controleur->commande(id);
        controleur->commande(QString("STO"));
    }
    catch (UTComputerException e) { message->setText(e.what());}
    catch (ComputerException e) { message->setText(e.getInfo());}

    editProgrammesWidget->close();

    updateProgrammes();
}

void QComputer::updateProgrammes() {
    int row = 0;
    commande->clear();
    vueProgrammes->clear();
    std::vector<Atome *> list = controleur->getListeProgrammes();

    for(std::vector<Atome *>::iterator it = list.begin(); it!=list.end(); ++it) {
        QString s = (*it)->toString();
        vueProgrammes->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem((*it)->getID());
        //item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        vueProgrammes->setItem(row, 0, item);
        vueProgrammes->setItem(row, 1, new QTableWidgetItem((*it)->getValue().toString()));
        row++;
    }
    vueProgrammes->setRowCount(list.size());
    programmesWidget->show();
}


///////////////////////////////////////


///////////SLOTS VARIABLE////////////
void QComputer::addVariable() {
    if(variableLine->text() != "" && variableIdLine->text() != "") {
        QString variableLineText = variableLine->text();
        QString variableLineIdText = variableIdLine->text();

        /*vueVariables->insertRow(vueVariables->rowCount());
        vueVariables->setRowCount(vueVariables->rowCount());
        int rowCount = vueVariables->rowCount();
        QTableWidgetItem *item = new QTableWidgetItem(variableLineIdText);
        vueVariables->setItem(rowCount-1,0, item);
        vueVariables->setItem(rowCount-1,1, new QTableWidgetItem(variableLineText));
        vueVariables->setColumnCount(2);*/

        QString id = QString("\"%1\"").arg(variableLineIdText);

        try{
            controleur->commande(variableLineText);
            controleur->commande(id);
            controleur->commande(QString("STO"));
        }
        catch (UTComputerException e) { message->setText(e.what());}
        catch (ComputerException e) { message->setText(e.getInfo());}

    }
    updateVariables();
}

void QComputer::deleteVariable() {
    int iRows = vueVariables->rowCount();
    for(int i = iRows-1; i >= 0; i--) {
        if(vueVariables->item(i,0)->isSelected() || vueVariables->item(i,1)->isSelected()) {
            controleur->getListeAtomes().erase(controleur->getListeAtomes().begin()+i);
        }
    }
    updateVariables();
}

void QComputer::editerVariableFunc() {
    if(vueVariables->selectedItems().size()>0)  {
        QList<QTableWidgetItem *> list = vueVariables->selectedItems();
        int row = list.at(0)->row();
        editVariablesTextEdit->setText(vueVariables->item(row,1)->text());

        editVariablesWidget->setWindowModality(Qt::ApplicationModal);
        editVariablesWidget->show();
    }
}

void QComputer::lancerEditionVariable() {
    QString str = editVariablesTextEdit->toPlainText();

    QList<QTableWidgetItem *> list = vueVariables->selectedItems();
    int row = list.at(0)->row();
    QString variableLineIdText = vueVariables->item(row,0)->text();

    QString id = QString("\"%1\"").arg(variableLineIdText);
    try {
        controleur->commande(str);
        controleur->commande(id);
        controleur->commande(QString("STO"));
    }
    catch (UTComputerException e) { message->setText(e.what());}
    catch (ComputerException e) { message->setText(e.getInfo());}


    editVariablesWidget->close();

    updateVariables();
}

void QComputer::updateVariables() {
    int row = 0;
    commande->clear();
    vueVariables->clear();
    std::vector<Atome *> list = controleur->getListeAtomes();

    for(std::vector<Atome *>::iterator it = list.begin(); it!=list.end(); ++it) {
        QString s = (*it)->toString();
        vueVariables->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem((*it)->getID());
        //item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        vueVariables->setItem(row, 0, item);
        vueVariables->setItem(row, 1, new QTableWidgetItem((*it)->getValue().toString()));
        row++;
    }
    vueVariables->setRowCount(list.size());
    variablesWidget->show();
}


///////////////////////////////////////

QComputer::QComputer(QWidget *parent) {
    setWindowTitle("UTComputer");
    //Création de la pile
    pile = new Pile();
    pile->setMessage("Bienvenue !");
    //Liste des opérateurs
    std::vector<Operateur*>* listeOperateurs = new std::vector<Operateur*>;
    listeOperateurs->push_back(new OperateurPlus);
    listeOperateurs->push_back(new OperateurMoins);
    listeOperateurs->push_back(new OperateurMult);
    listeOperateurs->push_back(new OperateurDiv);
    listeOperateurs->push_back(new OperateurDivEntiere);
    listeOperateurs->push_back(new OperateurNeg);
    listeOperateurs->push_back(new OperateurMod);
    listeOperateurs->push_back(new OperateurNum);
    listeOperateurs->push_back(new OperateurDen);
    listeOperateurs->push_back(new OperateurDup);
    listeOperateurs->push_back(new OperateurDrop);
    listeOperateurs->push_back(new OperateurSwap);
    listeOperateurs->push_back(new OperateurClear);
    listeOperateurs->push_back(new OperateurComplexe);
    listeOperateurs->push_back(new OperateurRe);
    listeOperateurs->push_back(new OperateurIm);
    listeOperateurs->push_back(new OperateurEgal);
    listeOperateurs->push_back(new OperateurNonEgal);
    listeOperateurs->push_back(new OperateurInfOuEgal);
    listeOperateurs->push_back(new OperateurSup);
    listeOperateurs->push_back(new OperateurSupOuEgal);
    listeOperateurs->push_back(new OperateurInf);
    listeOperateurs->push_back(new OperateurAnd);
    listeOperateurs->push_back(new OperateurOr);
    listeOperateurs->push_back(new OperateurNot);
    listeOperateurs->push_back(new OperateurEval);
    listeOperateurs->push_back(new OperateurUndo);
    listeOperateurs->push_back(new OperateurRedo);
    listeOperateurs->push_back(new OperateurSto);
    listeOperateurs->push_back(new OperateurIft);
    listeOperateurs->push_back(new OperateurForget);
    listeOperateurs->push_back(new OperateurLastOp);
    listeOperateurs->push_back(new OperateurEdit);


    listeOperateurs->push_back(new OperateurLastArgs);
    //Liste des littéraux
    std::vector<Regex*>* listeRegex = new std::vector<Regex*>;
    listeRegex->push_back(new Regex_entier);
    listeRegex->push_back(new Regex_reel);
    listeRegex->push_back(new Regex_rationnel);
    listeRegex->push_back(new Regex_programme);
    listeRegex->push_back(new Regex_expression);
    listeRegex->push_back(new Regex_atome);



    //contrôleur
    controleur = & Controleur::getInstance();
    controleur->init(pile,listeOperateurs,listeRegex);

    //// MESSAGE POUR L'UTILISATEUR ////
    message = new QLineEdit(this);
    message->setEnabled(false);
    message->setStyleSheet("background:darkblue;color:yellow");
    message->setText(pile->getMessage());
    ///////////////////////////////////////


    /// PILE ////
    vuePile = new QTableWidget(pile->getNbItemsToAffiche(), 1);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    vuePile->verticalHeader()->setStretchLastSection(true);
    vuePile->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vuePile->setStyleSheet("background:darkcyan");
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList numberList;
    /* for (unsigned int i = pile->getNbItemsToAffiche(); i>0; i--){
        QString str = QString::number(i);
        str+= ": ";
        numberList<<str;
        vuePile->setItem(i-1,0,new QTableWidgetItem(""));
    }
    vuePile->setVerticalHeaderLabels(numberList);*/
    /////////////////////////////////////////////////

    //// TRACE ENTREES UTILISATEUR /////////
    listeCommandes = new QLineEdit(this);
    listeCommandes->setEnabled(false);
    listeCommandes->setStyleSheet("QLineEdit {background-color: yellow;}");
    /////////////////////////////////////////////

    //// OPTIONS ////
    QHBoxLayout * fonctionnaliteLayout = new QHBoxLayout();
    options = new QPushButton("Options", this);
    voirProgrammes = new QPushButton("Voir mes programmes", this);
    voirVariables = new QPushButton("Voir mes variables", this);
    fonctionnaliteLayout->addWidget(options);
    fonctionnaliteLayout->addWidget(voirProgrammes);
    fonctionnaliteLayout->addWidget(voirVariables);
    //////////////////////////


    //// VOIR PROGRAMMES ///
    programmesWidget = new QWidget();
    programmesWidget->setWindowTitle("Voir Programmes");
    QPushButton* ajouterProgramme = new QPushButton("Ajouter un programme");
    QPushButton* editerProgramme = new QPushButton("Editer un programme");
    QPushButton* supprimerProgramme = new QPushButton("Supprimer un programme");
    vueProgrammes = new QTableWidget(0, 2);
    //vueProgrammes->horizontalHeader()->setStretchLastSection(true);
    //vueProgrammes->verticalHeader()->setStretchLastSection(true);
    vueProgrammes->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QHeaderView* header = vueProgrammes->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    vueProgrammes->setSelectionBehavior( QAbstractItemView::SelectItems );
    vueProgrammes->setSelectionMode( QAbstractItemView::SingleSelection );
    //vueProgrammes->setStyleSheet("background:yellow");
    vueProgrammes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout* optionsProgrammesLayout = new QVBoxLayout();
    QHBoxLayout* programmeEditLineLayout = new QHBoxLayout();
    programmeLine = new QLineEdit(this);
    programmeLine->setPlaceholderText(QString("Votre Programme ici"));
    programmeIdLine = new QLineEdit(this);
    programmeIdLine->setPlaceholderText(QString("Votre identifiant de Programme ici"));
    programmeEditLineLayout->addWidget(programmeIdLine);
    programmeEditLineLayout->addWidget(programmeLine);
    optionsProgrammesLayout->addWidget(vueProgrammes);
    optionsProgrammesLayout->addLayout(programmeEditLineLayout);
    optionsProgrammesLayout->addWidget(ajouterProgramme);
    optionsProgrammesLayout->addWidget(editerProgramme);
    optionsProgrammesLayout->addWidget(supprimerProgramme);
    programmesWidget->setLayout(optionsProgrammesLayout);

    editProgrammesWidget = new QWidget();
    editProgrammesWidget->setWindowTitle("Editer un programme");
    editProgrammesWidget->setFixedWidth(400);
    QVBoxLayout* programmeEditLineWidgetLayout = new QVBoxLayout();
    editProgrammesTextEdit = new QTextEdit(this);
    QPushButton * editProgrammesLineEditButton = new QPushButton("Lancer l'edition");
    programmeEditLineWidgetLayout->addWidget(editProgrammesTextEdit);
    programmeEditLineWidgetLayout->addWidget(editProgrammesLineEditButton);
    editProgrammesWidget->setLayout(programmeEditLineWidgetLayout);
    /////////////////////////////


    //// VOIR VARIABLES ///
    variablesWidget = new QWidget();
    variablesWidget->setWindowTitle("Voir variables");
    QPushButton* ajouterVariable = new QPushButton("Ajouter une variable");
    QPushButton* editerVariable = new QPushButton("Editer une variable");
    QPushButton* supprimerVariable = new QPushButton("Supprimer une variable");
    vueVariables = new QTableWidget(0, 2);
    vueVariables->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QHeaderView* header_2 = vueVariables->horizontalHeader();
    header_2->setSectionResizeMode(QHeaderView::Stretch);
    vueVariables->setSelectionBehavior( QAbstractItemView::SelectItems );
    vueVariables->setSelectionMode( QAbstractItemView::SingleSelection );
    vueVariables->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout* optionsVariablesLayout = new QVBoxLayout();
    QHBoxLayout* variableEditLineLayout = new QHBoxLayout();
    variableLine = new QLineEdit(this);
    variableLine->setPlaceholderText(QString("Votre variable ici"));
    variableIdLine = new QLineEdit(this);
    variableIdLine->setPlaceholderText(QString("Votre identifiant de variable ici"));
    variableEditLineLayout->addWidget(variableIdLine);
    variableEditLineLayout->addWidget(variableLine);
    optionsVariablesLayout->addWidget(vueVariables);
    optionsVariablesLayout->addLayout(variableEditLineLayout);
    optionsVariablesLayout->addWidget(ajouterVariable);
    optionsVariablesLayout->addWidget(editerVariable);
    optionsVariablesLayout->addWidget(supprimerVariable);
    variablesWidget->setLayout(optionsVariablesLayout);

    editVariablesWidget = new QWidget();
    editVariablesWidget->setWindowTitle("Editer une variable");
    editVariablesWidget->setFixedWidth(400);
    QVBoxLayout* variableEditLineWidgetLayout = new QVBoxLayout();
    editVariablesTextEdit = new QTextEdit(this);
    QPushButton * editVariablesLineEditButton = new QPushButton("Lancer l'edition");
    variableEditLineWidgetLayout->addWidget(editVariablesTextEdit);
    variableEditLineWidgetLayout->addWidget(editVariablesLineEditButton);
    editVariablesWidget->setLayout(variableEditLineWidgetLayout);
    /////////////////////////////


    //// ENTREE UTILISATEUR ////
    commande = new QLineEdit(this);
    commande->setFocus();
    /////////////////////////////

    //// OPTIONS WIDGET ////
    optionsWidget = new QWidget();
    optionsWidget->setWindowTitle("Options");
    QCheckBox* optionClavier = new QCheckBox("clavier cliquable");
    QCheckBox* optionErreur = new QCheckBox("bip lors d'un message d'erreur");
    QSpinBox* optionNombrePile = new QSpinBox();
    optionNombrePile->setMinimum(0);
    optionNombrePile->setMaximum(6);
    optionNombrePile->setSingleStep(1);
    optionNombrePile->setValue(4);
    QPushButton* optionFermetureWidget = new QPushButton("Fermeture des options");
    QHBoxLayout * optionsLayout = new QHBoxLayout();
    optionsLayout->addWidget(optionClavier);
    optionsLayout->addWidget(optionErreur);
    optionsLayout->addWidget(optionNombrePile);
    optionsLayout->addWidget(optionFermetureWidget);
    optionsWidget->setLayout(optionsLayout);
    ////////////////////////

    //////CLAVIER CLIQUABLE//////
    clavierWidget = new QWidget();
    QGridLayout * clavierLayout = new QGridLayout();
    QPushButton * boutons[16];
    boutons[12] = new QPushButton("0");
    boutons[8] =  new QPushButton("1");
    boutons[9] =  new QPushButton("2");
    boutons[10] =  new QPushButton("3");
    boutons[4] = new QPushButton("4");
    boutons[5] = new QPushButton("5");
    boutons[6] = new QPushButton("6");
    boutons[0] = new QPushButton("7");
    boutons[1] = new QPushButton("8");
    boutons[2] = new QPushButton("9");
    boutons[3] = new QPushButton("+");
    boutons[7] = new QPushButton("-");
    boutons[11] = new QPushButton("*");
    boutons[15] = new QPushButton("/");
    boutons[14] = new QPushButton("Entree");
    boutons[13] = new QPushButton("Espace");
    int compteur = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            clavierLayout->addWidget(boutons[compteur], i, j);
            compteur++;
        }
    }
    clavierLayout->addWidget(boutons[12], 3, 0);
    clavierLayout->addWidget(boutons[13], 3, 1);
    clavierLayout->addWidget(boutons[14], 3, 2);
    clavierLayout->addWidget(boutons[15], 3, 3);

    clavierWidget->setLayout(clavierLayout);
    clavierWidget->hide();
    ////////////////////////////


    //// Construction de la fenetre ////
    couche = new QVBoxLayout(this);
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(listeCommandes);
    couche->addWidget(commande);
    couche->addWidget(clavierWidget);
    // couche->addWidget(options);
    couche->addLayout(fonctionnaliteLayout);//On met le "options" tout en bas
    setLayout(couche);
    ///////////////////////////////////

    /////SIGNAUX/////
    QSignalMapper *signalMapper = new QSignalMapper(this);
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttonTriggered(int)));

    for (int i = 0; i < 16; ++i) {
        signalMapper->setMapping(boutons[i], i);
        connect(boutons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }

    QObject::connect(optionClavier, SIGNAL(stateChanged(int)),this, SLOT(stateChangedOptionClavier(int)));
    QObject::connect(optionErreur, SIGNAL(stateChanged(int)),this, SLOT(stateChangedBipOptions(int)));
    QObject::connect(optionFermetureWidget, SIGNAL(pressed()),optionsWidget, SLOT(close()));
    QObject::connect(options, SIGNAL(pressed()),optionsWidget, SLOT(show()));
    QObject::connect(pile, SIGNAL(modificationEtat()),this, SLOT(refresh()));
    QObject::connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));

    ////////////////// CONNECT PROGRAMMES //////////////////////
    QObject::connect(voirProgrammes, SIGNAL(pressed()),this, SLOT(updateProgrammes()));
    QObject::connect(ajouterProgramme, SIGNAL(pressed()),this, SLOT(addProgramme()));
    QObject::connect(supprimerProgramme, SIGNAL(pressed()),this, SLOT(deleteProgramme()));
    QObject::connect(editerProgramme, SIGNAL(pressed()),this, SLOT(editerProgrammeFunc()));
    QObject::connect(editProgrammesLineEditButton, SIGNAL(pressed()),this, SLOT(lancerEditionProgramme()));
    ////////////////////////////////////////////////////////////

    ////////////////// CONNECT VARIABLES //////////////////////
    QObject::connect(voirVariables, SIGNAL(pressed()),this, SLOT(updateVariables()));
    QObject::connect(ajouterVariable, SIGNAL(pressed()),this, SLOT(addVariable()));
    QObject::connect(supprimerVariable, SIGNAL(pressed()),this, SLOT(deleteVariable()));
    QObject::connect(editerVariable, SIGNAL(pressed()),this, SLOT(editerVariableFunc()));
    QObject::connect(editVariablesLineEditButton, SIGNAL(pressed()),this, SLOT(lancerEditionVariable()));
    ////////////////////////////////////////////////////////////


    /// DIMENSIONNEMENT DE LA FENETRE ////
    //QRect rec = QApplication::desktop()->screenGeometry();
    //int height = rec.height();
    //int width = rec.width();
    //setGeometry((width - 300) / 2, (height - 300) / 2, 300, 275);
    setFixedWidth(425);
    ///////////////////////////////////

    show();
}
