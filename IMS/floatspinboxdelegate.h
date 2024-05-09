#ifndef FLOATSPINBOXDELEGATE_H
#define FLOATSPINBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

class FloatSpinboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FloatSpinboxDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
    // 实现代理需要实现的函数
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // FLOATSPINBOXDELEGATE_H
