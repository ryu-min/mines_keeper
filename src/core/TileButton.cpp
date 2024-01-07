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

bool mk::core::TileButton::hasBomb() const {
    return m_hasBomb;
}

void mk::core::TileButton::defuse() {
    Q_ASSERT(!m_hasBomb);
    setState(State::DEFUSED);
}

bool mk::core::TileButton::isDefused() const {
    return m_state == State::DEFUSED;
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
            emit defused();
        } break;
        default: {
            setIcon(QIcon());
        } break;
    }
}


void mk::core::TileButton::setBombsAround(int bombs) {
    Q_ASSERT(m_state == State::DEFUSED);
    Q_ASSERT(bombs >= 0);
    Q_ASSERT(bombs <= 8);

    if (bombs == 0) {
        setIcon(QIcon());
    } else {
        setIcon(QIcon(QString(":/images/%1.png").arg(bombs)));
    }
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
