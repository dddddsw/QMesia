#include "InteractionModeManager.hpp"

namespace Mesia {
    InteractionModeManager::InteractionModeManager(QObject* parent) : QObject(parent),
                                                                      m_currentMode(InteractionMode::Select) {
    }

    InteractionModeManager::~InteractionModeManager() = default;

    void InteractionModeManager::setCurrentMode(const InteractionMode mode) {
        if (m_currentMode == mode) {
            return;
        }
        m_currentMode = mode;
        emit currentModeChanged(mode);
    }

    InteractionMode InteractionModeManager::currentMode() const {
        return m_currentMode;
    }
} // Mesia