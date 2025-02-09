/**
 * @file CodeWriter.hpp
 * @author huangjian
 * @date 2022-02-21
 * @version 1.0
 * @copyright huangjian
 **/
#ifndef CODEWRITER_HPP
#define CODEWRITER_HPP

#include "Types.hpp"

/**
 * @brief The CodeWriter class  代码写入器基类，所有代码写入器都需要继承该类，并实现writeString方法
 */
class CodeWriter
{
  public:
    CodeWriter();
    virtual ~CodeWriter();

  public:
    /**
     * @brief writeString
     * @param str
     *        占位符：
     *          $>: 缩进+1
     *          $<: 缩进-1
     *          $s: 间隔
     *          $^: 当前行禁用缩进
     * @return
     */
    virtual int writeString(const String &str) = 0;
};

#endif // CODEWRITER_HPP
