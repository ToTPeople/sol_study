//
//  add_lua_class_2_c_mgr_test.cpp
//  sol_study
//
//  Created by lifushan on 2018/4/13.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


class CBase {
public:
    CBase() : vv(0) {}
    
    virtual void set_value(int ii) {
        vv = ii;
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

class ClassMgr {
public:
    static ClassMgr* getInstance();
    
    void set_base(CBase* pB) {
        pBase = pB;
    }
//    void set_base(void* pB) {
//        pBase = (CBase*)pB;
//    }
    
    void test_base() {
        if (NULL == pBase) {
            printf("========= pBase is null ========\n");
            return;
        }
        
        pBase->set_value(88);
        pBase->show_value();
    }
    
public:
    ~ClassMgr() {
        if (NULL != pBase) {
            delete pBase;
            pBase = NULL;
        }
    }
    
private:
    ClassMgr() {}
    
private:
    static ClassMgr* ins;
    CBase*           pBase;
};

ClassMgr* ClassMgr::ins = NULL;

ClassMgr* ClassMgr::getInstance() {
    if (NULL == ins) {
        ins = new ClassMgr();
    }
    return ins;
}

int add_lua_class_2_c_mgr_test()
{
    sol::state lua;
    lua.open_libraries();
    
    lua.new_usertype<CBase>("CBase"
                            , "set_value", &CBase::set_value
                            , "show_value", &CBase::show_value
                            );
    
    lua.new_usertype<ClassMgr>("ClassMgr"
                               , "new", sol::no_constructor
                               , "getInstance", &ClassMgr::getInstance
                               , "set_base", &ClassMgr::set_base
                               , "test_base", &ClassMgr::test_base
                               );
    
    lua.script_file("./other_test/add_lua_class_2_c_mgr_test.lua");
    
    ClassMgr::getInstance()->test_base();
    
    return 0;
}
