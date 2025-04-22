#pragma once 

struct Color {
    int r;
    int g;
    int b;
    int a;
};

/* Generated Comparator for Color Struct */
struct ColorComparator {
    bool operator()(const Color& lhs, const Color& rhs) const {
        return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) < std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
    }
};

// Calculate these at compile time
constexpr Color RED   { 255, 0,   0,   255 };
constexpr Color GREEN { 0,   255, 0,   255 };
constexpr Color BLUE  { 0,   0,   255, 255 };

constexpr Color WHITE  { 255,   255,   255, 255 };
constexpr Color BLACK  { 0,   0,   0, 255 };
constexpr Color YELLOW  { 255,   255,   0, 255 };

constexpr Color BROWN  { 139, 69, 19, 255 };


/* City/Town Colors */
constexpr Color GRAY  { 128,   128,   128, 255 };
constexpr Color CYAN  { 0, 255, 255, 255 };


