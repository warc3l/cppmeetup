// based on https://hannes.hauswedell.net/post/2018/04/11/view1/

#include <range/v3/all.hpp>
#include <iostream>

template <typename Rng>
class view_add_constant : public ranges::view_base
{
private:
    struct data_members_t
    {
        Rng urange;
    };
    std::shared_ptr<data_members_t> data_members;

    struct iterator_type : ranges::iterator_t<Rng>
    {
        using base = ranges::iterator_t<Rng>;
        using reference = uint64_t;

        iterator_type() = default;
        iterator_type(base const & b) : base{b} {}

        iterator_type operator++(int)
        {
            return static_cast<base&>(*this)++;
        }

        iterator_type & operator++()
        {
            ++static_cast<base&>(*this);
            return (*this);
        }

        reference operator*() const
        {
            return *static_cast<base>(*this) + 42;
        }
    };

public:
    /* member type definitions */
    using reference         = uint64_t;
    using const_reference   = uint64_t;
    using value_type        = uint64_t;

    using iterator          = iterator_type;
    using const_iterator    = iterator_type;

    /* constructors and deconstructors */
    view_add_constant() = default;
    constexpr view_add_constant(view_add_constant const & rhs) = default;
    constexpr view_add_constant(view_add_constant && rhs) = default;
    constexpr view_add_constant & operator=(view_add_constant const & rhs) = default;
    constexpr view_add_constant & operator=(view_add_constant && rhs) = default;
    ~view_add_constant() = default;

    view_add_constant(Rng && urange)
        : data_members{new data_members_t{std::forward<Rng>(urange)}}
    {}

    /* begin and end */
    iterator begin() const
    {
        return std::begin(data_members->urange);
    }

    auto end() const
    {
        return std::end(data_members->urange);
    }
};

template <typename Rng>
     view_add_constant(Rng &&) -> view_add_constant<Rng>;

struct add_constant_fn
{
    template <typename Rng>
    auto operator()(Rng && urange) const
    {
        return view_add_constant{std::forward<Rng>(urange)};
    }

    template <typename Rng>
    friend auto operator|(Rng && urange, add_constant_fn const &)
    {
        return view_add_constant{std::forward<Rng>(urange)};
    }

};

namespace view
{
    add_constant_fn constexpr add_constant;
}

int main()
{
    std::vector<uint64_t> in{1, 4, 6, 89, 56, 45, 7};

    for (auto && i : in | view::add_constant)
        std::cout << i << ' ';
    std::cout << '\n'; // should print: 43 47 64 131 98 87 49

    // combine it with other views:
    for (auto && i : in | view::add_constant | ranges::view::take(3))
        std::cout << i << ' ';
    std::cout << '\n'; // should print: 43 47 64
}
