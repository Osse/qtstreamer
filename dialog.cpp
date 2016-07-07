#include "dialog.h"
#include "ui_dialog.h"
#include "git_version.h"

#include <QStringList>
#include <QProcess>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    ui->processOutput->setReadOnly(true);
    ui->processOutput->setPlaceholderText("Version " GIT_VERSION ". Ready.");

    if (QStandardPaths::findExecutable(program).isEmpty())
        ui->processOutput->appendPlainText(program + " not found.");
    else
        connect(ui->streamComboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
                this, &Dialog::startLivestreamer);

    readCache();
}

Dialog::~Dialog()
{
    writeCache();
    delete ui;
}

void Dialog::startLivestreamer(const QString& text)
{
    ui->streamComboBox->blockSignals(true);
    ui->processOutput->clear();
    QStringList arguments{"twitch.tv/" + text, ui->qualityComboBox->currentText()};

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
    ui->streamComboBox->blockSignals(false);
}

void Dialog::appendOutput()
{
    char buf[1024] = { 0 };
    process->readLine(buf, 1024);
    QString str(buf);
    ui->processOutput->appendPlainText(str.trimmed());
}

void Dialog::readCache()
{
    auto cacheLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QDir cacheDir(cacheLocation);
    if (!cacheDir.exists())
        cacheDir.mkpath(cacheLocation);

    cacheFile = cacheLocation + "/cache.txt";
    QFile cache(cacheFile);
    if (cache.exists())
    {
        cache.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream textStream(&cache);
        ui->streamComboBox->addItems(textStream.readAll().split("\n", QString::SkipEmptyParts));
    }
}

void Dialog::writeCache()
{
    QFile cache(cacheFile);
    cache.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream textStream(&cache);
    for(int i = 0; i < ui->streamComboBox->count(); i++)
        textStream << ui->streamComboBox->itemText(i) << "\n";
}
