#pragma once

#include "TileButton.h"
#include "IBombGenerator.h"

#include <QWidget>

#include <unordered_map>
#include <memory>

namespace mk::core {
    struct QPointHash {
        std::size_t operator()(const QPoint& point) const {
            return std::hash<int>()(point.x()) ^ std::hash<int>()(point.y());
        }
    };

    class FieldWidget final : public QWidget {
        Q_OBJECT
    public:
        FieldWidget(int rows, int cols,
            std::shared_ptr<IBombGenerator> bombGenerator,
            QWidget * parent = nullptr);

    private slots:
        void bombAroundRequested() const;
        void explosion();

    private:
        void buildForm();
        QPoint getButtonPos(TileButton* b) const;
        std::vector<TileButton*> getButtonsAround(const QPoint & point) const;

        int m_rows;
        int m_cols;
        std::unordered_map<QPoint, TileButton*, QPointHash> m_buttonsPos;
        std::shared_ptr<IBombGenerator> m_bombGenerator;
    };
}

