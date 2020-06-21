#ifndef GJJDK_H
#define GJJDK_H

#include <QWidget>

namespace Ui {
class gjjdk;
}

class gjjdk : public QWidget
{
    Q_OBJECT
public:
    explicit gjjdk(QWidget *parent = nullptr);
    //用户输入数据
    int dkfs;
    int hkfs;
    int qishu,mianji,danjia,ajcs;
    long long zong;
    double lilv=0,chengshu;
    //程序输出信息
    double yuehk; //首月还款
    long long hkzong;//还款总额
    double zonglx; //总利息
    int hkys;//   还款月数
    double dijian ;//等额本金还款每月递减
    //两种计算方式
    void debj();
    void debx();
    //总贷款
    void get_sj();//得到用户输入的数据
    void guilin();//清空输入框
    ~gjjdk();
signals:
    void back();
private:
    Ui::gjjdk *ui;
};

#endif // GJJDK_H
