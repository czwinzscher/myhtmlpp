#include "myhtmlpp/collection.hpp"

myhtmlpp::Collection::Collection(myhtml_collection_t* raw_collection)
    : m_raw_collection(raw_collection) {}

myhtmlpp::Collection::~Collection() {
    myhtml_collection_destroy(m_raw_collection);
}
