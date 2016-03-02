#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include "instapicture.h"
#include <QtWebKitWidgets/QWebView>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    //InstaPicture *InstPi ;

private:
  //  Ui::Dialog *ui;
    QWebView *web;
    QLineEdit *EnterText;
    QPushButton *but;


private slots:

    void Add_text(QString str);
    void Ok();


};

#endif
