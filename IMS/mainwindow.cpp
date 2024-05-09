#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "const.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 连接数据库
    linkDataBase();

    _adminPage = new AdminPage(this, DB);
    _userPage = new UserPage(this);
    _settingPage = new SettingPage(this);
    _cvDialog = new RoleCltDialog(this);

    ui->stackedWidget->addWidget(_userPage);
    ui->stackedWidget->addWidget(_adminPage);
    ui->stackedWidget->addWidget(_cvDialog);
    ui->stackedWidget->addWidget(_settingPage);

    // 将button添加到 buttonGroup中 设置id与其对应的 stackWidget 页面 id 一致
    _btnGroup.addButton(ui->user, 0);
    _btnGroup.addButton(ui->admin, 1);
    _btnGroup.addButton(ui->roleClt, 2);
    _btnGroup.addButton(ui->setting, 3);
    // 设置按钮互斥
    _btnGroup.setExclusive(true);

    // 设置默认选中的页面
    _btnGroup.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    // 设置页面转换槽函数
    connect(&_btnGroup, &QButtonGroup::buttonClicked, this, &MainWindow::slot_changePage);

}

MainWindow::~MainWindow()
{
    delete ui;
}

const QSqlDatabase& MainWindow::getDatabase() const
{
    return DB;
}

void MainWindow::linkDataBase()
{
    //链接数据库
    DB = QSqlDatabase::addDatabase("QMYSQL");

    DB.setHostName("192.168.154.133");
    DB.setUserName("root");
    DB.setPassword("1234");
    DB.setDatabaseName("Qt_DB");
    if(!DB.open()){
        qDebug() << "未成功链接到数据库";
        ui->admin->setVisible(false);    // 设置数据库页面不可见
    }else{
        qDebug() << "成功链接到数据库";
    }
}

void MainWindow::slot_changePage(QAbstractButton *button)
{
    int idx = _btnGroup.id(button);  // 获取当前 button 设置的 id
    qDebug() << "切换到：" << idx;
                ui->stackedWidget->setCurrentIndex(idx);  // 切换页面
}

// 权限控制，限制访问页面
void MainWindow::slot_permission_clt(int role_id)
{
    if(role_id != ADMIN)
    {
        ui->admin->setVisible(false);
        ui->roleClt->setVisible(false);
    }
}
