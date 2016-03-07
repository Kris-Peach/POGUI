#include "yantranslate.h"

YanTranslate::YanTranslate(QNetworkAccessManager* man):QObject()
{
    QString key ("trnsl.1.1.20160223T163752Z.4ac0c18bf2406e04.f5b813437ccfb127de3d1bf07e0ad35d8474ec66");
    YanKey = key;
    QString url("https://translate.yandex.net/api/v1.5/tr.json/translate?");
    YanUrl = url;
    this->manager=man;
}
QString YanTranslate::translate()
{
    QUrl url(YanUrl);
    QUrlQuery current(url);
    current.addQueryItem("key", YanKey);
    current.addQueryItem("text", Text);
    current.addQueryItem("lang", Lang);
    url.setQuery(current);

    QByteArray answer = GET(url);
    if (answer.isEmpty())
    {
        int n = QMessageBox::critical(0, "Attention","Нет соединения с Яндекс.Переводчик",
                                              QMessageBox::Cancel | QMessageBox::Escape);
                if (n == QMessageBox::Cancel)
                    return "";
    }
    QString translation (parsJson(answer));
    return translation;

}

QByteArray YanTranslate::GET(QUrl r)
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

QString YanTranslate::parsJson(QByteArray answer)
{
    QString translation("");
    QJsonDocument jsondoc = QJsonDocument::fromJson(answer);
    int code = jsondoc.object()["code"].toInt();
    if (code == 200)
    {
        QJsonArray array = jsondoc.object()["text"].toArray();
        for(QJsonArray::Iterator iter = array.begin();iter!=array.end();  ++iter)
            {
            translation.append((*iter).toString());
        }
    }
    else {
        parsError(code);
        translation=" ";
    }
    return translation;
}

void YanTranslate::parsError(int code)
{
    switch (code) {
    case 401:
       {int n = QMessageBox::critical(0, "Attention","Неправильный ключ API",
                                      QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    case 402:
        {int n = QMessageBox::critical(0, "Attention","Ключ API заблокирован",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
       }
        break;
    case 403:
        {int n = QMessageBox::critical(0, "Attention","Превышено суточное ограничение на количество запросов",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    case 404:
        {int n = QMessageBox::critical(0, "Attention","Превышено суточное ограничение на объем переведенного текста",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    case 413:
        {int n = QMessageBox::critical(0, "Attention","Превышен максимально допустимый размер текста",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    case 422:
        {int n = QMessageBox::critical(0, "Attention","Текст не может быть переведен",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    case 501:
        {int n = QMessageBox::critical(0, "Attention","Заданное направление перевода не поддерживается",
                                       QMessageBox::Cancel | QMessageBox::Escape);
        if (n == QMessageBox::Cancel) return;
        }
        break;
    default:
        break;
    }
    return;
}


