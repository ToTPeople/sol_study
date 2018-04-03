//
//  access_noname_table.cpp
//  sol_study
//  测试 获取lua没有名称的表中的元素
//  Created by lifushan on 2018/3/20.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int access_noname_table()
{
    sol::state lua;
    lua.open_libraries();
    
    lua.script_file("./other_test/access_noname_table.lua");
    
    printf("\n------------------------ C get no name table test st -------------------------\n\n");
    
    sol::object oo = lua["enemy"];
    sol::table ob = lua["enemy"];
    for (int i = 1; i < 3; ++i) {
        oo = ob[i]["name"];
        std::string name = ob[i]["name"];
        int health = ob[i]["health"];
        printf("--- index[%d], type[%d], name[%s], health[%d] ----\n", i, oo.get_type(), name.c_str(), health);
    }
//    sol::type::function;
    
    printf("\n------------------------ C get no name table test st -------------------------\n\n");
    
    return 0;
}
