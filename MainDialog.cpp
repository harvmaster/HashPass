#include "MainDialog.h"
#include "ui_MainDialog.h"

#include <QCryptographicHash>
#include <QClipboard>
#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog),
    m_version(4)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_buttonBox_accepted()
{
    // Get the master password (salt)
    QString masterPassword = ui->masterPasswordEdit->text();

    // Get the service
    QString service = ui->serviceEdit->text();

    // Combine the two
    QString combined = masterPassword + "-" + service;

    // Get the hash ready
    QString hashed;

    // If we're using Version 1
    if (m_version == 1) {

        // Generate hash
        hashed = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha1).toHex();

        // Truncate to 16 characters
        hashed.truncate(16);
    }

    // If we're using Version 2
    else if (m_version == 2) {

        // Generate hash
        hashed = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256).toHex();

        // Truncate to 16 characters
        hashed.truncate(16);

        // Make first character a letter
        hashed.replace(0, 1, 't');

        // Replace 4th character with a capital
        hashed.replace(4, 1, 'J');

        // Replace 10th character with a number
        hashed.replace(10, 1, QString::number(3));

        // Replace last character with exclamation
        hashed.replace(15, 1, "!");
    }

    // If we're using Version 3
    else if (m_version == 3) {
        hashed = combined;

        // Generate hash of 65536 rounds
        for (int i = 0; i < 65536; i++) {
            hashed = QCryptographicHash::hash(hashed.toUtf8(), QCryptographicHash::Sha512).toHex();
        }

        // Truncate to 16 characters
        hashed.truncate(16);

        // Make first character a letter
        hashed.replace(0, 1, 'u');

        // Replace 4th character with a capital
        hashed.replace(4, 1, 'J');

        // Replace 10th character with a number
        hashed.replace(10, 1, QString::number(3));

        // Replace last character with exclamation
        hashed.replace(15, 1, "!");
    }

    else if (m_version == 4) {



        hashed = combined;
        QByteArray hash = hashed.toUtf8();

        for (int i = 0; i < 65536; i++) {
            hash = QCryptographicHash::hash(hash, QCryptographicHash::Sha256);
        }

        hashed = hash.toHex();

        /*
        QByteArray temp;
        temp.append(hashed);
        hashed = temp.toHex();
        */

        //replace first character with a letter
        hashed.replace(0, 1, "z");
        //replace 4th character with a Capital
        hashed.replace(3, 1, "H");
        //relace 11tth character with a number
        hashed.replace(10, 1, QString::number(7));
        //replace the last character with exclamation
        hashed.replace(15, 1, "!");

        //shorten the string to 16 characters
        hashed.truncate(16);

    }

    // Save to clipboard
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(hashed);

    // Make sure it is persisted after application exit
    QEvent event(QEvent::Clipboard);
    QApplication::sendEvent(clipboard, &event);
}

void MainDialog::on_switchButton_clicked()
{
    if (m_version == 1) {
        m_version = 2;
        ui->versionLabel->setText("<center>Version 2</center>");
    } else if (m_version == 2) {
        m_version = 3;
        ui->versionLabel->setText("<center>Version 3</center>");
    } else if (m_version == 3) {
        m_version = 4;
        ui->versionLabel->setText("<center>Version 4</center>");
    } else if (m_version == 4) {
        m_version = 1;
        ui->versionLabel->setText("<center>Version 1</center>");
    }
}
