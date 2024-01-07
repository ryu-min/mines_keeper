#pragma once

#include <QPushButton>

namespace mk::core {
    class TileButton final : public QPushButton {
    public:
        enum class State {
            EMPTY,
            FLAG,
            BOMB,
            DEFUSED
        };

        explicit TileButton(QWidget * parent = nullptr);

        signals:
        void requestBombsAround();

    public slots:
        void setBombsAround(int bombs);

    protected:
        void mousePressEvent(QMouseEvent *e) override;

    private:
        void setState(State state);
        [[nodiscard]] State getState() const;

    private:
        State m_state;
    };
}


