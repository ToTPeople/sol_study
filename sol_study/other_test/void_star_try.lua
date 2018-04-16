------------------------------
-- void*可传递，const void*无法传递（应该跟模板传递有关，引用或其他因素引起）
-- lua中没有指针类型，从C传递void*到lua，再从lua传递回C，中间转换应该不是地址，导致最后出错
------------------------------

print("============================ lua test st ===========================")

--print(it);

try = CVoidStarTry.new();
try:show_value();
try:set_value(1, it);
try:show_value();
try:set_value(1, cit);
try:show_value();

try:set_vv(7);
try:show_value();


print("============================ lua test en ===========================")
