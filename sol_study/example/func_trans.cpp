//
//  func_trans.cpp
//  sol_study
//  测试：C与lua间函数传递
//  Created by lifushan on 2018/3/15.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "example_header.h"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

static void some_function()
{
    std::cout << "some function!" << std::endl;
}

static void some_other_function()
{
    std::cout << "some other function!" << std::endl;
}

static struct some_class
{
    int variable = 30;
    
    double member_function() {
        return 24.5;
    }
};

int func_trans()
{
    sol::state lua;
    lua.open_libraries();
    
    // 传递C函数到lua，方法一
    lua["f1"] = some_function;
    
    // 传递C函数到lua，方法二
    lua.set("f2", some_other_function);
    
    // 传递C函数到lua，方法三
    lua.set_function("f3", &some_class::member_function, some_class{});
    
    lua.script_file("./example/func_trans.lua");
    
    // 从lua获取函数，方法一
    sol::function f1 = lua["m1"];
    f1();
    // 从lua获取函数，方法二
    sol::function f2 = lua.get<sol::function>("m2");
    f2();
    
    sol::function ftt = lua.get<sol::function>("tt");
    ftt(131, "Hi Hahaha", some_function);
    
    return 0;
}
