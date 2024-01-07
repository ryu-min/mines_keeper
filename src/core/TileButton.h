#pragma once

#include <QPushButton>

namespace mk::core {
    class TileButton final : public QPushButton {
    public:
        enum class State {
            EMPTY,
            FLAG,
            BOBM
        };

        explicit TileButton(QWidget * parent = nullptr);

    private:
        void setState(State state);

        State m_state;
    };
}


