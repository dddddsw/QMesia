#ifndef MESIA_GRAPHICS_SCENE_H
#define MESIA_GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include "tools/GraphicsToolManager.hpp"
#include "actions/UndoAction.hpp"
#include "GraphicsItem.hpp"
#include "GraphicsItemsBoundingBox.hpp"
#include "InteractionModeManager.hpp"

namespace Mesia {
    class GraphicsView;
    class GraphicsTool;
    class InteractionModeManager;
    class GraphicsToolManager;;

    class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        explicit GraphicsScene(QObject *parent);
        ~GraphicsScene() override;

        void appendAction(UndoAction *undoAction);
        void setGraphicsToolManager(GraphicsToolManager *toolManager) { m_graphicsToolManager = toolManager; }
        void setView(GraphicsView *view) { m_view = view; }
        [[nodiscard]] GraphicsView *view() const { return m_view; }
        [[nodiscard]] GraphicsItemsBoundingBox* selectedItemsBoundingBox() { return &m_selectedItemsBoundingBox; }

    protected:
        void drawForeground(QPainter *painter, const QRectF &rect) override;
        void drawBackground(QPainter *painter, const QRectF &rect) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void wheelEvent(QGraphicsSceneWheelEvent *event) override;

    private:
        void setupInteractionModeManager();
        void setupGraphicsToolManager();

    private slots:
        void onSelectionChanged();

    private:
        QSet<QGraphicsItem*> m_recycleItems;

        QSizeF m_size{500, 500};
        QColor m_color;

        InteractionModeManager *m_interactionModeManager;
        GraphicsToolManager *m_graphicsToolManager;
        GraphicsItemsBoundingBox m_selectedItemsBoundingBox;
        GraphicsView *m_view;
    };
}

#endif
