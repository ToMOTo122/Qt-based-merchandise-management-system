#ifndef GOODSMAINDIALOG_H
#define GOODSMAINDIALOG_H

#include "goods.h"

#include <QDialog>

namespace Ui {
class GoodsMainDialog;
}

class GoodsMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoodsMainDialog(Goods* good,QWidget *parent = nullptr);
    ~GoodsMainDialog();
    Goods* goods;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GoodsMainDialog *ui;
};

#endif // GOODSMAINDIALOG_H
