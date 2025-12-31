#pragma once

#ifndef MESIA_INTERACTION_MODE_MANAGER_HPP
#define MESIA_INTERACTION_MODE_MANAGER_HPP

#include <QObject>
#include "InteractionMode.hpp"

namespace Mesia {
    class InteractionModeManager : public QObject {
        Q_OBJECT

    public:
        explicit InteractionModeManager(QObject* parent = nullptr);
        ~InteractionModeManager() override;

        void setCurrentMode(InteractionMode mode);
        InteractionMode currentMode() const;

    signals:
        void currentModeChanged(InteractionMode mode);

    private:
        InteractionMode m_currentMode;
    };
}

#endif
