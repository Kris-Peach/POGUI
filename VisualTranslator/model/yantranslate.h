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

class YanTranslate: public QObject
{
    Q_OBJECT
private:
    QString Text;
    QString YanKey;
    QString Lang;
    QUrl YanUrl;
    QByteArray GET(QUrl);
    QString parsJson(QByteArray);
    void parsError(int);
public:
    YanTranslate();
    Q_INVOKABLE void setText(QString);
    Q_INVOKABLE QString getText();
    Q_INVOKABLE void setLang(QString);
    Q_INVOKABLE QString getLang();
    Q_INVOKABLE QString yantranslate();

};

#endif // YANTRANSLATE_H
