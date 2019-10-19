#include "myhtmlpp/collection.hpp"

#include <stdexcept>

myhtmlpp::Collection::Collection(myhtml_collection_t* raw_collection)
    : m_raw_collection(raw_collection) {}

myhtmlpp::Collection::~Collection() {
    myhtml_collection_destroy(m_raw_collection);
}

myhtmlpp::Node myhtmlpp::Collection::operator[](size_t n) const noexcept {
    return Node(m_raw_collection->list[n]);
}

myhtmlpp::Node myhtmlpp::Collection::at(size_t n) const {
    if (n >= size()) {
        throw std::out_of_range("Index out of bounds.");
    }

    return (*this)[n];
}

size_t myhtmlpp::Collection::size() const { return m_raw_collection->length; }

// Iterator
myhtmlpp::Collection::Iterator::Iterator(myhtml_collection_t* c, size_t pos)
    : m_data(c), m_pos(pos), m_node(m_data->list[m_pos]) {}

myhtmlpp::Collection::Iterator& myhtmlpp::Collection::Iterator::operator++() {
    m_node = Node(m_data->list[++m_pos]);

    return *this;
}

myhtmlpp::Collection::Iterator myhtmlpp::Collection::begin() noexcept {
    return Iterator(m_raw_collection, 0);
}

myhtmlpp::Collection::Iterator myhtmlpp::Collection::end() noexcept {
    return Iterator(m_raw_collection, m_raw_collection->length);
}

// ConstIterator
myhtmlpp::Collection::ConstIterator::ConstIterator(myhtml_collection_t* c,
                                                   size_t pos)
    : m_data(c), m_pos(pos), m_node(m_data->list[m_pos]) {}

myhtmlpp::Collection::ConstIterator&
myhtmlpp::Collection::ConstIterator::operator++() {
    m_node = Node(m_data->list[++m_pos]);

    return *this;
}

myhtmlpp::Collection::ConstIterator myhtmlpp::Collection::begin() const
    noexcept {
    return ConstIterator(m_raw_collection, 0);
}

myhtmlpp::Collection::ConstIterator myhtmlpp::Collection::end() const noexcept {
    return ConstIterator(m_raw_collection, m_raw_collection->length);
}
