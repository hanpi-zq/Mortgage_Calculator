#ifndef SYDK_H
#define SYDK_H

#include <QWidget>

namespace Ui {
class sydk;
}

class sydk : public QWidget
{
    Q_OBJECT

public:
    explicit sydk(QWidget *parent = nullptr);
    ~sydk();
    //用户输入的数据
    int dkfs;
    int hkfs;
    int qishu,mianji,danjia;
    long long zong=0;
    double lilv=0,chengshu;
    //程序输出信息
    double yuehk=0; //首月还款
    double long hkzong=0;//还款总额
    double zonglx; //总利息
    int hkys;//   还款月数
    double dijian;//等额本金还款每月递减
    //两种计算方式
    void debj();
    void debx();
    void get_sj();//获取yo用户输入的数据
    void guilin();

signals:
    void back();

private:
    Ui::sydk *ui;
};

#endif // SYDK_H
