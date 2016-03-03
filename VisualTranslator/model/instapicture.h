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


class InstaPicture : public QObject
{

 Q_OBJECT

public:


    InstaPicture();
    Q_INVOKABLE QString getPicture(QString str);


private:

QByteArray GET(QUrl);

QString hesh;


};

#endif
