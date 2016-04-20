#include "interf.h"

Interf::Interf()
{

}

Interf::~Interf()
{
    delete m_audioInput;
    delete m_reply;
}

const QByteArray &Interf::data() const
{

    return m_buffer.data();
}

QString Interf::recognizeSpeech()
{
    QUrl url(QString("https://asr.yandex.net/asr_xml?key=aaf9bbe9-63ed-49e6-81e5-27173ef4668a&uuid=12345678123459881234567812345678&topic=notes&lang=ru-RU"));
    QNetworkRequest request(url);

     request.setHeader(QNetworkRequest::ContentTypeHeader, "audio/x-pcm;bit=16;rate=16000");
     m_state = SpeechReq;
     qDebug()<< m_buffer.size();
     m_reply=m_manager->post(request, data());

     //setReply(m_manager->post(request, data()));
     return onReplyFinished();
}


void Interf::deleteReply()
{
    if (m_reply != nullptr) {
        m_reply->deleteLater();
        m_reply = nullptr;
    }

    m_state = Ready;
}


void Interf::setReply(QNetworkReply *reply)
{

    m_reply = reply;
    connect(m_reply, SIGNAL(finished()), SLOT(onReplyFinished()));
}



QString Interf::parseSpeechRecognitionResult(const QString &response, QString *result)
{
    QXmlStreamReader xml(response);
    QString recognitionResult;
    double maxConfidence = INT32_MIN;

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == "recognitionResults") {
                QXmlStreamAttributes attributes = xml.attributes();
                if (!attributes.hasAttribute("success")) {
                    recognitionResult="400";
                    return recognitionResult;
                }

                bool ok = false;
                int success = attributes.value("success").toInt(&ok);
                if (!ok || !success) {
                    recognitionResult="400";
                    return recognitionResult;
                }
            }

            if (xml.name() == "variant") {
                QXmlStreamAttributes attributes = xml.attributes();
                if (!attributes.hasAttribute("confidence"))
                    continue;

                bool ok = false;
                double confidence = attributes.value("confidence").toDouble(&ok);
                if (!ok)
                    continue;

                if (confidence > maxConfidence) {
                    maxConfidence = confidence;
                    recognitionResult = xml.readElementText();
                }
            }
        }
    }

    *result = recognitionResult;
    return recognitionResult;
}


QString Interf::onReplyFinished()
{
   QEventLoop wait;
   QTimer::singleShot(10000,&wait,SLOT(quit()));
   wait.exec();
   QByteArray answer = (QByteArray)m_reply->readAll();
   QString str =(QString)answer;
   qDebug()<< str;

    if (m_reply == nullptr)
        return "400";
    if (m_state == SpeechReq) {

        QString recognitionResult;
        QString SpeechAnsw;
        SpeechAnsw=parseSpeechRecognitionResult(str, &recognitionResult);
        return SpeechAnsw;
        //qDebug()<< SpeechAnsw;
        deleteReply();
    }
 }

