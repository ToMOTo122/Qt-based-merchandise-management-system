#ifndef ADDGOODSDIALOG_H
#define ADDGOODSDIALOG_H

#include <QDialog>

namespace Ui {
class AddGoodsDialog;
}

class AddGoodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGoodsDialog(QWidget *parent = nullptr);
    ~AddGoodsDialog();
    QString myName;
    float additionalNum;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddGoodsDialog *ui;
};

#endif // ADDGOODSDIALOG_H
