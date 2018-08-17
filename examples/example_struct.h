#include <jmarkinstall/soa/convertable.h>
using jmarkinstall::soa::convertable;

struct example_struct : public convertable<example_struct, int, int, int>{
    int x, y, z;

    constexpr example_struct(): x(0), y(0), z(0){}

    /// Helper static values referencing column indices for x, y, z.
    constexpr static size_t c_x = 0;
    constexpr static size_t c_y = 1;
    constexpr static size_t c_z = 2;
    /// Construct via tuple of ints.
    constexpr example_struct(const soa_value_type& t) noexcept
    :
        x(std::get<c_x>(t)),
        y(std::get<c_y>(t)),
        z(std::get<c_z>(t))
    {}
    constexpr operator soa_value_type() const{
        return { x, y, z };
    }
};
