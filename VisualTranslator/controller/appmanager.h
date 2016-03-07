#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QString>
#include <QQmlEngine>

#include "model/instapicture.h"
#include "model/yantranslate.h"
#include "model/translator.h"
#include "model/imager.h"

class AppManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AppManager)
private:
    InstaPicture* InstagramManager;
    YanTranslate* YandexTranslator;
    Imager* imager;
    Translator* translator;
    QNetworkAccessManager* NetworkManager;
public:
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
        {
            Q_UNUSED(engine);
            Q_UNUSED(scriptEngine);

            return new AppManager;
        }
    explicit AppManager(QObject *parent = 0);
    Q_INVOKABLE QString translate(int numTranslator, QString langs, QString text);
    Q_INVOKABLE QVariantList getDataForCards(int numSource,QString text);
    Q_INVOKABLE QString updatePicture(QString word);
signals:

public slots:
};

#endif // APPMANAGER_H
