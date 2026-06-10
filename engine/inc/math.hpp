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

        Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
        Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
        Vector2& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }
        Vector2& operator/=(T scalar) { x /= scalar; y /= scalar; return *this; }

        // Equality Operators
        bool operator==(const Vector2& v) const { return x == v.x && y == v.y; }
        bool operator!=(const Vector2& v) const { return !(*this == v); }
    };

    template<typename T> struct Vector3 {
        T x, y, z;

        constexpr Vector3() : x(0), y(0), z(0) {}
        constexpr Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        // Math Operators
        Vector3 operator+(const Vector3& v) const { return { x + v.x, y + v.y, z + v.z }; }
        Vector3 operator-(const Vector3& v) const { return { x - v.x, y - v.y, z - v.z }; }
        Vector3 operator*(T scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        Vector3 operator/(T scalar) const { return { x / scalar, y / scalar, z / scalar }; }

        Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
        Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
        Vector3& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
        Vector3& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

        // Equality Operators
        bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }
        bool operator!=(const Vector3& v) const { return !(*this == v); }
    };

    // FIXME: move this to api.hpp (may break things)
    // .. (vector aliases) -----------------------------------------------------------+
    using Vec2df = Vector2<f32>;                                  // 2D Float Vector  |
    using Vec3df = Vector3<f32>;                                  // 3D Float Vector  |
    using Vec2di = Vector2<i32>;                                  // 2D Int Vector    |
    using Vec3di = Vector3<i32>;                                  // 3D Int Vector    |
    // -------------------------------------------------------------------------------+
}
