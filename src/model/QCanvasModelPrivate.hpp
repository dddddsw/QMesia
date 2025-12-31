#pragma once

#ifndef Q_CANVAS_MODEL_PRIVATE_HPP
#define Q_CANVAS_MODEL_PRIVATE_HPP

#include "ObjectTreeModel.hpp"
#include "Types.hpp"

namespace mks {
    class QCanvasModelPrivate {
    public:
        QCanvasModelPrivate() = default;
        ~QCanvasModelPrivate() = default;

        std::vector<std::pair<LayerAttribute, std::string>> m_headers;
        ObjectTreeModel m_treeModel;
    };

} // namespace mks

#endif
