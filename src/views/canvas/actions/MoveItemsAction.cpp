#include "MoveItemsAction.hpp"

namespace Mesia {
    MoveItemsAction::MoveItemsAction(QList<GraphicsItem*> items, const QPointF& delta) : m_items(std::move(items)), m_delta(delta) {
    }

    void MoveItemsAction::undo() {
        for (const auto item : m_items) {
            item->moveBy(-m_delta.y(), -m_delta.x());
        }
    }

    void MoveItemsAction::redo() {
        for (const auto item : m_items) {
            item->moveBy(m_delta.y(), m_delta.x());
        }
    }
} // Mesia