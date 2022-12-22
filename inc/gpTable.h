#pragma once
#include <__utility/integer_sequence.h>
#include <__utility/piecewise_construct.h>

#include <map>
#include <tuple>
#include <type_traits>

namespace Infra {

template <typename... Ts, size_t... Is>
std::ostream& printTuple(std::ostream& s, const std::tuple<Ts...>& t,
                         std::index_sequence<Is...>) {
    static_assert(sizeof...(Is) == sizeof...(Ts),
                  "Indices must have same number of elements as tuple types!");
    static_assert(sizeof...(Ts) > 0, "Cannot insert empty tuple into stream.");
    auto last = sizeof...(Ts);  // assuming index sequence 0,...,N-1

    //return ((s << std::get<Is>(t) << (Is == last ? "\n" : ", ")), ...);
    return ((s << std::get<Is>(t) << ", "), ...);
}

template <typename Key, typename... Args>
class Table {
public:
    using value_type = std::tuple<Args...>;
    using Container  = std::multimap<Key, value_type>;
    static constexpr const size_t ArgsSize = sizeof...(Args);

    template <typename K, typename... T>
    void emplace(K&& key, T&&... args) {
        static_assert(std::is_same_v<K, Key>);
        m_container.emplace(std::piecewise_construct,
                            std::forward_as_tuple(std::forward<K>(key)),
                            std::forward_as_tuple(std::forward<T>(args)...));
    }

    friend std::ostream& operator<<(std::ostream& stream, const Table& obj) {
        for (const auto& t : obj.m_container) {
            printTuple(stream, t.second, std::index_sequence_for<Args...>{});
        }
        return stream;
    }

    typename Container::iterator begin() { return m_container.begin();}
    typename Container::iterator end() { return m_container.end();}

private:
    Container m_container;
};
}  // namespace Infra
