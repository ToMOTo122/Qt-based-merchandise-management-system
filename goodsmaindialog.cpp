#include "goodsmaindialog.h"
#include "ui_goodsmaindialog.h"

GoodsMainDialog::GoodsMainDialog(Goods *good, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GoodsMainDialog)
{
    ui->setupUi(this);
    this->goods=good;
    if(goods)
    {
        ui->lineEdit_1Name->setText(good->name);
        ui->lineEdit_2ID->setText(good->id);
        ui->lineEdit_3TotalNumber->setText(QString::number(goods->totalNumber));
        ui->lineEdit_4PurchasePrice->setText(QString::number(good->purchasePrice));
        ui->lineEdit_5SellingPrice->setText(QString::number(good->sellingPrice));
        ui->lineEdit_6Factory->setText(good->factory);
        ui->dateEdit_7ProducingDate->setDate(good->productionDate);
        ui->dateEdit_8ValidationDate->setDate(good->validationDate);
    }
}

GoodsMainDialog::~GoodsMainDialog()
{
    delete ui;
}

void GoodsMainDialog::on_buttonBox_accepted()
{
    if(!goods)
    {
        goods=new Goods;
    }
    goods->name=ui->lineEdit_1Name->text();
    goods->id=ui->lineEdit_2ID->text();
    goods->totalNumber=ui->lineEdit_3TotalNumber->text().toFloat();
    goods->purchasePrice=ui->lineEdit_4PurchasePrice->text().toFloat();
    goods->sellingPrice=ui->lineEdit_5SellingPrice->text().toFloat();
    goods->factory=ui->lineEdit_6Factory->text();
    goods->productionDate=ui->dateEdit_7ProducingDate->date();
    goods->validationDate=ui->dateEdit_8ValidationDate->date();
}

