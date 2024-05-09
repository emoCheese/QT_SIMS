#ifndef ROLECLTDIALOG_H
#define ROLECLTDIALOG_H

#include <QDialog>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class OpenCVDialog;
}

class RoleCltDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoleCltDialog(QWidget *parent = nullptr);
    ~RoleCltDialog();

private slots:


    void on_selectImgBtn_clicked();

    void on_processImgBtn_clicked();

private:
    Ui::OpenCVDialog *ui;

    cv::Mat srcImg, grayImg, noiseImg;
};

#endif // ROLECLTDIALOG_H
