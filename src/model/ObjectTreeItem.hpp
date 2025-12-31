#pragma once

#ifndef MKS_OBJECT_TREE_ITEM_HPP
#define MKS_OBJECT_TREE_ITEM_HPP

#include <any>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "Types.hpp"

namespace mks {
    class ObjectTreeItem {
    public:
        enum Type { Layer, Shape, Group };

        explicit ObjectTreeItem(Type type, ObjectTreeItem* parent = nullptr) : m_type(type), m_parent(parent) {}
        virtual ~ObjectTreeItem() = default;

        ObjectTreeItem* parent() const { return m_parent; }
        void setParent(ObjectTreeItem* parent) { m_parent = parent; }

        const std::vector<ObjectTreeItem*>& children() const { return m_children; }
        ObjectTreeItem* child(int index) const { return m_children[index]; }
        std::size_t childCount() const { return m_children.size(); }

        // void appendChild(ObjectTreeItem* child);
        // void insertChild(int index, ObjectTreeItem* child);
        // void removeChild(ObjectTreeItem* child);
        // ObjectTreeItem* takeChild(int index);

        Type type() const { return m_type; }

    protected:
        Type m_type;
        ObjectTreeItem* m_parent;
        std::vector<ObjectTreeItem*> m_children;
    };

    class ShapeTreeItem : public ObjectTreeItem {
    public:
        enum ShapeType { Rectangle, Ellipse, Polyline, Path, Text, Image };
        explicit ShapeTreeItem(ShapeType shapeType, ObjectTreeItem* parent = nullptr) :
            ObjectTreeItem(Shape, parent), m_shapeType(shapeType) {}
        ~ShapeTreeItem() override = default;

        [[nodiscard]] ShapeType shapeType() const { return m_shapeType; }

    private:
        ShapeType m_shapeType;
    };

    class GroupTreeItem : public ObjectTreeItem {
    public:
        explicit GroupTreeItem(ObjectTreeItem* parent = nullptr,
                               std::vector<ObjectTreeItem*> members = std::vector<ObjectTreeItem*>()) :
            ObjectTreeItem(Group, parent), m_members(std::move(members)) {}
        ~GroupTreeItem() override = default;

        [[nodiscard]] std::vector<ObjectTreeItem*> members() const { return m_members; }
        [[nodiscard]] std::size_t memberCount() const { return m_members.size(); }

    private:
        std::vector<ObjectTreeItem*> m_members;
    };

    class LayerTreeItem : public ObjectTreeItem {
    public:
        explicit LayerTreeItem(ObjectTreeItem* parent = nullptr,
                               std::vector<ObjectTreeItem*> elements = std::vector<ObjectTreeItem*>()) :
            ObjectTreeItem(Layer, parent), m_elements(std::move(elements)) {}
        ~LayerTreeItem() override = default;

        [[nodiscard]] std::string name() const noexcept { return m_name; }
        [[nodiscard]] LayerMode mode() const noexcept { return m_mode; }
        [[nodiscard]] float speed() const noexcept { return m_speed; }
        [[nodiscard]] float power() const noexcept { return m_power; }
        [[nodiscard]] bool output() const noexcept { return m_output; }
        [[nodiscard]] bool assistGas() const noexcept { return m_assistGas; }
        [[nodiscard]] bool visible() const noexcept { return m_visible; }

        void setName(std::string name) noexcept { m_name = std::move(name); }
        void setMode(LayerMode mode) noexcept { m_mode = mode; }
        void setSpeed(float speed) noexcept { m_speed = speed; }
        void setPower(float power) noexcept { m_power = power; }
        void setOutput(bool output) noexcept { m_output = output; }
        void setAssistGas(bool assistGas) noexcept { m_assistGas = assistGas; }
        void setVisible(bool visible) noexcept { m_visible = visible; }

        [[nodiscard]] std::vector<ObjectTreeItem*> elements() const { return m_elements; }
        [[nodiscard]] std::size_t size() const { return m_elements.size(); }

    private:
        std::string m_name;
        LayerMode m_mode;
        float m_speed;
        float m_power;
        bool m_output;
        bool m_assistGas;
        bool m_visible;
        std::vector<ObjectTreeItem*> m_elements;
    };
} // namespace mks

#endif
