//
//  container_trans.cpp
//  sol_study
//  测试：C容器传递给lua
//  Created by lifushan on 2018/3/15.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <vector>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
    class A {
    public:
        A() : _value(0) {}
        A(int v) : _value(v) {}
        
        void ShowValue() {
            int ccc = 1010;
            printf("\nvalue = %d, ccc = %d\n", _value, ccc);
        }
        
    private:
        int _value;
    };
    
    class CTestVec {
    public:
        static A* GetAIns() { A* pA = new A(); return pA; }
        static A* GetAIns(int v) { A* pA = new A(v); return pA; }
        
    public:
        CTestVec() : a(0) {}
        
        void SetValue(int value) { a = value; }
        void SetValue() { a = 123; }
        void ShowValue() { printf("value=%d", a); }
        void AddA(A* p) {
            pa = p;
        }
        
    private:
        int a;
        A* pa;
    };
}

int container_trans()
{
    sol::state lua;
    lua.open_libraries();
    
    std::vector<CTestVec> vecTest;
    for (int i = 0; i < 5; ++i) {
        CTestVec vecT;
        vecT.SetValue(i*10);
        vecTest.push_back(vecT);
    }
    
    printf("--------------------- C show[before lua deal] st ===================\n");
    int nSize = vecTest.size();
    printf("---- size = %d =====\n", nSize);
    for (int i = 0; i < nSize; ++i) {
        vecTest[i].ShowValue();
        printf("\n");
    }
    printf("--------------------- C show en ===================\n");
    
    // Set a global variable called
    // "vecTest" to be a vector of 5 lements
    lua["vecTest"] = std::ref(vecTest);         // 引用传递，值传递的话，lua中修改不会影响C端
    
    lua.new_usertype<A>("A", sol::constructors<A(), A(int)>(),
                        "ShowValue", &A::ShowValue);
    
    lua.new_usertype<CTestVec>("CTestVec", sol::constructors<CTestVec()>(),
                               "SetValue", sol::overload(sol::resolve<void(int)>(&CTestVec::SetValue),
                                                         sol::resolve<void()>(&CTestVec::SetValue) ),
                               "GetAIns", sol::overload(sol::resolve<A* ()> (&CTestVec::GetAIns),
                                                        sol::resolve<A* (int)> (&CTestVec::GetAIns) ),
                               "ShowValue", &CTestVec::ShowValue,
                               "AddA", &CTestVec::AddA
                               );
    
    lua.script_file("./example/container_trans.lua");
    
    printf("\n--------------------- C show st[after lua deal] ===================\n");
    nSize = vecTest.size();
    printf("---- size = %d =====\n", nSize);
    for (int i = 0; i < nSize; ++i) {
        vecTest[i].ShowValue();
        printf("\n");
    }
    printf("--------------------- C show en ===================\n");
    
    return 0;
}
