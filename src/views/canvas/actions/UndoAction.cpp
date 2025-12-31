#include "UndoAction.hpp"

namespace Mesia {
    void UndoAction::undo() {
        QUndoCommand::undo();
    }

    void UndoAction::redo() {
        QUndoCommand::redo();
    }
} // Mesia