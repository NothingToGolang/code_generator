/**
 * @file Macro.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef MACRO_HPP
#define MACRO_HPP
#include "Code.hpp"

class Macro;
typedef RefObject<Macro> MacroRef;

/// @brief  宏类，用于表示一段宏类型，如#define PI 3.1415926
class Macro : public Code
{
 public:
    static const uint16_t ID;
 public:
    /// @brief  create 创建一个宏，使用方式为macro("content")，例如macro("#define PI 3.1415926")
    /// @param content 
    /// @return 
    static MacroRef create(const String &content);

 public:
    Macro();
    Macro(const String &content);

 public:
  virtual String toString() override;
  virtual int write(CodeWriter &writer) override;
  virtual Kind kind() const override { return CodeStatment; }
  virtual CodeType codeType() const override { return CodeType_Macro; }
  /**
   * @brief id 类型ID
   * @return
   */
  virtual uint16_t id() const override { return ID; }

 public:
    String content() const;
    void setContent(const String &content);

private:
    String m_content;
};

class Define;
typedef RefObject<Define> DefineRef;

/// @brief define类，用于表示一个宏定义，如#define PI 3.1415926
class Define : public Macro {
  public:
    static const uint16_t ID;

    /// @brief  create 创建一个宏定义，使用方式为define("name", "value")，例如define("PI", "3.1415926")
    /// @param name 
    /// @param value 
    /// @return 
    static DefineRef create(const String &name, const String &value = String());

  public:
    Define();

    /// @brief  构造函数 
    /// @param name  宏名称
    /// @param value  宏值
    Define(const String &name, const String &value = String());

  public:
    virtual uint16_t id() const override { return ID; }
    virtual int write(CodeWriter &writer) override;

  public:
    /// @brief  获取宏定义名称
    /// @return 
    String name() const;

    /// @brief  设置宏定义名称
    /// @param name 
    void setName(const String &name);

    /// @brief  获取宏定义值
    /// @return 
    String value() const;

    /// @brief  设置宏定义值
    /// @param value 
    void setValue(const String &value);

  protected:
    void setMacroContent(const String &name, const String &value);

  private:
    String m_name;
    String m_value;
};

#ifndef macro_
# define macro_(...) Macro::create(__VA_ARGS__)
#endif

#ifndef define_
# define define_(...) Define::create(__VA_ARGS__)
#endif

#endif // MACRO_HPP
