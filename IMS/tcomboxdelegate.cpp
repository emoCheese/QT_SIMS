#include "tcomboxdelegate.h"
#include <QComboBox>

TComboxDelegate::TComboxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void TComboxDelegate::setItems(QStringList items, bool editable)
{
    m_itemList = items;
    m_editable = editable;
}

QWidget *TComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox * editor = new QComboBox(parent);
    editor->setEditable(m_editable);                     // 设置是否可编辑
    for(const auto& i : m_itemList)                      // 初始化字符串下拉列表
    {
        editor->addItem(i);
    }
    return editor;
}

void TComboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString  str = index.model()->data(index, Qt::EditRole).toString();  // 从模型获取数据
    QComboBox * comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);
}

void TComboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox * comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);               // 保存数据到模型
}

void TComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);  // 设置组件大小
}
