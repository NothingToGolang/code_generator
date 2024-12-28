/**
 * @file Function.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "Code.hpp"
#include "FunctionDeclare.hpp"
#include "NamedType.hpp"
#include "CodeBlock.hpp"
#include "TypeDefinition.hpp"
#include "Var.hpp"
#include <vector>

class Function;
typedef RefObject<Function> FunctionRef;

/// @brief The Function class 函数类，用于表示一个函数，如int func(int a, int b) {return a + b;}
///        用法为func_("func", BuiltInType::INT, {argument_("a", BuiltInType::INT), argument_("b", BuiltInType::INT)}, {代码块}),
///        生成int func(int a, int b) {}的函数
class Function : public CodeBlock {
  public:
    static const uint16_t ID;

  public:
    /// @brief          创建一个函数类型
    /// @param ret      返回值类型
    /// @param params   参数列表
    /// @param codeContainer 代码块
    /// @return 
    static FunctionRef create(const String &name,
                              TypeRef ret,
                              const FunctionType::ParamsContainer &params,
                              const CodeContainer &codeContainer);

  public:
    Function(const String &name,
             TypeRef ret,
             const FunctionType::ParamsContainer &params,
             const CodeContainer &codeContainer);
    virtual ~Function() override;

  public:
    virtual int write(CodeWriter &writer) override;
    virtual CodeType codeType() const override { return Code::CodeType_Function; }
    virtual uint16_t id() const override { return Function::ID; }

  public:
    /// @brief  declare 获取函数声明
    /// @return 
    NamedTypeRef declare() const {
      return m_namedFunc;
    }

    /// @brief  type 获取函数类型
    /// @return 
    FunctionTypeRef type() const {
      return m_declare;
    }

    /// @brief  call 调用函数，使用方式为func_->call({参数列表}, 调用者)
    /// @param codeContainer 参数容器
    /// @param var           调用者
    /// @return 
    CodeRef call(const CodeContainer &codeContainer, const VarRef &var = nullptr);

    /**
     * @brief var 转换为一个变量类型
     * @return
     */
    VarRef var();

  public:
    /// @brief  setName 设置函数名称
    /// @param name 
    void setName(const String &name);

    /// @brief  name 获取函数名称
    /// @return 
    String name() const;

  private:
    FunctionTypeRef m_declare;
    NamedTypeRef m_namedFunc;
    CodeContainer m_codeContainer;
};

/// @brief        创建一个函数类型, 使用方式为 func_("func", BuiltInType::INT, {argument_("a", BuiltInType::INT), argument_("b", BuiltInType::INT)}, {代码块}),
///               生成int func(int a, int b) {}的函数
/// @param name   函数名称
/// @param ret    返回值类型
/// @param params 参数列表
/// @param codeContainer 函数代码
/// @return 
inline static FunctionRef func_(const String &name,
                          TypeRef ret,
                          const FunctionType::ParamsContainer &params,
                         const Function::CodeContainer &codeContainer) {
  return Function::create(name, ret, params, codeContainer);
}

/// @brief      生成一个函数调用代码，例如call_("func", {参数列表}, 调用者), 代表 调用者.func(参数列表)，如a.func(1, 2)
/// @param name 
/// @param codeContainer 
/// @param var 
/// @return 
CodeRef call_(const String &name,
             const Function::CodeContainer &codeContainer,
             const VarRef &var = nullptr);

#endif // FUNCTION_HPP
