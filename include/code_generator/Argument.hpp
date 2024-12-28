/**
 * @file Argument.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP
#include "NamedType.hpp"

typedef NamedTypeRef ArgumentRef;

/// @brief        创建一个参数类型，使用方式为 argument_("name", BuiltInType::INT), 生成一个int name的参数
/// @param name   参数名称
/// @param parent 参数类型
/// @return       
inline static ArgumentRef argument_(const String &name, TypeRef parent) {
  return namedType_(name, parent);
}

#endif // ARGUMENT_HPP
