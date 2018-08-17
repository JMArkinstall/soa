#ifndef jmarkinstall_tuple_utils_header
#define jmarkinstall_tuple_utils_header

#include <tuple>
#include <functional>

namespace jmarkinstall::tuple_utilities{
    /*!
    @brief A couple of utilities used to manipulate tuples
    
    Implementation is performed inside the impl sub-namespace
    */
    
    namespace impl{
        template<typename T, typename F, size_t... Is>
        constexpr auto map(const T& t, const F& f, std::index_sequence<Is...>){
            return std::make_tuple(
                std::invoke(f, std::get<Is>(t))...
            );
        }

        template<size_t I, typename F, typename T>
        constexpr void foreach(T& t, const F& f){
            std::invoke(f, std::get<I>(t));
            if constexpr(I > 0){
                foreach<I - 1>(t, f);
            }
        }
    }
    /*!
    @brief Map a (constant) tuple through a function, such that
           map(tuple(a,b,c), f) => tuple(f(a), f(b), f(c))
    */
    template<typename function_t, typename tuple_t>
    constexpr auto map(
        const tuple_t& tuple,
        const function_t& function
    ){
        return impl::map(
            tuple,
            function,
            std::make_index_sequence<
                std::tuple_size_v<tuple_t>
            >{}
        );
    }
    /*!
    @brief Modify every element of a tuple via a function. The
           function operates on each tuple element.
    */
    template<typename function_t, typename... tuple_contents>
    constexpr void foreach(
        std::tuple<tuple_contents...>& tuple,
        const function_t& function
    ){
        impl::foreach<sizeof...(tuple_contents) - 1>(
            tuple,
            function
        );
    }
}

#endif
