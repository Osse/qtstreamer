#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

class QProcess;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void startLivestreamer(const QString& text);
    void handleFinished(int exitCode);
    void appendOutput();
    void appendError();
    void editList();

private:
    void fillStreams();
    QStringList readCacheFile();
    void writeCache();

    Ui::Dialog* ui;
    QProcess* process;
    QString program{"livestreamer"};
    QString cacheFile;
    QStringList streams;
};

#endif // DIALOG_H
