#ifndef MULTILECTTRANSLATE_H
#define MULTILECTTRANSLATE_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>
#include <QEventLoop>
#include <QUrlQuery>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iterator>
#include <QMessageBox>
#include "model/translator.h"

class MultilectTranslate:public QObject, public Translator
{
     Q_OBJECT
private:
    QString MultilectId;
    QString MultilectSig;
    QString MultilectMethod;
    QString lang_from;
    QString lang_to;
    QUrl MuiltilectUrl;
    QNetworkAccessManager* manager;
    QByteArray GET(QUrl);
    QString parsJson(QByteArray);

public:
    MultilectTranslate(QNetworkAccessManager* man);
    QString multranslate();
};

#endif // MULTILECTTRANSLATE_H
