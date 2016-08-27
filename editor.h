#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QStringList list, QWidget *parent = 0);
    ~Editor();

signals:
    void reload(QStringList);

private:
    Ui::Editor* ui;
};

#endif // EDITOR_H
