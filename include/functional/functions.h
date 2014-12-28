#ifndef HA980B189_62DA_454B_B213_0905ED542E61
#define HA980B189_62DA_454B_B213_0905ED542E61

#include <utility>

namespace functional
{
    template <typename Container, class Predicate>
    inline auto find_if(const Container& container, Predicate pred)
        -> decltype(std::begin(container))
    {
        auto first = std::begin(container);
        auto last  = std::end(container);

        for (; first != last; ++first)
            if (pred(*first))
                break;

        return first;
    }

    template <typename Container, typename Unary>
    Unary each(const Container& c, Unary f)
    {
        for (auto &e : c)
            f(e);

        return std::move(f);
    }

    template <typename Container, typename OutputIterator, typename Unary>
    inline OutputIterator map(const Container& c, OutputIterator result, Unary f)
    {
        for (auto &e : c)
            *result++ = f(e);

        return result;
    }

    template <class Container, class T, class Binary>
    inline T reduce(const Container& c, T init, Binary f)
    {
        for (auto &e : c)
            init = f(init, e);
        return init;
    }

    template <typename Container, typename OutputIterator, typename Predicate>
    OutputIterator filter(Container& c, OutputIterator result, Predicate pred)
    {
        for (auto &e : c)
            if (pred(e))
                *result++ = e;

        return result;
    }
}

#endif
