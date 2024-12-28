/**
 * @file FlowControl.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef FLOWCONTROL_H
#define FLOWCONTROL_H

#include "Code.hpp"
#include "CodeBlock.hpp"
#include <vector>

class FlowControl;
typedef RefObject<FlowControl> FlowControlRef;

/// @class FlowControl 流程控制基类，用于表示if, else等流程控制语句
class FlowControl : public CodeBlock
{
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个流程控制对象
    /// @param name       流程控制名称, 如if, else等
    /// @param condition  流程控制条件, 如if(a > 0)中的a > 0
    /// @param codeContainer 流程控制代码块
    /// @return 
    static FlowControlRef create(const String &name,
                                 const CodeRef condition,
                                 const CodeContainer &codeContainer);

  public:
    FlowControl(const String &name);
    FlowControl(const String &name,
                const CodeRef condition,
                const CodeContainer &codeContainer);

  public:
    /// @brief  toString 将代码转换为字符串
    /// @return 
    virtual String toString() override;

    /// @brief  代码类型，固定为Code::CodeType_Conditaion
    /// @return 
    virtual CodeType codeType() const override { return CodeType_Conditaion; }

    /// @brief  id 类型ID，固定为FlowControl::ID
    /// @return 
    uint16_t id() const override { return ID; }

  public:
    virtual int write(CodeWriter &writer) override;

  public:
    /// @brief  name 获取流程控制名称
    String name() const;

    /// @brief  setName 设置流程控制名称
    /// @param name 
    void setName(const String &name);

    /// @brief  condition 获取流程控制条件
    /// @return 
    CodeRef condition() const;

    /// @brief  setCondition 设置流程控制条件
    /// @param condition 
    void setCondition(const CodeRef &condition);

  protected:
    /// @brief  elseFlowControl 添加else，else if流程控制
    FlowControlRef elseFlowControl() const;

    /// @brief  setElseFlowControl 添加else,else if流程控制
    /// @param elseFlowControl 
    void setElseFlowControl(const FlowControlRef &elseFlowControl);

    /// @brief  mainFlowControl 获取主流程控制，例如if，while等
    /// @return 
    FlowControlRef mainFlowControl() const;

    /// @brief  setMainFlowControl 设置主流程控制，例如if，while等
    /// @param mainFlowControl 
    void setMainFlowControl(const FlowControlRef &mainFlowControl);

  private:
    FlowControlRef m_mainFlowControl;
    FlowControlRef m_elseFlowControl;
    CodeRef m_condition;
    String m_name;
};


class If;
typedef RefObject<If> IfRef;

class Else;
typedef RefObject<Else> ElseRef;

class ElseIf;
typedef RefObject<ElseIf> ElseIfRef;


/// @class Else else流程控制类，用于表示else语句, 用法为else_({代码块})，需要配合if_使用，如if_(a > 0, {代码块}).elsE({代码块}).endIf()
class Else : public FlowControl {
    friend class ElseIf;
    friend class If;
  public:
    static const uint16_t ID;

  public:
    Else();
    Else(const CodeContainer &codeContainer);

    /// @brief  endIf 结束if流程控制，用于表示if语句结束, 该函数必须调用
    /// @return 
    FlowControlRef endIf();
  public:
    uint16_t id() const override { return ID; }
};

/// @class ElseIf else if流程控制类，用于表示else if语句, 用法为elseIF(条件, {代码块})，需要配合if_使用，如if_(a > 0, {代码块}).elseIF(b > 0, {代码块})
class ElseIf : public FlowControl {
    friend class If;
  public:
    static const uint16_t ID;

  public:
    ElseIf();
    ElseIf(CodeRef condition,
       const CodeContainer &codeContainer);

  public:
    /// @brief   elsE 添加else流程控制，用于表示else语句，由原本if(0) elseif (0),
    ///          变成 if(0) elseif(0) else(0)
    /// @param codeContainer 
    /// @return 
    ElseRef elsE(const CodeContainer &codeContainer);

    /// @brief  elseIF 添加else if流程控制，用于表示else if语句，由原本if(0) elseif (0),
    ///                变成 if(0) elseif(0) elseif(0)
    /// @param condition  else if的条件
    /// @param codeContainer  else if的代码块
    /// @return 
    ElseIfRef elseIF(CodeRef condition,
                    const CodeContainer &codeContainer);

    /// @brief  endIf 结束if流程控制，用于表示if语句结束, 该函数必须调用
    /// @return 
    FlowControlRef endIf();

  public:
    uint16_t id() const override { return ID; }
};

/**
 * @brief The If class if流程控制类，用于表示if语句, 用法为if_(条件, {代码块})，如if_(a > 0, {代码块})
 */
class If : public FlowControl, public EnableSharedRefObject<If> {
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个if流程控制对象, 使用方式为if_(条件, {代码块})
    /// @param condition      流程控制条件, 如if(a > 0)中的a > 0
    /// @param codeContainer  流程控制代码块
    /// @return 
    static IfRef create(CodeRef condition = nullptr,
                        const CodeContainer &codeContainer = CodeContainer());

  public:
    If();
    If(CodeRef condition,
       const CodeContainer &codeContainer);

  public:
    /// @brief  elsE 设置else流程控制，用于表示else语句
    /// @param codeContainer  else代码块
    /// @return 
    ElseRef elsE(const CodeContainer &codeContainer);

    /// @brief  elseIF 设置else if流程控制，用于表示else if语句
    /// @param condition 
    /// @param codeContainer 
    /// @return 
    ElseIfRef elseIF(CodeRef condition,
                    const CodeContainer &codeContainer);

  public:
    uint16_t id() const override { return ID; }
};


/// @brief            创建一个if流程控制对象, 使用方式为if_(条件, {代码块})，
///                   如if_(a > 0, {代码块})，若存在eslE或者elseIF，需要调用endIf结束if流程控制
/// @param condition 
/// @param codeContainer 
/// @return 
inline static IfRef if_(CodeRef condition = nullptr,
                 const If::CodeContainer &codeContainer = If::CodeContainer()) {
    return If::create(condition, codeContainer);
}

#endif // FLOWCONTROL_H
