#pragma once

#include <myhtml/api.h>

namespace myhtmlpp {

class Collection {
public:
    explicit Collection(myhtml_collection_t* raw_collection);
    ~Collection();

    size_t size();

private:
    myhtml_collection_t* m_raw_collection;
};

}  // namespace myhtmlpp
