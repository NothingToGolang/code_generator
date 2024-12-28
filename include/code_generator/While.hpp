/**
 * @file While.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef WHILE_HPP
#define WHILE_HPP

#include "FlowControl.hpp"

class While;
typedef RefObject<While> WhileRef;

/// @brief While，代表一个while循环，使用方式while_(条件, {代码块})
class While : public FlowControl
{
public:
  static const uint16_t ID;

public:
  static WhileRef create(const CodeRef condition,
                        const CodeContainer &codeContainer);
public:
  While();
  While(CodeRef condition,
     const CodeContainer &codeContainer);

public:
  uint16_t id() const override { return ID; }
};

/// @brief while_ 生成while循环，使用方式while_(条件, {代码块})，则会生成 while(条件) { 代码块 }
/// @param condition 
/// @param codeContainer 
/// @return 
inline static WhileRef while_(const CodeRef condition,
                       const While::CodeContainer &codeContainer) {
  return While::create(condition, codeContainer);
}

#endif // WHILE_HPP
