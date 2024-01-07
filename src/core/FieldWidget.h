#pragma once

#include <QWidget>

namespace mk::core {
    class FieldWidget final : public QWidget {
    public:
        FieldWidget(int rows, int cols,
            QWidget * parent = nullptr);

    private:
        void buildForm();

        int m_rows;
        int m_cols;
    };
}

