#include <testpp/testpp.hpp>
#include <memory>
#include <optional>

TEST(null, simple_pass) {
    int* p = nullptr;
    EXPECT_NULL(p);
}

TEST(null, simple_fail) {
    int x = 5;
    int* p = &x;
    EXPECT_NOT_NULL(p);
}

TEST(null, Nullptr_Literal) {
    EXPECT_NULL(nullptr);
}

TEST(null, Nullptr_Ternary) {
    int x = 0;
    int* p = x ? &x : nullptr;
    EXPECT_NULL(p);
}

TEST(null, VoidPointer) {
    void* p = nullptr;
    EXPECT_NULL(p);
}

TEST(null, VoidPointer_NonNull) {
    int x = 10;
    void* p = &x;
    EXPECT_NOT_NULL(p);
}

TEST(null, ConstPointer) {
    int* const p = nullptr;
    EXPECT_NULL(p);
}

TEST(null, PointerToConst) {
    const int* p = nullptr;
    EXPECT_NULL(p);
}

TEST(null, FunctionReturn) {
    auto f = []() -> int* { return nullptr; };
    EXPECT_NULL(f());
}

TEST(null, ExpressionChain) {
    int* p = nullptr;
    EXPECT_NULL((p == nullptr ? p : nullptr));
}

TEST(null, UniquePtr_Empty) {
    std::unique_ptr<int> p;
    EXPECT_NULL(p.get());
}

TEST(null, UniquePtr_NonEmpty) {
    auto p = std::make_unique<int>(5);
    EXPECT_NOT_NULL(p.get());
}

TEST(null, sharedPtr_Empty) {
    std::shared_ptr<int> p;
    EXPECT_NULL(p.get());
}

TEST(null, SharedPtr_NonEmpty) {
    auto p = std::make_shared<int>(10);
    EXPECT_NOT_NULL(p.get());
}

TEST(null, DoublePointer) {
    int** pp = nullptr;
    EXPECT_NULL(pp);
}

TEST(null, ArrayDecay) {
    int arr[3] = {1,2,3};
    EXPECT_NOT_NULL(arr);  // decays to pointer → NOT null
}

TEST(null, StringLiteral) {
    const char* s = "hello";
    EXPECT_NOT_NULL(s);
}

TEST(null, Optional_Empty) {
    std::optional<int> o;
    EXPECT_NULL(o.has_value() ? &*o : nullptr);
}

TEST(null, Optional_WithValue) {
    std::optional<int> o = 5;
    EXPECT_NOT_NULL(o.has_value() ? &*o : nullptr);
}

TEST(null, ShouldFail_WhenNonNull) {
    int x = 42;
    int* p = &x;

    ASSERT_FAILS(EXPECT_NULL(p));
}

TEST(null, ShouldFail_WhenNull) {
    int* p = nullptr;

    ASSERT_FAILS(EXPECT_NOT_NULL(p));
}

template <typename T>
T* identity(T* ptr) {
    return ptr;
}

TEST(null, TemplateForwarding) {
    int* p = nullptr;
    EXPECT_NULL(identity(p));
}

TEST(null, ZeroLiteral) {
    int* p = 0;  // old-style null
    EXPECT_NULL(p);
}

TEST(null, MixedExpression) {
    int x = 5;
    int* p = (x > 10) ? &x : nullptr;
    EXPECT_NULL(p);
}

TEST(null, Torture_Pointers) {
    int x = 5;

    int* p1 = nullptr;
    int* p2 = &x;

    EXPECT_NULL(p1);
    EXPECT_NOT_NULL(p2);

    // double pointer
    int** pp = nullptr;
    EXPECT_NULL(pp);

    int* inner = nullptr;
    int** pp2 = &inner;
    EXPECT_NOT_NULL(pp2);   // pointer itself is not null
}

TEST(null, Torture_SmartPointers) {
    std::unique_ptr<int> u1;
    std::unique_ptr<int> u2 = std::make_unique<int>(5);

    EXPECT_NULL(u1);
    EXPECT_NOT_NULL(u2);

    std::shared_ptr<int> s1;
    std::shared_ptr<int> s2 = std::make_shared<int>(10);

    EXPECT_NULL(s1);
    EXPECT_NOT_NULL(s2);
}

TEST(null, Torture_Optional_Basic) {
    std::optional<int> o1;
    std::optional<int> o2 = 5;

    // These will FAIL in your current system unless you added has_value() handling
    EXPECT_NULL(o1);
    EXPECT_NOT_NULL(o2);
}

TEST(null, Torture_Optional_Nested) {
    std::optional<std::unique_ptr<int>> o1;
    std::optional<std::unique_ptr<int>> o2 = std::make_unique<int>(5);

    // semantic ambiguity test
    EXPECT_NULL(o1);          // empty optional
    EXPECT_NOT_NULL(o2);      // optional has value

    // BUT:
    std::optional<std::unique_ptr<int>> o3 = nullptr;

    // 👇 This is a tricky one:
    // optional HAS value, but value is nullptr
    EXPECT_NOT_NULL(o3);  // Should this pass or fail?
}

TEST(null, Torture_WeirdCases) {
    // function pointer
    void (*fn)() = nullptr;
    EXPECT_NULL(fn);

    // array decay
    int arr[3] = {1,2,3};
    int* p = arr;
    EXPECT_NOT_NULL(p);

    // const pointer
    const int* cp = nullptr;
    EXPECT_NULL(cp);
}