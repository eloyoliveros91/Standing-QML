#include "team.h"

Team::Team(QString name, int problemas)
{
    nombre = name;
    penalidad.resize(problemas);
    intentos.resize(problemas);
    aceptado.resize(problemas);
    penalidadTotal=0;
    totalAceptado=0;
    posicionActual=0;
}

Team::Team(const Team & equipo){
    nombre = equipo.nombre;
    penalidad = equipo.penalidad;
    intentos = equipo.intentos;
    aceptado = equipo.aceptado;

    penalidadTotal = equipo.penalidadTotal;
    totalAceptado = equipo.totalAceptado;
    posicionActual = equipo.posicionActual;

}

void Team::setIntento(int problema, bool acc, int tiempo){
    if (acc){
        aceptado[problema]=true;
        penalidad[problema] = intentos[problema]*20 + tiempo;
        penalidadTotal+=penalidad[problema];
        totalAceptado++;
    }
    intentos[problema]++;
}



bool Team::operator <(const Team equipo) const{
    if (totalAceptado > equipo.totalAceptado)
        return true;
    if (totalAceptado < equipo.totalAceptado)
        return false;
    if (penalidadTotal < equipo.penalidadTotal)
        return true;
    if (penalidadTotal > equipo.penalidadTotal)
        return false;
    return nombre<equipo.nombre;
}
