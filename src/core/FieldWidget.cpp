
#include "FieldWidget.h"

#include <QGridLayout>
#include <QMessageBox>

mk::core::FieldWidget::FieldWidget(int rows, int cols, QWidget *parent)
    : QWidget(parent), m_rows(rows), m_cols(cols) {
    buildForm();
}

void mk::core::FieldWidget::bombAroundRequested() const {
    auto * button = qobject_cast<TileButton*>(sender());
    Q_ASSERT(button);
    button->setBombsAround(3);
}

void mk::core::FieldWidget::explosion() {
    QMessageBox::information(this, "saaaad", "you lose, bro :(");
}

void mk::core::FieldWidget::buildForm() {
    Q_ASSERT(m_rows > 0);
    Q_ASSERT(m_cols > 0);
    auto * gridLayout = new QGridLayout(this);
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            const bool hasBomb = ((row + col) % 2 == 0);
            const auto button = new TileButton(hasBomb);
            gridLayout->addWidget(button, row, col);
            m_buttonsPos[button] = QPoint(row, col);
            QObject::connect(button, &mk::core::TileButton::explosion, this, &mk::core::FieldWidget::explosion);
            QObject::connect(button, &mk::core::TileButton::requestBombsAround, this, &mk::core::FieldWidget::bombAroundRequested);
        }
    }
}
