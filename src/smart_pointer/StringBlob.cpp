#include "smart_pointer/StringBlob.h"
#include <stdexcept>

inline void StringBlob::check(const size_type i) const
{
    if (i >= size())
        throw std::out_of_range("out of bound");
}

StringBlob::StringBlob(std::initializer_list<value_type> list)
  : data{ std::make_shared<container_type>(list) }
{
}

auto StringBlob::size() const -> size_type
{
    return data->size();
}

bool StringBlob::empty() const
{
    return data->empty();
}

void StringBlob::push_back(const_reference str)
{
    return data->push_back(str);
}

void StringBlob::pop_back()
{
    check(0);
    return data->pop_back();
}

auto StringBlob::front() -> reference
{
    check(0);
    return data->front();
}

auto StringBlob::back() -> reference
{
    check(0);
    return data->front();
}

auto StringBlob::front() const -> const_reference
{
    check(0);
    return data->front();
}

auto StringBlob::back() const -> const_reference
{
    check(0);
    return data->back();
}

auto StringBlob::operator[](size_type i) -> reference
{
    return (*data)[i];
}

auto StringBlob::operator[](size_type i) const -> const_reference
{
    return (*data)[i];
}

auto StringBlob::begin() -> iterator
{
    return data->begin();
}

auto StringBlob::end() -> iterator
{
    return data->end();
}

auto StringBlob::begin() const -> const_iterator
{
    return data->begin();
}

auto StringBlob::end() const -> const_iterator
{
    return data->end();
}
