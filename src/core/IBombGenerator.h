#pragma once

#include <QSize>
#include <QPoint>

namespace mk::core {
    class IBombGenerator {
    public:
        virtual void setSize(const QSize & size) = 0;
        virtual bool hasBomb(const QPoint & pos) = 0;
    };
}