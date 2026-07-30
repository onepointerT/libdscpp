// Copyright 2026 The OnePointer Authors.
//

#include "ds_varenvironment.hpp"


namespace dscpp {
namespace expr { // DataScience


Variable::Variable( const std::string vname, const std::string vvalue, const std::string orig_name )
    :   std::string_view( vvalue )
    ,   name( vname )
    ,   original_name( orig_name )
{}

Variable& Variable::setValue( const std::string vvalue ) {
    this->swap( *new std::string_view(vvalue) );
    return *this;
}


VarEnvironment::VarEnvironment()
    :   std::map< std::string, Variable* >()
{}

bool VarEnvironment::add( const std::string vname, const std::string vvalue ) {
    if ( this->count(vname) > 0 ) return false;
    (*this)[vname] = new Variable( vname, vvalue );
    return true;
}

Variable& VarEnvironment::set( const std::string vname, const std::string vvalue ) {
    if ( this->count(vname) >= 0 )
        (*this)[vname]->setValue( vvalue );
    else this->add( vname, vvalue );
    return this->get( vname );
}

Variable& VarEnvironment::get( const std::string vname ) {
    if ( this->count(vname) == 0 ) this->add( vname );
    return *(this->at(vname));
}


Variable& VarEnvironment::get( const std::string vname ) const {
    return *(this->at(vname));
}


bool VarEnvironment::remove( const std::string vname ) {
    if ( this->count(vname) > 0 ) {
        this->erase( vname );
        return true;
    } return false;
}

} // namespace expr
} // namespace dscpp
