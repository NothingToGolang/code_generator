/**
 * @file Code.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef CODE_HPP
#define CODE_HPP

#include "CodeWriter.hpp"
#include "Common.hpp"
#include "IdGenerator.hpp"

/**
 * @brief The Code class 代码基类，用于表示代码段，代码块等，是所有代码的基类
 */
class Code
{
  public:
    enum Kind {
      CodeBlock,    // 代码块
      CodeStatment  // 代码段
    };

    enum CodeType {
      CodeType_Normal,  // 普通代码
      CodeType_Type,    // 类型
      CodeType_Var,     // 变量
      CodeType_VarDef,  // 变量定义
      CodeType_Function,// 函数
      CodeType_Conditaion, // 条件变量，如if, else等
      CodeType_Text,      // 文本
      CodeType_Macro      // 宏定义
    };

  public:
    Code() = default;
    virtual ~Code() = default;

  public:
    /// @brief  toString 将代码转换为字符串
    /// @return 
    virtual String toString() = 0;

    /// @brief   write 将代码写入到writer中
    /// @param writer 
    /// @return 
    virtual int write(CodeWriter &writer) = 0;

    /// @brief  kind 代码类型，是代码块还是代码段，参考枚举Kind
    /// @return 
    virtual Kind kind() const = 0;

    /// @brief  codeType 代码类型，用于区分代码的类型，参考枚举CodeType
    /// @return 
    virtual CodeType codeType() const { return CodeType_Normal; }
    /**
     * @brief id 类型ID，用于区分不同的代码类型
     * @return
     */
    virtual uint16_t id() const = 0;
};

typedef RefObject<Code> CodeRef;

#endif // CODE_HPP
