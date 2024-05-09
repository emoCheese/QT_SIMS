#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>
#include <QFile>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建 QApplication 实例后，加载样式表文件
    QFile styleFile(":/res/stylesheet.qss"); // 样式表文件路径
    if (!styleFile.open(QFile::ReadOnly))
    {
        qDebug() << "QSS 文件打开失败";
        return 0;
    }
    QString style = QLatin1String(styleFile.readAll());
    a.setStyleSheet(style);
    styleFile.close();

    MainWindow w;

    QSqlDatabase db = w.getDatabase();

    LoginDialog* loginDlg = new LoginDialog(&w, db);
    if(loginDlg->exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
}
