#include "TileButton.h"

#include <QMouseEvent>

mk::core::TileButton::TileButton(bool hasBomb, QWidget *parent)
    : QPushButton(parent)
    , m_state(State::EMPTY)
    , m_hasBomb(hasBomb)
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


void mk::core::TileButton::setBombsAround(int bombs) {
    Q_ASSERT(m_state == State::DEFUSED);
    setIcon(QIcon());
    setText(QString::number(bombs));
}

void mk::core::TileButton::mousePressEvent(QMouseEvent *e) {
    QPushButton::mousePressEvent(e);
    const Qt::MouseButton button = e->button();
    if (button == Qt::RightButton) {
        if (State::EMPTY == m_state) {
            setState(State::FLAG);
        } else {
            setState(State::EMPTY);
        }
    } else if (button == Qt::LeftButton) {
        if (m_hasBomb) {
            setState(State::BOMB);
            emit explosion();
        } else {
            setState(State::DEFUSED);
        }
    }
}
