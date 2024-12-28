/**
 * @file Lit.h
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef LIT_H
#define LIT_H
#include "Code.hpp"

class Lit;
typedef RefObject<Lit> LitRef;

/// @brief The Lit class 文本类，用于表示一段文本，如"hello world"
class Lit : public Code
{
public:
  static const uint16_t ID;

public:
  static LitRef create(const String &str);

public:
  Lit(const String &str);

public:
  virtual String toString() override;
  virtual int write(CodeWriter &writer) override;
  virtual Kind kind() const override { return CodeStatment; }
  virtual CodeType codeType() const override { return CodeType_Text; }
  virtual uint16_t id() const override { return ID; }

public:
  /// @brief  value 获取文本内容
  /// @return 
  const String &value() const;

  /// @brief  setValue 设置文本内容
  /// @param value 
  void setValue(const String &value);

private:
  String m_value;
};

#endif // LIT_H
