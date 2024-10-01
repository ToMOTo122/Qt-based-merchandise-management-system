#include "goodsmaindialog.h"
#include "mainwindow.h"
#include "salesdialog.h"
#include "TableWidgetInt.h"
#include "ui_mainwindow.h"
#include "addgoodsdialog.h"

#include <goods.h>
#include<QString>
#include<QStyleFactory>
#include <QMessageBox>
#include<QFileDialog>
#include <QPropertyAnimation>
#include <QDateTimeAxis>
#include <QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    ui->stackedWidget->setCurrentIndex(0);
    for(int i=0;i<goodsArray.length();i++)
    {
        showGoods(goodsArray[i]);
    }
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
    removeAllGoods();
}

Goods *MainWindow::getGoods(QString myName)
{
    for (int i=0;i<goodsArray.length();i++ )
    {
        if(goodsArray[i]->name==myName)
        {
            return goodsArray[i];
        }
    }
    return NULL;
}

Sales *MainWindow::getSales(QString myName, QString order)
{
    Goods* goods=getGoods(myName);
    if(goods)
    {
        return goods->getSales(order);
    }
    return NULL;
}

void MainWindow::removeAllGoods()
{
    for(int i=0;i<goodsArray.length();i++)
    {
        delete goodsArray[i];
    }
    goodsArray.clear();
    updateStatus();
}

bool MainWindow::removeGoods(QString myID)
{
    for(int i=0;i<goodsArray.length();i++)
    {
        if(goodsArray[i]->name==myID)
        {
            Goods* temp = goodsArray[i];  // 保存指针以便于安全删除
            goodsArray.removeAt(i);  // 从数组中移除
            delete temp;  // 删除对象，释放内存
            updateStatus();  // 调整 UI
            return true;
        }
    }
    return false;
}

void MainWindow::showGoods(Goods *goods,int row)
{

    if(row<0)
    {
        row=ui->tableWidgetGoods->rowCount();
    }
    if(goods)
    {
        ui->tableWidgetGoods->insertRow(row);
        ui->tableWidgetGoods->setItem(row,0,new QTableWidgetItem(goods->name));
        ui->tableWidgetGoods->setItem(row,1,new QTableWidgetItem(goods->id));
        ui->tableWidgetGoods->setItem(row,2,new TableWidgetInt(QString::number(goods->totalNumber)));
        ui->tableWidgetGoods->setItem(row,3,new TableWidgetInt(QString::number(goods->purchasePrice)));
        ui->tableWidgetGoods->setItem(row,4,new TableWidgetInt(QString::number(goods->sellingPrice)));
        ui->tableWidgetGoods->setItem(row,5,new QTableWidgetItem(goods->factory));
        ui->tableWidgetGoods->setItem(row,6,new QTableWidgetItem(goods->productionDate.toString("yyyy-MM-dd")));
        ui->tableWidgetGoods->setItem(row,7,new QTableWidgetItem(goods->validationDate.toString("yyyy-MM-dd")));
        QPushButton* pushButton=new QPushButton("修改",this);

        ui->tableWidgetGoods->setCellWidget(row,8,pushButton);
        connect(pushButton,&QPushButton::clicked,
                [=]()
                {
                    int row=ui->tableWidgetGoods->currentRow();
                    QString myName=ui->tableWidgetGoods->item(row,0)->text();
                    Goods* goods=getGoods(myName);
                    if(goods)
                    {
                        GoodsMainDialog goods_dlg(goods);
                        goods_dlg.setWindowTitle("修改商品信息");
                        if(QDialog::Accepted==goods_dlg.exec())
                        {
                            ui->tableWidgetGoods->item(row,0)->setText(goods_dlg.goods->name);
                            ui->tableWidgetGoods->item(row,1)->setText(goods_dlg.goods->id);
                            ui->tableWidgetGoods->item(row,3)->setText(QString::number(goods_dlg.goods->purchasePrice));
                            ui->tableWidgetGoods->item(row,4)->setText(QString::number(goods_dlg.goods->sellingPrice));
                            ui->tableWidgetGoods->item(row,5)->setText(goods_dlg.goods->factory);
                            ui->tableWidgetGoods->item(row,6)->setText(goods_dlg.goods->productionDate.toString("yyyy-MM-dd"));
                            ui->tableWidgetGoods->item(row,7)->setText(goods_dlg.goods->validationDate.toString("yyyy-MM-dd"));
                        }
                    }
                }
                );

        pushButton=new QPushButton("删除",this);
        // 创建并设置按钮
        ui->tableWidgetGoods->setCellWidget(row, 9, pushButton);
        // 连接按钮点击信号
        connect(pushButton, &QPushButton::clicked,
                [=]()
                {
                    QMessageBox box;
                    int ret = box.question(this, "删除商品", "确认要删除吗？");
                    if (QMessageBox::Yes == ret)
                    {
                        int row=ui->tableWidgetGoods->currentRow();
                        if (row >= 0)
                        {
                            QString myID = ui->tableWidgetGoods->item(row, 0)->text();
                            removeGoods(myID);
                            ui->tableWidgetGoods->removeRow(row);
                            updateStatus();
                        }
                    }
                }
                );

        pushButton=new QPushButton("销售信息",this);
        ui->tableWidgetGoods->setCellWidget(row,10,pushButton);
        connect(pushButton,&QPushButton::clicked,
                [=]()
                {
                    int row=ui->tableWidgetGoods->currentRow();
                    QString myName=ui->tableWidgetGoods->item(row,0)->text();
                    Goods* goods=getGoods(myName);
                    if(goods)
                    {
                        ui->stackedWidget->setCurrentIndex(1);
                        int row=ui->tableWidgetSales->rowCount();
                        for(int i=0;i<row;i++)
                        {
                            ui->tableWidgetSales->removeRow(0);
                        }
                        for(int i=0;i<goods->salesArray.length();i++)
                        {
                            showSales(goods->salesArray[i]);
                        }
                    }
                    updateStatus();
                }
                );
        ui->tableWidgetGoods->setSortingEnabled(true);
        //附加功能
        /*pushButton=new QPushButton("计算利润",this);
        ui->tableWidgetGoods->setCellWidget(row,11,pushButton);
        connect(pushButton,&QPushButton::clicked,
                [=]()
                {
                    QMessageBox box;
                    int ret = box.question(this,"计算利润",QString("该商品").arg());
                    if(QMessageBox::Yes==ret)
                    {
                    }
                    else
                    {
                    }
                }
                );*/
        if(goods->totalNumber<=5)
        {
        ui->tableWidgetGoods->setItem(row,11,new QTableWidgetItem("注意补货！"));
        }
        QDate date1(2024,10,1);
        QDate date2(2024,9,15);
        if(goods->totalNumber>5 && goods->validationDate<=date1 &&goods->validationDate>=date2)
        {
            ui->tableWidgetGoods->setItem(row,11,new QTableWidgetItem("即将过期！"));
        }
        if(goods->totalNumber>5 && goods->validationDate<=date2)
        {
            ui->tableWidgetGoods->setItem(row,11,new QTableWidgetItem("请清理！"));
        }
    }
}

void MainWindow::showSales(Sales *sales,int row)
{

    if(row<0)
    {
        row=ui->tableWidgetSales->rowCount();
    }
    ui->tableWidgetSales->insertRow(row);
    ui->tableWidgetSales->setItem(row,0,new QTableWidgetItem(sales->order));
    ui->tableWidgetSales->setItem(row,1,new TableWidgetInt(QString::number(sales->num)));
    ui->tableWidgetSales->setItem(row,2,new TableWidgetInt(QString::number(sales->offRate)));
    ui->tableWidgetSales->setItem(row,3,new QTableWidgetItem(sales->tradeDate.toString("yyyy-MM-dd")));
    ui->tableWidgetSales->setItem(row,4,new QTableWidgetItem(sales->tel));
    QPushButton* pushButton= new QPushButton("修改",this);
    ui->tableWidgetSales->setCellWidget(row,5,pushButton);
    connect(pushButton,&QPushButton::clicked,
        [=]()
        {
        QString myName=ui->tableWidgetGoods->item(ui->tableWidgetGoods->currentRow(),0)->text();
        Goods* goods=getGoods(myName);
        if(goods)
        {
            int row=ui->tableWidgetSales->currentRow();
            QString order=ui->tableWidgetSales->item(row,0)->text();
            Sales* sales=goods->getSales(order);
            SalesDialog sales_dlg(sales);
            sales_dlg.setWindowTitle("修改销售信息");
            if(QDialog::Accepted==sales_dlg.exec())
            {
                ui->tableWidgetSales->item(row,0)->setText(sales->order);
                ui->tableWidgetSales->item(row,1)->setText(QString::number(sales->num));
                ui->tableWidgetSales->item(row,2)->setText(QString::number(sales->offRate));
                ui->tableWidgetSales->item(row,3)->setText(sales->tradeDate.toString("yyyy-MM-dd"));
                ui->tableWidgetSales->item(row,4)->setText(sales->tel);
            }
        }
        }
    );

    pushButton=new QPushButton("删除",this);
    ui->tableWidgetSales->setCellWidget(row,6,pushButton);
    connect(pushButton,&QPushButton::clicked,
            [=]()
            {
                QMessageBox box;
                int ret=box.question(this,"删除销售信息","确定要删除吗？");
                if(QMessageBox::Yes== ret)
                {
                    QString myName=ui->tableWidgetGoods->item(ui->tableWidgetGoods->currentRow(),0)->text();
                    Goods* goods=getGoods(myName);
                    int row=ui->tableWidgetSales->currentRow();
                    QString order=ui->tableWidgetSales->item(row,0)->text();
                    goods->removeSales(order);
                    ui->tableWidgetSales->removeRow(row);
                }
            }
            );
    updateStatus();
}


void MainWindow::on_pushButtonAddGoods_clicked()
{
    GoodsMainDialog goods_dlg(NULL,this);
    goods_dlg.setWindowTitle("添加商品");
    if(QDialog::Accepted==goods_dlg.exec())
    {
        goodsArray.append(goods_dlg.goods);
        int row=goodsArray.length()-1;
        showGoods(goods_dlg.goods,row);
    }
    updateStatus();
}

void MainWindow::on_pushButtonSalesAdd_clicked()
{
    SalesDialog sales_dlg(NULL,this);
    sales_dlg.setWindowTitle("增加销售信息");
    if(QDialog::Accepted==sales_dlg.exec())
    {
        int row=ui->tableWidgetGoods->currentRow();
        QString myName=ui->tableWidgetGoods->item(row,0)->text();
        Goods* goods=getGoods(myName);
        if(goods)
        {
            goods->salesArray.append(sales_dlg.sales);
            goods->totalNumber -= sales_dlg.sales->num;
            showSales(sales_dlg.sales);
        }
    }
}

void MainWindow::on_pushButtonExit_clicked()
{
    close();
}


void MainWindow::on_pushButtonExit2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    int row = ui->tableWidgetGoods->currentRow();
    QString myName = ui->tableWidgetGoods->item(row,0)->text();
    Goods* goods = getGoods(myName);
    if(goods)
    {
        ui->tableWidgetGoods->item(row,2)->setText(QString::number(goods->getNum(),'f',2));
    }
}


void MainWindow::on_actionopenFile_triggered()
{
    QString path=QFileDialog::getOpenFileName(this,"open","../");
    if(false==path.isEmpty())
    {
        QFile file;
        file.setFileName(path);
        bool isOK=file.open(QIODevice::ReadOnly);
        if(true==isOK)
        {
            pathName=path;
            removeAllGoods();
            QDataStream stream(&file);
            int length;
            stream>>length;
            for(int i=0;i<length;i++)
            {
                Goods* goods=new Goods;
                stream>>*goods;
                goodsArray.append(goods);
            }
            file.close();
            ui->stackedWidget->setCurrentIndex(0);
            int row=ui->tableWidgetGoods->rowCount();
            for(int i=0;i<row;i++)
            {
                ui->tableWidgetGoods->removeRow(0);
            }
            ui->tableWidgetGoods->clearContents();
            for(int i=0;i<goodsArray.length();i++)
            {
                showGoods(goodsArray[i],i);
            }
        }
    }
    updateStatus();
}


void MainWindow::on_actionsaveFileAs_triggered()
{
    QString path=QFileDialog::getSaveFileName(this,"save as","../");
    if(false==path.isEmpty())
    {
        QFile file;
        file.setFileName(path);
        bool isOK=file.open(QIODevice::WriteOnly);
        if(true==isOK)
        {
            pathName=path;
            QDataStream stream(&file);
            int length=goodsArray.length();
            stream<<length;
            for(int i=0;i<length;i++)
            {
                stream<<*goodsArray[i];
            }
            file.close();
        }
    }
}


void MainWindow::on_actionsaveFile_triggered()
{
    if(false==pathName.isEmpty())
    {
        QFile file;
        file.setFileName(pathName);
        bool isOK=file.open(QIODevice::WriteOnly);
        if(true==isOK)
        {
            QDataStream stream(&file);
            int length=goodsArray.length();
            stream<<length;
            for(int i=0;i<length;i++)
            {
                stream<<*goodsArray[i];
            }
            file.close();
        }
    }
}


//拓展功能1：基本查询功能（按商品、时间等），查询后部分显示 查询完成后可以回到默认格式
//拓展功能2：添加销售信息时检查是否有货，是否过期
//拓展功能3：一键生成销售数据分析
//拓展功能4：导出pdf格式查询结果
//拓展功能5：排序功能，允许用户点击表头对查询结果进行排序
//拓展功能6：

void MainWindow::on_actioninquiry_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButtonBackToMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateStatus();
}

void MainWindow::on_pushButtonInquiry1_clicked()
{
    ui->tableWidgetGoodsInquiry->clear();

    int type = ui->comboBox->currentIndex();
    QString keyWords=ui->lineEdit->text();
    QList<Goods*> filteredData;  // 存储符合条件的结果列表

    // 遍历数据，筛选出符合条件的行
    if(type==0)
    {
        for (int i=0;i<goodsArray.length();i++)
        {
            if (goodsArray[i]->name==keyWords)// 判断对应列的内容是否包含查询关键字
            {
                filteredData.append(goodsArray[i]);  // 如果包含，则将该行数据加入到结果列表中
            }
        }
    }
    else if(type==1)
    {
        for (int i=0;i<goodsArray.length();i++)
        {
            if (goodsArray[i]->id==keyWords)// 判断对应列的内容是否包含查询关键字
            {
                filteredData.append(goodsArray[i]);  // 如果包含，则将该行数据加入到结果列表中
            }
        }
    }
    else if(type==2)
    {
        for (int i=0;i<goodsArray.length();i++)
        {
            if (goodsArray[i]->factory==keyWords)// 判断对应列的内容是否包含查询关键字
            {
                filteredData.append(goodsArray[i]);  // 如果包含，则将该行数据加入到结果列表中
            }
        }
    }

    // 使用筛选后的数据填充表格
    populateTable_goodsInquiry(filteredData);  // 将筛选结果填充到表格中
}

void MainWindow::populateTable_goodsInquiry(const QList<Goods*> &results)
{
    ui->tableWidgetGoodsInquiry->setRowCount(0);  // 清空表格内容

    QStringList headers = {"商品名称", "编号","总数量","进价","售价" ,"生产厂家","生产日期","保质期"};  // 创建一个QStringList，包含每列的表头文字
    ui->tableWidgetGoodsInquiry->setHorizontalHeaderLabels(headers);  // 将headers设置为表格的水平表头

    // 遍历结果并将其添加到表格中
    for (int i=0;i<results.length();i++)
    {
        int rowIndex = ui->tableWidgetGoodsInquiry->rowCount();  // 获取当前表格的行数
        ui->tableWidgetGoodsInquiry->insertRow(rowIndex);  // 添加新行
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,0,new QTableWidgetItem(results[i]->name));  // 将数据填入对应的单元格
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,1,new QTableWidgetItem(results[i]->id));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,2,new QTableWidgetItem(QString::number(results[i]->totalNumber)));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,3,new QTableWidgetItem(QString::number(results[i]->purchasePrice)));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,4,new QTableWidgetItem(QString::number(results[i]->sellingPrice)));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,5,new QTableWidgetItem(results[i]->factory));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,6,new QTableWidgetItem(results[i]->productionDate.toString("yyyy-MM-dd")));
        ui->tableWidgetGoodsInquiry->setItem(rowIndex,7,new QTableWidgetItem(results[i]->validationDate.toString("yyyy-MM-dd")));
    }
}

void MainWindow::populateTable_salesInquiry(const QList<Sales*> &results)
{
    ui->tableWidgetSalesInquiry->setRowCount(0);  // 清空表格内容
    QStringList headers = {"订单号", "总数量","折扣率","交易日期","联系电话"};  // 创建一个QStringList，包含每列的表头文字
    ui->tableWidgetSalesInquiry->setHorizontalHeaderLabels(headers);  // 将headers设置为表格的水平表头

    // 遍历结果并将其添加到表格中
    for (int i=0;i<results.length();i++)
    {
        int rowIndex = ui->tableWidgetSalesInquiry->rowCount();  // 获取当前表格的行数
        ui->tableWidgetSalesInquiry->insertRow(rowIndex);  // 添加新行
        ui->tableWidgetSalesInquiry->setItem(rowIndex,0,new QTableWidgetItem(results[i]->order));  // 将数据填入对应的单元格
        ui->tableWidgetSalesInquiry->setItem(rowIndex,1,new QTableWidgetItem(QString::number(results[i]->num)));
        ui->tableWidgetSalesInquiry->setItem(rowIndex,2,new QTableWidgetItem(QString::number(results[i]->offRate)));
        ui->tableWidgetSalesInquiry->setItem(rowIndex,3,new QTableWidgetItem(results[i]->tradeDate.toString("yyyy-MM-dd")));
        ui->tableWidgetSalesInquiry->setItem(rowIndex,4,new QTableWidgetItem(results[i]->tel));
    }
}

void MainWindow::populateTable_goodsInquiryAdvanced(const QList<Goods *> &results)
{
    ui->tableWidgetGoodsInquiryAdvanced->setRowCount(0);  // 清空表格内容

    QStringList headers = {"商品名称", "编号","总数量","进价","售价" ,"生产厂家","生产日期","保质期"};  // 创建一个QStringList，包含每列的表头文字
    ui->tableWidgetGoodsInquiryAdvanced->setHorizontalHeaderLabels(headers);  // 将headers设置为表格的水平表头

    // 遍历结果并将其添加到表格中
    for (int i=0;i<results.length();i++)
    {
        int rowIndex = ui->tableWidgetGoodsInquiryAdvanced->rowCount();  // 获取当前表格的行数
        ui->tableWidgetGoodsInquiryAdvanced->insertRow(rowIndex);  // 添加新行
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,0,new QTableWidgetItem(results[i]->name));  // 将数据填入对应的单元格
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,1,new QTableWidgetItem(results[i]->id));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,2,new QTableWidgetItem(QString::number(results[i]->totalNumber)));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,3,new QTableWidgetItem(QString::number(results[i]->purchasePrice)));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,4,new QTableWidgetItem(QString::number(results[i]->sellingPrice)));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,5,new QTableWidgetItem(results[i]->factory));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,6,new QTableWidgetItem(results[i]->productionDate.toString("yyyy-MM-dd")));
        ui->tableWidgetGoodsInquiryAdvanced->setItem(rowIndex,7,new QTableWidgetItem(results[i]->validationDate.toString("yyyy-MM-dd")));
    }
}

void MainWindow::populateTable_salesInquiryAdvanced(const QList<Sales *> &results)
{
    ui->tableWidgetSalesInquiryAdvanced->setRowCount(0);  // 清空表格内容

    QStringList headers = {"订单号", "总数量","折扣率","交易日期","联系电话"};  // 创建一个QStringList，包含每列的表头文字
    ui->tableWidgetSalesInquiryAdvanced->setHorizontalHeaderLabels(headers);  // 将headers设置为表格的水平表头

    // 遍历结果并将其添加到表格中
    for (int i=0;i<results.length();i++)
    {
        int rowIndex = ui->tableWidgetSalesInquiryAdvanced->rowCount();  // 获取当前表格的行数
        ui->tableWidgetSalesInquiryAdvanced->insertRow(rowIndex);  // 添加新行
        ui->tableWidgetSalesInquiryAdvanced->setItem(rowIndex,0,new QTableWidgetItem(results[i]->order));  // 将数据填入对应的单元格
        ui->tableWidgetSalesInquiryAdvanced->setItem(rowIndex,1,new QTableWidgetItem(QString::number(results[i]->num)));
        ui->tableWidgetSalesInquiryAdvanced->setItem(rowIndex,2,new QTableWidgetItem(QString::number(results[i]->offRate)));
        ui->tableWidgetSalesInquiryAdvanced->setItem(rowIndex,3,new QTableWidgetItem(results[i]->tradeDate.toString("yyyy-MM-dd")));
        ui->tableWidgetSalesInquiryAdvanced->setItem(rowIndex,4,new QTableWidgetItem(results[i]->tel));
    }
}

void MainWindow::updateStatus()
{
    ui->statusbar->showMessage(QString("您已登录商品销售系统，目前商品总数为：%1").arg(goodsArray.length()));
}

void MainWindow::on_actionupdate_triggered()
{


}


void MainWindow::on_pushButtonInquirt2_clicked()
{
    ui->tableWidgetSalesInquiry->clear();
    int type = ui->comboBox_2->currentIndex();
    QString keyWords=ui->lineEdit_2->text();
    QList<Sales*> filteredData;  // 存储符合条件的结果列表

    // 遍历数据，筛选出符合条件的行
    if(type==0)
    {
        for (int i=0;i<goodsArray.length();i++)
        {
            for(int j=0;j<goodsArray[i]->salesArray.length();j++)
            {
                if (goodsArray[i]->salesArray[j]->order==keyWords)// 判断对应列的内容是否包含查询关键字
                {
                    filteredData.append(goodsArray[i]->salesArray[j]);  // 如果包含，则将该行数据加入到结果列表中
                }
            }
        }
    }
    else if(type==1)
    {
        for (int i=0;i<goodsArray.length();i++)
        {
            for(int j=0;j<goodsArray[i]->salesArray.length();j++)
            {
                if (goodsArray[i]->salesArray[j]->tel==keyWords)// 判断对应列的内容是否包含查询关键字
                {
                    filteredData.append(goodsArray[i]->salesArray[j]);  // 如果包含，则将该行数据加入到结果列表中
                }
            }
        }
    }
    // 使用筛选后的数据填充表格
    populateTable_salesInquiry(filteredData);  // 将筛选结果填充到表格中
}



void MainWindow::on_pushButtonInquiry1Advanced_clicked()
{
    ui->tableWidgetGoodsInquiryAdvanced->clear();
    QString keyWords=ui->lineEdit_3->text();
    QList<Goods*> filteredData;  // 存储符合条件的结果列表
    // 遍历数据，筛选出符合条件的行
    for (int i=0;i<goodsArray.length();i++)
    {
        for(int j=0;j<8;j++)
        {
            if (goodsArray[i]->getContent(j).contains(keyWords))// 判断对应列的内容是否包含查询关键字
            {
                filteredData.append(goodsArray[i]);
                break; // 如果包含，则将该行数据加入到结果列表中
            }
        }
    }
    populateTable_goodsInquiryAdvanced(filteredData); // 将筛选结果填充到表格中
}

void MainWindow::on_pushButtonInquiry2Advanced_clicked()
{
    ui->tableWidgetSalesInquiryAdvanced->clear();
    QString keyWords=ui->lineEdit_4->text();
    QList<Sales*> filteredData;  // 存储符合条件的结果列表
    // 遍历数据，筛选出符合条件的行
    for (int i=0;i<goodsArray.length();i++)
    {
        for(int j=0;j<goodsArray[i]->salesArray.length();j++)
        {
            for(int k=0;k<5;k++)
            {
                if (goodsArray[i]->salesArray[j]->getContent(k).contains(keyWords))// 判断对应列的内容是否包含查询关键字
                {
                    filteredData.append(goodsArray[i]->salesArray[j]);
                    break; // 如果包含，则将该行数据加入到结果列表中
                }
            }
        }
    }
    populateTable_salesInquiryAdvanced(filteredData); // 将筛选结果填充到表格中
}


void MainWindow::on_pushButtonBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateStatus();
}


void MainWindow::on_actiondataAnalysis_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);

    // 创建页面
    QWidget *page  = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    // 创建商品名称输入框
    QLineEdit *input = new QLineEdit(page);
    input->setPlaceholderText("输入商品名称");
    layout->addWidget(input);
    // 创建一个空的图表对象和图表视图
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
    // 创建一个返回按钮
    QPushButton *backButton = new QPushButton("返回", page);
    layout->addWidget(backButton);

    // 处理输入商品名称并更新图表的逻辑
    connect(input, &QLineEdit::returnPressed, [this, input, chart]()
            {
                QString productName = input->text();

                // 清空之前的图表数据
                chart->removeAllSeries();
                // 获取商品的销售数据
                QList<Sales*> salesList = getGoods(productName)->salesArray;
                //处理异常情况
                if (salesList.isEmpty())
                {
                    QMessageBox::warning(this, "无数据", "未查询到此产品");
                    return;
                }
                QLineSeries *series = new QLineSeries();
                // 将销售数据添加到 QLineSeries 中
                for (int i = 0; i < salesList.length(); i++)
                {
                    series->append(QDateTime(salesList[i]->tradeDate.startOfDay()).toMSecsSinceEpoch(), salesList[i]->num);
                }
                // 将 QLineSeries 添加到图表中
                chart->addSeries(series);
                // 自动生成坐标轴
                chart->createDefaultAxes();
                // 设置X轴为日期
                QDateTimeAxis *axisX = new QDateTimeAxis;
                axisX->setFormat("yyyy-MM-dd");
                axisX->setTitleText("日期");
                chart->setAxisX(axisX, series);
                // 设置Y轴为销售额
                QValueAxis *axisY = new QValueAxis;
                axisY->setTitleText("销量");
                chart->setAxisY(axisY, series);
                // 设置图表标题
                chart->setTitle(  productName+"日销售量变化");
            });

    // 处理返回按钮的逻辑
    connect(backButton, &QPushButton::clicked, [this] ()
        {
        ui->stackedWidget->setCurrentIndex(0);  // 返回主页面
        });

    // 将页面添加到 stackedWidget 并显示
    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);
}

void MainWindow::on_actionnonStock_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    AddGoodsDialog dlg(this);
    dlg.setWindowTitle("补货管理");
    if(QDialog::Accepted==dlg.exec())
    {
        // 获取用户输入的商品名称和补货数量
        QString productName = dlg.myName;  // dlg.myName 获取输入的商品名称
        float additionalQuantity = dlg.additionalNum;  // dlg.additionNum 获取补货的数量
        // 获取对应商品，并更新其库存数量
        Goods* goods = getGoods(productName);
        if (goods)
        {
            // 增加商品的数量
            goods->totalNumber += additionalQuantity;
            for(int i=0;i<ui->tableWidgetGoods->rowCount();i++)
            {
                if(goodsArray[i]==goods)
                {
                    goodsArray[i]->totalNumber=goods->totalNumber;
                    ui->tableWidgetGoods->item(i,2)->setText(QString::number(goodsArray[i]->totalNumber));
                    break;
                }
            }
            // 刷新界面显示（假设需要刷新）
            ui->tableWidgetGoods->update();
        }
        else
        {
            // 如果商品不存在，弹出警告框
            QMessageBox::warning(this, "商品未找到", "无法找到该商品: " + productName);
        }
    }
}



