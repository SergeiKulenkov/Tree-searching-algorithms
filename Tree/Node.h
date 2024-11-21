#pragma once
#include <concepts>
#include <type_traits>

template<typename T>
concept Numeric = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>;

template<typename T>
class Node
{
public:
    Node() : value(0), left(nullptr), right(nullptr)
    {
        static_assert(Numeric<T>, "only numbers are allowed.");
    }

    Node(T newValue) : value(newValue), left(nullptr), right(nullptr)
    {
        static_assert(Numeric<T>, "only numbers are allowed.");
    }

    Node* GetLeft() const { return left; }

    Node* GetRight() const { return right; }

    void SetLeft(Node* newLeft) { left = newLeft; }

    void SetRight(Node* newRight) { right = newRight; }

    T GetValue() const { return value; }

    void SetValue(const T newValue) { value = newValue; }

private:
    T value;
    Node* left;
    Node* right;
};