local component = require("component")
local sides = require("sides")

local rds = component.redstone
rds.setOutput(sides.north, 4)

local rs1 = component.proxy("")
local rs2 = component.proxy("")

x = rs1.getInput(sides.up)
y = rs2.getInput(sides.up)
print(x, y)

rs1.setOutput(sides.south, y)
rs2.setOutput(sides.south, x)