#pragma once

#include <QSize>
#include <QPoint>

namespace mk::core {
    class IBombGenerator {
    public:
        virtual void setSettings(const QSize & size, int bombs) = 0;
        virtual bool hasBomb(const QPoint & pos) = 0;
    };
}