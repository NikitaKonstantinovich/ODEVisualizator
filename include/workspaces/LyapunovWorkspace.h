#ifndef LYAPUNOVWORKSPACE_H
#define LYAPUNOVWORKSPACE_H

#include <QWidget>

namespace ODV {
    class LyapunovWorkspace : public QWidget {
        Q_OBJECT
    public:
        explicit LyapunovWorkspace(QWidget* parent = nullptr)
            : QWidget(parent)
        {
        }
    };
}
#endif // LYAPUNOVWORKSPACE_H
