#include "userpage.h"
#include "ui_userpage.h"

UserPage::UserPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserPage)
{
    ui->setupUi(this);
}

UserPage::~UserPage()
{
    delete ui;
}
