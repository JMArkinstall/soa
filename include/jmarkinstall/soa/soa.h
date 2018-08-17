#ifndef jmarkinstall_soa_soa_header
#define jmarkinstall_soa_soa_header

#include <tuple>
#include <functional>

#include <jmarkinstall/tuple_utilities.h>

namespace jmarkinstall::soa{
    /*!
    @brief A Struct of Arrays wrapping a struct which extends @convertable.
    @tparam container_type the container to use for each struct element.
    @tparam convertable_t a struct to wrap. It must extend @convertable or otherwise
                          expose the soa-prefixed types defined therein.
    */
    template<
        template<class...> class container_type,
        typename convertable_t
    >
    class SoA{
    public:
        /// The type of the tuple holding the element containers
        using multi_container_type =
            typename convertable_t::template soa_container_type<
                container_type
            >;
        /// The type of the tuple holding iterators to the element containers
        using array_iterator_type =
            typename convertable_t::template soa_iterator_type<
                container_type
            >;
        /// The type of the tuple holding const iterators to the element containers
        using const_array_iterator_type =
            typename convertable_t::template soa_const_iterator_type<
                container_type
            >;
        /// The type of the tuple holding values representing the base struct
        using value_type = typename convertable_t::soa_value_type;
        /// The type of the base struct.
        using base_type = typename convertable_t::soa_base_type;

        SoA()
        :
            containers()
        {}
        /*!
         @brief Get a naive size of represented structs
         This is naively judged by the size of the first
         element container.
        */
        size_t size() const{
            return std::get<0>(containers).size();
        }
        /*!
        @brief Get a reference to the value of an element by column and row.
        @tparam column_index The index of the member, indexed by the order of
                             the @ref convertable base_members template parameter.
        @param row_index The index of the row representing the nth struct.
        */
        template<size_t column_index>
        auto& at(const size_t& row_index){
            return std::get<column_index>(containers).at(row_index);
        }
        
        // Expose this container to the struct and array views.
        template<typename>
        friend class soa::struct_view;
        
        template<size_t, typename>
        friend class array_view;
        
    protected:
        multi_container_type containers;
    };
}

#endif
