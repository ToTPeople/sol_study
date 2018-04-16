------------------------------
-- lua中包装传递过来的C++类进行扩展（继承）
-- 无法加入到C++类管理中（lua中调用时，table --> usertype非法）
------------------------------

-------------------
-- Car table/class
-------------------
Car = {}
Car.__index = Car

-- constructor
function Car.new()
    local instance = {
        cpb = CBase.new();
    }

    -- set Car as prototype for the new instance
    setmetatable(instance, Car)

    return instance
end

-- method definitions
function Car:set_value(value)
    self.cpb:set_value(value);
end

print("============================ lua test st ===========================")

cc = Car.new();

pp = CBase.new();
dd = ClassMgr.getInstance();

print(type(cc))
print(type(pp))

dd:set_base(pp);
--dd:set_base(cc);

dd:test_base();

print("============================ lua test en ===========================")
