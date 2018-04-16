print("--------------------------- lua st ===================")

print("class A test:")
local a = A.new();
a:call(); -- a.call(self)
aa = A.new(131);
aa:call();

print("\nclass B test:")
local b = B.new();
b:call();
b:only_parent_has();
b:only_b_has();

print("\nclass C test:")
local c = C.new();
c.set_c_value();
c:call();
c:set_c_value(999);
c:call();
C.set_c_value();
c:call();
c:only_parent_has();
c:only_b_has();

c = nil;
collectgarbage();

print("--------------------------- lua en ===================")


