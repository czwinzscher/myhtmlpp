# 2.0.0 (2019-11-14)
## Tree
- add `select(selector)`
- add `filter(predicate)`
- add `find_by_tag(tag_id)`
- add `find_by_tag(tag_string)`
- add `find_by_id(id)`
- add `find_by_class(class)`
- add `find_by_attr(key, value)`
- remove `create_node`
## Node
- `at(key)` returns optional with value of attribute
- `operator[]` return value of attribute, does not do any error checking
- `is_text_node()` returns true if tag is one one `TEXT_`, `COMMENT_`, `STYLE`
- add `inner_text()`
- rename `tag_string()` to `tag_name()`
- remove `set_namespace`
- remove `add_child`
- remove `insert_before`
- remove `insert_after`
- remove `remove`
- remove `add_attribute`
- remove `remove_attribute_by_key`
## Attribute
- add `operator<<`, gives out key="value"
- remove `set_namespace`

# 1.1.0 (2019-11-10)
## parser
- all thrown exceptions have a `status_code()` method to return the mystatus_t value
## Tree
- add `find_all(tag_string)` and `find_all(tag_id)` to filter nodes by tag
## Node
- add `has_attribute(key)`

# 1.0.0 (2019-11-08)
## parser
- remove `parse_with_options` and `parse_fragment_with_options`
- add default parameters to `parse` and `parse_fragment` for options
- set default queue_size to 4096
- use custom exceptions to indicate errors
## Tree
- mark copy constructor and copy assignment operator as `delete`
- invalidate Tree after moving (set pointers to nullptr)
- remove `pretty_html`
- add `operator==` for iterators
## Node
- remove `pretty_html_deep`
- invalidate Node after moving (set pointer to nullptr)
- add `operator==` for iterators
- rename `ns` to `get_namespace`
- rename `set_ns` to `set_namespace`
- add `siblings` method
- add `has_attributes` method
- add `is_text_node` method
## Attribute
- invalidate Attribute after moving (set pointer to nullptr)
- rename `ns` to `get_namespace`
- rename `set_ns` to `set_namespace`
## other
- use an enum class wrapper for all tags, namespaces and options

# 0.2.1 (2019-11-05)
- fix the `MYHTMLPP_LIBRARIES` variable in `CMakeLists.txt`
- add more infos to readme

# 0.2.0 (2019-11-04)
- add documentation, which can be generated with `make doc`
- add `good` method for Tree
- add `good` method for Attribute
- add structured bindings [key, value] support for Attribute
- The second parameter of `Tree::create_node` defaults to `MyHTML_NAMESPACE_HTML`

# 0.1.0 (2019-11-04)
- first pre-release
