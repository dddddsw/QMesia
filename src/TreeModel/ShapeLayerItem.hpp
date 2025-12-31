#pragma once

#ifndef MELEOA_SHAPE_LAYER_ITEM_HPP
#define MELEOA_SHAPE_LAYER_ITEM_HPP

#include <string>
#include <utility>
#include "ShapeBaseItem.hpp"

namespace Meleoa {
    class ShapeLayerItem : public ObjectTreeItem {
    public:
        using Color = uint32_t;

        enum Mode {
            Line,
            Fill,
            Image
        };

        explicit ShapeLayerItem(std::string name,
                                const Color color,
                                const Mode mode,
                                ObjectTreeItemPtr parent = {},
                                std::vector<ObjectTreeItemPtr> elements = {}) :
            ObjectTreeItem(Layer, std::move(parent)),
            m_name(std::move(name)),
            m_color(color),
            m_mode(mode),
            m_speed(1000),
            m_power(0.1),
            m_output(true),
            m_assistGas(false),
            m_visible(true),
            m_elements(std::move(elements)) {
        }

        ~ShapeLayerItem() override = default;

        [[nodiscard]] std::string name() const noexcept { return m_name; }
        [[nodiscard]] Color color() const noexcept { return m_color; }
        [[nodiscard]] Mode mode() const noexcept { return m_mode; }
        [[nodiscard]] float speed() const noexcept { return m_speed; }
        [[nodiscard]] float power() const noexcept { return m_power; }
        [[nodiscard]] bool output() const noexcept { return m_output; }
        [[nodiscard]] bool assistGas() const noexcept { return m_assistGas; }
        [[nodiscard]] bool visible() const noexcept { return m_visible; }

        void setName(std::string name) noexcept { m_name = std::move(name); }
        void setMode(const Mode mode) noexcept { m_mode = mode; }
        void setSpeed(const float speed) noexcept { m_speed = speed; }
        void setPower(const float power) noexcept { m_power = power; }
        void setOutput(const bool output) noexcept { m_output = output; }
        void setAssistGas(const bool assistGas) noexcept { m_assistGas = assistGas; }
        void setVisible(const bool visible) noexcept { m_visible = visible; }

        [[nodiscard]] std::vector<ObjectTreeItemPtr> elements() const { return m_elements; }
        [[nodiscard]] std::size_t size() const { return m_elements.size(); }

    private:
        std::string m_name;
        Color m_color;
        Mode m_mode;
        float m_speed;
        float m_power;
        bool m_output;
        bool m_assistGas;
        bool m_visible;
        std::vector<ObjectTreeItemPtr> m_elements;
    };
}

#endif
