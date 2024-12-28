/**
 * @file Var.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef VAR_HPP
#define VAR_HPP

#include "NamedType.hpp"
#include "CodeContainer.hpp"
#include <vector>

class Var;
typedef RefObject<Var> VarRef;

class VarDefinition;
typedef RefObject<VarDefinition> VarDefinitionRef;

/// @brief VarDefinition 变量定义，用于定义一个类型的变量，例如int a = 1;
///                      VarDefinition::create("a", BuiltinType::Int, _("1"))
class VarDefinition : public Code, public EnableSharedRefObject<VarDefinition> {
public:
    enum AssignKind {
        EQUAL,        /// 采用赋值方式
        CONSTRUCTOR   /// 采用构造函数方式
    };

    typedef ::CodeContainer CodeRefList;

public:
  static const uint16_t ID;

public:
  static VarDefinitionRef create(const String &name,
                                 TypeRef typ,
                                 const CodeRef &value = nullptr);

public:
  VarDefinition(const String &name, TypeRef parent, const CodeRef &value = nullptr);

public:
  virtual String toString() override;
  virtual int write(CodeWriter &writer) override;
  virtual CodeType codeType() const override { return CodeType_VarDef; }
  virtual uint16_t id() const override { return ID; }
  virtual Kind kind() const override;

public:
  /// @brief  获取给当前变量赋值的值
  /// @return 
  CodeRef value() const;

  /// @brief 当前变量类型
  /// @return 
  TypeRef type() const;

  /// @brief  当前遍历名称
  /// @return 
  String name() const;

public:
  /// @brief  将code赋值给当前变量
  /// @param code 
  /// @return 新的变量类型，其中名称和类型与当前相同，仅类型不同
  VarDefinitionRef assign(const CodeRef &code);

  /// @brief  将当前code作为构造函数参数进行调用，例如 a.construct(_("1")),则代表 类型 a(1);
  /// @param code 构造函数内容
  /// @return 
  VarDefinitionRef construct(const CodeRef &code);

  /// @brief  将当前codes作为构造函数参数进行调用，例如 a.construct({_("1"), _("2")}),则生成 类型 a(1, 2);
  /// @param codes 
  /// @return 
  VarDefinitionRef construct(const CodeRefList &codes);

protected:
  AssignKind assignKind() const;
  void setAssignKind(const AssignKind &assignKind);

private:
  NamedTypeRef m_namedType;
  CodeRef m_value;
  AssignKind m_assignKind;
};

/// @class Var 变量，与VarDefinition不同，该类指代某一个变量，可用于调用函数，寻址，获取下标等
class Var : public Code, public EnableSharedRefObject<Var>
{
public:
    typedef ::CodeContainer CodeContainer;

public:
  static const uint16_t ID;

public:
  static VarRef create(const String &name,
                       TypeRef parent);

public:
  Var(const String &name, TypeRef parent);

public:
  VarRef assign(const CodeRef &code);
  VarRef operator=(const CodeRef &code);

public:
  /**
     * @brief index 获取下标为idx的数组值
     * @param idx
     * @return 若不是数组，那么返回nullptr
     *         若数组越界，抛出out_of_range异常
     */
  VarRef index(size_t idx);

  /**
   * @brief ref 返回一个引用值
   * @return 若不能进行引用，抛出logic_error异常
   */
  VarRef ref();

  /**
   * @brief element 取地址值
   * @return 若不能取地址值，那么直接返回nullptr
   */
  VarRef element();

  /**
   * @brief address 取地址
   * @return 若不能取地址，那么直接返回nullptr
   */
  VarRef address();

  /**
   * @brief call 调用函数
   * @param name
   * @param container
   * @return
   */
  CodeRef call(const String &name, const CodeContainer &container);

public:
  virtual String toString() override;
  virtual int write(CodeWriter &writer) override;
  virtual CodeType codeType() const override { return CodeType_Var; }
  virtual uint16_t id() const override { return ID; }
  virtual Kind kind() const override;

public:
  CodeRef value() const;
  TypeRef type() const;
  String name() const;
  VarDefinitionRef definition() const;

private:
  CodeRef m_value;
  TypeRef m_type;
  String m_name;
};

inline static VarRef var_(const String &name, TypeRef parent) {
  return Var::create(name, parent);
}

#endif // VAR_HPP
