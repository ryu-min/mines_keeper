
#include "FieldWidget.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>

mk::core::FieldWidget::FieldWidget(int rows, int cols, int bombs, std::shared_ptr<IBombGenerator> bombGenerator, QWidget *parent)
    : QWidget(parent), m_rows(rows), m_cols(cols), m_bombGenerator(std::move(bombGenerator)) {
    m_bombGenerator->setSettings(QSize(m_rows, m_cols), bombs);
    buildForm();
}

void mk::core::FieldWidget::bombDefused() {
    auto * button = qobject_cast<TileButton*>(sender());
    Q_ASSERT(button);
    button->setBombsAround(getBombsAround(button));
    defuseAround(button);
}

void mk::core::FieldWidget::explosion() {
    QMessageBox::information(this, "saaaad", "you lose, bro :(");
}

void mk::core::FieldWidget::defuseAround(mk::core::TileButton * button) {
    if (getBombsAround(button) == 0 && !button->hasBomb()) {
        for (const auto & b : getButtonsAround(button)) {
            if (!b->isDefused()) {
                b->defuse();
                defuseAround(b);
            }
        }
    }
}


void mk::core::FieldWidget::buildForm() {
    Q_ASSERT(m_rows > 0);
    Q_ASSERT(m_cols > 0);
    auto * gridLayout = new QGridLayout(this);
    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            const auto button = new TileButton(m_bombGenerator->hasBomb(QPoint(row, col)));
            gridLayout->addWidget(button, row, col);
            m_buttonsPos[QPoint(row, col)] = button;
            QObject::connect(button, &mk::core::TileButton::explosion, this, &mk::core::FieldWidget::explosion);
            QObject::connect(button, &mk::core::TileButton::defused, this, &mk::core::FieldWidget::bombDefused);
        }
    }
}

/// suboptiomal :(
QPoint mk::core::FieldWidget::getButtonPos(TileButton *b) const {
    for (const auto& pair : m_buttonsPos) {
        if (pair.second == b) {
            return pair.first;
        }
    }
    Q_ASSERT(false);
}

std::vector<mk::core::TileButton *> mk::core::FieldWidget::getButtonsAround(mk::core::TileButton * button) const {
    QPoint point = getButtonPos(button);
    std::vector<QPoint> pointsAround;
    pointsAround.reserve(8);
    pointsAround.push_back(point + QPoint(-1, 1));
    pointsAround.push_back(point + QPoint(-1, 0));
    pointsAround.push_back(point + QPoint(-1, -1));
    pointsAround.push_back(point + QPoint(0, -1));
    pointsAround.push_back(point + QPoint(1, -1));
    pointsAround.push_back(point + QPoint(1, 0));
    pointsAround.push_back(point + QPoint(1, 1));
    pointsAround.push_back(point + QPoint(0, 1));

    std::vector<mk::core::TileButton *> res;
    for (const auto & p : pointsAround) {
        auto buttonIt = m_buttonsPos.find(p);
        if (buttonIt != m_buttonsPos.end()) {
            res.push_back(buttonIt->second);
        }
    }
    return res;
}

int mk::core::FieldWidget::getBombsAround(TileButton *button) const {
    int bombsAround = 0;
    for (const auto & b : getButtonsAround(button)) {
        if (b->hasBomb()) {
            bombsAround++;
        }
    }
    return bombsAround;
}
