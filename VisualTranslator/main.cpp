#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "model/yantranslate.h"
#include <QQmlContext>
#include "model/instapicture.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    YanTranslate* yandex=new YanTranslate();
    InstaPicture* instagram=new InstaPicture();
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("yandexTranslater",yandex);
    engine.rootContext()->setContextProperty("instaPicture",instagram);
    return app.exec();
}
