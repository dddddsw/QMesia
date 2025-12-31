#include "GraphicsToolManager.hpp"
#include "GraphicsMoveTool.hpp"
#include "GraphicsResizeTool.hpp"
#include "GraphicsRotateTool.hpp"
#include "GraphicsSelectTool.hpp"
#include "views/canvas/GraphicsScene.hpp"

namespace Mesia {
    GraphicsToolManager::GraphicsToolManager(GraphicsView* view, GraphicsScene* scene) :
        QObject(scene),
        m_selectTool(new GraphicsSelectTool(this)),
        m_moveTool(new GraphicsMoveTool(this)),
        m_scaleTool(new GraphicsResizeTool(this)),
        m_rotateTool(new GraphicsRotateTool(this)),
        m_currentGraphicsTool(m_selectTool)
    {
        const QList tools = {m_selectTool, m_moveTool, m_scaleTool, m_rotateTool};

        for (const auto tool : tools) {
            tool->setView(view);
            tool->setScene(scene);
            connect(tool, &GraphicsTool::requestSwitchTool, this, &GraphicsToolManager::setCurrentGraphicsTool);
        }
    }

    GraphicsTool* GraphicsToolManager::findGraphicsTool(const GraphicsTool::Type toolType) const
    {
        GraphicsTool* target = nullptr;
        switch (toolType) {
            case GraphicsTool::SelectTool:
                target = m_selectTool;
                break;
            case GraphicsTool::MoveTool:
                target = m_moveTool;
                break;
            case GraphicsTool::ResizeTool:
                target = m_scaleTool;
                break;
            case GraphicsTool::RotateTool:
                target = m_rotateTool;
                break;
        }

        return target;
    }

    void GraphicsToolManager::setCurrentGraphicsTool(const GraphicsTool::Type type)
    {
        const auto tool = findGraphicsTool(type);
        if (tool != m_currentGraphicsTool) {
            if (tool) {
                tool->reset();
            }
            qDebug() << "GraphicsTool switch to" << type;
        }
        m_currentGraphicsTool = tool;
    }
} // namespace Mesia
