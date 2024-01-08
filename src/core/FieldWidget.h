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
        FieldWidget(int rows, int cols, int bombs,
            std::shared_ptr<IBombGenerator> bombGenerator,
            QWidget * parent = nullptr);

    private slots:
        void bombDefused();
        void explosion();
        void defuseAround(mk::core::TileButton * button);

    private:
        void buildForm();
        [[nodiscard]] QPoint getButtonPos(TileButton* b) const;
        [[nodiscard]] std::vector<TileButton*> getButtonsAround(mk::core::TileButton * button) const;
        [[nodiscard]] int getBombsAround(TileButton * button) const;

        int m_rows;
        int m_cols;
        std::unordered_map<QPoint, TileButton*, QPointHash> m_buttonsPos;
        std::shared_ptr<IBombGenerator> m_bombGenerator;
    };
}

