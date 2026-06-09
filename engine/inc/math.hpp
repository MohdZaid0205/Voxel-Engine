namespace Engine {

    template<typename T> struct Vector2 {
        T x, y;

        constexpr Vector2() : x(0), y(0) {}
        constexpr Vector2(T x, T y) : x(x), y(y) {}

        // Math Operators
        Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
        Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
        Vector2 operator*(T scalar) const { return { x * scalar, y * scalar }; }
        Vector2 operator/(T scalar) const { return { x / scalar, y / scalar }; }

