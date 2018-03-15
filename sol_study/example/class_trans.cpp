//
//  class_trans.cpp
//  sol_study
//
//  Created by lifushan on 2018/3/15.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
    
    class A {
    public:
        A() : a(10) {}
        A(int _a) : a(_a) {}
        
        void only_parent_has() {
            printf("[A::only_parent_has] just a test.\n");
        }
        
        virtual int call() {
            printf("[A::call] a[%d]\n", a);
            return a;
        }
        
    public:
        int a;
    };
    
    class B : public A {
    public:
        B() : A(), b(20) {
        }
        
        void only_b_has() {
            printf("[B::only_b_has] only B has....\n");
        }
        
        virtual int call() {
            printf("[B::call] b[%d]\n", b);
            return b;
        }
        
    public:
        int b;
    };
    
    class C : public B {
    public:
        C() : B(), c(30) {}
        ~C() { printf("~C\n"); }
        
        virtual int call() {
            printf("[C::call] c[%d]\n", c);
            return c;
        }
        
        void set_c_value(int _c) {
            c = _c;
        }
        
        void set_c_value() {
            c += 1000;
        }
        
    public:
        int c;
    };
}

int class_trans()
{
    sol::state lua;
    lua.open_libraries();
    
    // c/c++ class to lua
    lua.new_usertype<A>("A", sol::constructors<A(), A(int)>()           // construct
                        , "call", &A::call
                        , "only_parent_has", &A::only_parent_has);
    
    lua.new_usertype<B>("B"
                        , "call", &B::call
                        , "only_b_has", &B::only_b_has
                        , "only_parent_has", &A::only_parent_has
                        , sol::base_classes, sol::bases<A>()
                        );
    
    lua.new_usertype<C>("C"
                        , "c", &C::c
                        , "call", &C::call
                        , "set_c_value", sol::overload(sol::resolve<void()>(&C::set_c_value)        // overload
                                                       , sol::resolve<void(int)>(&C::set_c_value)
                                                       )
                        , sol::base_classes, sol::bases<B, A>()         // inherite
                        );
    
    lua.script_file("./example/class_trans.lua");
    
    return 0;
}
