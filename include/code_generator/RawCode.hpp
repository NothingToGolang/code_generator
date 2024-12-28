/**
 * @file RawCode.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef RAWCODE_H
#define RAWCODE_H

#include "Code.hpp"

class RawCode;
typedef RefObject<RawCode> RawCodeRef;

/// @brief  The RawCode class 原始代码类，用于表示一段原始代码，如"int a = 0;"
class RawCode : public Code
{
  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个原始代码对象，全部为用户自定义
    /// @param custom   用户自定义代码
    /// @param typ      代码类型
    /// @param kind     代码种类
    /// @return 
    static RawCodeRef create(const String &custom, CodeType typ = CodeType_Normal, Kind kind = CodeStatment);

  public:
    RawCode(const String &custom, CodeType typ = CodeType_Normal, Kind kind = CodeStatment);

  public:
    virtual String toString() override;
    virtual int write(CodeWriter &writer) override;
    virtual Kind kind() const override { return m_kind; }
    virtual CodeType codeType() const override { return m_type; }
    virtual uint16_t id() const override { return RawCode::ID; }

  private:
    String m_custom;
    Kind m_kind;
    CodeType m_type;
};

/// @brief  _ 创建一个原始代码对象
/// @param custom 
/// @return 
inline static RawCodeRef _(const String &custom) {
    return RawCode::create(custom);
}

extern CODEC_GENERATOR_API RawCodeRef EMPTY_LINE;

#endif // RAWCODE_H
