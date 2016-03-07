#include "appmanager.h"

AppManager::AppManager(QObject *parent) : QObject(parent)
{
    NetworkManager=new QNetworkAccessManager(this);
    InstagramManager=new InstaPicture(NetworkManager);
    YandexTranslator=new YanTranslate(NetworkManager);
}
QString  AppManager::translate(int numTranslator, QString langs, QString text)
{
    Translator* translator;
    switch ( numTranslator )
    {
        case 0 : translator=YandexTranslator;
        default : translator=YandexTranslator;
    }
    translator->setLang(langs);
    translator->setText(text);
    QString str=translator->translate();
   // if(str=="Error500") str="sorry, it is not possible to translate. try in a few minutes";
    return str;

}
