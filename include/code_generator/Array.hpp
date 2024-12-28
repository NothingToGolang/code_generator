/**
 * @file Array.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "Type.hpp"

class Array;
typedef RefObject<Array> ArrayRef;

/**
 * @brief The Array class 数组类，用于表示数组类型，如int[1]，int[2]等
 */
class Array : public Type {
  public:
    static const uint16_t ID;

  public:
    static ArrayRef create(int n, TypeRef parent);

  public:
    Array(int n, TypeRef parent);

  public:
    int size() const;
    void setSize(int size);

  public:
    /// @brief typeWrite 类型写入，将数组类型写入到对应的队列中
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    /// @brief id 类型id
    virtual uint16_t id() const override {
      return Array::ID;
    }

  private:
    int m_size;
};

/// @brief  创建一个数组类型，使用方式为 array_(1, BuiltInType::INT), 生成一个int[1]的数组
/// @param n      数组元素个数
/// @param parent 数组元素类型
/// @return       数组类型
inline static ArrayRef array_(int n, TypeRef parent) {
  return Array::create(n, parent);
}

#endif // ARRAY_HPP
