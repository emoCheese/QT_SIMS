#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMouseEvent>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "const.h"

LoginDialog::LoginDialog(QWidget *parent, QSqlDatabase& DB)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    , _DB(DB)
{
    ui->setupUi(this);
    _w = static_cast<MainWindow*>(parent);
    this->setAttribute(Qt::WA_DeleteOnClose);   //
    this->setWindowFlag(Qt::SplashScreen);
    ui->stackedWidget->setCurrentIndex(0);

    ui->user_edit->clear();
    ui->pwd_edit->clear();

    connect(this, &LoginDialog::sig_get_role, _w, &MainWindow::slot_permission_clt);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}



void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        // 获取上一次的鼠标光标位置   this->pos()获取窗口左上角相对屏幕左上角的位置
        m_last_pos = event->globalPosition().toPoint() - this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    m_moving = false;
    event->accept();
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    // 鼠标偏离左上角屏幕的位置
    QPoint event_pos = event->globalPosition().toPoint();
    if (m_moving && (event->buttons() & Qt::LeftButton)
        && (event_pos - m_last_pos - this->pos()).manhattanLength() >  QApplication::startDragDistance())
    {
        move(event_pos - m_last_pos);
        m_last_pos = event_pos - this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void LoginDialog::on_cancel_btn_clicked()
{
    this->close();
}


void LoginDialog::on_login_btn_clicked()
{
    // 懒得每次输入用户名和密码，完成时再删这句
    this->accept(); return;


    QString pwd = ui->pwd_edit->text();
    QString name = ui->user_edit->text();
    QString role = ui->roleComboBox->currentText();

    if(name == "" || pwd == "")
    {
        QMessageBox::critical(this, "错误信息", "用户名或密码未填写\n");
        return;
    }
    pwd = encryptString(pwd);

    int role_id;
    if(role == "管理员")
        role_id = ADMIN;
    else
        role_id = NORMAL;

    // TO DO 验证用户名和密码是否正确 否则提示
    QSqlQuery query(_DB);
    QString sql = QString("SELECT * FROM user WHERE username='%1' AND password='%2' AND role_id=%3")
                      .arg(name).arg(pwd).arg(role_id);
    if (!query.exec(sql))
    {
        qDebug() << "查询失败:" << query.lastError().text();
        QMessageBox::critical(this, "错误信息", "系统错误\n");
        return;
    }
    if(query.isValid())
    {
        QMessageBox::critical(this, "错误信息", "用户名或密码错误：\n");
        return;
    }
    if(!query.next())
    {
        qDebug() << "未找到匹配记录";
        QMessageBox::critical(this, "错误信息", "用户名或密码错误：\n");
        return;
    }

    qDebug() <<"查询成功";
    role_id = query.value("role_id").toInt(); // 使用索引获取字段值
    // 或者使用字段名称获取字段值：int role_id = query.value("role_id").toInt();
    qDebug() << "用户权限:" << role_id;

    emit sig_get_role(role_id);
    this->accept();
}

void LoginDialog::on_reg_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void LoginDialog::on_back_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// 加密字符串
QString LoginDialog::encryptString(const QString& input)
{
    // 将输入字符串转换为 QByteArray
    QByteArray byteArray = input.toUtf8();

    // 计算哈希值
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);

    // 将哈希值转换为十六进制字符串
    QString encryptedString = QString(hash.toHex());

    return encryptedString;
}


void LoginDialog::on_reg_btn_2_clicked()
{
    QString name = ui->uname_edit->text();
    QString pwd = encryptString(ui->pwd_edit_2->text());  // 对密码进行加密
    int role_id = -1;
    if(ui->role_box->currentText() == "普通用户")
        role_id = NORMAL;
    else
        role_id = ADMIN;
    QSqlQuery query(_DB);

    // 准备插入语句
    QString sql =
        QString("INSERT INTO user (username,password,role_id) VALUES ('%1','%2',%3)")
            .arg(name)
            .arg(pwd)
            .arg(role_id);

    // 执行插入语句
    if (!query.exec(sql))
    {
        qDebug() << "Insertion failed:" << query.lastError().text();
        return;
    }
    qDebug() << "Insertion successful! " << "用户添加成功！";

    emit sig_get_role(role_id);
    this->accept();
}

