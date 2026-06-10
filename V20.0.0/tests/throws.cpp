#include <testpp/testpp.hpp>

TEST(Throws, BasicThrowsPass) {
    EXPECT_THROWS(throw std::runtime_error("err"));
}

TEST(Throws, BasicThrowsFailsWhenNoThrow) {
    ASSERT_FAILS(
        EXPECT_THROWS([](){}())
    );
}

void throwsFunc() {
    throw std::logic_error("boom");
}

TEST(Throws, FunctionThrowsPass) {
    EXPECT_THROWS(throwsFunc());
}

void noThrowFunc() {}

TEST(Throws, FunctionNoThrowFails) {
    ASSERT_FAILS(
        EXPECT_THROWS(noThrowFunc())
    );
}

TEST(Throws, CorrectTypePass) {
    EXPECT_THROWS(throw std::runtime_error("err"), std::runtime_error);
}

TEST(Throws, WrongTypeFails) {
    ASSERT_FAILS(
        EXPECT_THROWS(throw std::logic_error("err"), std::runtime_error)
    );
}

TEST(Throws, TypeNoThrowFails) {
    ASSERT_FAILS(
        EXPECT_THROWS([](){}(), std::runtime_error)
    );
}

struct MyError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

TEST(Throws, DerivedTypePass) {
    EXPECT_THROWS(throw MyError("err"), std::runtime_error);
}

TEST(Throws, DoesNotThrowPass) {
    EXPECT_DOES_NOT_THROW([](){}());
}

TEST(Throws, DoesNotThrowFailsStdException) {
    ASSERT_FAILS(
        EXPECT_DOES_NOT_THROW(throw std::runtime_error("err"))
    );
}

TEST(Throws, DoesNotThrowFailsUnknownException) {
    ASSERT_FAILS(
        EXPECT_DOES_NOT_THROW(throw 42)
    );
}

TEST(Throws, ThrowsMessageStdPass) {
    EXPECT_THROWS_MSG(
        throw std::runtime_error("hello"),
        "hello"
    );
}

TEST(Throws, ThrowsMessageStdWrongMessageFails) {
    ASSERT_FAILS(
        EXPECT_THROWS_MSG(
            throw std::runtime_error("actual"),
            "expected"
        )
    );
}

TEST(Throws, ThrowsMessageNoThrowFails) {
    ASSERT_FAILS(
        EXPECT_THROWS_MSG([](){}(), "msg")
    );
}

TEST(Throws, ThrowsMessageStringPass) {
    EXPECT_THROWS_MSG(
        throw std::string("hello"),
        "hello"
    );
}

TEST(Throws, ThrowsMessageStringWrongFails) {
    ASSERT_FAILS(
        EXPECT_THROWS_MSG(
            throw std::string("actual"),
            "expected"
        )
    );
}

TEST(Throws, ThrowsMessageUnknownTypeFails) {
    ASSERT_FAILS(
        EXPECT_THROWS_MSG(
            throw 123,
            "anything"
        )
    );
}

TEST(Throws, InlineExpressionWorks) {
    EXPECT_THROWS(throw std::runtime_error("inline"));
}

int maybeThrow(bool x) {
    if (x) throw std::runtime_error("err");
    return 1;
}

TEST(Throws, ComplexExpressionWorks) {
    EXPECT_THROWS(maybeThrow(true));
}

TEST(Throws, ComplexExpressionFailsWhenNoThrow) {
    ASSERT_FAILS(
        EXPECT_THROWS(maybeThrow(false))
    );
}

TEST(Throws, MessageUsesWhatFromStdException) {
    EXPECT_THROWS_MSG(
        throw std::logic_error("logic"),
        "logic"
    );
}

TEST(Throws, TypeMismatchNonStdExceptionFails) {
    ASSERT_FAILS(
        EXPECT_THROWS(throw 5, std::runtime_error)
    );
}