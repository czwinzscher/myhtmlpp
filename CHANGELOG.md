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
