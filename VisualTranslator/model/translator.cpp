#include "translator.h"
Translator::Translator(){}
void Translator::setText(QString str)
{
    Text = str;
    return;
}

QString Translator::getText()
{
    return Text;
}

void Translator::setLang(QString str)
{
    Lang = str;
    return;
}

QString Translator::getLang()
{
    return Lang;
}
