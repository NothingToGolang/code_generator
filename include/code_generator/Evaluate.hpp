/**
 * @file Evaluate.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "Code.hpp"
#include "CodeContainer.hpp"
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

class Evaluate;
typedef RefObject<Evaluate> EvaluateRef;

/// @brief The Evaluate class 任意代码类，用于表示一段代码，用于格式化使用，采用{}占位符，
///                           用于格式化代码，如Evaluate::create("int a = {};", {$("15")}), 
///                           生成 int a = 15; 的代码，参数部分为Code类型即可
class Evaluate : public Code
{
public:
    typedef::CodeContainer CodeArguments;

public:
    static const uint16_t ID;

public:
    /// @brief  create 创建一个Evaluate对象, 使用方式为Evaluate::create("int a = {};", {$("15")})
    /// @param format    格式化字符串
    /// @param arguments  参数列表
    /// @return 
    static EvaluateRef create(const String &format, const CodeArguments &arguments = CodeArguments());

    /// @brief          create 创建一个Evaluate对象，采用模板类型推导，使用方式为Evaluate::create("int a = {};", "15")
    /// @tparam ...Args 
    /// @param format 
    /// @param ...args 
    /// @return 
    template<typename... Args>
    static EvaluateRef create(const String &format, Args&&... args) {
      String value = fmt::format<Args...>(format, std::forward<Args>(args)...);
      return create(value, {});
    }

public:
    Evaluate();
    Evaluate(const String &format, const CodeArguments &arguments = CodeArguments());

public:
    virtual String toString() override;
    virtual int write(CodeWriter &writer) override;

    /// @brief  kind 代码种类，固定为Code::CodeStatment
    /// @return 
    virtual Kind kind() const override { return Code::CodeStatment; }

    /// @brief  codeType 代码类型，固定为CodeType_Normal
    /// @return 
    virtual CodeType codeType() const override { return CodeType_Normal; }
    /**
     * @brief id 类型ID，固定为Evaluate::ID
     * @return
     */
    virtual uint16_t id() const override { return ID; }

public:
    String format() const;
    void setFormat(const String &format);

    const CodeArguments &arguments() const;
    void setArguments(const CodeArguments &arguments);

private:
    String m_format;
    CodeArguments m_arguments;
};

#define $(...) Evaluate::create(__VA_ARGS__)

#endif // EVALUATE_HPP


