#ifndef USERPAGE_H
#define USERPAGE_H

#include <QDialog>

namespace Ui {
class UserPage;
}

class UserPage : public QDialog
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    ~UserPage();

private:
    Ui::UserPage *ui;
};

#endif // USERPAGE_H
