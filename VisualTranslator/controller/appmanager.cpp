#include "appmanager.h"

AppManager::AppManager(QObject *parent) : QObject(parent)
{
    NetworkManager=new QNetworkAccessManager(this);
    InstagramManager=new InstaPicture(NetworkManager);
    YandexTranslator=new YanTranslate(NetworkManager);
    MultilectTranslator=new MultilectTranslate(NetworkManager);
    GettyImageManager=new GettyImag(NetworkManager);
    voiceRSSClient=new VoiceRSSClient(NetworkManager);

    Speech = new Interf;
    Speech->m_manager= new QNetworkAccessManager(this);
    Speech->m_buffer.setData(QByteArray());
    Speech->m_buffer.open(QIODevice::ReadWrite);
    //Setting=loadSetting(AppManager::Json);
}
AppManager::~AppManager()
{
    delete InstagramManager;
    delete YandexTranslator;
    delete MultilectTranslator;
    delete GettyImageManager;
    delete voiceRSSClient;
    delete Speech;
    delete NetworkManager;

}

QString  AppManager::translate(int numTranslator, int lang_from, int lang_to, QString text)
{
    QString langs;
    switch ( numTranslator )
    {
        case 0 : translator=YandexTranslator;
                switch(lang_from)
                {
                case 1: langs="ru-";
                            break;
                case 0: langs="en-";
                            break;
                }
                switch(lang_to)
                {
                case 1: langs+="ru";
                            break;
                case 0: langs+="en";
                            break;
                }

                 break;
        case 1:translator=MultilectTranslator;
                switch(lang_from)
                {
                case 1: langs="rus-";
                            break;
                case 0: langs="eng-";
                            break;
                }
                switch(lang_to)
                {
                case 1: langs+="rus";
                            break;
                case 0: langs+="eng";
                            break;
                }

               break;
        default : translator=YandexTranslator;
                 break;
    }
    text.toLower();
    //text.remove(QRegExp("\\b(the|a|in|from|and|or|to|about)\\s\\b"));
    //text.remove(QRegExp("\\b(и|а|у|с|к|в)\\b"));
    //qDebug()<<text;
    translator->setLang(langs);
    translator->setText(text);
    QString str=translator->translate();
    return str;

}
QVariantList AppManager::getDataForCards(int numSource,QString text)
{
    switch (numSource) {
    case 0:imager=InstagramManager;
        break;
    case 1:imager=GettyImageManager;
        break;

    default: imager=InstagramManager;
        break;
    }
    qDebug()<<numSource;
    text.remove(QRegExp("[\.\,\!\?\^\\\\\/\&\$\*\\[\\]\\{\\}\+\-;=@%:><\(\)\~\`\"\'%№#\|]"));

    //text.remove(QRegExp("\b(the\s|a\s)\b"));
    //text.remove(QRegExp("\\b(the|a|in|from|and|or|to|about)\\b"));
   // text.remove(QRegExp("\\b(и|а|у|с|к|в|из)\\b"));
    QVariantList list;
    QStringList words=text.split(" ");
    words.removeAll("");
    QStringList translations;
    QStringList urlImages;
    for(int i=0;i<words.length();i++)
    {
        QString picture=words[i];
        YandexTranslator->setText(words[i]);
        //YandexTranslator->setLang("ru-en");
        translations.append(YandexTranslator->translate());
        if(YandexTranslator->getLang().split("-")[0]=="ru") picture=translations.at(i);
        picture.remove(QRegExp("\\b(the|a)\\b"));
        picture.remove(QRegExp("\\s"));

        QString str=imager->getPicture(picture);
        urlImages.append(str);
        qDebug()<<words[i]<<translations[i]<<urlImages.at(i);
    }
    list.append(words);
    list.append(translations);
    list.append(urlImages);
    return list;

}
QString AppManager::updatePicture(QString word)
{
    //qDebug()<<word;
    //MultilectTranslator->setLang("rus-eng");
    //MultilectTranslator->setText(word);
    //QString tr=MultilectTranslator->translate();
    //qDebug()<<tr;
    YandexTranslator->setLang("ru-en");
    YandexTranslator->setText(word);
    QString url=imager->getPicture(YandexTranslator->translate());
    //qDebug()<<url;
    return url;
}
void AppManager::speak(QString text,QString lang)
{
    QString l="en-GB";
    if(lang=="Русский") l="ru-ru";
    voiceRSSClient->speak(text,l);
}
void AppManager::startSpeak()
{
    //чистим буф
    Speech->m_buffer.buffer().clear();

    //устанавливаем формат аудио
    Speech->m_format.setSampleRate(16000);
    Speech->m_format.setChannelCount(1);
    Speech-> m_format.setSampleSize(16);
    Speech->m_format.setSampleType(QAudioFormat::SignedInt);
    Speech-> m_format.setByteOrder(QAudioFormat::LittleEndian);
    Speech->m_format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(Speech->m_format)) {
        Speech->m_format = info.nearestFormat(Speech->m_format);
    }


    Speech->m_audioInput = new QAudioInput(Speech->m_format, this);
    //начинаем запись
    Speech->m_audioInput->start(&Speech->m_buffer);

}

void AppManager::stopSpeak()
{
    Speech->m_audioInput->stop();
    delete  Speech->m_audioInput;
    RecordText=Speech->recognizeSpeech();
    if(RecordText=="400")
        RecordText="Sorry it is not possible to recognize.";
    emit textIsWritten();
}
QString AppManager::getRecordText()
{
    return RecordText;
}

/*QJsonObject AppManager::loadSetting(AppManager::SaveFormat saveFormat)
{
    QFile loadFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData)
        : QJsonDocument::fromBinaryData(saveData));

    return loadDoc.object();
}
bool AppManager::saveSetting(AppManager::SaveFormat saveFormat) const
{
    QFile saveFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    //QJsonObject gameObject;
   // write(gameObject);
    QJsonDocument saveDoc(Setting);
    saveFile.write(saveFormat == Json
        ? saveDoc.toJson()
        : saveDoc.toBinaryData());

    return true;
}
void AppManager::write(QJsonObject &json, QString name,QString value) const
{
       // QJsonObject playerObject;
       // mPlayer.write(playerObject);
        json[name] = value;

       QJsonArray levelArray;
        foreach (const Level level, mLevels) {
            QJsonObject levelObject;
            level.write(levelObject);
            levelArray.append(levelObject);
        }
        json["levels"] = levelArray;
}
QString AppManager::read(const QJsonObject &json,QString name)
{
    return json[name];
   // mPlayer.read(json["player"].toObject());

   /* mLevels.clear();
    QJsonArray levelArray = json["levels"].toArray();
    for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
        QJsonObject levelObject = levelArray[levelIndex].toObject();
        Level level;
        level.read(levelObject);
        mLevels.append(level);
    }
}
void AppManager::putSetting(QString name, QString value)
{
    write(Setting,name,value);
}

QString AppManager::getSetting(QString name)
{
    read(Setting,name);
}

void AppManager::~AppManager()
{
    saveSetting(AppManager::Json);
}
*/
