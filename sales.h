#ifndef SALES_H
#define SALES_H

#include <QDataStream>
#include <QDate>
#include <QString>



class Sales
{
public:
    Sales();
    QString order;//订单号
    int num;//数量
    float offRate;//折扣率
    QDate tradeDate;//订单日期
    QString tel;//联系电话
    friend QDataStream& operator<<(QDataStream& ds,Sales& s)//输出运算符重载
    {
        ds<<s.order<<s.num<<s.offRate<<s.tradeDate<<s.tel;
        return ds;
    }
    friend QDataStream& operator>>(QDataStream& ds,Sales& s)//输入运算符重载
    {
        ds>>s.order>>s.num>>s.offRate>>s.tradeDate>>s.tel;
        return ds;
    }
    int getNum()
    {
        return num;
    }
    QString getContent(int i)
    {
        switch (i)
        {
        case 0:return this->order;break;
        case 1:return QString::number(this->num);break;
        case 2:return QString::number(this->offRate);break;
        case 3:return this->tradeDate.toString();break;
        case 4:return this->tel;break;
        default:return NULL;break;
        }
    }

};

#endif // SALES_H
