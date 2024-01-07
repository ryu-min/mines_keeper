
#include "FieldWidget.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>

mk::core::FieldWidget::FieldWidget(int rows, int cols, std::shared_ptr<IBombGenerator> bombGenerator, QWidget *parent)
    : QWidget(parent), m_rows(rows), m_cols(cols), m_bombGenerator(std::move(bombGenerator)) {
    m_bombGenerator->setSize(QSize(m_rows, m_cols));
    buildForm();
}

void mk::core::FieldWidget::bombAroundRequested() const {
    auto * button = qobject_cast<TileButton*>(sender());
    Q_ASSERT(button);
    const QPoint buttonPos = getButtonPos(button);
    int bombsAround = 0;
    for (const auto & b : getButtonsAround(buttonPos)) {
        if (b->hasBomb()) {
            bombsAround++;
        }
    }
    button->setBombsAround(bombsAround);
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
            const auto button = new TileButton(m_bombGenerator->hasBomb(QPoint(row, col)));
            gridLayout->addWidget(button, row, col);
            m_buttonsPos[QPoint(row, col)] = button;
            QObject::connect(button, &mk::core::TileButton::explosion, this, &mk::core::FieldWidget::explosion);
            QObject::connect(button, &mk::core::TileButton::requestBombsAround, this, &mk::core::FieldWidget::bombAroundRequested);
        }
    }
}

QPoint mk::core::FieldWidget::getButtonPos(TileButton *b) const {
    for (const auto& pair : m_buttonsPos) {
        if (pair.second == b) {
            return pair.first;
        }
    }
    Q_ASSERT(false);
}

std::vector<mk::core::TileButton *> mk::core::FieldWidget::getButtonsAround(const QPoint &point) const {
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
