#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include "contest.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Contest comp;
    QFile *descrFile= new QFile("./descr.json");
    comp.cargarDescripcion(descrFile);
    QFile *problemas= new QFile("./prob.json");
    comp.cargarProblemas(problemas);
    QFile *enviosFile= new QFile("./envios.json");
    comp.cargarEnvios(enviosFile);


    int totalProb = comp.getCantProblemas();

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    context->setContextProperty("cantProblemas", totalProb);


    QObject *object = engine.rootObjects().at(0);
    QStringList equipos = comp.getEquipos();

    foreach (QString equipo, equipos) {
        QMetaObject::invokeMethod(object,"insertarEquipo", Q_ARG(QVariant, equipo));
    }

    comp.setObject(object);
    QMetaObject::invokeMethod(object,"crearProblemas", Q_ARG(QVariant, totalProb));

    QObject::connect(object, SIGNAL(envioSignal()), &comp, SLOT(proximoEnvio()));

    return app.exec();
}
