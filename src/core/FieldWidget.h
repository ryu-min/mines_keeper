#pragma once

#include "TileButton.h"

#include <QWidget>

#include <unordered_map>

namespace mk::core {
    class FieldWidget final : public QWidget {
        Q_OBJECT
    public:
        FieldWidget(int rows, int cols,
            QWidget * parent = nullptr);

    private slots:
        void bombAroundRequested() const;
        void explosion();

    private:
        void buildForm();

        int m_rows;
        int m_cols;
        std::unordered_map<TileButton*, QPoint> m_buttonsPos;
    };
}

