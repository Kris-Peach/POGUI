#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QString>
#include "model/instapicture.h"
#include "model/yantranslate.h"
#include "model/translator.h"

class AppManager : public QObject
{
    Q_OBJECT
private:
    InstaPicture* InstagramManager;
    YanTranslate* YandexTranslator;
    QNetworkAccessManager* NetworkManager;
public:
    explicit AppManager(QObject *parent = 0);
    Q_INVOKABLE QString translate(int numTranslator, QString langs, QString text);
signals:

public slots:
};

#endif // APPMANAGER_H
