//
//  lua_table_trans.cpp
//  sol_study
//  测试：lua table传递给C
//  Created by lifushan on 2018/3/20.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <string>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int lua_table_trans()
{
    sol::state lua;
    lua.open_libraries();
    
    lua.script_file("./example/lua_table_trans.lua");
    
    printf("\n------------------------ C get table test st -------------------------\n\n");
    sol::optional<int> _price = lua["suv_car"]["_price"];
    if (_price == sol::nullopt) {
        printf("oh no, get table var failed.\n");
    } else {
        printf("get table var[_price] = %d success.\n", _price.value());
    }
    
    sol::table suv = lua["suv_car"];
    sol::object obj = lua["suv_car"]["getPrice"];
    printf("--------- getPrice type[%d] =====\n", obj.get_type());
    sol::optional<sol::function> getPrice = lua["suv_car"]["getPrice"];
    if (getPrice == sol::nullopt) {
        printf("oh no, get table function failed.\n");
    } else {
        printf("get table function[getPrice] success.\n");
        sol::function f = getPrice.value();
        // 需要把操作对象作为第一个参数传递，让lua知道要操作哪个对象
        int r = f(suv);
        printf("function run result is price[%d].\n", r);
    }
    printf("\n------------------------ C get table test en -------------------------\n\n");
    
    
    return 0;
}
