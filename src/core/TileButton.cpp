//
// Created by ryu-min on 07.01.2024.
//

#include "TileButton.h"

mk::core::TileButton::TileButton(QWidget *parent)
    : QPushButton(parent)
    , m_state(State::EMPTY)
{
    setCheckable(true);
}

void mk::core::TileButton::setState(State state) {
    m_state = state;
    switch (m_state) {
        case 
        default: ;
    }
}
