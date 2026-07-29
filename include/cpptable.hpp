/**
 * @file ql_dataset.hpp
 * @brief A file that defines a `libds` query language data set for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "cppmap.hpp"
#include "cpputils.hpp"
#include "cppvector.hpp"

#include <concepts>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <ranges>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cpptable.hpp>


namespace dscpp {

class TableElementBase
    :   public Element::Base
{
public:
    TableElementBase();
};

template< class T >
class TableElement final
    :   public ContainerElement<T>
{
public:
    
};


namespace details {
template< class T >
using is_table_element = std::is_base_of< typename dscpp::TableElementBase, T >::value;

template< typename T >
class CompareTable
{
public:
    bool operator()( const TableElement<T>& lhs, const TableElement<T>& rhs ) const {
        return lhs < rhs;
    }
    bool operator()( const T& lhs, const T& rhs ) const {
        return ((std::string) lhs) < ((std::string) rhs);
    }
};
} // namespace details


template< class T, class Compare = details::CompareTable<T> >
//    requires details::is_table_element< T >
class Table
{
public:
    /**
     * @brief This class represents a row of data
     * @note Inherits `std::set< T, dscpp::details::Compare<T> >`
     */
    class Row
        :   public std::unordered_set< typename dscpp::TableElement<T> >
    {
    public:
        typedef typename std::unordered_set< dscpp::TableElement<T> > set_row_t;
        typedef typename set_row_t::value_type row_element_t;
        typedef typename std::unordered_set< T > set_t;
        typedef typename std::set< T > stl_set_t;

        Row()
            :   set_row_t()
        {}
        Row( const set_row_t& other )
            :   set_row_t( other )
        {}

        Row& operator<<( const T& element ) {
            TableElement<T>* te = new TableElement<T>( element );
            this->insert( te );
            return *this;
        }
        Row& operator<<( const set_t& another ) {
            for ( typename set_t::const_iterator sai = another.cbegin()
                ; sai != another.cend(); sai++
            ) {
                *this << *sai;
            }
            return *this;
        }
        Row& operator<<( const stl_set_t& another ) {
            for ( typename set_t::const_iterator sai = another.cbegin()
                ; sai != another.cend(); sai++
            ) {
                *this << *sai;
            }
            return *this;
        }

        using RowIterator = typename set_row_t::iterator;
        using ConstRowIterator = typename set_row_t::const_iterator;
        using SizeType = typename set_row_t::size_type;

        size_t is_element_pos( const typename ConstRowIterator cri ) {
            size_t pos = 0;
            for ( typename dscpp::Table<T>::Row::ConstRowIterator ri = this->begin()
                ; pos < this->size() && ri != this->end()
                ; pos++, ri++
            ) {
                if ( *ri == *cri ) return pos;
            }
            return this->size();
        }
        const typename ConstRowIterator iterate_until( const SizeType pos ) {
            if ( pos >= this->size() ) return this->cend();
            size_t p = 0;
            for ( typename dscpp::Table<T>::Row::ConstRowIterator ri = this->begin()
                ; p < this->size() && ri != this->end()
                ; p++, ri++
            ) {
                if ( pos == p ) return ri;
            }
            return this->cend();
        }

        void swap( const typename ConstRowIterator lhs, const typename ConstRowIterator rhs ) {
            typename dscpp::Table<T>::Row::RowIterator one = this->insert( lhs, *rhs );
            typename dscpp::Table<T>::Row::RowIterator two = this->insert( rhs, *lhs );
            this->erase( one + 1 );
            this->erase( two + 1 );
        }

        void swap( const Table<T>::Row::size_type one, const Table<T>::Row::size_type another ) {
            if ( one >= this->size() || another >= this->size() ) return;
            const ConstRowIterator one_it = this->iterate_until( one );
            const ConstRowIterator another_it = this->iterate_until( another );
            this->swap( one_it, another_it );
        }

        const Table<T>::Row::value_type swapElement( const ConstRowIterator pos, const Table<T>::Row::value_type value ) {
            const typename Table<T>::Row::value_type old = *pos;
            typename Table<T>::Row::iterator it = this->insert( pos, value );
            this->erase( it + 1 );
            return old;
        }

        typedef typename std::pair< SizeType, SizeType > row_range_t;
        typedef typename std::pair< typename row_range_t, bool > sorting_result_t;

        virtual sorting_result_t& sortRange( const ConstRowIterator from
                                               , const ConstRowIterator until
        ) {
            sorting_result_t* sr = new sorting_result_t{ {0, 0}, false };

            for ( ConstRowIterator rcri = until
                ; rcri != from; rcri--
            ) {
                for ( ConstRowIterator prev_other = from
                    ; prev_other != this->cend() && prev_other != until && prev_other != rcri
                    ; prev_other++
                ) {
                    if ( rcri == prev_other ) break;
                    if ( Compare( *rcri, *prev_other ) ) {
                        this->swap( rcri, prev_other );
                    } else continue;
                }
            }

            sr->first.first = from;
            sr->first.second = until;
            sr->second = true;

            return *sr;
        }

        virtual sorting_result_t& sortRange( const SizeType from
                                           , const SizeType until
                                           , Row& other_row
        ) {
            const ConstRowIterator cri_from = other_row.iterate_until(from);
            const ConstRowIterator cri_until = other_row.iterate_until(until);
            return this->sortWithOther( cri_from, cri_until );
        }

        virtual sorting_result_t& sort() {
            return this->sortRange( this->cbegin(), this->cend() );
        }

        
    private:
        static inline std::unique_ptr< typename Table<T>::Row > endrow;

    public:
        static inline const Table<T>::Row::const_iterator static_endrow() {
            if ( ! Table<T>::Row::endrow ) {
                Table<T>::Row::endrow = std::unique_ptr<typename Table<T>::Row>( new Table<T>::Row() );
            }
            return Table<T>::Row::endrow->cend();
        }

        static bool is_end( const Table<T>::Row::const_iterator rit ) {
            return rit == Table<T>::Row::static_endrow();
        }
    };

    class Column
        :   public dscpp::SortableVector< typename Table<T>::Row >
    {
    public:
        typedef typename dscpp::SortableVector< typename Table<T>::Row > vector_t;

        Column()
            :   vector_t()
        {}
        Column( const typename vector_t& other )
            :   vector_t( other )
        {}

        typename Table<T>::Row& getRow( const unsigned int r ) const {
            if ( r >= this->size() ) {
                typename Table<T>::Row* row = new Table<T>::Row();
                this->push_back( row );
                return *row;
            }
            return &this->at( r );
        }

        Column& operator<<( const typename Table<T>::Row& row ) {
            this->push_back( row );
            return *this;
        }
        Column& operator<<( const typename Table<T>::Row::set_t& set ) {
            typename Table<T>::Row::set_row_t* row = new Table<T>::Row::set_row_t();
            *row << set;
            this->insert( *row );
            return *this;
        }

        using ColumnIterator = typename vector_t::iterator;
        using ConstColumnIterator = typename vector_t::const_iterator;
        using SizeType = typename vector_t::size_type;

        const SizeType getIteratorPositionIndex( const ConstColumnIterator cci ) const {
            for ( SizeType i = 0; i < this->size(); i++ ) { if ( *cci == this->at(i) ) return i; }
            return this->size();
        }

        typedef typename std::pair< ConstColumnIterator, ConstColumnIterator > column_range_t;
        typedef typename std::pair< column_range_t, bool > sorting_result_t;

        sorting_result_t& sortMultivariative( std::initializer_list<SizeType> rows ) {
            sorting_result_t* sr = new sorting_result_t{ {0, 0}, false };

            unsigned int rows_sorted = 0;
            typename Table<T>::Row* prev_row = NULL;
            for ( const SizeType row_i : rows ) {
                typename Table<T>::Row& row = this->at( row_i );

                if ( rows_sorted > 0 && prev_row != NULL ) {
                    
                    for ( unsigned int pri = 1; pri < prev_row->size(); pri++ ) {
                        SizeType pos_last_equal = pri;

                        typename dscpp::TableElement<T>& prev = prev_row->at( pri - 1 );
                        typename dscpp::TableElement<T>& current = prev_row->at( pri );
                        
                        if ( ((std::string) prev) == ((std::string) current) ) {
                            // Find the number of same element keys in this row
                            for ( unsigned int pr2 = 0; pr2 < prev_row->size(); pr2++ ) {
                               if ( ((std::string) current) == ((std::string) prev_row->at(pr2)) ) ++pos_last_equal;
                               else break;
                            }
                            
                            // Now sort this range of all equal elements in this interval of the current row
                            // inside of the next row and continue.
                            typename dscpp::Table<T>::Row::sorting_result_t& sr_row = row.sortRange( row.iterate_until(pri-1)
                                                                            , row.iterate_until(pos_last_equal) );
                            if ( sr_row.second ) { pri = pos_last_equal; break; }
                            else return *sr;
                        }
                    }

                    sr->first.second = row.iterate_until(row_i);
                    
                    
                } else {
                    typename dscpp::Table<T>::Row::sorting_result_t& sr_row = row.sort();
                    if ( sr_row.second ) sr->first.first = row.iterate_until(row_i);
                }

                if ( ! sr_row.second ) return *sr;
                else {
                    prev_row = row;
                    ++rows_sorted;
                }
            }

            sr->second = true;

            return *sr;
        }

        typename sorting_result_t& sortMultivariative( std::ranges::subrange<ConstColumnIterator> row_range ) {
            std::vector<SizeType> st_vec;

            for ( const ConstColumnIterator cci : row_range ) {
                st_vec.emplace_back( this->getIteratorPositionIndex(cci) );
            }

            return this->sortMultivariative( st_vec );
        }
    };
    
    
    using Tensor = typename Table<T>::Column;

    class Named
        :   public dscpp::Map< std::string, typename Table<T>::Row >
    {
    public:
        typedef typename dscpp::Map< std::string, typename Table<T>::Row > map_t;

        Named()
            :   dscpp::Map< std::string, typename Table<T>::Row >()
        {}
        Named( const dscpp::Map< std::string, typename Table<T>::Row >& other )
            :   dscpp::Map< std::string, typename Table<T>::Row >( other )
        {}

        size_t getPositionOfName( const std::string col_name ) {
            typename map_t::iterator mi = this->begin();
            for ( unsigned int i = 0; i < this->size() && mi != this->end(); i++, mi++ ) {
                if ( mi->first == col_name ) return i;
            }
            return this->size();
        }

        typedef typename map_t::iterator iterator;
        typedef typename Table<T>::Row::const_iterator element_iterator;
        using SizeType = map_t::size_type;
        using SizeTypeRow = Table<T>::Row::SizeType;

        typename Table<T>::Row* getRowOfElement( const typename element_iterator eit ) {
            for ( typename Table<T>::Row::const_iterator rit : *this ) {
                typename Table<T>::Row& row = rit->second;
                for ( typename Table<T>::Named::element_iterator eit : row ) {
                    if ( *rit == *eit ) return &row;
                }
            }
            return NULL;
        }

        class ElementIterator
            :   public iterator
        {
        public:
            element_iterator elem;

        protected:
            element_iterator get_element_iterator( const iterator it ) {
                if ( Map<std::string, typename Table<T>::Row>::is_end(static_cast<iterator>(this->elem)) )
                    return Table<T>::Row::static_endrow();
                return (*it)->second.begin();
            }

            void set_element_iterator( const iterator it ) {
                this->elem = this->get_element_iterator( it );
            }

        public:
            typename Table<T>::Row *const row() const {
                if ( Table<T>::Named::is_end(static_cast<iterator>(this->elem)) )
                    return NULL;
                return &(this->second);
            }

            const std::string rowname() const {
                return this->first;
            }

            ElementIterator( const typename Table<T>::Named::iterator row_it )
                :   iterator( row_it )
            {
                this->set_element_iterator( static_cast<iterator>(this->elem) );
            }

            ElementIterator( const typename Table<T>::Named::iterator row_it
                           , const typename Table<T>::Row::SizeType elem_pos
            )   :   iterator( row_it )
                ,   elem( this->row() != 0 ?
                                    ( elem_pos < this->row().size() ? this->row().iterate_until(elem_pos)
                                                        : this->row().cend() )
                                : Table<T>::Row::static_endrow() )
            {}

            element_iterator operator~() const {
                return this->elem;
            }

            ElementIterator operator++() {
                iterator::operator++();
                this->set_element_iterator( static_cast<iterator>(this) );
                return *this;
            }

            ElementIterator operator--() {
                iterator::operator--();
                this->set_element_iterator( static_cast<iterator>(this) );
                return *this;
            }

            constexpr inline bool operator==( const ElementIterator& another ) {
                if ( static_cast<iterator>(this->elem) == static_cast<iterator>(another) ) return true;
                else if ( Table<T>::Named::is_end(this) && Table<T>::Named::is_end(&another) ) return true;
                return ~(*this) == ~another;
            }
        };

        ElementIterator ebegin( const SizeTypeRow row_pos = 0 ) const {
            return *new ElementIterator( this->begin(), row_pos );
        }

        ElementIterator eend() const {
            return *new ElementIterator( this->end(), Table<T>::Row::static_endrow() );
        }

        void swapRowElement( const element_iterator lhs, const element_iterator rhs ) {
            typename Table<T>::Row* lrow = this->getRowOfElement(lhs);
            if ( lrow == NULL ) return;
            typename Table<T>::Row* rrow = this->getRowOfElement(rhs);
            if ( rrow == NULL ) return;

            const typename Table<T>::Row::value_type old = lrow->swapElement( lhs, *rhs );
            rrow->swapElement( rhs, old );
        }

        Named& operator<<( const typename std::pair< std::string, typename Table<T>::Column > new_value ) {
            (*this)[new_value.first] = new_value.second;
            return *this;
        }
        Named& operator<<( const std::initializer_list<std::string> column_names ) {
            for ( std::string col_name : column_names ) {
                *this << std::pair{ col_name, *new Table<T>::Column() };
            }
            return *this;
        }

        std::vector<std::string>& getSortingNames() const {
            std::vector< std::string >* sn_vec = new std::vector< std::string >();

            for ( typename Table<T>::Named::const_iterator ci : *this ) {
                sn_vec->emplace_back( ci->first );
            }

            return *sn_vec;
        }

        

        static SizeTypeRow iterator_find_position_index_in_row( const typename Table<T>::Row::iterator row_it
                                                              , typename Table<T>::Row row
        ) {
            for ( unsigned int r = 0; r < row.size(); r++ ) {
                if ( row.at(r) == *row_it ) return r;
            }
            return row.size();
        }

        static SizeType iterator_find_position_index_row( const typename Table<T>::Row::iterator row_it
                                                           , typename Table<T>::Named& table
        ) {
            unsigned int r = 0;
            for ( typename Table<T>::Named::iterator tn_it : table ) {
                typename Table<T>::Row& row = *tn_it->second;
                if ( Table<T>::Named::iterator_find_position_index_in_row(row.begin(), row) < row.size() )
                    return r;
                ++r;
            }
            return table.size();
        }

        typename Table<T>::Named::iterator iterate_until( const SizeType row_idx ) {
            if ( row_idx >= this->size() ) return NULL;

            unsigned int r = 0;
            for ( typename Table<T>::Named::iterator tn_it : *this ) {
                if ( r == row_idx ) return tn_it->second;
                else ++r;
            }
            return NULL;
        }

        class ColumnIterator final
        /* requires std::random_access_iterator< Table<T>::Named::ElementIterator >
                    && std::incrementable< ColumnIterator >
                    && std::decrementable< ColumnIterator >
                    && std::indirectly_readable< T >
                    && std::indirectly_writable< Table<T>::Row::value_type, T >
                    && std::sized_sentinel_for< Table<T>::Named::value_type, Table<T>::Named::ColumnIterator > */
            :   protected Table<T>::Named::ElementIterator
        {
        protected:
            typename Table<T>::Named& table;
            typename Table<T>::Row::size_type col_idx;
            typename Table<T>::Named::SizeType row_idx;
            typename Table<T>::Row& current_row;
            typename Table<T>::Row::value_type& current_elem;

            friend class Table<T>::Named::ColumnIterator;

            bool set_attributes_row() {
                if ( this->row_idx < this->table.size() ) {
                    this->current_row = table.iterate_until( this->row_idx )->second;
                    return true;
                }
                return false;
            }

            bool set_attributes_col() {
                if ( this->col_idx < this->current_row.size() ) {
                    this->elem = current_row.iterate_until( this->col_idx );
                    return true;
                }
                return false;
            }

            bool set_attributes_elem() {
                if ( ! this->is_end() ) {
                    this->current_elem = *this->elem;
                    return true;
                }
                return false;
            }

            bool set_attributes() {
                if ( ! this->set_attributes_row() ) return false;
                if ( ! this->set_attributes_col() ) return false;
                if ( ! this->set_attributes_elem() ) return false;
                return true;
            }
        public:
            ColumnIterator( const size_t col_idx
                          , typename Table<T>::Named& table )
                :   Table<T>::Named::ElementIterator( *Table<T>::Named::iterate_until( 0, table ) )
                ,   table( table )
                ,   col_idx( col_idx )
                ,   row_idx( 0 )
                ,   current_row( table.front() )
                ,   current_elem( current_row.front() )
            {}

            ColumnIterator( const size_t col_idx
                          , const size_t row_idx
                          , typename Table<T>::Named& table )
                :   Table<T>::Named::ElementIterator( *Table<T>::Named::iterate_until( row_idx, table ) )
                ,   table( table )
                ,   col_idx( col_idx )
                ,   row_idx( row_idx )
                ,   current_row( *this->second )
                ,   current_elem( current_row(col_idx) )
            {}

            ColumnIterator( const ColumnIterator& col_it )
                :   Table<T>::Named::ElementIterator( col_it.elem )
                ,   table( col_it.table )
                ,   col_idx( col_it.col_idx )
                ,   row_idx( col_it.row_idx )
                ,   current_row( col_it.current_row )
                ,   current_elem( col_it.current_elem )
            {}

            typedef typename Table<T>::Row::value_type value_type;
            typedef typename Table<T>::Row& row_reference_t;

            row_reference_t operator~() const {
                return this->current_row;
            }

            value_type& operator*() const {
                return this->current_elem;
            }

            ColumnIterator operator++() {
                if ( this->row_idx < this->table.size() ) {
                    ++this->row_idx;
                    if ( this->row_idx < this->table.size() ) {
                        this->set_attributes();
                    }
                }
                return *this;
            }

            ColumnIterator operator--() {
                if ( this->row_idx < this->table.size() ) {
                    --this->row_idx;
                    if ( this->row_idx < this->table.size() ) {
                        this->set_attributes();
                    }
                }
                return *this;
            }

            ColumnIterator operator+( const size_t pos_offset ) const {
                ColumnIterator* col_it = new ColumnIterator( *this );

                for ( unsigned int c = 0
                    ; c < pos_offset && *col_it != this->table->end()
                    ; c++ )
                { ++col_it; }

                return *col_it;
            }

            ColumnIterator operator-( const size_t pos_offset ) const {
                ColumnIterator* col_it = new ColumnIterator( *this );

                for ( unsigned int c = 0
                    ; c < pos_offset && *col_it >= this->table->begin()
                    ; c++ )
                { --col_it; }

                return *col_it;
            }

            bool is_end() const {
                if ( this->row_idx == this->table.size() ) return true;
                else if ( this->col_idx == this->current_row.size() ) return true;
                else return false;
            }

            constexpr inline bool operator==( const ColumnIterator another ) {
                if ( this->is_end() ) return another.is_end();
                else return **this == *another;
            }

            void set_end() {
                this->row_idx = this->table.size() - 1;
                this->set_attributes_row();
                this->col_idx = this->current_row.size();
            }

            ColumnIterator next_column() {
                if ( this->col_idx < this->current_row.size() ) {
                    ++this->col_idx;
                    if ( ! this->set_attributes() ) this->set_end();
                }
                return *this;
            }

            ColumnIterator previous_column() {
                if ( this->col_idx > 0 ) {
                    --this->col_idx;
                    if ( ! this->set_attributes() ) this->set_end();
                }
                return *this;
            }

            const size_t index_column() const { return this->col_idx; }
            const size_t index_row() const { return this->row_idx; }
        };

        typedef typename Table<T>::Named::ColumnIterator col_iterator;
        
        using sorting_result_row_t = typename Table<T>::Row::sorting_result_t;

        ColumnIterator colbegin( const size_t column_idx, const size_t row_idx = 0 ) {
            return *new ColumnIterator( column_idx, row_idx, *this );
        }

        ColumnIterator colend() {
            ColumnIterator* col_it = new ColumnIterator( 0, 0, *this );
            col_it->set_end();
            return *col_it;
        }

        using other_rows_ft = sorting_result_row_t& (*)( const typename dscpp::Table<T>::Row&, const size_t, const size_t);
        using if_elements_equals_ft = bool& (*)( const ColumnIterator, const ColumnIterator );
        using sorting_result_col_t = std::pair< std::pair< size_t, size_t >, bool >;
        using sorting_assertion_col_ft = bool (*)( const sorting_result_col_t& );

        virtual typename Table<T>::Named::sorting_result_row_t& sortRow( const size_t row_index
                                         , const typename Table<T>::Named::other_rows_ft other_rows_f
                                         , const typename Table<T>::Named::if_elements_equals_ft ife_equal_f
        ) {
            typename Table<T>::Named::iterator rowIt = this->atPos( row_index );
            if ( rowIt != this->end() ) {
                rowIt->second->sort();
                for ( typename Table<T>::Named::iterator it : *this ) {
                    other_rows_f( *it->second, 0, it->second->size() - 1 );
                }
                return *new Table<T>::Named::sorting_result_row_t{ new Table<T>::Column(*rowIt->second), rowIt };
            }

        }

        virtual sorting_result_col_t& sortColumn( const size_t col_index
                                        , const if_elements_equals_ft ife_equals_f
                                        , const sorting_assertion_col_ft assert_sorting
        ) const {
            sorting_result_col_t* src = new sorting_result_col_t{ { col_index, 0 }, false };

            ColumnIterator co_it = this->colbegin( col_index );
            while ( ! co_it.is_end() ) {
                if ( Compare( *(co_it+1), *co_it ) ) {
                    this->swapRowElement( co_it+1, co_it );
                    ++co_it;
                    src->first.second = co_it.index_row();
                } else if ( *(co_it+1) == *co_it ) src->second = src->second && ife_equals_f( co_it, co_it+1 );
            }

            if ( ! assert_sorting( *src ) ) src->second = false;

            return *src;
        }

        typename Table<T>::Named& sortBy( const std::initializer_list<std::string> sortColumnsByPriority ) {
            std::vector<size_t>* pos_vec ;

            for ( std::string sort_priority : sortColumnsByPriority ) {
                size_t pos = this->getPositionOfName(sort_priority);
                if ( pos < this->size() ) pos_vec->emplace_back( pos );
            }

            return *pos_vec;
        }
    };

    template< class Key, class SubType = typename dscpp::Table<T>::Named >
    class SubOrdering
        :   public SubType
    {
    public:
        const typename Key name;

        SubOrdering( const Key ordering_name, typename SubType& subtype_container )
            :   SubType( subtype_container )
            ,   name( ordering_name )
        {}

        void set( const typename SubType::iterator it, const typename SubType::value_type value ) {
            typename SubType::iterator insert_it = this->insert( it, value );
            this->erase( insert_it + 1 );
        }

        class SubTypeIterator
        {
        protected:
            typename SubType::iterator it;
            typename SubOrdering< SubType >& container;

        public:
            SubTypeIterator( const typename SubType::iterator iter
                           , typename SubOrdering< SubType > container )
                :   it( iter )
                ,   container( container )
            {}

            operator typename SubType::iterator() const { return this->it; }

            SubTypeIterator& operator++() {
                ++this->it;
                return *this;
            }
            
            SubTypeIterator& operator--() {
                --this->it;
                return *this;
            }
            
            typename SubType::iterator::value_type& operator*() const {
                return (*this->it);
            }

            void apply() {
                this->container.set( *this, *(*this) );
            }

            typename SubType::value_type& value() const { return **this; }
            bool is_end() const { return this->container.end() == *this; }
        };

        typename dscpp::Table<T>::SubOrdering< Key, SubType >::SubTypeIterator stbegin() {
            return *new SubTypeIterator( this->begin(), *this );
        }

        typename dscpp::Table<T>::SubOrdering< Key, SubType >::SubTypeIterator stend() {
            return *new SubTypeIterator( this->end(), *this );
        }

        bool sortBy( const std::initializer_list<Key> il ) {
            SubType::sortBy( il );
        }

        bool sort() {
            SubType::sort();
        }
    };

    template< typename Key, class SubType = typename dscpp::Table<T>::Named >
    class SortingKind
        :   public dscpp::Map< Key, SubOrdering< Key, SubType >* >
    {
    protected:
        static bool compare_subordering( const SubOrdering< Key, SubType >& st1
                                       , const SubOrdering< Key, SubType >& st2
        ) {
            return st1.name < st2.name;
        }

    public:
        SortingKind()
            :   dscpp::Map< Key, SubOrdering< Key, SubType >* >()
        {}
        SortingKind( const std::initializer_list<Key> column_names )
            :   dscpp::Map< Key, SubOrdering< Key, SubType >* >()
        {
            for ( const Key k : column_names ) {
                *this << std::pair{ k, new SubOrdering< Key, SubType >(k, *new SubType()) };
            }
        }

        typedef typename dscpp::Map< Key, SubOrdering< Key, SubType >* >::iterator iterator;

        class SortingKindIterator
            :   public SortingKind< Key, SubType >::iterator
        {
        protected:
            typename SortingKind< Key, SubType >& sorting;

        public:
            typename SubOrdering< Key, SubType >::SubTypeIterator* subtype_it;

            SortingKindIterator( const SortingKind< Key, SubType >::iterator it
                               , SortingKind< Key, SubType >& sorting_container
            )   :   SortingKind< Key, SubType >::iterator( it )
                ,   sorting( sorting_container )
                ,   subtype_it( this->is_end() ? NULL : (*this)->begin() )
            {}

            size_t sort( const Key key );
        };
    };
};


template< typename T >
inline bool equals( const typename dscpp::Table<T>::Row::const_iterator lhs
                  , const typename dscpp::Table<T>::Row::const_iterator rhs
) {
    if ( lhs == rhs ) return true;
    else if ( dscpp::Table<T>::Row::is_end(lhs) ) return dscpp::Table<T>::Row::is_end(rhs);
    return false;
}


} // namespace dscpp
