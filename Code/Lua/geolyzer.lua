local component = require("component")
local sides = require("sides")

-- 天空是否可见？透明方块不会影响结果
local ge = component.geolyzer
x = ge.canSeeSky()
print("Is sky visible？ ", x)

-- 能否看见太阳、天气？时间和方块都会影响结果
x = ge.isSunVisible()
print("Is sun and weather visible？ ", x)

-- 探测相对坐标方块
-- 输入：相对地质探测器的x和y坐标
-- 输出：以地质探测器为中心33，[1, 64]对应方块的硬度，由于存在噪声影响导致离探测器越远值变化越大
x = ge.scan(0, 0)
print(x[33])

-- 输入：一个矩形区域的x, z, y相对坐标
-- 输出：一个64个值的线性表，只有前n个值有效。n=x*y*z
x = ge.scan(0, 0, 0, 0, 1, 0)
print(x[2])

-- 分析相邻方块的详细信息
x = ge.analyze(sides.up)
for k, v in pairs(x) do
    print(k, v)
end