/**
 * @file CodeBlock.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef CODEBLOCK_HPP
#define CODEBLOCK_HPP

#include "Code.hpp"
#include "CodeContainer.hpp"
#include <vector>

/// @brief The CodeBlock class 代码块类，用于表示一段代码，如函数体，if语句体等
class CodeBlock : public Code
{
  public:
    typedef ::CodeContainer CodeContainer;

  public:
    CodeBlock();
    CodeBlock(const CodeContainer &codeContainer);
    virtual ~CodeBlock() override;

  public:
    /// @brief  toString 将代码转换为字符串，实现Code的虚函数
    /// @return 
    virtual String toString() override;

    /// @brief  write 将代码写入到writer中，实现Code的虚函数
    /// @param writer 
    /// @return 
    virtual int write(CodeWriter &writer) override;

    /// @brief  kind 代码类型，是代码块还是代码段，固定返回Code::CodeBlock
    /// @return 
    virtual Kind kind() const override { return Code::CodeBlock; }

  public:
    /// @brief  codeContainer 获取代码容器, 容器储存所有该代码块的数据
    /// @return 
    CodeContainer codeContainer() const;

    /// @brief  setCodeContainer 设置代码容器
    /// @param codeContainer 
    void setCodeContainer(const CodeContainer &codeContainer);

    /// @brief  addCode 添加代码，可添加所有类型代码
    /// @param code 
    void addCode(const CodeRef &code);

  private:
    CodeContainer m_codeContainer;
};

#endif // CODEBLOCK_HPP
