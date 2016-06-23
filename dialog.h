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
    void startLivestreamer();
    void handleFinished(int exitCode);
    void appendOutput();

private:
    Ui::Dialog* ui;
    QProcess* process;
    QString program{"livestreamer"};
};

#endif // DIALOG_H
