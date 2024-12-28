/**
 * @file Typedef.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include "NamedType.hpp"

class Typedef;
typedef RefObject<Typedef> TypedefRef;

/// @brief The Typedef class 类型定义类，用于表示一个类型定义，如typedef int MyType;
class Typedef : public NamedType {
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个类型定义
    /// @param origin 原始类型
    /// @param name   新类型名称
    /// @return 
    static TypedefRef create(TypeRef origin, const String &name);

  public:
    Typedef(TypeRef origin, const String &name);

    virtual int write(CodeWriter &writer);

    virtual Kind kind() const {
      return Code::Kind::CodeStatment;
    }

  private:
    String m_name;
};

/// @brief  创建一个类型定义，使用方式为typedef_(BuiltInType::INT, "MyType"), 生成typedef int MyType
/// @param origin 
/// @param name 
/// @return 
inline static TypedefRef typedef_(TypeRef origin, const String &name) {
  return Typedef::create(origin, name);
}

#endif // TYPEDEF_HPP
