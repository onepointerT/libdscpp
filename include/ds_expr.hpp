// Copyright (C) 2026 The OnePointer Authors.
//

#pragma once


#include "ds_expression_varenv.hpp"

#include <string_view>


namespace dscpp {
namespace expr {


class Expression
    :   protected std::string_view
    ,   public dscpp::expr::ExprVarEnv
{
public:
    Expression( const std::string expr_str, ExprVarEnv::getVarValue_f gvv_func );

    const std::string str_expr() const;
    std::string_view& expr() const;
};


} // namespace expr
} // namespace dscpp