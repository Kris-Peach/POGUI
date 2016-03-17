#include "gettyimag.h"


GettyImag::GettyImag(QNetworkAccessManager* man)
{
    this->manager=man;
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}


QByteArray GettyImag::GET(QUrl r)
{

    QNetworkRequest request;
    request.setUrl(r);

   //В заголовок get запроса добовляю свой ключ
    request.setRawHeader("Api-Key", "sfhf75uavk739jg4v3krwvtw");

    QNetworkReply *reply = manager->get(QNetworkRequest(request));
    QEventLoop wait;
    connect (manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();

     //Получаю ответ

    QByteArray answer = (QByteArray)reply->readAll();
    reply->deleteLater();
    return answer;
}

QString GettyImag::getPicture(QString str)
{
    hesh = str;
    QString ret_answer = "";

    //Для рандомизации выбора
    int in=qrand()%5;
    rand.setNum(in);
    hesh= str;

    //Отправляем запрос
    QUrl url ( "https://api.gettyimages.com/v3/search/images?phrase="+hesh+"&page="+rand+"&page_size=1" );
    QByteArray answer = GET (url);
    qDebug()<< answer; // Получаем ответ в json формате
    QJsonParseError *errPar =new QJsonParseError();
    QJsonDocument doc= QJsonDocument::fromJson(answer,errPar);

    QJsonObject jObj= doc.object();

    if(!jObj["images"].isNull())
    {//Получаем массивчик json-чиков
    QJsonArray value = jObj["images"].toArray();

    // Получаем из json адрес нашей картинки
    QJsonArray mainMap = value[0].toObject()["display_sizes"].toArray();
    QString uri =mainMap[0].toObject()["uri"].toString();
    ret_answer=uri;
    }
    else ret_answer="http://t-cent.com/img/clipart-cross-icon-512x512-f5d9.png";

    return ret_answer;
}
