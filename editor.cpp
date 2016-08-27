#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QStringList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    ui->textEdit->appendPlainText(list.join('\n'));
    connect(ui->pbOk, QPushButton::clicked, this, [&] {
        emit reload(ui->textEdit->toPlainText().split("\n"));
        close();
    });
    connect(ui->pbCancel, &QPushButton::clicked, this, &Editor::close);
}

Editor::~Editor()
{
    delete ui;
}
