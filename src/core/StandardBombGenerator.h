#pragma once

#include "IBombGenerator.h"

namespace mk::core {
    class StandardBombGenerator : public IBombGenerator {
    public:
        void setSize(const QSize & size) override;
        bool hasBomb(const QPoint & pos) override;

    private:

        int getIndex(int row, int col) const;
        /// index for (row, col) is row * width + col
        std::vector<bool> m_bombMap;
        QSize m_mapSize;
    };
}


