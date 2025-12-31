#pragma once

#ifndef MESIA_UNDO_ACTION_HPP
#define MESIA_UNDO_ACTION_HPP

#include <QUndoCommand>

namespace Mesia {
    class UndoAction : public QUndoCommand {
    public:
        explicit UndoAction(UndoAction* parent = nullptr) : QUndoCommand(parent) {
        }

        ~UndoAction() override = default;

        void undo() override;
        void redo() override;
    };
}

#endif
