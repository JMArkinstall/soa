#ifndef jmarkinstall_soa_convertable_header
#define jmarkinstall_soa_convertable_header

#include <tuple>

namespace jmarkinstall::soa{
    /*!
    @brief A struct to extend a data struct with to enable a struct of arrays.
    @tparam base_type The struct to represent (passed to soa::convertable with CRTP)
    @tparam base_members The types of the members in the struct to represent
    */
    template<typename base_type, typename... base_members>
    struct convertable{
        /// The type to view as structs
        using soa_base_type = base_type;
        /// A tuple type holding references to each of the @ref base_members
        using soa_reference_type = std::tuple<base_members&...>;
        /// A tuple type holding values of each of the @ref base_members
        using soa_value_type = std::tuple<base_members...>;
        /// A tuple of containers (specified by container_type),
        /// each container holding a container of one of the @ref base_members
        template<template<class...> class container_type>
        using soa_container_type = std::tuple<
            container_type<base_members>...
        >;
        /// A tuple of iterators to use with @ref soa_container_type.
        template<template<class...> class container_type>
        using soa_iterator_type = std::tuple<
            typename container_type<base_members>::iterator...
        >;
        /// A tuple of const iterators to use with @ref soa_container_type.
        template<template<class...> class raw_container_type>
        using soa_const_iterator_type = std::tuple<
            typename raw_container_type<base_members>::const_iterator...
        >;
    };
}

#endif
