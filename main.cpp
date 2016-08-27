#include "dialog.h"
#include <QApplication>

#ifdef QT_STATIC
    #include <QtCore/QtPlugin>
    Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
