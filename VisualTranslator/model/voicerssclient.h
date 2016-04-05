#ifndef VOICERSSCLIENT_H
#define VOICERSSCLIENT_H
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QUrlQuery>
#include <QDebug>
#include <QTimer>
#include <QtMultimedia>

class VoiceRSSClient:public QObject
{
    QByteArray Get(QUrl url);
    QString key="363b0feabbc84af9a83fd6d406cb3054";
public:
    VoiceRSSClient(QNetworkAccessManager* manager);
    QNetworkAccessManager* networkManager;
    QBuffer* buffer;
    QMediaPlayer* player;
    void speak(QString text,QString lang);

};

#endif // VOICERSSCLIENT_H
