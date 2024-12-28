/**
 * @file StructOrUnion.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef STRUCTORUNION_HPP
#define STRUCTORUNION_HPP

#include "StructorType.hpp"
#include "Function.hpp"
#include "Field.hpp"
#include <vector>

class Struct;
class Union;
typedef RefObject<Struct> StructRef;
typedef RefObject<Union> UnionRef;

/**
 * @brief The Struct class 结构体类型，用于表示一个结构体类型，如struct A {int a; float b;};等，
 *                         使用方式为struct_({field_("int", "a"), field_("float", "b")}, "A")，生成一个结构体类型
 *                         struct A {int a; float b;}
 *                    
 *                         同时支持添加成员函数和成员字段，通过addFunction和addField添加成员函数和成员字段，
 *                         支持三种权限，PUBLIC, PROTECTED, PRIVATE
 */
class Struct : public StructorType {
  public:
    /// @brief The Permission enum 权限枚举
    enum Permission {
      PUBLIC,     ///< 公有
      PROTECTED,  ///< 保护
      PRIVATE,    ///< 私有
      PERMISSION_COUNT ///< 权限数量（不使用，仅标识）
    };

  public:
    typedef std::vector<FunctionRef> FunctionContainer;
    typedef std::vector<FieldRef> FieldContainer;

  public:
    static const uint16_t ID;

  public:
    /// @brief  create 创建一个结构体类型
    /// @param fields  结构体字段列表
    /// @param name    结构体名称
    /// @return 
    static StructRef create(const MembersContainer &fields, const String &name = "");

  public:
    Struct(const MembersContainer &fields, const String &name = "");

  public:
    virtual uint16_t id() const override {
      return Struct::ID;
    }

  public:
    /**
     * @brief addFunction 添加成员函数
     * @param permission  权限
     * @param func        函数
     */
    void addFunction(const Permission &permission, FunctionRef func);

    /**
     * @brief addField    添加成员字段
     * @param persmission 权限
     * @param field       字段
     */
    void addField(const Permission &persmission, FieldRef field);

    /**
     * @brief addFields   批量添加成员字段
     * @param persmission 权限
     * @param container   字段列表
     */
    void addFields(const Permission &persmission, const FieldContainer &container);

    /**
     * @brief typeWrite  类型写入，实现Type接口
     * @param larea
     * @param rarea
     * @return
     */
    virtual int typeWrite(Dequque &larea, Dequque &rarea) override;

  protected:
    void addPermissionFunc(Permission p, const FunctionContainer &container);
    void addPermissionField(Permission p, const FieldContainer &container);

  private:
    FunctionContainer m_functions[PERMISSION_COUNT];
    FieldContainer m_fields[PERMISSION_COUNT];
};

/**
 * @brief The Union class 联合体类型，用于表示一个联合体类型，如union A {int a; float b;};等
 *                        使用方式为union_({field_("int", "a"), field_("float", "b")}, "A")，
 *                        生成一个联合体类型union A {int a; float b;}         
 */
class Union : public StructorType {
  public:
    static const uint16_t ID;

  public:
    static UnionRef create(const MembersContainer &fields, const String &name = "");

  public:
    Union(const MembersContainer &fields, const String &name = "");

  public:
    virtual uint16_t id() const override {
      return Union::ID;
    }
};

/// @brief        创建一个结构体类型，使用方式为 struct_({field_("int", "a"), field_("float", "b")}, "A")，生成一个结构体类型
/// @param fields 结构体字段列表
/// @param name  结构体名称
/// @return 
inline static StructRef struct_(const Struct::MembersContainer &fields, const String &name = "") {
  return Struct::create(fields, name);
}

/// @brief        创建一个联合体类型，使用方式为 union_({field_("int", "a"), field_("float", "b")}, "A")，生成一个联合体类型
/// @param fields 联合体字段列表
/// @param name   名称
/// @return 
inline static UnionRef union_(const Struct::MembersContainer &fields, const String &name = "") {
  return Union::create(fields, name);
}

#endif // STRUCTORUNION_HPP
