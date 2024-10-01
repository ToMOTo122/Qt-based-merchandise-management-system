#ifndef SALESDIALOG_H
#define SALESDIALOG_H

#include "sales.h"

#include <QDialog>

namespace Ui {
class SalesDialog;
}

class SalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesDialog(Sales* sale,QWidget *parent = nullptr);
    ~SalesDialog();
    Sales* sales;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SalesDialog *ui;
};

#endif // SALESDIALOG_H
