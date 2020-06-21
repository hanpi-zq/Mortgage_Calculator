#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "sydk.h"
#include "zhxdk.h"
#include "gjjdk.h"
#include<QFontDialog>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->setWindowTitle("房贷计算器");
    sydk *s =new sydk();
    zhxdk *z=new zhxdk();
    gjjdk *g=new gjjdk();
    //创建三个按钮
    QPushButton *btn= new QPushButton("商业贷款",this);
    btn->move(375,300);
    connect(btn,&QPushButton::clicked,[=](){
        //进入商业贷款页面
        this->hide();
        s->show();
    });
    //检测到返回信号
    connect(s,&sydk::back,[=](){
       //返回主界面
        s->hide();
        this->show();
    });

    QPushButton *btn2= new QPushButton("组合型贷款",this);
    btn2->move(705,300);
    connect(btn2,&QPushButton::clicked,[=](){
        //进入组合型贷款页面
        this->hide();
        z->show();
    });
    //检测到返回信号
    connect(z,&zhxdk::back,[=](){
       //返回主界面
        z->hide();
        this->show();
    });

    QPushButton *btn3= new QPushButton("公积金贷款",this);
    btn3->move(525,300);
    connect(btn3,&QPushButton::clicked,[=](){
        //进入公积金贷款页面
        this->hide();
        g->show();
    });
    //检测到返回信号
    connect(g,&gjjdk::back,[=](){
       //返回主界面
        g->hide();
        this->show();
    });
    btn->setFixedSize(100,40);
    btn2->setFixedSize(120,40);
    btn3->setFixedSize(120,40);
    QFont font = btn->font();
     font.setPointSize(12);
     font.setFamily("KaiTi");//楷体
     btn->setFont(font);
     QFont font2 = btn2->font();
      font2.setPointSize(12);
      font2.setFamily("KaiTi");//楷体
      btn2->setFont(font);
      QFont font3 = btn3->font();
       font3.setPointSize(12);
       font3.setFamily("KaiTi");//楷体
       btn3->setFont(font);
    //设置背景图片
       QPixmap pixmap = QPixmap(":/image/bjt.jpg").scaled(this->size());

               QPalette palette(this->palette());

               palette.setBrush(QPalette::Background, QBrush(pixmap));

               this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

