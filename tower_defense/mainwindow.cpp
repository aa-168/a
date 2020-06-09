#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include "mywindow.h"
#include "sbutton.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    SButton * btn = new SButton(":/StartButton.jpg");
    btn->setParent(this);
 //   QPushButton *btn = new QPushButton(this);
  //  btn->setFixedSize(100,50);
    btn->move(100,300);
//    connect(btn,&SButton::clicked,this,&QMainWindow::close);

    MyWindow * scene = new MyWindow;
    connect(btn,&QPushButton::clicked,this,[=](){
        btn->btdown();
        btn->btup();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            scene->show();
        });

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*){
  QPainter painter(this);
  QPixmap pixmap(":/background.jpeg");
  painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
