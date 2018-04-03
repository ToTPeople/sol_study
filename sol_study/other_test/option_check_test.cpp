//
//  option_check_test.cpp
//  sol_study
//  测试：安全从lua获取变量
//  Created by lifushan on 2018/3/19.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include "other_test_header.h"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


int option_check_test()
{
    sol::state lua;
    lua.open_libraries();
    
    // 通过sol::optional安全获取 变量类型及值
    sol::optional<double> d_var = lua["df"];
    if (d_var == sol::nullopt) {
        printf("===== var is not exist or double type =====\n");
    }
    
    lua.script("df = 'Hello World!'");
    sol::optional<double> f_var = lua["df"];
    if (f_var == sol::nullopt) {
        printf("===== var is not exist or double type =====\n");
    }
    
    sol::optional<std::string> str_var = lua["df"];
    if (str_var == sol::nullopt) {
        printf("===== var is not exist or double type =====\n");
    } else {
        printf("===== var is [%s] =====\n", str_var.value().c_str());
    }
    
    // 通过获取object，根据object类型判断，再转到对应类型
    sol::object obj = lua.get<sol::object>("df");
    printf("---- obj type[%d] =====\n", obj.get_type());
    bool is_d = obj.is<std::string>();
    std::string str = obj.as<std::string>();
    obj = lua.get<sol::object>("if");
    printf("---- obj type[%d], is_d[%d], str[%s] =====\n", obj.get_type(), is_d, str.c_str());
    
    return 0;
}
