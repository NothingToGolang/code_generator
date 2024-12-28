/**
 * @file NamedType.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef NAMEDTYPE_HPP
#define NAMEDTYPE_HPP

#include "Type.hpp"

class NamedType;
typedef RefObject<NamedType> NamedTypeRef;

/**
 * @brief The NamedType class 命名类型，实际和变量类似，但是不包含变量的值，只包含变量的类型，一般不使用，提供给typedef使用
 */
class NamedType : public Type {
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个命名类型, create("name", BuildInType::INT), 生成一个int name
    static NamedTypeRef create(const String &name, TypeRef parent);

  public:
    NamedType(const String &name, TypeRef parent);

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    virtual uint16_t id() const override {
      return parent() != nullptr ? parent()->id() : NamedType::ID;
    }

    virtual Kind kind() const override { return parent() != nullptr ? parent()->kind() : Type::kind(); }

  public:
    String name() const;
    void setName(const String &name);

    TypeRef type() const;

 protected:
    bool skipSpace(TypeRef origin);

  private:
    String m_name;
};

/// @brief  创建一个命名类型, namedType_("name", BuildInType::INT), 生成一个int name，一般用于typedef使用，外部不需要直接调用
/// @param name 
/// @param parent 
/// @return 
inline static NamedTypeRef namedType_(const String &name, TypeRef parent) {
  return NamedType::create(name, parent);
}

#endif // NAMEDTYPE_HPP
