#include "sydk.h"
#include "ui_sydk.h"
#include<QPushButton>
#include<QDebug>
#include<qmath.h>
#include<QButtonGroup>
#include<QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>

sydk::sydk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sydk)
{
    //返回按钮的设置时提示
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton ret = QMessageBox::question(this,"警告","确定返回主界面并清空数据！！！",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
        {
            guilin();
            get_sj();
             emit this->back();
        }
    });
    //设置按揭成数
    ui->comboBox->addItem("按揭成数",QVariant(0));
    ui->comboBox->addItem("2成",QVariant(0.2));
    ui->comboBox->addItem("2.5成",QVariant(0.25));
    ui->comboBox->addItem("3成",QVariant(0.3));
    ui->comboBox->addItem("3.5成",QVariant(0.35));
    ui->comboBox->addItem("4成",QVariant(0.4));
    ui->comboBox->addItem("4.5成",QVariant(0.45));
    ui->comboBox->addItem("5成",QVariant(0.5));
    ui->comboBox->addItem("5.5成",QVariant(0.55));
    ui->comboBox->addItem("6成",QVariant(0.6));
    ui->comboBox->addItem("6.5成",QVariant(0.65));
    ui->comboBox->addItem("7成",QVariant(0.7));
    ui->comboBox->addItem("7.5成",QVariant(0.75));
    ui->comboBox->addItem("8成",QVariant(0.8));


    //设置按揭年数
    ui->comboBox_2->addItem("选择期数",QVariant(0));
    ui->comboBox_2->addItem("1年(12期)",QVariant(12));
    ui->comboBox_2->addItem("2年(24期)",QVariant(24));
    ui->comboBox_2->addItem("3年(36期)",QVariant(36));
    ui->comboBox_2->addItem("4年(48期)",QVariant(48));
    ui->comboBox_2->addItem("5年(60期)",QVariant(60));
    ui->comboBox_2->addItem("6年(72期)",QVariant(72));
    ui->comboBox_2->addItem("7年(84期)",QVariant(84));
    ui->comboBox_2->addItem("8年(96期)",QVariant(96));
    ui->comboBox_2->addItem("9年(108期)",QVariant(108));
    ui->comboBox_2->addItem("10年(120期)",QVariant(120));
    ui->comboBox_2->addItem("11年(132期)",QVariant(132));
    ui->comboBox_2->addItem("12年(144期)",QVariant(144));
    ui->comboBox_2->addItem("13年(156期)",QVariant(156));
    ui->comboBox_2->addItem("14年(168期)",QVariant(168));
    ui->comboBox_2->addItem("15年(180期)",QVariant(180));
    ui->comboBox_2->addItem("16年(192期)",QVariant(192));
    ui->comboBox_2->addItem("17年(204期)",QVariant(204));
    ui->comboBox_2->addItem("18年(216期)",QVariant(216));
    ui->comboBox_2->addItem("19年(228期)",QVariant(228));
    ui->comboBox_2->addItem("20年(240期)",QVariant(240));
    //贷款利率的下拉列表
    ui->comboBox_3->addItem("选择利率");
    ui->comboBox_3->addItem("2020年1月1日基准利率");
    ui->comboBox_3->addItem("2020年1月1日利率上限(1.1倍)");
    ui->comboBox_3->addItem("2020年1月1日利率上限(1.2倍)");
    ui->comboBox_3->addItem("2020年1月1日利率上限(1.3倍)");
    ui->comboBox_3->addItem("2020年1月1日利率下限(7折)");
    ui->comboBox_3->addItem("2020年1月1日利率下限(85折)");
    ui->widget->hide();
    ui->widget_2->hide();
    ui->widget_3->hide();
    QButtonGroup *r1= new QButtonGroup(this);
    QButtonGroup *r2= new QButtonGroup(this);
    r1->addButton(ui->radioButton);
    r1->addButton(ui->radioButton_2);
    r2->addButton(ui->radioButton_3);
    r2->addButton(ui->radioButton_4);


    //按钮选择
    connect(ui->radioButton,&QRadioButton::clicked,[=](){
        ui->widget->show();
        ui->widget_2->hide();
        dkfs=1;
    });

    connect(ui->radioButton_2,&QRadioButton::clicked,[=](){
        ui->widget_2->show();
        ui->widget->hide();
        dkfs=2;

    });

    //得到期数
    void(QComboBox:: *q)(int)= &QComboBox::currentIndexChanged;
    connect(ui->comboBox_2,q,[&](int index){
        qishu = ui->comboBox_2->itemData(index).toInt();
        get_sj();
        ui->lineEdit->clear();
        ui->lineEdit->insert(QString::number((double)lilv*100)+"%") ;
    });

    //显示利率
    void(QComboBox:: *p2)(int)= &QComboBox::currentIndexChanged;
    connect(ui->comboBox_3,p2,[=](){
        get_sj();
        ui->lineEdit->clear();
        ui->lineEdit->insert(QString::number((double)lilv*100)+"%") ;
    });
    //得到成数
    void(QComboBox:: *p)(int)= &QComboBox::currentIndexChanged;
    connect(ui->comboBox,p,[&](int index){
        chengshu = ui->comboBox->itemData(index).toDouble();
    });
    connect(ui->radioButton_3,&QRadioButton::clicked,[=](){
        hkfs=1;
    });
    connect(ui->radioButton_4,&QRadioButton::clicked,[=](){
        hkfs=2;
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        ui->widget_3->show();
        if(hkfs==1)
        {
            get_sj();
            if(zong<10000)
            {
                QMessageBox::StandardButton ret1 = QMessageBox::warning(this,"提示","你输入的总额过小！！！");

                     ui->lineEdit_2->clear();
                     ui->lineEdit_3->clear();
                     ui->lineEdit_4->clear();

            }
            get_sj();
            debj();
        }
        else if(hkfs==2)
        {
            get_sj();
            if(zong<10000)
            {
                QMessageBox::StandardButton ret1 = QMessageBox::warning(this,"提示","你输入的总额过小！！！");

                     ui->lineEdit_2->clear();
                     ui->lineEdit_3->clear();
                     ui->lineEdit_4->clear();

            }
            get_sj();
            debx();
        }

    });
    //点击清除按钮
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton ret = QMessageBox::question(this,"警告","确定清除所有数据！！！",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
        {
             guilin();
             get_sj();
        }
    });

    //设置背景
    QPixmap pixmap = QPixmap(":/image/hh.jpg").scaled(this->size());

            QPalette palette(this->palette());

            palette.setBrush(QPalette::Background, QBrush(pixmap));

            this->setPalette(palette);
    //正则表达式
    QRegExp regexp1("^[0-9]*[1-9][0-9]*$");
    ui->lineEdit_2->setValidator(new QRegExpValidator(regexp1,ui->lineEdit_2));
    ui->lineEdit_3->setValidator(new QRegExpValidator(regexp1,ui->lineEdit_3));
    ui->lineEdit_4->setValidator(new QRegExpValidator(regexp1,ui->lineEdit_4));

}

sydk::~sydk()
{
    delete ui;
}
void sydk::get_sj()
{
    danjia=ui->lineEdit_3->text().toInt();
    mianji=ui->lineEdit_4->text().toInt();
    if(dkfs==2)
    {
        QString str = ui->lineEdit_2->text();
         zong = str.toLongLong();

    }
    //总金额
    else if(dkfs==1)
    {
        danjia=ui->lineEdit_3->text().toFloat();
        mianji=ui->lineEdit_4->text().toFloat();
        zong=(double)danjia*(double)mianji*chengshu;
        //qDebug()<<zong;
     }
    //得到利率
    if(ui->comboBox_3->currentIndex()==1&&qishu<=60)
        lilv=0.0475;
    else if(ui->comboBox_3->currentIndex()==1&&qishu>=60)
        lilv=0.049;
    else if(ui->comboBox_3->currentIndex()==2&&qishu<=60)
        lilv=0.0523;
    else if(ui->comboBox_3->currentIndex()==2&&qishu>=60)
        lilv=0.0539;
    else if(ui->comboBox_3->currentIndex()==3&&qishu<=60)
        lilv=0.057;
    else if(ui->comboBox_3->currentIndex()==3&&qishu>=60)
        lilv=0.0588;
    else if(ui->comboBox_3->currentIndex()==4&&qishu<=60)
        lilv=0.0566;
    else if(ui->comboBox_3->currentIndex()==4&&qishu>=60)
        lilv=0.0637;
    else if(ui->comboBox_3->currentIndex()==5&&qishu<=60)
        lilv=0.0305;
    else if(ui->comboBox_3->currentIndex()==5&&qishu>=60)
        lilv=0.0343;
    else if(ui->comboBox_3->currentIndex()==6&&qishu<=60)
        lilv=0.0404;
    else if(ui->comboBox_3->currentIndex()==6&&qishu>=60)
        lilv=0.0417;
    else if(ui->comboBox_3->currentIndex()==0)
        lilv=0;
}
void sydk::debj()
{
    yuehk=zong/qishu+(zong*lilv)/12.0;
    dijian= (zong/qishu)*lilv/12.0;
    zonglx=((zong/qishu+zong*lilv/12.0)+zong/qishu*(1+lilv/12.0))/2*qishu-zong;
    hkzong=zong+zonglx;
    ui->lineEdit_5->setText(QString::number(yuehk,'.',2));
    ui->lineEdit_6->setText(QString::number(dijian,'.',2));
    ui->lineEdit_7->setText(QString::number(zong,'.',2));
    ui->lineEdit_8->setText(QString::number(zonglx,'.',2));
    ui->lineEdit_9->setText(QString::number(hkzong,'.',2));
    ui->lineEdit_10->setText(QString::number((int)qishu));
}
void sydk::debx()
{
    yuehk=(zong*lilv/12.0*qPow(1+lilv/12.0,qishu))/(qPow(1+lilv/12.0,(qishu-1)));
    dijian=0;
    zonglx=zong*lilv/12.0*(qishu+1)/2;
    hkzong=zong+zonglx;
    ui->lineEdit_5->setText(QString::number(yuehk,'.',2));
    ui->lineEdit_6->setText(QString::number(dijian,'.',2));
    ui->lineEdit_7->setText(QString::number(zong,'.',2));
    ui->lineEdit_8->setText(QString::number(zonglx,'.',2));
    ui->lineEdit_9->setText(QString::number(hkzong,'.',2));
    ui->lineEdit_10->setText(QString::number((int)qishu));
}

//清除数据
void sydk::guilin()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);

}





