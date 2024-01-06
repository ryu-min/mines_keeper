#pragma once

#include <QWidget>

namespace mk::core {
    class FieldWidget : public QWidget {
    public:
        FieldWidget(int rows, int cols,
            QWidget * parent = nullptr);

    protected:
        void buildForm();

    protected:
        int m_rows;
        int m_cols;
    };
}

