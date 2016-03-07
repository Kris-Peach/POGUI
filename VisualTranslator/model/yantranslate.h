#ifndef YANTRANSLATE_H
#define YANTRANSLATE_H

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

class YanTranslate: public QObject, public Translator
{
    Q_OBJECT
private:
    QString YanKey;
    QUrl YanUrl;
    QNetworkAccessManager* manager;
    QByteArray GET(QUrl);
    QString parsJson(QByteArray);
    void parsError(int);
public:
    YanTranslate(QNetworkAccessManager* man);
    /*Q_INVOKABLE void setText(QString);
    Q_INVOKABLE QString getText();
    Q_INVOKABLE void setLang(QString);
    Q_INVOKABLE QString getLang();*/
    //Q_INVOKABLE QString yantranslate();
    QString translate();

};

#endif // YANTRANSLATE_H
