#include "instapicture.h"

InstaPicture::InstaPicture()
{

}


QByteArray InstaPicture::GET(QUrl r)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager (this);
    QNetworkReply *reply = manager->get(QNetworkRequest(r));
    QEventLoop wait;
    connect (manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();


    QByteArray answer = (QByteArray)reply->readAll();
    reply->deleteLater();
    return answer;
}

QString InstaPicture::Get_Picture(QString str)
{
    hesh = str;
    QString ret_answer = "";

    //Отправляем запрос к Instagram
    QUrl url ("https://api.instagram.com/v1/tags/"+hesh+"/media/recent?");
    QUrlQuery query;
    query.addQueryItem("count","1");

    //Мой токен,Сонь, поменяй на свой
    query.addQueryItem("access_token","886211474.1677ed0.d8603ee68db5465d9bf66ce0ad13c159");
    url.setQuery(query);

     // Получаем ответ в json формате
    QByteArray answer = GET (url);

    //Мэпим
    QJsonParseError *errPar =new QJsonParseError();
    QJsonDocument doc= QJsonDocument::fromJson(answer,errPar);
    QJsonObject jObj= doc.object();
    QVariantMap CodeMain = jObj.toVariantMap();

    //Узнаю код, который возвращается
    QVariantMap CodeMap = CodeMain["meta"].toMap();
    int code = CodeMap["code"].toInt();

    //Если все ок
    if (code==200){
    QJsonArray value = jObj["data"].toArray();

    // Получаем из json-a адрес нашей картинки
    QJsonObject mainMap = value[0].toObject()["images"].toObject();
    QVariantMap mMap =mainMap.toVariantMap();
    QVariantMap tmp_1= mMap["low_resolution"].toMap();
    ret_answer = tmp_1["url"].toString();

    }

    else
    {
        ret_answer = 400;
    }

    return ret_answer;
}
