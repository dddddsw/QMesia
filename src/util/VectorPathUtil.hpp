#pragma once

#ifndef MESIA_VECTOR_PATH_UTIL_HPP
#define MESIA_VECTOR_PATH_UTIL_HPP

#include <QPainterPath>
#include <Meleoa/Geometry/VectorPath.hpp>

namespace Mesia {
    QPainterPath fromMeleoaVectorPath(const Meleoa::Geometry::VectorPath &path);
} // Mesia

#endif
