#include <iostream>
#include <range/v3/all.hp>

// A range that iterates over all the characters in a
// null-terminated string.
class c_string_range: public ranges::view_facade<c_string_range>
{
    friend ranges::range_access;
    char const * sz_ = "";
    char const & read() const { return *sz_; }
    bool equal(ranges::default_sentinel_t) const { return *sz_ == '\0'; }
    void next() { ++sz_; }
public:
    c_string_range() = default;
    explicit c_string_range(char const *sz) : sz_(sz)
    {
        assert(sz != nullptr);
    }
};

template<class Rngs>
class facade_view : public range_facade<facade_view<Rngs>> {
    private:
        friend ranges::range_acces;

        std::vector<ranges::range_value_t<Rngs>> rngs_;

        struct cursor;
        cursor begin_cursor() {
            return {0, &rngs_, ranges::view::transform(rngs_, ranges::begin)};
        }

    public:
        facade_view() = default;
        explicit facade_view(Rngs rngs) : rngs_(std::move(rngs)) {}
};



template<class Rngs>
struct facade_view<Rngs>::cursor {
    private:
        std::size_t n;
        std::vector<range_value_t<Rngs>> *rngs_;
        std::vector<range_iterator_t<range_value_t<Rngs>>> its_;

        decltype(auto) current() const {
            return *its_[n_];
        }

        void next() {
            if (0 == (++n) %= its_.size())
                for_each(its_, [](auto& it) { ++it; });
        }

        bool done() const {
            return n_ == 0 && its_.end() != mismatch(its_,
            ranges::view::transform(*rngs_, ranges::end), std::not_equal_to<>).first;
        }

        CONCEPT_REQUIRES(ForwardIterable<ranges_value_t<Rngs>>())
        bool equal(cursor const& that) const {
            return n_ == that.n_ && its_ == that.its_;
        }
};

auto interlave() {
    return make_pipeable([](auto && rngs) {
            using Rngs = decltype(rngs);
            return facade_view<ranges::view::all_t<Rngs>>(
                ranges::view::all(std::forward<Rngs>(rngs));
            );
    });
}


