#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QSqlDatabase>

#include "adminpage.h"
#include "userpage.h"
#include "settingpage.h"
#include "rolecltdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const QSqlDatabase &getDatabase() const;

private:
    void linkDataBase();

    Ui::MainWindow *ui;

    QSqlDatabase DB;
    QButtonGroup _btnGroup;
    AdminPage* _adminPage;
    UserPage* _userPage;
    SettingPage* _settingPage;
    RoleCltDialog* _cvDialog;

private slots:
    void slot_changePage(QAbstractButton *button);

public slots:
    void slot_permission_clt(int);
};
#endif // MAINWINDOW_H
