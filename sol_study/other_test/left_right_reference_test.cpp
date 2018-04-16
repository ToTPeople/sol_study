//
//  left_right_reference_test.cpp
//  sol_study
//
//  Created by lifushan on 2018/4/16.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


namespace {
    
    struct lua_wrap_int {
        int tt;
    };
    
    class A {
    public:
        A() : a(10) {}
        A(int _a) : a(_a) {}
        
        void only_parent_has() {
            printf("[A::only_parent_has] just a test.\n");
        }
        
        
        void test_rf(lua_wrap_int* test) {
            //        void test_rf(int* test) {
            int ii = test->tt;
            printf("----------******** test in: %d \n", ii);
            if (ii < 10) {
                ii = 10;
            } else {
                ii = 13;
            }
            printf("----------******** test in end: %d \n", ii);
            test->tt = ii;
        }
        
        virtual int call() {
            printf("[A::call] a[%d]\n", a);
            return a;
        }
        
    public:
        int a;
    };
    
    class ContructA {
    public:
        ContructA(int _V) : value(_V) {}
        
        void ShowValue() {
            printf("------------- value[%d] -----------\n", value);
        }
        
        void l_rf_test(int & l_rf) {
            l_rf = 8;
        }
        void r_rf_test(int && r_rf) {
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ r_rf[%d] $$$$$$$$$$$$$$$$$$$\n", r_rf);
            r_rf = 7;
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  out r_rf[%d] $$$$$$$$$$$$$$$$$$$\n", r_rf);
        }
        void p_l_rf_test(int *&& p_l_rf) {
            //
        }
        
        void class_rf(A& a) {
            printf("-=-=-=-=-=-=-=- & call -=-=-=-=-=-=-=-=-=\n");
            a.a = 70;
        }
        void class_rf(A&& aa) {
            printf("-=-=-=-=-=-=-=- && call -=-=-=-=-=-=-=-=-=\n");
            aa.a = 60;
        }
        //        void class_rf(A aa) {
        //            printf("-=-=-=-=-=-=-=- call -=-=-=-=-=-=-=-=-=\n");
        //            aa.a = 50;
        //        }
        
    private:
        int value;
    };
}

int left_right_reference_test()
{
    sol::state lua;
    lua.open_libraries();
    
    // c/c++ class to lua
    lua.new_usertype<A>("A", sol::constructors<A(), A(int)>()           // construct
                        , "call", &A::call
                        , "only_parent_has", &A::only_parent_has
                        , "test_rf", &A::test_rf
                        //                        , "att", A::att
                        );
    
    lua.new_usertype<ContructA>("ContructA", sol::constructors<ContructA(int)>()
                                , "ShowValue", &ContructA::ShowValue
                                //                                , "l_rf_test", &ContructA::l_rf_test
                                , "r_rf_test", &ContructA::r_rf_test
                                , "p_l_rf_test", &ContructA::p_l_rf_test
                                //                                , "class_l_rf", &ContructA::class_l_rf
                                //                                , "class_r_rf", &ContructA::class_r_rf
                                , "class_rf", sol::overload(sol::resolve<void(A&)>(&ContructA::class_rf)
//                                                                                                                        , sol::resolve<void(A&&)>(&ContructA::class_rf)
                                                            )
                                );
    
    A yy;
    lua["a"] = yy;
    
    lua.script_file("./other_test/left_right_reference_test.lua");
    
    ContructA conA(10);
    int uu = 90;
    conA.r_rf_test(90);
    printf("===========--------- uu[%d] ----------========\n", uu);
    
    conA.class_rf(yy);
    
    return 0;
}
