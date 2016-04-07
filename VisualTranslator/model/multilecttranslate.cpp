#include "multilecttranslate.h"


MultilectTranslate::MultilectTranslate(QNetworkAccessManager* man):QObject()
{
    QString id("274");
    MultilectId = id;
    QString url("http://api.multillect.com/translate/json/1.0/" + id);
    MuiltilectUrl = url;
    QString sig("391a3b207d6a81e2790399c394ef769a");
    MultilectSig = sig;
    QString method("translate/api/translate");
    MultilectMethod = method;
    Lang="rus-eng";
    //обратить внимание на то, что присутствет lang_from и lang_to
    //примеры задания языка смотри ниже
    //QString langFrom("rus");
    //lang_from = langFrom;
    //QString langTo("eng");
   //lang_to = langTo;
    //this->manager=man;

}


QString MultilectTranslate::translate()
{
    QStringList langs=Lang.split('-');
    QUrl url(MuiltilectUrl);
    QUrlQuery current(url);
    current.addQueryItem("method", MultilectMethod);
    current.addQueryItem("from", langs.at(0));//lang_from);
    current.addQueryItem("to", langs.at(1));//lang_to);
    current.addQueryItem("text", Text);
    current.addQueryItem("sig",  MultilectSig);
    url.setQuery(current);

    QByteArray answer = GET(url);
   qDebug()<<QString::fromUtf8(answer);
    if(answer.isEmpty())
            {
            int n = QMessageBox::critical(0, "Attention","Нет соединения с Multilect",
                                                  QMessageBox::Cancel | QMessageBox::Escape);
                    if (n == QMessageBox::Cancel)
                        return "";
            }

    QString translation (parsJson(answer));
    return translation;

}

QByteArray MultilectTranslate::GET(QUrl r)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(QNetworkRequest (r));
    QEventLoop wait;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit())); //когда придет ответ, мы выйдем из loop
    QTimer::singleShot(1000, &wait, SLOT(quit()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();

    QByteArray answer = reply->readAll();  //считываем ответ
    reply->deleteLater();
    return answer;
}

QString MultilectTranslate::parsJson(QByteArray answer)
{
    QString translation("");
    QJsonDocument jsondoc = QJsonDocument::fromJson(answer);
    int error = jsondoc.object()["error"].toInt();
    if(error == 0)
    {
        QJsonObject js = jsondoc.object()["result"].toObject();
        for(QJsonObject::Iterator iter = js.begin();iter!=js.end();  ++iter)
            {
            translation.append(iter.value().toString());
        }

     }
   else{
        int n = QMessageBox::critical(0, "Attention","Ошибка перевода",
                                              QMessageBox::Cancel | QMessageBox::Escape);
                if (n == QMessageBox::Cancel) return"";
        }
    return translation;
}
/*
 * <lang_from> Source language for translation

rus — Russian
eng — English
ara — Arabic
fra — French
deu — German
spa — Spanish
tur — Turkish
ukr — Ukrainian
*/
