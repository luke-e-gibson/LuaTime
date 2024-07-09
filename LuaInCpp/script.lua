require "test"


function update()
    print("Omg i got called")
    return 0
end

print("Hello From A Lua Script")

local a = "Hello From Var"

print(a)

function SayHello()
    print("Hello")
end


TestFile.test()

SayHello()