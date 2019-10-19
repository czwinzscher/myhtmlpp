#pragma once

#include "node.hpp"

#include <myhtml/api.h>

namespace myhtmlpp {

class Collection {
public:
    explicit Collection(myhtml_collection_t* raw_collection);
    ~Collection();

    size_t size() const;

    // implement an Iterator for the collection to enable range based for loops
    class Iterator {
    public:
        Iterator(myhtml_collection_t* c, size_t pos);

        constexpr Node& operator*() { return m_node; }

        Iterator& operator++();

        constexpr bool operator!=(const Iterator& other) const {
            return m_data != other.m_data || m_pos != other.m_pos;
        }

    private:
        myhtml_collection_t* m_data;
        size_t m_pos;
        Node m_node;
    };

    class ConstIterator {
    public:
        ConstIterator(myhtml_collection_t* c, size_t pos);

        constexpr Node& operator*() { return m_node; }

        ConstIterator& operator++();

        constexpr bool operator!=(const ConstIterator& other) const {
            return m_data != other.m_data || m_pos != other.m_pos;
        }

    private:
        myhtml_collection_t* m_data;
        size_t m_pos;
        Node m_node;
    };

    Iterator begin() noexcept;
    Iterator end() noexcept;

    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;

private:
    myhtml_collection_t* m_raw_collection;
};

}  // namespace myhtmlpp
