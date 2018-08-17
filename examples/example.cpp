#include <jmarkinstall/soa.h>
#include "example_struct.h"

using namespace jmarkinstall;

template<typename T> using my_fixed_array = std::array<T, 20000>;

int main(){
    soa::SoA<my_fixed_array, example_struct> array;

    // Create iteration objects.
    
    auto array_view = soa::array_view<
        example_struct::c_x,
        decltype(array)
    >(array);

    auto struct_view = soa::struct_view(array);

    // Modify values of X in the SoA
    
    int previous_x = 1;
    array.at<example_struct::c_x>(0) = previous_x;

    for(auto& x : array_view){
        x = previous_x++;
    }

    // iterate through structs and print
    for(const example_struct& h : struct_view){
        printf("x: %d, y: %d, z: %d\n", h.x, h.y, h.z);
    }
    return 0;
}
