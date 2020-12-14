#pragma once

#include <memory>
#include <variant>
#include <vector>

namespace util {

template <typename T>
class LinkedList {
private:
  struct Node : public std::variant<T> {
    using std::variant<T>::variant;
    std::unique_ptr<Node> next = nullptr;
  };

public:
  struct Iterator {
    friend LinkedList;

    Iterator() = default;
    Iterator(Iterator const&) = default;
    Iterator(Node& n) : _node(&n) {}

    Iterator& operator=(Iterator const&) = default;

    bool operator==(Iterator const& rhs) const {
      return _node == rhs._node;
    }

    bool operator!=(Iterator const& rhs) const {
      return !(*this == rhs);
    }

    Iterator& operator++() {
      _node = _node->next.get();
      return *this;
    }

    T& operator*() const {
      return std::get<T>(*_node);
    }

  private:
    Node* _node = nullptr;
  };

  Iterator begin() const {
    return Iterator(*_begin);
  }

  Iterator end() const {
    return Iterator();
  }

  bool empty() const {
    return !_begin;
  }

  void pushFront(T&& t) {
    auto newElem =
        std::make_unique<Node>(std::in_place_type<T>, std::forward<T>(t));

    newElem->next = std::move(_begin);
    _begin = std::move(newElem);
  }

  Iterator kthTo(std::size_t const k, Iterator const& it) const {
    auto result = begin();
    auto leader = begin();
    for (std::size_t i = 0; i < k && leader != end() && leader != it; ++leader)
      ;

    while (leader != it && leader != end()) {
      ++leader;
      ++result;
    }

    return result;
  }

  Iterator erase(Iterator it, Iterator prevIt = Iterator()) {
    if (it == end())
      return it;

    if (it == begin()) {
      _begin = std::move(it._node->next);
      return Iterator(*_begin);
    }

    if (prevIt == Iterator() || (prevIt._node->next.get() != it._node))
      prevIt = kthTo(1, it);
    prevIt._node->next = std::move(it._node->next);
    return Iterator(*prevIt._node->next);
  }

  std::enable_if_t<std::is_fundamental_v<T>, bool> friend
  operator==(std::vector<T> const& rhs, LinkedList const& lhs) {
    auto it = lhs.begin();
    auto rit = rhs.begin();
    for (; it != lhs.end() && rit != rhs.end(); ++it, ++rit)
      if (*it != *rit)
        return false;

    return it == lhs.end() && rit == rhs.end();
  }

private:
  std::unique_ptr<Node> _begin;
};

} // namespace util
