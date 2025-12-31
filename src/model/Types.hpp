#ifndef MKS_CANVAS_TYPES_HPP
#define MKS_CANVAS_TYPES_HPP

namespace mks {

enum class LayerAttribute : int {
    Name,
    Mode,
    Speed,
    Power,
    Output,
    AssistGas,
    Visibility
};

enum class LayerMode {
    Line,
    Image
};

}

#endif //TYPES_HPP
