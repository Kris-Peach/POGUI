#include "dialog.h"
#include "ui_dialog.h"
#include "instapicture.h"
Dialog::Dialog(QWidget *parent) : QDialog(parent)
    //ui(new Ui::Dialog)

{
   // ui->setupUi(this);

    web = new QWebView();//для отображения картинок
    EnterText = new QLineEdit;//для ввода хэшей
    but= new QPushButton("enter");
    but->setDefault(true);
    but->setEnabled(false);

    QHBoxLayout *lay_1 = new QHBoxLayout;
    lay_1->addWidget(EnterText);
    lay_1->addWidget(but);

    QVBoxLayout *lay_2 = new QVBoxLayout;
    lay_2->addWidget(web);
    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(lay_1);
    main->addLayout(lay_2);
    setLayout(main);

    connect(EnterText,SIGNAL(textChanged(QString)),this,SLOT(Add_text(QString)));
    connect(but,SIGNAL(clicked()),this,SLOT(Ok()));

}

Dialog::~Dialog()
{
  //  delete ui;
}


void Dialog::Add_text(QString str)
{
    but->setEnabled(!str.isEmpty());
}

void Dialog::Ok()
{
    InstaPicture *InstPi = new InstaPicture;
    QString answ = InstPi->Get_Picture(EnterText->text());
    web->load(answ);

}
