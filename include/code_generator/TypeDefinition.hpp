/**
 * @file TypeDefinition.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef TYPEDEFINITION_HPP
#define TYPEDEFINITION_HPP

#include "Type.hpp"
#include "CodeContainer.hpp"
#include <vector>

/**
 * @brief The TypeDefinition class 类型定义
 */
class TypeDefinition : public Type
{
  public:
    TypeDefinition(const String &name,
                   TypeRef declare);
  public:
    /**
     * @brief declare 返回一个纯类型，无命名
     * @return
     */
    TypeRef declare() const;

    /**
     * @brief name 获取类型名称
     * @return
     */
    String name() const;

  private:
    String m_name;
};

/// @brief 类型块定义，主要用于类似结构体类型中的类型定义，
///        根据不同的类型确保是否需要换行等，该类型一般不直接使用，而是给struct_和union_等继承，
///        区别于CodeBlock，CodeBlock是提供给所有代码，而该类仅仅是对类型的排版。
///        例如 如struct A {int a; int b;}中的int a; int b
///         struct B { union { int a, int b } C; int d; } 的内部块
class BlockTypeDefinition : public TypeDefinition {
  public:
    enum Position {
      Position_Start = 0x01,
      Position_End = 0x02
    };

    /// @brief  是否有对应的类型标识
    /// @param pos 
    /// @param check 
    /// @return 
    static bool hasPosition(int pos, Position check);

    /**
     * @brief indexToPosition 判断索引的位置信息，例如是否在开头还是结尾等
     * @param idx
     * @param count
     * @return
     */
    static int indexToPosition(int idx, int count);

  public:
    typedef ::CodeContainer CodesContainer;

  public:
    BlockTypeDefinition(const String &name,
                        TypeRef declare,
                        const CodesContainer &codeContainer);
    virtual ~BlockTypeDefinition() override;

  public:
    const CodesContainer &codeContainer() const;

  public:
    virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;
    virtual Kind kind() const override { return Code::CodeBlock; }

  protected:
    /// @brief  添加类型代码
    /// @param code 
    void addCode(CodeRef code);

    /**
     * @brief writeCode
     * @param code
     */
    void writeCode(CodeRef code, int position, Dequque &larea, Dequque &rarea);
  private:
    CodesContainer m_codeContainer;
};

#endif // TYPEDEFINITION_HPP
