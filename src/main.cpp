#include <QApplication>
#include <QDebug>

#include "core/FieldWidget.h"
#include "core/StandardBombGenerator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mk::core::FieldWidget w(20, 20, 40,
        std::make_shared<mk::core::StandardBombGenerator>());
    w.show();
    w.setWindowIcon(QIcon(":/images/bomb.png"));
    return QApplication::exec();
}
