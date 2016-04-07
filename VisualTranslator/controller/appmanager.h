#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include "model/instapicture.h"
#include "model/yantranslate.h"
#include "model/translator.h"
#include "model/imager.h"
#include "model/multilecttranslate.h"
#include "model/gettyimag.h"
#include "model/voicerssclient.h"
#include "model/interf.h"


class AppManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AppManager)
private:
    InstaPicture* InstagramManager;
    YanTranslate* YandexTranslator;
    MultilectTranslate* MultilectTranslator;
    GettyImag* GettyImageManager;
    VoiceRSSClient* voiceRSSClient;
    Imager* imager;
    Translator* translator;
    QNetworkAccessManager* NetworkManager;
    QJsonObject Setting;
    Interf* Speech;
    QString RecordText;



    enum SaveFormat {
            Json, Binary
        };

    QString read(const QJsonObject &json,QString name);
   // void write(QJsonObject &json, QString name,QString value) const;
   // bool saveSetting(AppManager::SaveFormat saveFormat) const;
   // QJsonObject loadSetting(AppManager::SaveFormat saveFormat);
    // ~AppManager();
public:
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
        {
            Q_UNUSED(engine);
            Q_UNUSED(scriptEngine);

            return new AppManager;
        }
    explicit AppManager(QObject *parent = 0);

    Q_INVOKABLE QString translate(int numTranslator, int lang_from, int lang_to, QString text);
    Q_INVOKABLE QVariantList getDataForCards(int numSource,QString text);
    Q_INVOKABLE QString updatePicture(QString word);
    Q_INVOKABLE void speak(QString text,QString lang);
    Q_INVOKABLE void startSpeak();
    Q_INVOKABLE void stopSpeak();
    Q_INVOKABLE QString getRecordText();
    //Q_INVOKABLE void putSetting(QString name, QString value);
   // Q_INVOKABLE QString getSetting(QString name);

signals:
void textIsWritten();
public slots:
};

#endif // APPMANAGER_H
