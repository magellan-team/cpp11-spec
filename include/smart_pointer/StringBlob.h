#ifndef HD9AE3BE5_C7B8_431E_A93F_28C9F8D55FFF
#define HD9AE3BE5_C7B8_431E_A93F_28C9F8D55FFF

#include <string>
#include <memory>
#include <vector>

struct StringBlob
{
    using container_type = std::vector<std::string>;
    using value_type = container_type::value_type;
    using size_type  = container_type::size_type;
    using reference = container_type::reference;
    using const_reference = container_type::const_reference;

    using iterator = container_type::iterator;
    using const_iterator = container_type::const_iterator;

    StringBlob() = default;
    StringBlob(std::initializer_list<value_type> list);

    size_type size() const;
    bool empty() const;

    void push_back(const_reference str);
    void pop_back();

    reference front();
    reference back();

    const_reference front() const;
    const_reference back() const;

    reference operator[](size_type);
    const_reference operator[](size_type) const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

private:
    void check(const size_type i) const;

private:
    std::shared_ptr<container_type> data { std::make_shared<container_type>() };
};

#endif
