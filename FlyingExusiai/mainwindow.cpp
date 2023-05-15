#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //点击发信号
        emit this->start();

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
