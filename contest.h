#ifndef CONTEST_H
#define CONTEST_H

#include <QMap>
#include <QFile>
#include <QDateTime>
#include <QJsonDocument>
#include <QList>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QProgressDialog>
#include <QObject>
#include <QNetworkReply>
#include <QJsonParseError>
#include "team.h"
struct envio{
    QString equipo;
    int problema;
    bool aceptado;
    int segundo;
    envio(QString a, int b, bool c, int d):equipo(a),problema(b),aceptado(c), segundo(d){}
};

typedef QPair<int, int> QAccPen;
class Contest: public QObject
{
    Q_OBJECT
    QMap<int, int> mapaProblemas;
    QList<envio> envios;
    QStringList equipos;
    QList<Team> standing;
    int durationMins;
    QString name;
    QDateTime *start;
    QDateTime *end;
    int envioActual;
    QProgressDialog *progress;

    QObject* ui;

public:
    explicit Contest(QObject * parent = 0);
    void cargarProblemas(QFile *);
    void cargarDescripcion(QFile *);
    void cargarEnvios(QFile *);
    bool cargarCompetencia(bool = false);

    bool endContest(){return envioActual==envios.size();}

    //funciones getters para el envio actual
    QString getEquipo();
    int getSegundo();
    int getProblema();
    bool getAceptado();
    //funciones getters para el envio actual

    int getDuracionMins(){return durationMins;}
    QString getName(){return name;}
    int getCantProblemas(){return mapaProblemas.size();}
    QStringList getEquipos(){return equipos;}

    void setObject(QObject *object){ui = object;}
    ~Contest();
public slots:
    void slotProgress(qint64, qint64);
    bool proximoEnvio();
};

#endif // CONTEST_H
