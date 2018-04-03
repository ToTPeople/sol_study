--
-- http://lua-users.org/wiki/TablesTutorial
-- 
print("\n------------------------ Lua table no name access test en -------------------------\n\n");

enemy = {
    aa = "cc",

    {
        name = "ogre",
        health = 30,
        skill = 10,
        sounds = { "ogresond1", "ogresound2"},
    },
    {
        name = "orc",
        health = 10,
        skill = 20,
        sounds = { "orcsond1", "orcsound2"},
    }
    -- and so on
}

print("index 1 name is " .. enemy[1].name);
print("index 2 name is " .. enemy[2].name);

level1 =
{
    music = "music1",
    items =
    {
        A = 1,
        B = 2,
        {
            c = "C",
        }
    }
}

print("level1 table's items table index 1's c value is " .. level1.items[1].c);

print("\n------------------------ Lua table no name access test en -------------------------\n\n");
