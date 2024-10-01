#ifndef GOODS_H
#define GOODS_H

#include <QDataStream>
#include <QDate>
#include <QString>
#include"sales.h"


class Goods
{
public:
    Goods();
    ~Goods()//析构函数
    {
        for(int i=0;i<salesArray.length();i++)
        {
            delete salesArray[i];
        }
        salesArray.clear();
    }

    QString name;//商品名称
    QString id;//编号
    int totalNumber;//总数量
    float purchasePrice;//进价
    float sellingPrice;//售价
    QString factory;//生产厂家
    QDate productionDate;//生产日期
    QDate validationDate;//保质期
    QList<Sales*> salesArray;//销售数据集

    friend QDataStream& operator<<(QDataStream& ds,Goods& g)//输出运算符重载
    {
        ds<<g.name<<g.id<<g.totalNumber<<g.purchasePrice<<g.sellingPrice<<g.factory<<g.productionDate<<g.validationDate;
        int len=g.salesArray.length();
        ds<<len;
        for(int i=0;i<g.salesArray.length();i++)
        {
            ds<<*g.salesArray[i];
        }
        return ds;
    }

    friend QDataStream& operator>>(QDataStream& ds,Goods& g)//输入运算符重载
    {
        ds>>g.name>>g.id>>g.totalNumber>>g.purchasePrice>>g.sellingPrice>>g.factory>>g.productionDate>>g.validationDate;
        int length;//交易额数
        ds>>length;
        Sales*s=NULL;
        for(int i=0;i<length;i++)
        {
            s=new Sales;
            ds>>*s;
            g.salesArray.append(s);
        }
        return ds;
    }

    QString getContent(int i)//获取Goods类中第n项内容
    {
        switch (i)
        {
        case 0:return this->name;break;
        case 1:return this->id;break;
        case 2:return QString::number(this->totalNumber);break;
        case 3:return QString::number(this->purchasePrice);break;
        case 4:return QString::number(this->sellingPrice);break;
        case 5:return this->factory;break;
        case 6:return this->productionDate.toString();break;
        case 7:return this->validationDate.toString();break;
        default:return NULL;break;
        }
    }

    Sales* getSales(QString order) //获取销售记录
    {
        for(int i=0;i<salesArray.length();i++)
        {
            if(salesArray[i]->order==order)
            {
                return salesArray[i];
            }
        }
        return nullptr;
    }


    bool removeSales(QString order)//删除销售记录
    {
        for(int i=0;i<salesArray.length();i++)
        {
            if(salesArray[i]->order==order)
            {
                delete salesArray[i];
                salesArray.removeAt(i);
                return true;
            }
        }
        return false;
    }

    int getNum()
    {
        return totalNumber;
    }
};

#endif // GOODS_H
