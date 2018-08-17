#ifndef jmarkinstall_soa_struct_view_header
#define jmarkinstall_soa_struct_view_header

#include <tuple>
#include <jmarkinstall/tuple_utilities.h>
#include <functional>

namespace jmarkinstall::soa{
    /*!
    @brief Provides an iterator through structs. This is essentially
    equivalent to a zip iterator, but dereferences to the base struct type
    rather than a tuple.

    The dereference strictly produces a const value type. It may be possible
    to produce a non-const value-like type if there's a version of the
    base struct which stores references rather than values. That's a potential
    future update.

    @tparam soa_type The type of the SoA container.
    */
    template<typename soa_type>
    class struct_iterator{
    public:
        /// The type of the tuple with iterators to the underlying containers.
        using iterator_type = typename soa_type::const_array_iterator_type;
        /// The type of the base_type value to cast to.
        using value_type = typename soa_type::base_type;
        struct_iterator(const iterator_type& iterators)
        :
            iterators(iterators)
        {}
        constexpr value_type operator*() const{
            return value_type(tuple_utilities::map(iterators, [](auto& t){ return *t; }));
        }
        constexpr struct_iterator& operator++(){
            tuple_utilities::foreach(iterators, [](auto& t){ ++t; });
            return *this;
        }
        constexpr struct_iterator& operator--(){
            tuple_utilities::foreach(iterators, [](auto& t){ --t; });
            return *this;
        }
        constexpr size_t operator-(const struct_iterator& other) const{
            return std::distance(std::get<0>(other.iterators), std::get<0>(iterators));
        }
        constexpr bool operator==(const struct_iterator& other) const{
            return iterators == other.iterators;
        }
        constexpr bool operator!=(const struct_iterator& other) const{
            return iterators != other.iterators;
        }
    private:
        iterator_type iterators;
    };

    /*!
    @brief Provides const struct iteration through an SoA container
    @param soa_type The type of the SoA container

    Stores a const reference to the underlying parent's tuple of containers,
    and produces begin() and end() via the @ref struct_iterator.
    */
    template<typename soa_type>
    struct struct_view{
        using multi_container_type = typename soa_type::multi_container_type;
        using iterator_type = struct_iterator<soa_type>;

        const multi_container_type& parent_containers;

        struct_view(const soa_type& t)
        :
            parent_containers(t.containers)
        {}
        
        iterator_type begin() const{
            return iterator_type(
                tuple_utilities::map(
                    parent_containers,
                    [](const auto& t){
                        return std::begin(t);
                    }
                )
            );
        }
        iterator_type end() const{
            return iterator_type(
                tuple_utilities::map(
                    parent_containers,
                    [](const auto& t){
                        return std::end(t);
                    }
                )
            );
        }
    };
}

#endif
