#pragma once
#include <list>
#include <optional>
#include <unordered_map>

namespace GpCpplib {
template <typename K, typename V>
class LruCache {
    using KVPair   = std::pair<K, V>;
    using ListType = std::list<KVPair>;
    using MapType  = std::unordered_map<K, typename ListType::const_iterator>;

public:
    using OptionalValueType = std::optional<std::reference_wrapper<const V>>;
    explicit LruCache(std::size_t size) : m_maxSize(size) {}

    template <typename Key, typename Value>
    void put(Key &&key, Value &&value) {
        static_assert(std::is_same_v<Key, K>, "Key type not same as class Key");
        static_assert(std::is_same_v<Value, V>,
                      "Value type not same as class Value");
        auto kv =
            std::make_pair(std::forward<Key>(key), std::forward<Value>(value));
        put(std::move(kv));
    }

    OptionalValueType get(const K &key);

    void remove(const K &key) {
        if (auto it = m_map.find(key); it != m_map.end()) {
            m_list.erase(it->second);
            m_map.erase(it);
            --m_size;
        }
    }

private:
    void              put(KVPair &&data);
    const std::size_t m_maxSize;
    std::size_t       m_size{0};
    ListType          m_list;
    MapType           m_map;
};

template <typename K, typename V>
void LruCache<K, V>::put(KVPair &&kv) {
    // check key is already present in map;
    if (auto it = m_map.find(kv.first); it != m_map.end()) {
        m_list.erase(it->second);
        m_map.erase(it);
        --m_size;
    }

    // Check if cache is full
    if (m_size >= m_maxSize) {
        // Remove last from cache
        auto key = m_list.back().first;
        m_list.pop_back();
        m_map.erase(key);
        --m_size;
    }

    // Now add new Item
    auto key = kv.first;
    m_list.emplace_front(std::move(kv));
    m_map[key] = m_list.begin();
    ++m_size;
}

template <typename K, typename V>
typename LruCache<K, V>::OptionalValueType LruCache<K, V>::get(const K &key) {
    if (auto it = m_map.find(key); it != m_map.end()) {
        if (it->second != m_list.begin()) {
            auto kv = std::move(*it->second);
            m_list.erase(it->second);
            m_map.erase(it);
            m_list.emplace_front(std::move(kv));
            m_map[key] = m_list.begin();
        }
        return OptionalValueType{std::cref(m_list.begin()->second)};
    }
    return {};
}
}  // namespace GpCpplib
