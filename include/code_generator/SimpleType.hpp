/**
 * @file SimpleType.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef SIMPLETYPE_HPP
#define SIMPLETYPE_HPP

#include "Type.hpp"

class SimpleType;
typedef RefObject<SimpleType> SimpleTypeRef;

/// @brief  The SimpleType class 简单类型类，用于表示一个简单类型，如int, char, float，或者自定义类型等，
///                      内置类型可通过BuiltinType获取，如BuiltinType::Int, BuiltinType::Float等，
///                      其他类型可通过simpleType_获取，如simpleType_("MyType")
class SimpleType : public Type {
  public:
    static const uint16_t ID;

  public:
    static SimpleTypeRef create(const String &codeType, TypeRef parent = nullptr);

  public:
    SimpleType(const String &codeType, TypeRef parent = nullptr);

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    virtual uint16_t id() const override {
      return SimpleType::ID;
    }

  private:
    String m_type;
};

/// @brief  创建一个简单类型，使用方式为simpleType_("MyType")，生成一个MyType的类型
/// @param codeType 类型名称
/// @param parent   父类，一般不需要使用，若不为空，则会生成 " 父类 当前类 " 的类型，例如父类是一个某类型指针，然后在其基础上添加其他的引用等
/// @return 
inline static SimpleTypeRef simpleType_(const String &codeType, TypeRef parent = nullptr) {
  return SimpleType::create(codeType, parent);
}

/// @brief  创建一个简单类型，使用方式为type_("MyType")，生成一个MyType的类型
/// @param codeType  类型名称
/// @param parent    父类，一般不需要使用，若不为空，则会生成 " 父类 当前类 " 的类型，例如父类是一个某类型指针，然后在其基础上添加其他的引用等
/// @return 
inline static SimpleTypeRef type_(const String &codeType, TypeRef parent = nullptr) {
  return SimpleType::create(codeType, parent);
}

/// @brief  内置类型类，用于表示一些内置类型，如int, char, float等
class CODEC_GENERATOR_API BuiltinType {
  public:
    static SimpleTypeRef Int;
    static SimpleTypeRef UInt;
    static SimpleTypeRef Float;
    static SimpleTypeRef Double;
    static SimpleTypeRef Char;
    static SimpleTypeRef Long;
    static SimpleTypeRef ULong;
    static SimpleTypeRef Short;
    static SimpleTypeRef UShort;
    static SimpleTypeRef Void;
};

#endif // SIMPLETYPE_HPP
