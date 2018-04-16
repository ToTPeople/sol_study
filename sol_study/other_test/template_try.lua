------------------------------
-- 模板类型实化后，可通过sol传递
-- 宏参数可简化模板传递 编写代码量
------------------------------

print("----------------------------- lua test st -----------------------------");

-- int class
ii_v = ValuePosition_int.new();
print(ii_v.time);
ii_v:Show();

ii_v = ValuePosition_int.new(1, 31);
print(ii_v.time, ii_v.value);
ii_v:Show();

-- string class
ss_v = ValuePosition_string.new()
print(ss_v.time);
ss_v:Show();

ss_v = ValuePosition_string.new(23, "I'm string!!!")
print(ss_v.time);
ss_v:Show();

one_c = OneChangePositionsAnimation_int.new();
one_c:SetValue(99);
one_c:ShowValue();
one_c:ShowA();

print("----------------------------- lua test en -----------------------------");

--[[
lua.new_usertype<TestTemplateFunc>("TestTemplateFunc"
, "show_value", &TestTemplateFunc::show_value
, "set_value_int", &TestTemplateFunc::set_value<int>
, "set_value_float", &TestTemplateFunc::set_value<float>
);
]]

tfunc = TestTemplateFunc.new();
tfunc:show_value();
tfunc:set_value_int(0, 18);
tfunc:show_value();
tfunc:set_value_float(1, 3.14);
tfunc:show_value();
tfunc:set_value_float(0, 9.45);
tfunc:show_value();


print("----------------------------- lua test en222 -----------------------------");
