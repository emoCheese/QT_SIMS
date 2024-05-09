#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QCryptographicHash>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent, QSqlDatabase& DB);
    ~LoginDialog();

private:
    QString encryptString(const QString& input);

    bool m_moving;
    QPoint m_last_pos;

    Ui::LoginDialog *ui;
    QSqlDatabase& _DB;
    MainWindow* _w;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void sig_get_role(int);

private slots:
    void on_cancel_btn_clicked();
    void on_login_btn_clicked();
    void on_reg_btn_clicked();
    void on_back_btn_clicked();
    void on_reg_btn_2_clicked();
};

#endif // LOGINDIALOG_H
