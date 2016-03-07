#include "appmanager.h"

AppManager::AppManager(QObject *parent) : QObject(parent)
{
    NetworkManager=new QNetworkAccessManager(this);
    InstagramManager=new InstaPicture(NetworkManager);
    YandexTranslator=new YanTranslate(NetworkManager);
}
QString  AppManager::translate(int numTranslator, QString langs, QString text)
{
    switch ( numTranslator )
    {
        case 0 : translator=YandexTranslator;
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
    default: imager=InstagramManager;
        break;
    }
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
        YandexTranslator->setText(words[i]);
        translations.append(YandexTranslator->translate());
        urlImages.append(imager->getPicture(words[i]));
        qDebug()<<words[i]<<translations[i];
    }
    list.append(words);
    list.append(translations);
    list.append(urlImages);
    return list;

}
QString AppManager::updatePicture(QString word)
{
    qDebug()<<word;
    QString url=imager->getPicture(word);
    qDebug()<<url;
    return url;//imager->getPicture(word);
}
