#include "agespinboxdelegate.h"

AgeSpinboxDelegate::AgeSpinboxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

QWidget *AgeSpinboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(16);
    editor->setMaximum(35);
    return editor;
}

void AgeSpinboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

void AgeSpinboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    int value = spinbox->value();
    QString str = QString::asprintf("%2d",value);
    model->setData(index, str, Qt::EditRole);
}

void AgeSpinboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
