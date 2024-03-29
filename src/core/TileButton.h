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
        [[nodiscard]] bool hasBomb() const;
        void defuse();
        [[nodiscard]] bool isDefused() const;

        signals:
        void defused();
        void explosion();

    public slots:
        void setBombsAround(int bombs);

    protected:
        void mousePressEvent(QMouseEvent *e) override;

    private:
        void setState(State state);

        State m_state;
        bool m_hasBomb;
    };
}


