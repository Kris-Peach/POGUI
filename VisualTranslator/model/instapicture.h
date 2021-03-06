#ifndef INSTAPICTURE_H
#define INSTAPICTURE_H


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDebug>
#include <QTimer>
#include <QString>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonValue>
#include <QArrayData>
#include <QObject>
#include "imager.h"


class InstaPicture : public QObject, public Imager
{

 Q_OBJECT

public:


    InstaPicture(QNetworkAccessManager* man);
    QString getPicture(QString str);


private:
        QNetworkAccessManager* manager;
QByteArray GET(QUrl);

QString hesh;


};

#endif
