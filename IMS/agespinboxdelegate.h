#ifndef AGESPINBOXDELEGATE_H
#define AGESPINBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QSpinBox>

class AgeSpinboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit AgeSpinboxDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
    // 实现代理需要实现的函数
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // AGESPINBOXDELEGATE_H
