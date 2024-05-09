#ifndef TCOMBOXDELEGATE_H
#define TCOMBOXDELEGATE_H

#include <QStyledItemDelegate>

class TComboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TComboxDelegate(QObject *parent = nullptr);
    void setItems(QStringList itmes, bool editable);


private:
    QStringList m_itemList;
    bool m_editable;

    // QAbstractItemDelegate interface
    // 实现代理需要实现的函数
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TCOMBOXDELEGATE_H
