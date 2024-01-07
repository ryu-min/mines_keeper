//
// Created by ryu-min on 06.01.2024.
//

#include "FieldWidget.h"

#include <QGridLayout>
#include <QPushButton>

mk::core::FieldWidget::FieldWidget(int rows, int cols, QWidget *parent)
    : QWidget(parent), m_rows(rows), m_cols(cols) {
    buildForm();
}

void mk::core::FieldWidget::buildForm() {
    Q_ASSERT(m_rows > 0);
    Q_ASSERT(m_cols > 0);
    auto * gridLayout = new QGridLayout(this);
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            gridLayout->addWidget(new QPushButton(QIcon(":/images/bomb.png"), ""),row, col);
        }
    }
}
