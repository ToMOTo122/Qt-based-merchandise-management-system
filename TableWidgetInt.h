#ifndef TABLEWIDGETINT_H
#define TABLEWIDGETINT_H

#include <QTableWidgetItem>

class TableWidgetInt : public QTableWidgetItem
{
public:
    // 使用父类的构造函数来初始化文本
    explicit TableWidgetInt(const QString &text)
        : QTableWidgetItem(text) {}
    // 重写小于运算符，用于自定义排序逻辑
    bool operator<(const QTableWidgetItem &other) const override
    {
        return this->text().toFloat() < other.text().toFloat();
    }
};

#endif // TABLEWIDGETINT_H
