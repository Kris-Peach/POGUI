#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QtQml>
#include <QIcon>

#include "controller/appmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<AppManager>("Qt.controller.appmanager",1,0,"AppManager",&AppManager::qmlInstance);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    //QObject* root=engine.rootObjects()[0];

   // AppManager* manager=new AppManager();
   // engine.rootContext()->setContextProperty("manager",manager);
    //engineC.rootContext()->setContextProperty("manager",manager);
    //engine.rootContext()->setContextProperty("instaPicture",instagram);
    return app.exec();
}

