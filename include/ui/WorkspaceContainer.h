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
        void onTypeChanged(int index); // ������������ ����� �������

        QComboBox* m_typeCombo;  // ��������� ������ ����
        QStackedWidget* m_stack;      // ��� ����� ��������
        ODV::Viewport3DWorkspace* m_ws3d;      // ��������� �� 3D �������
        ODV::LyapunovWorkspace* m_wsLyap;    // ��������� �� ��������� ��������
        // ���� ��������� ��� ������ ��������
    };
}