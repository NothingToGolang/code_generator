/**
 * @file Ptr.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef PTR_HPP
#define PTR_HPP

#include "Type.hpp"

class Ptr;
typedef RefObject<Ptr> PtrRef;

/**
 * @brief The Ptr class 指针类型，用于表示一个指针类型，如int*，char*等
 */
class Ptr : public Type {
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个指针类型，使用方式为ptr_(BuiltInType::INT), 生成一个int*的指针类型
    /// @param parent 
    /// @return 
    static PtrRef create(TypeRef parent);

  public:
    Ptr(TypeRef parent);

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    virtual uint16_t id() const override {
      return Ptr::ID;
    }
};

/// @brief  创建一个指针类型，使用方式为ptr_(BuiltInType::INT), 生成一个int*的指针类型
/// @param parent 
/// @return 
inline static PtrRef ptr_(TypeRef parent) {
  return Ptr::create(parent);
}

#endif // PTR_HPP
