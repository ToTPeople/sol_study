------------------------------
-- lua中，C++的右值引用(&&) 和 普通 参数等价
------------------------------

print("--------------------------- lua st ===================")

cca = ContructA.new(32);
cca:ShowValue();
uua = 59;
cca:r_rf_test(uua);
print(uua);

cca:class_rf(a);
cca:class_rf(A.new());

print("--------------------------- lua en2 ===================")
