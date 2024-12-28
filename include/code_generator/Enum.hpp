/**
 * @file Enum.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef ENUM_HPP
#define ENUM_HPP

#include "Type.hpp"
#include <vector>

class Enum;
typedef RefObject<Enum> EnumRef;

class EnumDeclare;
typedef RefObject<EnumDeclare> EnumDeclareRef;

/// @brief The EnumDeclare class 枚举声明类，该类用于表示枚举的声明，如enum EnumName，不会包含具体的枚举值
class EnumDeclare : public Type
{
public:
  static EnumDeclareRef create(const String &name = String());

public:
  static const uint16_t ID;

public:
  EnumDeclare();

  /// @brief  构造函数
  /// @param name  枚举名称
  EnumDeclare(const String &name);

public:
  /// @brief  typeWrite 类型写入，将枚举类型写入到对应的队列中
  /// @return 
  virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

  /// @brief  id 类型id，固定为EnumDeclare::ID
  /// @return 
  virtual uint16_t id() const override {
    return EnumDeclare::ID;
  }

public:
  String name() const;
  void setName(const String &name);

private:
  String m_name;
};

/// @class Enum 枚举类，用于表示枚举类型，如enum_({"A", "B", "C"}, "EnumName") 生成 enum EnumName {A, B, C}
class Enum : public Type {
public:
  typedef std::vector<String> EnumNameContainer;

public:
  /// @brief        创建一个枚举类型，使用方式为 enum_({"A", "B", "C"}, "EnumName"), 生成一个EnumName {A, B, C}的枚举
  /// @param fields 枚举元素列表
  /// @param name   枚举名称
  /// @return 
  static EnumRef create(const EnumNameContainer &fields = EnumNameContainer(), const String &name = String());

public:
  static const uint16_t ID;

public:
  Enum(const EnumNameContainer &fields, const String &name);

public:
  /// @brief  typeWrite 实现Code类的typeWrite函数
  /// @param leftSide 
  /// @param rightSide 
  /// @return 
  virtual int typeWrite(Dequque &leftSide, Dequque &rightSide) override;

  /// @brief  id 类型id，固定为Enum::ID
  /// @return 
  virtual uint16_t id() const override {
    return Enum::ID;
  }

public:
  /// @brief  fields 获取枚举元素列表
  EnumNameContainer fields() const;

  /// @brief  setFields 设置枚举元素列表
  /// @param fields 
  void setFields(const EnumNameContainer &fields);

  /// @brief  name 获取枚举名称
  /// @return 
  String name() const;

  /// @brief  setName 设置枚举名称
  /// @param name 
  void setName(const String &name);

public: 
  /// @brief  declare 获取枚举声明
  EnumDeclareRef declare() const;

private:
  EnumDeclareRef m_declare;
  EnumNameContainer m_fields;
  String m_name;
};

/// @brief        创建一个枚举类型，使用方式为 enum_({"A", "B", "C"}, "EnumName"), 生成一个EnumName {A, B, C}的枚举
/// @param fields 枚举元素列表
/// @param name   枚举名称
/// @return 
inline static EnumRef enum_(const Enum::EnumNameContainer &fields = Enum::EnumNameContainer(), const String &name = String()) {
  return Enum::create(fields, name);
}

#endif // ENUM_HPP
