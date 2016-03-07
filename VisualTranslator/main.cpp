#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "controller/appmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    AppManager* manager=new AppManager();
    engine.rootContext()->setContextProperty("manager",manager);
    //engine.rootContext()->setContextProperty("instaPicture",instagram);
    return app.exec();
}
