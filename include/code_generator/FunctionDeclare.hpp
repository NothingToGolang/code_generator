/**
 * @file FunctionDeclare.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef FUNCTIONDECLARE_HPP
#define FUNCTIONDECLARE_HPP

#include "Type.hpp"
#include <vector>

class FunctionType;
typedef RefObject<FunctionType> FunctionTypeRef;

/**
 * @brief The FunctionType class 函数类型类，用于表示一个函数类型，如int func(int a, int b)的函数类型
 *                           一般可通过Function的type获取
 */
class FunctionType : public Type {
  public:
    typedef std::vector<TypeRef> ParamsContainer;

  public:
    static const uint16_t ID;

  public:
    static FunctionTypeRef create(TypeRef ret, const ParamsContainer &params);

  public:
    FunctionType(TypeRef ret, const ParamsContainer &params);
    virtual ~FunctionType() override;

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

    /// @brief  id 类型id，固定为FunctionType::ID
    /// @return 
    virtual uint16_t id() const override {
      return FunctionType::ID;
    }

    /// @brief  kind 类型种类，固定为Kind::CodeStatment
    /// @return 
    virtual Kind kind() const override { return Code::Kind::CodeStatment; }

  public:
    /// @brief 获取函数的返回值类型
    /// @return 
    TypeRef getReturn() const;

    /// @brief 设置函数的返回值类型
    /// @param ret 
    void setReturn(TypeRef ret);

    /// @brief  paramsContainer 获取函数的参数列表
    /// @return 
    const ParamsContainer &paramsContainer() const;

    /// @brief  setParamsContainer 设置函数的参数列表
    /// @param paramsContainer 
    void setParamsContainer(const ParamsContainer &paramsContainer);

  private:
    TypeRef m_return;
    ParamsContainer m_paramsContainer;
};


#endif // FUNCTIONDECLARE_HPP
