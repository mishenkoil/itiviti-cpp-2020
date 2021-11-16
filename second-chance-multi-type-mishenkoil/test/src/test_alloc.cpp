#include "allocator.h"

#include <gtest/gtest.h>

#include <array>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <tuple>
#include <type_traits>

namespace {

class CheckResult
{
public:
    explicit operator bool() const
    { return m_success; }

    std::ostream & print(std::ostream & strm) const
    {
        return strm << "Expected: " << std::hex << static_cast<unsigned>(m_expected) << ", found: "
            << std::hex << static_cast<unsigned>(m_found) << " at " << std::dec << m_mismatch_index;
    }

    friend std::ostream & operator << (std::ostream & strm, const CheckResult & cr)
    { return cr.print(strm); }

    static CheckResult success(const unsigned char expected)
    { return expected; }
    static CheckResult failure(const std::size_t mismatch_index, const unsigned char expected, const unsigned char found)
    { return {mismatch_index, expected, found}; }

    CheckResult() = default;

private:
    CheckResult(const unsigned char expected_)
        : m_success(true)
        , m_mismatch_index(-1)
        , m_expected(expected_)
        , m_found(expected_)
    {}

    CheckResult(const std::size_t mismatch_index_, const unsigned char expected_, const unsigned char found_)
        : m_success(false)
        , m_mismatch_index(mismatch_index_)
        , m_expected(expected_)
        , m_found(found_)
    {}

    bool m_success = false;
    std::size_t m_mismatch_index = 0;
    unsigned char m_expected = 0;
    unsigned char m_found = 0;
};

// test classes to allocate in a pool
//
template <std::size_t Size>
struct Dummy
{
    static int population;

    static void reset()
    { population = 0; }

    static unsigned char marker() { return 0; }

    std::array<unsigned char, Size> data;

    CheckResult check() const
    {
        for (std::size_t i = 0; i < data.size(); ++i) {
            if (data[i] != marker()) {
                return CheckResult::failure(i, marker(), data[i]);
            }
        }
        return CheckResult::success(marker());
    }

    Dummy()
    {
        data.fill(marker());
        ++population;
    }

    ~Dummy()
    {
        --population;
    }
};

template <std::size_t Size>
int Dummy<Size>::population = 0;

// exactly those variants should be used below in tests
//
#define DUMMY(size, marker_value) \
using D##size = Dummy<size>; \
template <> unsigned char Dummy<size>::marker() \
{ return marker_value; }

    DUMMY(1, 1)
    DUMMY(2, 2)
    DUMMY(4, 4)
    DUMMY(5, 8)
    DUMMY(6, 16)
    DUMMY(10, 32)
    DUMMY(20, 64)
    DUMMY(256, 128)
#undef DUMMY

template <class T>
struct DifferentSizesTest;

template <template <class...> class L, class... Ts>
struct DifferentSizesTest<L<Ts...>> : ::testing::Test
{
    static constexpr std::size_t N = 41;

    static constexpr std::size_t SizeCount = sizeof...(Ts);

    static void reset()
    {
        (Ts::reset(), ...);
    }

    static bool balanced()
    {
        return ((Ts::population == 0) && ... && true);
    }

    static std::string print_balance()
    {
        std::ostringstream strm;
        bool first = true;
        ((strm << (first ? "" : ", ") << sizeof(Ts) << " = " << Ts::population, first = false), ...);
        return strm.str();
    }

    using Indexes = std::index_sequence_for<Ts...>;

    PoolAllocator alloc;
    const std::vector<std::size_t> sizes;

    DifferentSizesTest()
        : alloc(N, {sizeof(Ts)... })
        , sizes({sizeof(Ts)... })
    {}

    template <std::size_t I>
    void destroy(const void * ptr)
    {
        if (ptr != nullptr) {
            using T = std::tuple_element_t<I, L<Ts...>>;
            const auto * t_ptr = static_cast<const T *>(ptr);
            t_ptr->~T();
        }
        alloc.deallocate(ptr);
    }

    template <std::size_t... Is>
    void destroy_impl(const std::size_t i, std::index_sequence<Is...>, const void * ptr)
    {
        ((Is == i ? (destroy<Is>(ptr), 0) : 0), ...);
    }

    void destroy(const std::size_t i, const void * ptr)
    {
        destroy_impl(i, Indexes{}, ptr);
    }

    template <std::size_t I, class... Args>
    auto create(Args &&... args)
        -> std::add_pointer_t<std::tuple_element_t<I, L<Ts...>>>
    {
        using T = std::tuple_element_t<I, L<Ts...>>;
        return new (alloc.allocate(sizeof(T))) T(std::forward<Args>(args)...);
    }

    template <std::size_t... Is, class... Args>
    void * create_impl(const std::size_t i, std::index_sequence<Is...>, Args &&... args)
    {
        void * ptr = nullptr;
        ((Is == i ? ptr = create<Is>(std::forward<Args>(args)...) : nullptr), ...);
        return ptr;
    }

    template <class... Args>
    auto create(const std::size_t i, Args &&... args)
    {
        return create_impl(i, Indexes{}, std::forward<Args>(args)...);
    }

    template <std::size_t I>
    auto check(const void * ptr)
    {
        using T = std::tuple_element_t<I, L<Ts...>>;
        return static_cast<const T *>(ptr)->check();
    }

    template <std::size_t... Is>
    CheckResult check_impl(const std::size_t i, std::index_sequence<Is...>, const void * ptr)
    {
        CheckResult res;
        ((Is == i ? (res = check<Is>(ptr), 0) : 0), ...);
        return res;
    }

    auto check(const std::size_t i, const void * ptr)
    {
        return check_impl(i, Indexes{}, ptr);
    }
};

template <class... Ts>
using L = std::tuple<Ts...>;
using TestedTypes = ::testing::Types<
      L<D1>
    , L<D1, D2>
    , L<D2, D4>
    , L<D1, D2, D5>
    , L<D1, D2, D4, D10>
    , L<D2, D4, D5, D6, D10>
    , L<D2, D4, D10, D20>
    , L<D4, D10, D20, D256>
>;
TYPED_TEST_SUITE(DifferentSizesTest, TestedTypes);

} // anonymous namespace

#define CHECK(i, ptr) \
    const auto check_result = this->check(i, ptr); \
    EXPECT_TRUE(static_cast<bool>(check_result)) << check_result

TYPED_TEST(DifferentSizesTest, create_and_destroy)
{
    this->reset();
    std::vector<const void *> ptrs;
    ptrs.reserve(this->N);
    for (std::size_t i = 0; i < this->N; ) {
        for (std::size_t j = 0; i < this->N && j < this->SizeCount; ++j, ++i) {
            ptrs.push_back(this->create(j));
        }
    }
    std::size_t j = 0;
    for (std::size_t i = 0; i < ptrs.size(); ++i) {
        CHECK(j, ptrs[i]) << " for " << i << " element [" << j << "]";
        this->destroy(j, ptrs[i]);
        ++j;
        if (j == this->SizeCount) {
            j = 0;
        }
    }
    EXPECT_TRUE(this->balanced());
}

TYPED_TEST(DifferentSizesTest, create__destroy_mixed__recreate_by_size_order)
{
    this->reset();
    std::vector<std::pair<const void *, std::size_t>> ptrs;
    ptrs.reserve(this->N);
    for (std::size_t i = 0; i < this->N; ) {
        for (std::size_t j = 0; i < this->N && j < this->SizeCount; ++j, ++i) {
            ptrs.emplace_back(this->create(j), j);
        }
    }

    std::vector<std::size_t> delete_counts(this->SizeCount, 0);
    {
        for (std::size_t i = 0; i < ptrs.size(); i += 3) {
            const auto [ptr, j] = ptrs[i];
            CHECK(j, ptr) << " for " << i << " element [" << j << "]";
            this->destroy(j, ptr);
            ptrs[i].first = nullptr;
            ++delete_counts[j];
        }
    }

    {
        std::size_t j = 0;
        for (const auto count : delete_counts) {
            for (std::size_t i = 0; i < count; ++i) {
                ptrs.emplace_back(this->create(j), j);
            }
            ++j;
        }
    }

    for (std::size_t i = 0; i < ptrs.size(); ++i) {
        const auto [ptr, j] = ptrs[i];
        if (ptr != nullptr) {
            CHECK(j, ptr) << " for " << i << " element [" << j << "]";
            this->destroy(j, ptr);
        }
    }
    EXPECT_TRUE(this->balanced()) << this->print_balance();
}

TYPED_TEST(DifferentSizesTest, create_many__destroy_some_whole_sets__recreate_some)
{
    this->reset();
    std::vector<std::vector<const void *>> ptrs;
    ptrs.reserve(this->N);
    for (std::size_t i = 0; i < this->N; ) {
        auto & group = ptrs.emplace_back();
        group.reserve(this->SizeCount);
        for (std::size_t j = 0; i < this->N && j < this->SizeCount; ++j, ++i) {
            group.push_back(this->create(j));
        }
    }
    std::size_t deleted = 0;
    for (std::size_t i = 0; i < ptrs.size(); ++i) {
        if (i % 2 == 0) {
            auto & group = ptrs[i];
            for (std::size_t j = 0; j < group.size(); ++j) {
                CHECK(j, group[j]) << " for " << i << " group [" << j << "]";
                this->destroy(j, group[j]);
            }
            group.clear();
            ++deleted;
        }
    }
    while (deleted > 0) {
        auto & group = ptrs.emplace_back();
        for (std::size_t i = 0; i < this->SizeCount; ++i) {
            group.push_back(this->create(i));
        }
        --deleted;
    }
    for (const auto & group : ptrs) {
        for (std::size_t i = 0; i < group.size(); ++i) {
            CHECK(i, group[i]);
            this->destroy(i, group[i]);
        }
    }
    EXPECT_TRUE(this->balanced());
}

TYPED_TEST(DifferentSizesTest, create_many__destroy_by_size__recreate_in_reverse_order)
{
    this->reset();
    std::vector<std::vector<const void *>> ptrs(this->SizeCount);
    for (std::size_t i = 0; i < this->N; ) {
        for (std::size_t j = 0; i < this->N && j < this->SizeCount; ++j, ++i) {
            ptrs[j].push_back(this->create(j));
        }
    }

    std::size_t total_deleted = 0;
    std::vector<std::size_t> delete_counts(this->SizeCount, 0);
    {
        std::size_t j = 0;
        for (auto & group : ptrs) {
            for (std::size_t i = 0; i < group.size(); i += 2) {
                ++delete_counts[j];
                ++total_deleted;
                this->destroy(j, group[i]);
                group[i] = nullptr;
            }
            ++j;
        }
    }

    while (total_deleted > 0) {
        for (std::size_t j = 0; j < delete_counts.size(); ++j) {
            if (delete_counts[j] > 0) {
                ptrs[j].push_back(this->create(j));
                --delete_counts[j];
                --total_deleted;
            }
        }
    }

    for (std::size_t j = 0; j < ptrs.size(); ++j) {
        for (std::size_t i = 0; i < ptrs[j].size(); ++i) {
            if (ptrs[j][i] != nullptr) {
                CHECK(j, ptrs[j][i]) << " for " << i << " element [" << j << "]";
            }
            this->destroy(j, ptrs[j][i]);
        }
    }
    EXPECT_TRUE(this->balanced());
}

TYPED_TEST(DifferentSizesTest, create_by_size__delete_some_in_reverse_size_order__recreate_some)
{
    this->reset();
    std::vector<std::pair<const void *, std::size_t>> ptrs;
    ptrs.reserve(this->N);
    const std::size_t part = this->N / this->SizeCount;
    for (std::size_t j = this->SizeCount; j > 0; --j) {
        for (std::size_t i = 0; i < part; ++i) {
            ptrs.emplace_back(this->create(j-1), j-1);
        }
    }
    while (ptrs.size() < this->N) {
        ptrs.emplace_back(this->create(this->SizeCount-1), this->SizeCount-1);
    }

    std::vector<std::size_t> delete_counts(this->SizeCount, 0);
    for (std::size_t i = 0; i < ptrs.size(); i += 3) {
        const auto [ptr, j] = ptrs[i];
        CHECK(j, ptr) << " for " << i << " element [" << j << "]";
        this->destroy(j, ptr);
        ptrs[i].first = nullptr;
        ++delete_counts[j];
    }

    for (std::size_t j = 0; j < this->SizeCount; ++j) {
        for (std::size_t i = 0; i < delete_counts[j]; ++i) {
            ptrs.emplace_back(this->create(j), j);
        }
    }

    for (std::size_t i = 0; i < ptrs.size(); ++i) {
        const auto [ptr, j] = ptrs[i];
        if (ptr != nullptr) {
            CHECK(j, ptr) << " for " << i << " element [" << j << "]";
            this->destroy(j, ptr);
        }
    }
    EXPECT_TRUE(this->balanced());
}
