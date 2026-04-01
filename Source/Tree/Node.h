#pragma once

template<typename T>
concept Numeric = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>;

template<Numeric T>
class Node
{
public:
    Node() : value(0), left(nullptr), right(nullptr) {}
    ~Node() = default;

    Node(const T newValue) : value(newValue), left(nullptr), right(nullptr) {}

    Node(const Node* node)
    {
        if (node != nullptr)
        {
            value = node->GetValue();
            if (node->GetLeft() != nullptr)
            {
                left = new Node(node->GetLeft());
            }
            if (node->GetRight() != nullptr)
            {
                right = new Node(node->GetRight());
            }
        }
    }

    Node* GetLeft() const { return left; }

    Node* GetRight() const { return right; }

    void SetLeft(Node* newLeft) { left = newLeft; }

    void SetRight(Node* newRight) { right = newRight; }

    T GetValue() const { return value; }

    void SetValue(const T newValue) { value = newValue; }

private:
    T value = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};