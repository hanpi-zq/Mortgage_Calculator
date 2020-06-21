#include "zhxdk.h"
#include "ui_zhxdk.h"
#include<QPushButton>
#include<qmath.h>
#include<QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
zhxdk::zhxdk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhxdk)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton ret = QMessageBox::question(this,"警告","确定返回主界面并清空数据！！！",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
        {
             guilin();
             emit this->back();
        }

    });
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
    //得到期数
    void(QComboBox:: *q)(int)= &QComboBox::currentIndexChanged;
    connect(ui->comboBox_2,q,[&](int index){
        qishu = ui->comboBox_2->itemData(index).toInt();
        get_sj();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_3->insert(QString::number((double)lilv1*100)+"%");
        ui->lineEdit_4->insert(QString::number((double)lilv2*100)+"%");
    });
    //显示利率
    void(QComboBox:: *p2)(int)= &QComboBox::currentIndexChanged;
    connect(ui->comboBox_3,p2,[=](){
        get_sj();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_3->insert(QString::number((double)lilv1*100)+"%");
        ui->lineEdit_4->insert(QString::number((double)lilv2*100)+"%");
    });

    //选择还款方式
    connect(ui->radioButton,&QRadioButton::clicked,[=](){
        hkfs=1;
    });
    connect(ui->radioButton_2,&QRadioButton::clicked,[=](){
        hkfs=2;
    });


    //点击开始计算按钮，显示计算框
    ui->widget->hide();
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        ui->widget->show();
        if(hkfs==1)
        {
            get_sj();
            if(zong<10000)
            {
                QMessageBox::StandardButton ret1 = QMessageBox::warning(this,"提示","你输入的总额过小！！！");

                     ui->lineEdit->clear();
                     ui->lineEdit_2->clear();

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

                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
            get_sj();
            debx();
        }

    });
    //点击清除按钮
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        QMessageBox::StandardButton ret = QMessageBox::question(this,"警告","确定清楚所有数据！！！",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
        {
             guilin();
        }
    });
    //正则表达式
    QRegExp regexp1("^[0-9]*[1-9][0-9]*$");
    ui->lineEdit->setValidator(new QRegExpValidator(regexp1,ui->lineEdit));
    ui->lineEdit_2->setValidator(new QRegExpValidator(regexp1,ui->lineEdit_2));

    //设置背景
    QPixmap pixmap = QPixmap(":/image/gg.jpg").scaled(this->size());

            QPalette palette(this->palette());

            palette.setBrush(QPalette::Background, QBrush(pixmap));

            this->setPalette(palette);


}
void zhxdk::get_sj()
{
    zong1=ui->lineEdit->text().toInt();
    zong2=ui->lineEdit_2->text().toInt();
    zong=zong1+zong2;

    //得到利率
    if(ui->comboBox_3->currentIndex()==1&&qishu<=60)
        {
             lilv1=0.0475;
             lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==1&&qishu>60)
        {
             lilv1=0.049;
             lilv2=0.0375;
        }
    else if(ui->comboBox_3->currentIndex()==2&&qishu<=60)
        {
             lilv1=0.0523;
             lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==2&&qishu>60)
        {
            lilv1=0.0539;
            lilv2=0.0325;
        }
    else if(ui->comboBox_3->currentIndex()==3&&qishu<=60)
        {
            lilv1=0.057;
            lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==3&&qishu>60)
        {
            lilv1=0.0588;
            lilv2=0.0325;
        }
    else if(ui->comboBox_3->currentIndex()==4&&qishu<=60)
        {
            lilv1=0.0566;
            lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==4&&qishu>60)
        {
            lilv1=0.0637;
            lilv2=0.0325;
        }
    else if(ui->comboBox_3->currentIndex()==5&&qishu<=60)
        {
            lilv1=0.0305;
            lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==5&&qishu>60)
        {
            lilv1=0.0343;
            lilv2=0.0325;
        }
    else if(ui->comboBox_3->currentIndex()==6&&qishu<=60)
        {
            lilv1=0.0404;
            lilv2=0.0275;
        }
    else if(ui->comboBox_3->currentIndex()==6&&qishu>60)
        {
            lilv1=0.0417;
            lilv2=0.0325;
        }
    else if(ui->comboBox_3->currentIndex()==0)
        {
            lilv1=0;
            lilv2=0;
        }
}
//等额本金的计算
void zhxdk::debj()
{
    zong = zong1+zong2;
    yuehk1 = zong1/qishu+(zong*lilv1)/12.0;
    yuehk2 = zong2/qishu+(zong*lilv2)/12.0;
    yuehk = yuehk1+yuehk2;
    zonglx1 = ((zong1/qishu+zong1*lilv1/12.0)+zong1/qishu*(1+lilv1/12.0))/2*qishu-zong1;
    zonglx2 = ((zong2/qishu+zong2*lilv2/12.0)+zong2/qishu*(1+lilv2/12.0))/2*qishu-zong2;
    zonglx=zonglx1+zonglx2;
    dijian1 = (zong1/qishu)*lilv1/12.0;
    dijian2 = (zong2/qishu)*lilv2/12.0;
    dijian = dijian1+dijian2;
    hkzong = zong+zonglx;
    ui->lineEdit_5->setText(QString::number(yuehk,'.',2));
    ui->lineEdit_6->setText(QString::number(dijian,'.',2));
    ui->lineEdit_7->setText(QString::number(zong,'.',2));
    ui->lineEdit_8->setText(QString::number(zonglx,'.',2));
    ui->lineEdit_9->setText(QString::number(hkzong,'.',2));
    ui->lineEdit_10->setText(QString::number((int)qishu));
}
void zhxdk::debx()
{
    zong=zong1+zong2;
    yuehk1=(zong1*lilv1/12.0*qPow(1+lilv1/12.0,qishu))/(qPow(1+lilv1/12.0,(qishu-1)));
    yuehk2=(zong2*lilv2/12.0*qPow(1+lilv2/12.0,qishu))/(qPow(1+lilv2/12.0,(qishu-1)));
    yuehk=yuehk1+yuehk2;
    zonglx1=zong1*lilv1/12.0*(qishu+1)/2;
    zonglx2=zong2*lilv2/12.0*(qishu+1)/2;
    zonglx=zonglx1+zonglx2;
    hkzong=zong+zonglx;
    dijian=0;
    ui->lineEdit_5->setText(QString::number(yuehk,'.',2));
    ui->lineEdit_6->setText(QString::number(dijian,'.',2));
    ui->lineEdit_7->setText(QString::number(zong,'.',2));
    ui->lineEdit_8->setText(QString::number(zonglx,'.',2));
    ui->lineEdit_9->setText(QString::number(hkzong,'.',2));
    ui->lineEdit_10->setText(QString::number((int)qishu));


}
void zhxdk::guilin()
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
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
}





zhxdk::~zhxdk()
{
    delete ui;
}
