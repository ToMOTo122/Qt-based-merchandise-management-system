#include "addgoodsdialog.h"
#include "ui_addgoodsdialog.h"

AddGoodsDialog::AddGoodsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGoodsDialog)
{
    ui->setupUi(this);
}

AddGoodsDialog::~AddGoodsDialog()
{
    delete ui;
}

void AddGoodsDialog::on_buttonBox_accepted()
{
    myName=ui->lineEdit->text();
    additionalNum=ui->lineEdit_2->text().toFloat();
}

