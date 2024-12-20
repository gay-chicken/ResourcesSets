local component = require("component")
local event = require("event")

local ms = component.proxy("")
x = ms.setSensitivity(0.1)
print(x)

local _, uuid, x, y, z, name = event.pull("motion")
print(uuid)
print(x, y, z)
print(name)