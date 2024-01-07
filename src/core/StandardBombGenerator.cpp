#include "StandardBombGenerator.h"

void mk::core::StandardBombGenerator::setSize(const QSize &size) {
    m_bombMap.clear();
    m_bombMap.resize(size.width() * size.height());
    for (int row = 0; row < size.width(); ++row) {
        for (int col = 0; col < size.height(); ++col) {
            m_bombMap[getIndex(row, col)] = (((row + col) % 3) == 0);
        }
    }
}

bool mk::core::StandardBombGenerator::hasBomb(const QPoint &pos) {
    return m_bombMap[getIndex(pos.x(), pos.y())];
}

int mk::core::StandardBombGenerator::getIndex(int row, int col) const {
    return m_mapSize.width() * row + col;
}

