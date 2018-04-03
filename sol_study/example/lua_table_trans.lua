-------------------
-- Car table/class
-- http://masputih.com/2012/04/easy-inheritance-modularity-in-lua
-------------------
Car = {}
Car.__index = Car

-- constructor
function Car.new(brand,price)
    local instance = {
        _brand = brand,
        _price = price
    }

    -- set Car as prototype for the new instance
    setmetatable(instance, Car)

    return instance
end

-- method definitions
function Car:getBrand()
    return self._brand;
end

function Car:getPrice()
    return self._price;
end

function Car:getInfo()
    print("Brand",self:getBrand(),"price:",self:getPrice())
end

-------------------
-- SUV
-- inherite from Car
-------------------
SUV = {};
SUV.__index = SUV

-- constructor
function SUV.new(brand,price,is4WD)
    local instance = {
        _is4WD = is4WD,
        _price = price,
        _brand = brand,
    }

    -- set SUV as prototype for instance
    setmetatable(instance,SUV)

    return instance
end

-- 设置__index，查找key时，若在SUV中查找不到，会在__index中查找key，若找到则返回；否则，若有__index，则递归查找；不然则返回nil
-- set up inheritance by making Car as prototype for SUV. Now SUV can access & override Car's methods
setmetatable(SUV, {__index = Car})

-- instance method
function SUV:get4WD()
    return self._is4WD;
end
-- override
function SUV:getInfo()
    print("SUV Brand",self:getBrand(),", price:",self:getPrice(),", 4WD",self:get4WD())
end

-------------------
-- 测试lua继承性
-------------------
print("\n------------------------ Lua table inherite test st -------------------------\n\n");
suv_car = SUV.new("Suzuki",150,true);


print(suv_car:getBrand())
print(suv_car:getInfo())
print(type(SUV), type(suv_car));

print("\n------------------------ Lua table inherite test en -------------------------\n\n");

