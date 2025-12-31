#include "VectorPathUtil.hpp"

namespace Mesia {
    QPainterPath fromMeleoaVectorPath(const Meleoa::Geometry::VectorPath &path) {
        QPainterPath result;
        auto elementSize = path.elementCount();
        result.reserve(static_cast<int>(elementSize));

        for (int i = 0; i < elementSize; ++i) {
            auto e = path.elementAt(i);
            switch (e.type) {
                case Meleoa::Geometry::VectorPath::MoveToElement: {
                    result.moveTo(e.x, e.y);
                    break;
                }
                case Meleoa::Geometry::VectorPath::LineToElement: {
                    result.lineTo(e.x, e.y);
                    break;
                }
                case Meleoa::Geometry::VectorPath::CurveToElement: {
                    result.cubicTo(e.x, e.y,
                                   path.elementAt(i + 1).x, path.elementAt(i + 1).y,
                                   path.elementAt(i + 2).x, path.elementAt(i + 2).y);
                    i += 2;
                    break;
                }
                case Meleoa::Geometry::VectorPath::CurveToDataElement: {
                    // do nothing
                    break;
                }
            }
        }
        return result;
    }
} // Mesia