#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void on_buttonBox_accepted();

    void on_switchButton_clicked();

private:
    Ui::MainDialog *ui;

    int m_version;
};

#endif // MAINDIALOG_H
