#ifndef MESIA_INTERACTION_MODE_HPP
#define MESIA_INTERACTION_MODE_HPP

namespace Mesia {
    enum class InteractionMode {
        Select,
        Move,
        Scale,
        Rotate,
        DrawRectangle,
        DrawEllipse,
        DrawPolyline,
        DrawBezierCurve
    };
}

#endif