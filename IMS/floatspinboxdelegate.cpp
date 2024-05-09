#include "floatspinboxdelegate.h"

FloatSpinboxDelegate::FloatSpinboxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

QWidget *FloatSpinboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMaximum(100);
    editor->setMinimum(0);
    editor->setDecimals(1);   // 设置显示小数
    return editor;
}

void FloatSpinboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    float value = index.model()->data(index, Qt::EditRole).toFloat();
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    spinbox->setValue(value);
}

void FloatSpinboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
    float value = spinbox->value();
    QString str = QString::asprintf("%.2f",value);
    model->setData(index, str, Qt::EditRole);
}

void FloatSpinboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
