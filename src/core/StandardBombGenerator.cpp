#include "StandardBombGenerator.h"

#include <QRandomGenerator>

void mk::core::StandardBombGenerator::setSettings(const QSize &size, int bombs) {
    Q_UNUSED(bombs);
    m_mapSize = size;
    m_bombMap.clear();
    m_bombMap.resize(size.width() * size.height(), false);

    for (int i = 0; i < bombs; ++i) {
        QPoint bombPos = getRandomPoint();
        /// @todo think about infitity loop here
        while (hasBombAround(bombPos)) {
            bombPos = getRandomPoint();
        }
        m_bombMap[getIndex(bombPos)] = true;
    }
}

bool mk::core::StandardBombGenerator::hasBomb(const QPoint &pos) {
    return m_bombMap[getIndex(pos)];
}

int mk::core::StandardBombGenerator::getIndex(const QPoint &p) const {
    return m_mapSize.width() * p.x() + p.y();
}

bool mk::core::StandardBombGenerator::hasBombAround(const QPoint &pos) const {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            const int index = getIndex(pos + QPoint(dx, dy));
            if (indexInMap(index) && m_bombMap[index]) {
                return true;
            }
        }
    }
    return false;
}

bool mk::core::StandardBombGenerator::indexInMap(int index) const {
    return 0 <= index && index < m_bombMap.size();
}

QPoint mk::core::StandardBombGenerator::getRandomPoint() const {
    return {QRandomGenerator::global()->bounded(0, m_mapSize.width()),
       QRandomGenerator::global()->bounded(0, m_mapSize.height())};
}