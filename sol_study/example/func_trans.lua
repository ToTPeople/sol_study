print("--------------------------- lua st ===================")
-- define lua func
function m1()
    print("lua func 1");
end

function m2()
    print("lua func 2");
end

function m3()
    print("lua func 3");
end

function tt(a, b, c)
    print(a, b)
    c()
end

-- call C func
f1();
f2();
print(f3());


print("--------------------------- lua en ===================")
