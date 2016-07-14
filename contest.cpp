#include "contest.h"
#include <QFile>
//#include <QtDebug>
#include <QFileDialog>
#include <QString>
#include <QLineEdit>
#include <QInputDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
Contest::Contest(QObject *parent):QObject(parent)
{
    envioActual=0;
    start = new QDateTime();
    end = new QDateTime();
}


bool Contest::cargarCompetencia(bool online){

    if (!online){

        QString descripcionName = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                               tr("Seleccione Fichero de Descripcion"), tr("./"), tr("JSON (*.json)"));

        if( descripcionName.isEmpty() )
            return false;
        QFile *descripcion= new QFile(descripcionName);

        cargarDescripcion(descripcion);

        QString problemasName = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                             "Seleccione Fichero con Lista de Problemas", "./", "JSON (*.json)");
        if( problemasName.isEmpty() )
            return false;

        QFile *problemas= new QFile(problemasName);

        cargarProblemas(problemas);

        QString enviosName = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                          "Seleccione Fichero de Envios", "./", "JSON (*.json)");
        if( enviosName.isEmpty() )
            return false;
        QFile *envios = new QFile(enviosName);

        cargarEnvios(envios);
        return true;

    }else{

        bool ok;
        int contestID=0;
        QString text = QInputDialog::getText(Q_NULLPTR, "Seleccionar ID de competencia",
                                             "ID:", QLineEdit::Normal,
                                             "1000", &ok);
        if (ok && !text.isEmpty())
            contestID = text.toInt();


        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        request.setUrl(QUrl("http://coj.uci.cu/contest/" + text));

        QNetworkReply *reply = manager->get(request);
        connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
                              this, SLOT(slotProgress(qint64,qint64)));

        progress = new QProgressDialog("Descargando ficheros competencia...", "Cancelar", 0, 100);
    }


    return true;

}

void Contest::slotProgress(qint64 bytesReceived, qint64 bytesTotal){

    if (bytesTotal <= 0)
        return;

    progress->setMaximum(bytesTotal);
    progress->setValue(bytesReceived);
    return;
}


void Contest::cargarDescripcion(QFile *file){
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }


    QByteArray fichero = file->readAll();

    QJsonParseError *error;
    QJsonDocument loadDoc(QJsonDocument::fromJson(fichero, error));

    while(error->error){
        fichero.replace(fichero.at(error->offset),' ');
        loadDoc = loadDoc.fromJson(fichero, error);
    }


//    if (!loadDoc.isNull()){
//        qWarning("El fichero fue bien parseado");
//    }
//    if (loadDoc.isArray())
//        qWarning("El fichero contiene un array de objetos");

    QJsonArray *array = new QJsonArray(loadDoc.array());

    QJsonObject obj = array->at(0).toObject();

    name = obj["name"].toString();

    start = new QDateTime (QDateTime::fromString(obj["start"].toString(), Qt::ISODate));
    end = new QDateTime(QDateTime::fromString(obj["end"].toString(), Qt::ISODate));

    int secs = start->secsTo(*end);
    durationMins = secs/60;

}

void Contest::cargarProblemas(QFile *file){
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray fichero = file->readAll();
    QJsonParseError *error;
    QJsonDocument loadDoc(QJsonDocument::fromJson(fichero, error));

    while(error->error){
        fichero.replace(fichero.at(error->offset),' ');
        loadDoc = loadDoc.fromJson(fichero, error);
    }

//    if (!loadDoc.isNull()){
//        qWarning("El fichero fue bien parseado");
//    }
//    if (loadDoc.isArray())
//        qWarning("El fichero contiene un array de objetos");

    QJsonArray *problemas = new QJsonArray(loadDoc.array());

    foreach (QJsonValue problem, *problemas) {
        QJsonObject obj = problem.toObject();
        mapaProblemas[obj["pid"].toInt()] = obj["letter"].toString().at(0).toLatin1()-'A';
    }

}

void Contest::cargarEnvios(QFile *file){
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray fichero = file->readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(fichero));

    QJsonArray *submissions = new QJsonArray(loadDoc.array());

    QSet<QString> teams;

    foreach (QJsonValue value, *submissions) {
        QJsonObject obj = value.toObject();
        QDateTime tiempo = QDateTime::fromString(obj["date"].toString(), Qt::ISODate);
        int segundo = start->secsTo(tiempo);
        envios.prepend(envio(obj["user"].toString(), mapaProblemas[obj["prob"].toInt()],
                             obj["judgment"].toString()=="Accepted", segundo));
        teams.insert(obj["user"].toString());
    }

    foreach (QString team, teams) {
        standing.push_back(Team(team,getCantProblemas()));
    }
    qSort(standing.begin(), standing.end());
    for (int i=0; i<standing.size(); i++){
        standing[i].setPosicion(i);
        equipos.push_back(standing[i].getNombre());
    }
}

bool Contest::proximoEnvio(){
    int posAnt; int posNew; bool acc;
    int tiempo = 0;
    if (envioActual < envios.size()){
        acc = envios[envioActual].aceptado;
        QString nombre = envios[envioActual].equipo;
        for (int i=0; i<standing.size(); i++) {
            if (standing[i].getNombre()==nombre){
                standing[i].setIntento(envios[envioActual].problema,
                                envios[envioActual].aceptado,
                                envios[envioActual].segundo/60);
                posAnt = standing[i].getPosicion();
                tiempo = standing[i].getPenalidad();
                break;
            }
        }

        qSort(standing.begin(), standing.end());
        bool prim=true;
        posNew = posAnt;

        for (int i=0; i<standing.size(); i++){
            if (standing[i].getPosicion() != i && prim){
                posNew = i;
                prim = false;
                tiempo = standing[i].getPenalidad();
            }
            standing[i].setPosicion(i);
        }
        QMetaObject::invokeMethod(ui,"envio", Q_ARG(QVariant, posAnt),
                                  Q_ARG(QVariant, posNew),
                                  Q_ARG(QVariant, envios[envioActual].problema),
                                  Q_ARG(QVariant, acc),
                                  Q_ARG(QVariant, tiempo));
        envioActual++;
        return true;
    }
    return false;

}
QString Contest::getEquipo(){
    return envios[envioActual].equipo;
}
int Contest::getSegundo(){
    return envios[envioActual].segundo;
}

int Contest::getProblema(){
    return envios[envioActual].problema;
}

bool Contest::getAceptado(){
    return envios[envioActual].aceptado;
}

Contest::~Contest()
{
    //delete start;
    //delete end;
}

