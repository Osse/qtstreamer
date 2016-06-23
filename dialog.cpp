#include "dialog.h"
#include "ui_dialog.h"

#include <QStringList>
#include <QProcess>
#include <QStandardPaths>
#include <QCoreApplication>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->processOutput->setReadOnly(true);

    if (QStandardPaths::findExecutable(program).isEmpty())
        ui->processOutput->appendPlainText(program + " not found.");
    else
        connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Dialog::startLivestreamer);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startLivestreamer()
{
    ui->lineEdit->blockSignals(true);
    ui->processOutput->clear();
    QStringList arguments{"twitch.tv/" + ui->lineEdit->text(), ui->comboBox->currentText()};

    process = new QProcess(this);
    connect(process, SIGNAL(finished(int)), this, SLOT(handleFinished(int)));
    connect(process, &QProcess::readyRead, this, &Dialog::appendOutput);
    process->start(program, arguments);
}

void Dialog::handleFinished(int exitCode)
{
    if (exitCode == 0)
        ui->processOutput->clear();
    delete process;
    ui->lineEdit->blockSignals(false);
}

void Dialog::appendOutput()
{
    char buf[1024] = { 0 };
    process->readLine(buf, 1024);
    QString str(buf);
    ui->processOutput->appendPlainText(str.trimmed());
}
