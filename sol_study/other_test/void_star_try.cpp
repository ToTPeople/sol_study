//
//  void_star_try.cpp
//  sol_study
//
//  Created by lifushan on 2018/4/13.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


class CVoidStarTry {
public:
    CVoidStarTry() : vv(0) {}
    
    void set_value(int type, const void* value) {
        printf("****** const *****\n");
        vv = *((int*)value);
    }
    
    void set_value(int type, void* value) {
        printf("****** normal *****\n");
        vv = *((int*)value);
    }
    
    void set_vv(int _vv) {
        set_value(3, &_vv);
    }
    
    void test(void* tc) {
        //
    }
    
    void show_value() {
        printf("------------ value[%d] -------\n", vv);
    }
    
private:
    int     vv;
};

int void_star_try()
{
    sol::state lua;
    lua.open_libraries();
    
    int ii = 10;
    int *it = &ii;
//    *it = 9;
    const int *cit;
    cit = it;
    CVoidStarTry tet;
    tet.show_value();
    tet.set_value(5, it);
    tet.show_value();
    
    tet.set_value(6, cit);
    tet.show_value();
    
    lua.new_usertype<CVoidStarTry>("CVoidStarTry"
                                   , "test", &CVoidStarTry::test
                                   , "set_vv", &CVoidStarTry::set_vv
                                   , "set_value", sol::overload(
                                                                sol::resolve<void(int, void*)>(&CVoidStarTry::set_value)
                                                                )
//                                   , "set_value", &CVoidStarTry::set_value
                                   , "show_value", &CVoidStarTry::show_value
                                   );
    
    lua["it"] = it;
//    lua["it"] = std::unique_ptr<int>(it);
    lua["cit"] = cit;
    
    lua.script_file("./other_test/void_star_try.lua");
    
    return 0;
}
