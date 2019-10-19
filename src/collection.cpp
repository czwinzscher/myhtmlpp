#include "myhtmlpp/collection.hpp"

myhtmlpp::Collection::Collection(myhtml_collection_t* raw_collection)
    : m_raw_collection(raw_collection) {}

myhtmlpp::Collection::~Collection() {
    myhtml_collection_destroy(m_raw_collection);
}

size_t myhtmlpp::Collection::size() { return m_raw_collection->length; }

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
