#pragma once

#ifndef MESIA_MOVE_ITEMS_ACTION_HPP
#define MESIA_MOVE_ITEMS_ACTION_HPP

#include "UndoAction.hpp"
#include "views/canvas/GraphicsItem.hpp"

namespace Mesia {
    class MoveItemsAction : public UndoAction {
    public:
        MoveItemsAction(QList<GraphicsItem *> items, const QPointF &delta);
        ~MoveItemsAction() override = default;

        void undo() override;
        void redo() override;

    private:
        QList<GraphicsItem *> m_items;
        QPointF m_delta;
    };
}

#endif
