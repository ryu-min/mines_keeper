#pragma once

#include <QPushButton>

namespace mk::core {
    class TileButton final : public QPushButton {
        Q_OBJECT
    public:
        enum class State {
            EMPTY,
            FLAG,
            BOMB,
            DEFUSED
        };

        explicit TileButton(bool hasBomb, QWidget * parent = nullptr);

        signals:
        void requestBombsAround();
        void explosion();

    public slots:
        void setBombsAround(int bombs);

    protected:
        void mousePressEvent(QMouseEvent *e) override;

    private:
        void setState(State state);

    private:
        State m_state;
        bool m_hasBomb;
    };
}


