#pragma once

#ifndef MESIA_GRAPHICS_TOOL_MANAGER_HPP
#define MESIA_GRAPHICS_TOOL_MANAGER_HPP

#include "GraphicsTool.hpp"

namespace Mesia {
    class GraphicsScene;
    class GraphicsView;
    class GraphicsToolManager : public QObject {
        Q_OBJECT
    public:
        explicit GraphicsToolManager(GraphicsView* view, GraphicsScene* scene);
        ~GraphicsToolManager() override = default;

        [[nodiscard]] GraphicsTool* findGraphicsTool(GraphicsTool::Type toolType) const;
        [[nodiscard]] GraphicsTool* currentGraphicsTool() const { return m_currentGraphicsTool; }

    public slots:
        void setCurrentGraphicsTool(GraphicsTool::Type type);

    signals:
        void currentGraphicsToolChanged(GraphicsTool* current);

    private:
        GraphicsTool* m_selectTool;
        GraphicsTool* m_moveTool;
        GraphicsTool* m_scaleTool;
        GraphicsTool* m_rotateTool;
        GraphicsTool* m_currentGraphicsTool;
        QVector<GraphicsTool*> m_graphicsTools;
    };
} // namespace Mesia

#endif
