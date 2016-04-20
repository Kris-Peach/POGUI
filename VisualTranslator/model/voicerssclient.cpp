#include "voicerssclient.h"

VoiceRSSClient::VoiceRSSClient(QNetworkAccessManager* manager)
{
    networkManager=manager;
    buffer=new QBuffer(this);
    player=new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    buffer = new QBuffer(this);
    buffer->open(QIODevice::ReadWrite);
}
VoiceRSSClient::~VoiceRSSClient()
{
    delete buffer;
    delete player;
}

void VoiceRSSClient::speak(QString text,QString lang){
    QUrl url("http://api.voicerss.org/?key="+key+"&src="+text+"&hl="+lang);
    QByteArray answer=Get(url);
    buffer->buffer().clear();
    buffer->seek(0);
    buffer->write(answer);
    buffer->seek(0);
    player->setMedia(QMediaContent(),buffer);
    player->play();
}

QByteArray VoiceRSSClient::Get(QUrl url){
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = networkManager->get(QNetworkRequest(request));
    QEventLoop wait;
    connect(networkManager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();
    QByteArray answer = (QByteArray)reply->readAll();
    reply->deleteLater();
    return answer;
}
