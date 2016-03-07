#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QString>

class Translator
{
protected:
    QString Lang;
    QString Text;
public:
    Translator();
    virtual QString translate()=0;
    void setText(QString);
    QString getText();
    void setLang(QString);
    QString getLang();

};

#endif // TRANSLATOR_H
