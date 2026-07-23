#include <algorithm>

struct OnlyEq {
    int v;
    bool operator==(const OnlyEq& other) const { return v == other.v; }
};

struct EqAndLess {
    int v;
    bool operator==(const EqAndLess& other) const { return v == other.v; }
    bool operator<(const EqAndLess& other) const { return v < other.v; }
};

struct EqAndHash {
    int v;
    bool operator==(const EqAndHash& other) const { return v == other.v; }
};

struct BadHash {
    int v;
    bool operator==(const BadHash& other) const { return v == other.v; }
};

namespace std {
    template <>
    struct hash<EqAndHash> {
        size_t operator()(const EqAndHash& x) const {
            return std::hash<int>()(x.v);
        }
    };

    template <>
    struct hash<BadHash> {
        size_t operator()(const BadHash&) const {
            return 0; // EVERYTHING COLLIDES
        }
    };
}