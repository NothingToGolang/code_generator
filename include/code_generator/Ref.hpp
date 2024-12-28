/**
 * @file Ref.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef REF_HPP
#define REF_HPP

#include "Type.hpp"

class Ref;
typedef RefObject<Ref> RefRef;

/// @brief The Ref class 引用类型，用于表示一个引用类型，如int&，char&等, 使用方式为ref_(BuiltInType::INT), 生成一个int&的引用类型
class Ref : public Type
{
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个引用类型，使用方式为Ref::create(BuiltInType::INT), 生成一个int&的引用类型
    /// @param parent 
    /// @return 
    static RefRef create(TypeRef parent);

  public:
    Ref(TypeRef parent);

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    virtual uint16_t id() const override {
      return Ref::ID;
    }
};

/// @brief  创建一个引用类型，使用方式为ref_(BuiltInType::INT), 生成一个int&的引用类型
/// @param parent 
/// @return 
inline static RefRef ref_(TypeRef parent) {
    return Ref::create(parent);
}

#endif // REF_HPP
