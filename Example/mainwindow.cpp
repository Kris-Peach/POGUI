#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->BtnTranslate, SIGNAL(clicked(bool)), this, SLOT(translate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translate()
{
    YanTranslate *YanTrans = new YanTranslate();
    YanTrans->setText(ui->Input->text());
    YanTrans->setLang("ru-en");
    ui->Output->setText(YanTrans->yantranslate());

}




