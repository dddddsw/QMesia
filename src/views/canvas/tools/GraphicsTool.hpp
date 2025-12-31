#pragma once

#ifndef MESIA_GRAPHICS_TOOL_HPP
#define MESIA_GRAPHICS_TOOL_HPP

#include <QGraphicsItem>
#include "views/canvas/InteractionMode.hpp"

class QGraphicsSceneMouseEvent;
class QKeyEvent;
class QPainter;

namespace Mesia {
    class GraphicsScene;
    class GraphicsView;
    class GraphicsTool : public QObject {
        Q_OBJECT

    public:
        enum Type {
            SelectTool,
            MoveTool,
            ResizeTool,
            RotateTool
        };

        explicit GraphicsTool(Type type, QObject* parent = nullptr);
        ~GraphicsTool() override = default;

        void setScene(GraphicsScene* scene) { m_scene = scene; }
        void setView(GraphicsView* view) { m_view = view; }
        [[nodiscard]] GraphicsScene *scene() const { return m_scene; }
        [[nodiscard]] GraphicsView *view() const { return m_view; }

        [[nodiscard]] Type type() const { return m_type; }

        virtual void reset() {}
        virtual bool drawForeground(QPainter *painter, const QRectF &rect) { return false; }
        virtual bool drawBackground(QPainter *painter, const QRectF &rect) { return false; }
        virtual bool mousePressEvent(QGraphicsSceneMouseEvent *event) { return false; }
        virtual bool mouseMoveEvent(QGraphicsSceneMouseEvent *event) { return false; }
        virtual bool mouseReleaseEvent(QGraphicsSceneMouseEvent *event) { return false; }
        virtual bool mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) { return false; }
        virtual bool keyPressEvent(QKeyEvent* event) { return false; }
        virtual bool keyReleaseEvent(QKeyEvent* event) { return false; }

        static bool isMousePressed(const QGraphicsSceneMouseEvent* event, Qt::MouseButton button);
        static QRectF boundingRect(const QList<QGraphicsItem*>& items);

    signals:
        void requestSwitchTool(Type toolType);

    protected:
        bool hasSelectedItems() const;
        QList<QGraphicsItem*> itemsAt(const QPointF &scenePos) const;

    private:
        GraphicsScene *m_scene;
        GraphicsView *m_view;
        Type m_type;
    };
}

#endif