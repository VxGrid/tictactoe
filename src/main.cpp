
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "logic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/tictac/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
    engine.load(url);
    Logic logic;
    logic.setEngine(&engine);
    logic.setupGUI();
    return app.exec();
}
