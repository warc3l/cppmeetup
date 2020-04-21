#include <iostream>
#include <range/v3/all.hpp>


#include <range/v3/all.hpp>

// A class that adapts an existing range with a function
template<class Rng, class Fun>
class transform_view
  : public ranges::view_adaptor<transform_view<Rng, Fun>, Rng>
{
    friend ranges::range_access;
    ranges::semiregular_t<Fun> fun_; // Make Fun model Semiregular if it doesn't
    class adaptor : public ranges::adaptor_base
    {
        ranges::semiregular_t<Fun> fun_;
    public:
        adaptor() = default;
        adaptor(ranges::semiregular_t<Fun> const &fun) : fun_(fun) {}
        // Here is where we apply Fun to the elements:
        auto read(ranges::iterator_t<Rng> it) const -> decltype(fun_(*it))
        {
            return fun_(*it);
        }
    };
    adaptor begin_adaptor() const { return {fun_}; }
    adaptor end_adaptor() const { return {fun_}; }
public:
    transform_view() = default;
    transform_view(Rng && rng, Fun fun)
      : transform_view::view_adaptor{std::forward<Rng>(rng)}
      , fun_(std::move(fun))
    {}
};

template<class Rng, class Fun>
transform_view<Rng, Fun> transform(Rng && rng, Fun fun)
{
    return {std::forward<Rng>(rng), std::move(fun)};
}


template<class Rng>
class new_view: public range_adaptor<new_view<Rng>, Rng> {
    private:
        CONCEPT_ASSERT(FordwardIterable<Rng>());

        std::size_t n_;
        friend ranges::range_access;
        class adaptor;

        adaptor begin_adaptor() {
                return adaptor {n_, ranges::end(this->base())};
        }
    public:
        new_view() = default;
        new_view(Rng rng, std::size_t n) : range_adaptor_t<new_view>(std::move(rng)), n_(n){

        }
};

template<class Rng>
class new_view<Rng>::adaptor : public adaptor_base {
    private:
        std::size_t n_;
        ranges::range_sentinel<Rng> end_;
        using adaptor_base::prev;
    public:
        adaptor() = default;
        adaptor(std::size_t n, ranges::range_sentinel_t<Rng> end) : n_(n), end_(end) {

        }

        auto current(ranges::range_iterator_t<Rng> it) const {
            return ranges::view::take(make_range(it, end_), n_);
        }

        void next(ranges::range_iterator_t<Rng> &it) {
            ranges::advance(it, n_, end_);
        }
};


auto chunk(std::size_t n) {
    return make_pipeable([=](auto&& rng) {
            using Rng = decltype(rng);
            return new_view<ranges::view::all_t<Rng>> {
                ranges::view::all(std::forward<Rng>(rng)), n };
    });
}

