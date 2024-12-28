#pragma once

#include "NamedType.hpp"
#include "Var.hpp"

class Field;
typedef RefObject<Field> FieldRef;

/**
 * @brief The Field class 成员字段类，用于表示一个类的成员字段，可以通过visit方法访问该字段
 *                      如field_("name", BuiltInType::INT), 生成一个int name的字段，将其付给struct_类型，
 *                     可以通过visit方法生成访问代码，如field_->visit("变量名称") 生成 变量名称->name
 */
class Field : public NamedType {
public:
    static const uint16_t ID;

public:
    using NamedType::NamedType;

public:
  static FieldRef create(const String &name, TypeRef parent);

public:
  /**
   * @brief visit 用于访问该字段
   * @param self  对应变量
   * @return 字段的变量 self->name
   **/
  VarRef visit(VarRef self);

  /**
   * @brief id 类型id
   * @return id
   **/
  virtual uint16_t id() const override {
    return Field::ID;
  }
};

/// @brief        创建一个字段类型，使用方式为 field_("name", BuiltInType::INT), 生成一个int name的字段
/// @param name   字段名称
/// @param parent 字段类型
/// @return 
inline static FieldRef field_(const String &name, TypeRef parent) {
  return Field::create(name, parent);
}