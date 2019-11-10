#pragma once

#include "node.hpp"
#include "tree.hpp"

#include <algorithm>
#include <functional>
#include <utility>

namespace myhtmlpp {

template <typename FilterFunc>
class Selection {
public:
    Selection(Tree& tree, FilterFunc filter_func)
        : m_tree(&tree), m_filter_func(filter_func) {}

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(Tree::Iterator tree_iter, Tree::Iterator tree_end,
                 const FilterFunc& filter_func)
            : m_tree_iter(std::move(tree_iter)),
              m_tree_end(std::move(tree_end)),
              m_filter_func(filter_func) {
            skip_failures();
        }

        reference operator*() { return *m_tree_iter; }

        Iterator& operator++() {
            ++m_tree_iter;
            skip_failures();

            return *this;
        }

        bool operator==(const Iterator& other) const {
            return m_tree_iter == other.m_tree_iter;
        }

        constexpr bool operator!=(const Iterator& other) const {
            return !operator==(other);
        }

    private:
        void skip_failures() {
            while (m_tree_iter != m_tree_end &&
                   !std::invoke(m_filter_func, *m_tree_iter)) {
                ++m_tree_iter;
            }
        }

        Tree::Iterator m_tree_iter;
        Tree::Iterator m_tree_end;
        FilterFunc m_filter_func;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator(Tree::ConstIterator tree_iter, Tree::ConstIterator tree_end,
                      const FilterFunc& filter_func)
            : m_tree_iter(std::move(tree_iter)),
              m_tree_end(std::move(tree_end)),
              m_filter_func(filter_func) {
            skip_failures();
        }

        reference operator*() const { return *m_tree_iter; }

        ConstIterator& operator++() {
            ++m_tree_iter;
            skip_failures();

            return *this;
        }

        bool operator==(const ConstIterator& other) const {
            return m_tree_iter == other.m_tree_iter;
        }

        bool operator!=(const ConstIterator& other) const {
            return !operator==(other);
        }

    private:
        void skip_failures() {
            while (m_tree_iter != m_tree_end &&
                   !std::invoke(m_filter_func, *m_tree_iter)) {
                ++m_tree_iter;
            }
        }

        Tree::ConstIterator m_tree_iter;
        Tree::ConstIterator m_tree_end;
        FilterFunc m_filter_func;
    };

    Iterator begin() noexcept {
        return Iterator(m_tree->begin(), m_tree->end(), m_filter_func);
    }

    Iterator end() noexcept {
        return Iterator(m_tree->end(), m_tree->end(), m_filter_func);
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator(m_tree->cbegin(), m_tree->cend(), m_filter_func);
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator(m_tree->cend(), m_tree->cend(), m_filter_func);
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept { return begin(); }

    [[nodiscard]] ConstIterator cend() const noexcept { return end(); }

    [[nodiscard]] std::vector<Node> to_vector() const {
        return std::vector(begin(), end());
    }

    template <typename Func>
    void for_each(Func f) {
        std::for_each(begin(), end(), f);
    }

private:
    Tree* m_tree;
    FilterFunc m_filter_func;
};

}  // namespace myhtmlpp
