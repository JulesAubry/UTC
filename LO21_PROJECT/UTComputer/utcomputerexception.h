#ifndef UTCOMPUTEREXCEPTION_H
#define UTCOMPUTEREXCEPTION_H

#include <exception>
#include <iostream>
#include <QString>


/*class UTComputerException {
    QString infos;
public:
    UTComputerException(const QString _infos) {
        infos = _infos;
    }

    virtual const QString what() const  {
        return infos;
    }
};*/

class UTComputerException {
    QString info;
public:
    UTComputerException(QString str):info(str){}
    QString what() const { return info; }
};

#endif // UTCOMPUTEREXCEPTION_H
