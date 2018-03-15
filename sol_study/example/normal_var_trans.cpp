//
//  normal_var_trans.cpp
//  sol_study
//
//  Created by lifushan on 2018/3/15.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#include "example_header.h"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int normal_var_trans()
{
    sol::state lua;
    lua.open_libraries();
    
    // 传递C变量到lua，方法一
    lua.script("print(num)");
    
    lua["num"] = 131;
    
    lua.script("print(num)");
    
    // 传递C变量到lua，方法二
    lua.script("print(str)");
    
    lua.set("str", "Value from C to lua");
    
    lua.script("print(str)");
    
    // C从lua获取变量，方法一
    int num = lua.get<int>("num");
    printf("value from lua, num = %d\n", num);
    // C从lua获取变量，方法二
    std::string str = lua["str"];
    printf("value from lua, string = %s\n", str.c_str());
    
    return 0;
}
