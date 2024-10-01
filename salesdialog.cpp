#include "salesdialog.h"
#include "ui_salesdialog.h"

SalesDialog::SalesDialog(Sales* sale,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalesDialog)
{
    ui->setupUi(this);
    this->sales=sale;
    if(sales)
    {
        ui->lineEdit_1order->setText(sale->order);
        ui->lineEdit_2num->setText(QString::number(sale->num));
        ui->lineEdit_3offRate->setText(QString::number(sale->offRate));
        ui->dateEdit_4tradeDate->setDate(sale->tradeDate);
        ui->lineEdit_5tel->setText(sale->tel);
    }
}

SalesDialog::~SalesDialog()
{
    delete ui;
}

void SalesDialog::on_buttonBox_accepted()
{
    if(!sales)
    {
        sales= new Sales;
    }
    sales->order=ui->lineEdit_1order->text();
    sales->num=ui->lineEdit_2num->text().toFloat();
    sales->offRate=ui->lineEdit_3offRate->text().toFloat();
    sales->tradeDate=ui->dateEdit_4tradeDate->date();
    sales->tel=ui->lineEdit_5tel->text();
}
