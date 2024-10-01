#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "goods.h"

#include <QList>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QApplication>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<Goods*> goodsArray;//参赛运动员集
    QString pathName;//记录文件路径，用于保存菜单项
    Goods* getGoods(QString myName);//通过商品名称获得商品信息
    Sales* getSales(QString myNmae,QString order);//通过商品名称和订单编号获得销售信息
    void removeAllGoods();//清空所有商品信息
    bool removeGoods(QString myID);//清空指定编号的商品信息
    void showGoods(Goods* goods,int row=-1);//显示商品函数
    void showSales(Sales* sales,int row=-1);//显示销售信息函数

    void populateTable_goodsInquiry(const QList<Goods *> &results);
    void populateTable_salesInquiry(const QList<Sales *> &results);
    void populateTable_goodsInquiryAdvanced(const QList<Goods *> &results);
    void populateTable_salesInquiryAdvanced(const QList<Sales *> &results);


    QStatusBar* status;
    void updateStatus();

private slots:
    void on_pushButtonAddGoods_clicked();

    void on_pushButtonSalesAdd_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonExit2_clicked();

    void on_actionopenFile_triggered();

    void on_actionsaveFileAs_triggered();

    void on_actionsaveFile_triggered();

    void on_actioninquiry_triggered();

    void on_pushButtonBackToMain_clicked();

    void on_pushButtonInquiry1_clicked();

    void on_actionupdate_triggered();

    void on_pushButtonInquirt2_clicked();

    void on_pushButtonInquiry1Advanced_clicked();

    void on_pushButtonInquiry2Advanced_clicked();

    void on_pushButtonBack_clicked();

    void on_actiondataAnalysis_triggered();

    void on_actionnonStock_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
