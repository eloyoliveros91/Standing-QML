#ifndef TEAM_H
#define TEAM_H


#include <QString>
#include <QStringList>
#include <QPair>
#include <QVector>

class Team
{
    QVector<int> penalidad;
    QVector<bool> aceptado;
    QVector<int> intentos;
    QString nombre;
    int penalidadTotal;
    int totalAceptado;
    int posicionActual;
public:
    Team(QString, int);
    Team(const Team&);
    void setIntento(int, bool, int);
    void setPosicion(int pos){posicionActual = pos;}

    int getAceptados(){return totalAceptado;}
    int getPenalidad(){return penalidadTotal;}
    int getPosicion(){return posicionActual;}
    QString getNombre(){return nombre;}

    bool operator<(const Team) const;
};

#endif // TEAM_H
