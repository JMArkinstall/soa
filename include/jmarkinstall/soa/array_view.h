#ifndef jmarkinstall_soa_array_view_header
#define jmarkinstall_soa_array_view_header

#include <tuple>

namespace jmarkinstall::soa{
    /*!
    @brief A struct used to iterate through values of a single struct member in the SoA.
    @tparam column_index The index of the column to iterate through
                         (in the order defined by the @ref convertable base_members)
    @tparam base_members The type of the soa container.
    */
    template<size_t column_index, typename soa_type>
    struct array_view{
        /// The type of the container representing the struct member
        using container_type = typename std::tuple_element_t<
            column_index,
            typename soa_type::multi_container_type
        >;
        /*!
        @brief Create an array view, via a reference to the SoA container.
        @param t The SoA object to access the containers through.
        */
        array_view(soa_type& t)
        :
            container(
                std::get<column_index>(t.containers)
            )
        {}
        auto begin() const{
            return std::begin(container);
        }
        auto end() const{
            return std::end(container);
        }
        auto begin(){
            return std::begin(container);
        }
        auto end(){
            return std::end(container);
        }    
    private:
        container_type& container;
    };
}

#endif
