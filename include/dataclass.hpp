/**
 * @file dataclass.hpp
 * @brief A file that defines the specific dataclass for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "classfactory.hpp"
#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>


namespace dscpp {

// Forward declaration
class OwnDataClass;
// Forward declaration
template< class InheritingClass, class DataType >
    requires std::is_base_of< OwnDataClass, InheritingClass >::value
class DataClass;

/**
 * @brief The virtual base class, that is to be derived from
 *      `DataClass` for functionality for a specific data type `DT`.
 * @note Classes deriving this class are designed to make a `DataType<DT>`
 *      feature-enabled and fully cabable to be used in the library that is
 *      used to work with your data design types.
 */
class OwnDataClass {
protected:
    /** 
     * @brief Get your data type as `void*` from latestly `DataClass`
     * @note This function is pure virtual
     */
    virtual void* getDT() const = 0;

    /**
     * @brief Get the data type `DT` in a common inheriting class like
     *      `DataClass< YourDataDesignFunctionalT, DT >` for more work and
     *      in calculations in your functions of the class inheriting `OwnDataClass`
     * @tparam DT The data type, inherited from `ClassFactory::DataType`, that is
     *      made functional with your class deriving from `OwnDataClass`
     * @returns A reference to `DT`, that is already casted to `DT`
     */
    template< class DT >
    DT& getDataType() const { *((DT*) this->getDT()); }

    /**
     * @brief Setup all variables inside of the class `InheritingClass`
     * @param ic A reference to the `InheritingClass`, that is thus feature-enabling
     *      this data type
     * @param dc A reference to a `DataClass` of the same type, thus `DataClass<InheritingClass, DataType>`
     * @returns True on success
     * @note This function is pure virtual
     */
    virtual bool setupVariables( InheritingClass& ic, DataClass<InheritingClass, DataType>& dc ) = 0;
};



/**
 * @brief The feature-enabling data class for data types of `libdsC`/`libdsC++`.
 * @tparam InheritingClass The class adding all functionality to `DataType`. 
 *      `OwnDataClass` is a base class of `InheritingClass`
 * @tparam DataType The self-designed data type, that has `ClassFactory::DataType`
 *      as its base class and is derived from `dscpp::Datatype<DataType>`
 */
template< class InheritingClass, class DataType >
    requires std::is_base_of< OwnDataClass, InheritingClass >::value
class DataClass
    :   public ClassFactory::DataClass
    ,   public Datatype<DataType>
    ,   public InheritingClass
{
protected:
    /**
     * @brief Setup all variables inside of the class `InheritingClass`
     * @param ic A reference to the `InheritingClass`, that is thus feature-enabling
     *      this data type
     * @param dc A reference to a `DataClass` of the same type, thus `DataClass<InheritingClass, DataType>`
     * @returns True on success
     */
    virtual bool setupVariables( InheritingClass& ic, DataClass<InheritingClass, DataType>& dc ) {
        return InheritingClass::setupVariables(ic, dc);
    }
    /**
     * @brief Setup all variables inside of the class `InheritingClass`
     * @param dc A reference to a `DataClass` of the same type, thus `DataClass<InheritingClass, DataType>`
     * @returns True on success
     */
    virtual bool setupVariables( DataClass<InheritingClass, DataType>& dc ) {
        return InheritingClass::setupVariables(*this, dc);
    }

    /** 
     * @brief Get your data type as `void*` from here
     * @returns A pointer to `DataType` as `void*`
     */
    virtual void* getDT() const final { return dscpp::ClassFactory::castData<DataType>(*this); }

public:
    /**
     * @brief Create a feature/functional `InheritingClass` from a `Dictionary::Section`
     *      reference
     * @param section A reference to a `Dictionary::Section` object
     * @returns A reference to a newly created `InheritingClass` object with all variables
     *      set up
     */
    virtual InheritingClass& toDataStructure( const Dictionary::Section& section ) {
        InheritingClass* ic = new InheritingClass( section );

        this->setupVariables( ic, *this );

        return *ic;
    }

    /**
     * @brief Constructor
     * @param section A reference to a `Dictionary::Section` object
     */
    DataClass( const Dictionary::Section& section )
        :   ClassFactory::DataClass( ClassFactory::getData( section ) )
        ,   Datatype<DataType>( toDataStruct<DataType>(this) )
        ,   InheritingClass( this->toDataStructure(section) )
    {
        this->data = (DataType*) this;
    }
};


/**
 * @brief Define a new type inheritor for your feature class for one of your library's data types
 * @param functional_cls The name of the class that adds features to `datatype`
 * @param datatype The name of the class/struct that holds the variables and datastructures of your data type
 */
#define DSC_DEFINE_DATACLASS(functional_cls, datatype) template class dscpp::DataClass< functional_cls, datatype >;
/**
 * @brief Typedef a new type for your feature class for one of your library's data types
 * @param functional_cls The name of the class that adds features to `datatype`
 * @param datatype The name of the class/struct that holds the variables and datastructures of your data type
 * @param nameCLS The name that the class will have
 */
#define DSC_MAKE_DATACLASS(functional_cls, datatype, nameCLS) typedef typename dscpp::DataClass< functional_cls, datatype > nameCLS;

} // namespace dscpp
