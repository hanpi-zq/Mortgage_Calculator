#ifndef ZHXDK_H
#define ZHXDK_H

#include <QWidget>

namespace Ui {
class zhxdk;
}

class zhxdk : public QWidget
{
    Q_OBJECT
public:
    explicit zhxdk(QWidget *parent = nullptr);
    long long zong1,zong2,zong;

    int qishu;
    int hkfs;
    double lilv1=0,lilv2=0;
    //输出信息
    double yuehk1,yuehk2,yuehk;
    double zonglx1,zonglx2,zonglx;
    double dijian1,dijian2,dijian;
    double long hkzong;

    //得到数据
    void get_sj();
    //计算
    void debj();
    void debx();
    void guilin();
    ~zhxdk();
signals:
    void back();
private:
    Ui::zhxdk *ui;
};

#endif // ZHXDK_H
