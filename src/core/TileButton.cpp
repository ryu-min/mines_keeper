#include "TileButton.h"

#include <QMouseEvent>

mk::core::TileButton::TileButton(QWidget *parent)
    : QPushButton(parent)
    , m_state(State::EMPTY)
{
    setCheckable(true);
    setState(State::EMPTY);
}

void mk::core::TileButton::setState(State state) {
    m_state = state;
    switch (m_state) {
        case State::FLAG: {
            setIcon(QIcon(":/images/flag.png"));
        } break;
        case State::BOMB: {
            setIcon(QIcon(":/images/bomb.png"));
            setEnabled(false);
            setChecked(true);
        } break;
        case State::EMPTY: {
            setIcon(QIcon());
        } break;
        case State::DEFUSED: {
            setIcon(QIcon());
            setEnabled(false);
            setChecked(true);
            emit requestBombsAround();
        } break;
        default: {
            setIcon(QIcon());
        } break;
    }
}

mk::core::TileButton::State mk::core::TileButton::getState() const {
    return m_state;
}

void mk::core::TileButton::setBombsAround(int bombs) {
    Q_ASSERT(getState() == State::DEFUSED);
    setIcon(QIcon());
    setText(QString::number(bombs));
}

void mk::core::TileButton::mousePressEvent(QMouseEvent *e) {
    QPushButton::mousePressEvent(e);
    const Qt::MouseButton button = e->button();
    if (button == Qt::RightButton) {
        if (State::EMPTY == getState()) {
            setState(State::FLAG);
        } else {
            setState(State::EMPTY);
        }
    } else if (button == Qt::LeftButton) {
        setState(State::BOMB);

    }
}
