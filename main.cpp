#include <QApplication>

#include "viewer.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Viewer viewer;
    viewer.show();
    return QApplication::exec();
}
