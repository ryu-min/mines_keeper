#include <QApplication>
#include <QPushButton>
#include <QDebug>

#include "core/FieldWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mk::core::FieldWidget w(10, 10);
    w.show();
    w.setWindowIcon(QIcon(":/images/bomb.png"));
    return app.exec();
}
