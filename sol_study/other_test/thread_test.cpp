//
//  thread_test.cpp
//  sol_study
//  简单线程传递测试
//  Created by lifushan on 2018/3/20.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <pthread/pthread.h>

#include <thread>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
    
//#define STD_THREAD_TEST
    
}

#ifdef STD_THREAD_TEST
void std_thread_test()
#else
void *posix_thread_test(void *arg)
#endif
{
    int cnt = 0;
    while (1) {
        printf("cnt = %d\n", cnt++);
        usleep(100000);
    }
}

void func()
{
    static int ii = 0;
    printf(" ii = %d\n", ii++);
}

int thread_test()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::coroutine);
    
    //////////////////////////////// C++ 从 lua 获取coroutine调用
    auto code = R"(
        function loop()
            local i = 0
            while true do
                print("pre-yield in loop")
                coroutine.yield(i)
                print("post-yield in loop")
                i = i+1
            end
        end
        loop_th = coroutine.create(loop)
    )";
        
    auto r = lua.safe_script(code, sol::script_pass_on_error);
    assert(r.valid());
    sol::thread runner_thread = lua["loop_th"];
    // C++ get var from lua, exec in C++
    sol::state_view th_state = runner_thread.state();
    sol::coroutine cr = th_state["loop"];
    sol::object oo = lua.get<sol::object>("loop_th");
    printf("----- oo type[%d] ===\n", oo.get_type());
    
    int a[7];
    for (int i = 0; i < 7; ++i) {
        a[i] = cr();
        printf("--- idx[%d], v[%d] ==\n", i, a[i]);
    }
    
    // script exec
    auto test_resume = [&runner_thread]() {
        sol::state_view th_state = runner_thread.state();
        sol::coroutine cr = th_state["loop"];
        int r = cr();
        return r;
    };
    
    lua.set_function("test_resume", std::ref(test_resume));
    
    int v0 = test_resume();
    int v1 = test_resume();
    int v2, v3;
    {
        auto r2 = lua.safe_script("return test_resume()", sol::script_pass_on_error);
        assert(r2.valid());
        auto r3 = lua.safe_script("return test_resume()", sol::script_pass_on_error);
        assert(r3.valid());
        v2 = r2;
        v3 = r3;
    }
    
    printf("v0[%d], v1[%d], v2[%d], v3[%d]\n", v0, v1, v2, v3);
    
    //////////////////////////////// C++ std::thread 传递给 lua
#ifdef STD_THREAD_TEST
    std::thread th(std_thread_test);
    lua["th"] = &th;
    
    lua.new_usertype<std::thread>("stdthread"
                                  , "detach", &std::thread::detach
                                  );
    lua.script_file("./other_test/thread_test.lua");
#else
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, posix_thread_test, NULL);
    if (0 != ret) {
        exit(-1);
    }

    lua.new_usertype<_opaque_pthread_t>("pthread_t");

    lua["pid"] = std::ref(pid);
    lua["th_de"] = pthread_detach;
//    pthread_detach(pid);      // 调用多次，返回值是22

    lua.script_file("./other_test/thread_posix_test.lua");
#endif
    
//    sleep(1);
    
    return 0;
}
