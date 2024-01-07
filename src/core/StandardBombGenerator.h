#pragma once

#include "IBombGenerator.h"

namespace mk::core {
    class StandardBombGenerator : public IBombGenerator {
    public:
        void setSettings(const QSize & size, int bombs) override;
        bool hasBomb(const QPoint & pos) override;

    private:
        [[nodiscard]] int getIndex(const QPoint & p) const;
        [[nodiscard]] bool hasBombAround(const QPoint & pos) const;
        [[nodiscard]] bool indexInMap(int index) const;
        [[nodiscard]] QPoint getRandomPoint() const;

        /// index for (row, col) is row * width + col
        std::vector<bool> m_bombMap;
        QSize m_mapSize;
    };
}


