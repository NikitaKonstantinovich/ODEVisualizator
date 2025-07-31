#pragma once

#include <QWidget>
#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "workspaces/Viewport3DWorkspace.h"
#include "workspaces/LyapunovWorkspace.h"

namespace ODV {

    class WorkspaceContainer : public QWidget {
        Q_OBJECT
    public:
        explicit WorkspaceContainer(QWidget* parent = nullptr);

    private:
        void onTypeChanged(int index); // обрабатывает смену вкладки

        QComboBox* m_typeCombo;  // выпадашка выбора типа
        QStackedWidget* m_stack;      // где лежат страницы
        ODV::Viewport3DWorkspace* m_ws3d;      // указатель на 3D вьюпорт
        ODV::LyapunovWorkspace* m_wsLyap;    // указатель на диаграмму Ћ€пунова
        // ЕещЄ указатели под другие страницы
    };
}