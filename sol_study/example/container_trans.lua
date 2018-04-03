print("--------------------------- lua st ===================")

function f (x)
print("container has:")
for k=1,#x do
local v = x[k]
print("\t", k, v:ShowValue())
--print("\t", k, v)
end
print()
end

-- 类对象 vector测试

f(vecTest);

--vecT = CTestVec.new();
local vecT = CTestVec.new();
vecT:SetValue(1010);
local newA = A.new(777);
vecT:AddA(newA);

vecTest:add(vecT);

f(vecTest)

vecTest:erase(1);
--vecTest:clear();
f(vecTest)


testa = CTestVec.GetAIns();
testa:ShowValue();

tt = CTestVec.GetAIns(10);
tt:ShowValue();


var = 10;
print(var);
var = "This is ten";
print(var);
var = 3.1415926;
print(var);

print("--------------------------- lua en ===================")
