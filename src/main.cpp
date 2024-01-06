#include <QApplication>
#include <QPushButton>

#include "core/FieldWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    mk::core::FieldWidget w(10, 10);
    w.show();
    return QApplication::exec();
}
