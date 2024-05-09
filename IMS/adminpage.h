#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include <QToolBar>
#include <QAction>
#include <QSqlRelationalTableModel>
#include <QSql>
#include <QSqlDatabase>
#include <QItemSelectionModel>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>

#include "tcomboxdelegate.h"
#include "floatspinboxdelegate.h"
#include "agespinboxdelegate.h"
#include <QDataWidgetMapper>
#include <QObject>
#include <QSqlRecord>
#include <QFileDialog>

namespace Ui {
class AdminPage;
}

class AdminPage : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent, QSqlDatabase& DB);
    ~AdminPage();

    void showRecordCount();

private:
    void initTableView();
    void getItem();
    void updatePic(const QModelIndex &current);

private:
    Ui::AdminPage *ui;

    QSqlDatabase& m_DB;
    QSqlRelationalTableModel* m_stuInfoTabModel;
    QItemSelectionModel* m_selModel;
    TComboxDelegate delegateSex;      // 自定义代理性别
    FloatSpinboxDelegate scoreDelegate;
    AgeSpinboxDelegate ageDelegate;
    QDataWidgetMapper* dataMapper;
    QSqlRecord record;

private slots:
    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_qureyBtn_clicked();
    void on_showAllBtn_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_saveBtn_clicked();
    void on_insertBtn_clicked();
    void on_deleteBtn_clicked();
    void on_cancelBtn_clicked();
    void on_picBtn_clicked();
};

#endif // ADMINPAGE_H
