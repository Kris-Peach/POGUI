#ifndef INTERF_H
#define INTERF_H

//#include "widget.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMediaRecorder>
#include <QUrl>
#include <QAudioFormat>
#include <QAudioInput>
#include <QBuffer>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QDataStream>



class Interf : public QObject
{
    Q_OBJECT

public:
    Interf();
    const QByteArray &data() const;
    enum State {
         Ready,
         SpeechReq,
         MorphologyRequest
     };
     State m_state;
     QAudioFormat m_format;
     QAudioInput *m_audioInput;
     QBuffer m_buffer;
     QNetworkAccessManager *m_manager;
     QNetworkReply *m_reply;

private:

    void setReply(QNetworkReply *reply);
    QString parseSpeechRecognitionResult(const QString &response, QString *result);
    void deleteReply();

public slots:
      QString recognizeSpeech();

private slots:
    QString onReplyFinished();


private:

};

#endif








