#include "rolecltdialog.h"
#include "ui_rolecltdialog.h"
#include <QFileDialog>


RoleCltDialog::RoleCltDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OpenCVDialog)
{
    ui->setupUi(this);
}

RoleCltDialog::~RoleCltDialog()
{
    delete ui;
}

void RoleCltDialog::on_selectImgBtn_clicked()
{
    QString fliter = "图片(*.jpg *.png *.jpeg *.bmp)";
    // 获取到是绝对路径
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个图片", QDir::currentPath(), fliter);
    if(fileName.isEmpty())
    {
        qDebug() << "读取图片失败\n";
        return;
    }

}


void RoleCltDialog::on_processImgBtn_clicked()
{
    cv::Mat img = cv::imread("D:\\QtProject\\IMS\\res\\images\\00.JPG");
    cv::imshow("test",img);
}

