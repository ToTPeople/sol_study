//
//  template_try.cpp
//  sol_study
//
//  Created by lifushan on 2018/4/12.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "other_test_header.h"
#include <stdio.h>
#include <string>
#include <vector>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

sol::state lua;

namespace {
    class CTest {
    public:
        CTest() {}
        
    public:
        double ff;
    };
    
    
    class A {
    public:
        A() {}
        
        void ShowA() {
            printf("============= A value[%d] ============\n", _v);
        }
        
    private:
        int _v;
    };
    
    // 模板
    template<typename T>
    struct ValuePosition {
        ValuePosition() : time(0) {}
        ValuePosition(int t, T v) : time(t), value(v) {}
        
        void Show() {
            std::cout << " time: " << time << ", value: " << value << std::endl;
        }
        
        // ms (0, duration)
        int time;
        T value;
    };
    
    template<typename T>
    class ChangePositionsAnimation : public A
    {
    public:
        void ShowValue() {
            c_value.Show();
        }
        
    protected:
        ValuePosition<T> c_value;
        /** 临时提供的参数默认值，后续看是否会影响到相关使用 */
        ChangePositionsAnimation(int64_t startTime = 0, int64_t duration = 0)
        : A() {
        }
    };
    
    // for one value change positions
    template<typename T>
    class OneChangePositionsAnimation : public ChangePositionsAnimation<T>
    {
    public:
        void setChangePositions(ValuePosition<T> positions[], int num) {
//            ChangePositionsAnimation<T>::valuesChange.addValueChange("", positions, num);
        }
        
        void SetValue(T v) {
            ChangePositionsAnimation<T>::c_value.time = 13;
            ChangePositionsAnimation<T>::c_value.value = v;
        }
    };
    
    class TB : public ChangePositionsAnimation<float>
    {
    public:
        TB() :_v(0), _fv(0.0) {}
        
        template<typename T>
        void set_value(int type, T value) {
            if (0 == type) {
                _v = value;
            } else {
                _fv = value;
            }
        }
        
        void show_value() {
            printf("=========== _v[%d], _fv[%d] ===========\n", _v, _fv);
        }
        
    private:
        int     _v;
        float   _fv;
    };
    
    class TestTemplateFunc
    {
    public:
        TestTemplateFunc() :_v(0), _fv(0.0) {}
        
        template<typename T>
        void set_value(int type, T value) {
            std::cout << " type: " << type << ", value: " << value << std::endl;
            if (0 == type) {
                _v = (int)value;
            } else {
                _fv = (float)value;
            }
        }
        
        void show_value() {
            printf("=========== _v[%d], _fv[%f] ===========\n", _v, _fv);
        }
        
    private:
        int     _v;
        float   _fv;
    };
}

//#define UU(TT)  ValuePosition<#TT>
#define STR(s)     #s//#s
//#define CON(S)     STR(ValuePosition  <##S> )
#define CON(S)     STR(ValuePositio##S)
#define CCC(S)         ValuePosition (  ##S ## )
#define macro_start int main ## (void)


#define new_type(type, lua_name) \
lua.new_usertype<ValuePosition<type> >(#lua_name, sol::constructors<ValuePosition<type>(), ValuePosition<type>(int, type)>()\
                                       , "Show", &ValuePosition<type>::Show\
                                       , "time", &ValuePosition<type>::time\
                                       , "value", &ValuePosition<type>::value\
                                       );


int template_try()
{
//    lua.open_libraries();
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table, sol::lib::debug, sol::lib::io, sol::lib::ffi, sol::lib::jit);
    
    lua.new_usertype<TB>("TB"
                         , sol::base_classes, sol::bases<ChangePositionsAnimation<float> >()
                         );
    
    lua.new_usertype<TestTemplateFunc>("TestTemplateFunc"
                                       , "show_value", &TestTemplateFunc::show_value
                                       , "set_value_int", &TestTemplateFunc::set_value<int>
                                       , "set_value_float", &TestTemplateFunc::set_value<float>
                                       );
    
    new_type(int, ValuePosition_int);
    new_type(std::string, ValuePosition_string);
    
    lua.new_usertype<A>("A"
                        , "ShowA", &A::ShowA
                        );
    
//    lua.new_usertype<ValuePosition<std::string> >("ValuePosition_string", sol::constructors<ValuePosition<std::string>(), ValuePosition<int>(int, std::string)>()
//                                          , "Show", &ValuePosition<std::string>::Show
//                                          , "time", &ValuePosition<std::string>::time
//                                          , "value", &ValuePosition<std::string>::value
//                                          );
    
    lua.new_usertype<ChangePositionsAnimation<int> >("ChangePositionsAnimation_int"
                                                     , "ShowValue", &ChangePositionsAnimation<int>::ShowValue
                                                     );
    
    // OneChangePositionsAnimation<<#typename T#>>
//    lua.new_usertype<OneChangePositionsAnimation<CTest> >("OneChangePositionsAnimation_CTest"
//                                                          , "setChangePositions", &OneChangePositionsAnimation<CTest>::setChangePositions
//                                                          , "SetValue", &OneChangePositionsAnimation<CTest>::SetValue
//                                                          , sol::base_classes, sol::bases<ChangePositionsAnimation<CTest> >()
//                                                          );
    
    lua.new_usertype<OneChangePositionsAnimation<int> >("OneChangePositionsAnimation_int"
                                                          , "setChangePositions", &OneChangePositionsAnimation<int>::setChangePositions
                                                          , "SetValue", &OneChangePositionsAnimation<int>::SetValue
                                                          , sol::base_classes, sol::bases<ChangePositionsAnimation<int>,A >()
                                                          );
    
    lua.script_file("./other_test/template_try.lua");
    
    return 0;
}
