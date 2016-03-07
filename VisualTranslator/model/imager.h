#ifndef IMAGER_H
#define IMAGER_H
#include<QString>


class Imager
{
public:
    Imager();
    virtual QString getPicture(QString str)=0;
};

#endif // IMAGER_H
