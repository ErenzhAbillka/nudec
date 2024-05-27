# 计算路径类
# distance: 正方形左上角到右上角的实际距离
# PathX: 输入(实际坐标, 目标坐标) 输出: int(水平方向转动角), int(垂直方向转动角)
class Motion_Path:
    def __init__(self, distance = 0.6):
        self.distance = (cx_list[1] - cx_list[0]) / distance * 1

    def PathX(self, actualx, actualy, targetx, targety):
        # Length calculation
        OriToActX = math.sqrt(abs(center_pointx - actualx) ** 2 +
                              abs(center_pointy - actualy) ** 2 )
        OriToTarY = math.sqrt(abs(center_pointx - targetx) ** 2 +
                              abs(center_pointy - actualy) ** 2)
        CamToActX = math.sqrt(OriToActX ** 2 + self.distance ** 2)
        CamToTarY = math.sqrt(OriToTarY ** 2 + self.distance ** 2)
        TarToAct  = abs(actualx - targetx)

        #Cosine theorem
        gammaRad  = math.acos((CamToActX ** 2 + CamToTarY ** 2 - TarToAct ** 2) /
                              (2 * CamToActX * CamToTarY))
        gammaDeg  = math.degrees(gammaRad)

        YOriToActX = math.sqrt(abs(center_pointx - targetx) ** 2 +
                              abs(center_pointy - actualy) ** 2)
        YOriToTarY = math.sqrt(abs(center_pointx - targetx) ** 2 +
                              abs(center_pointy - targety) ** 2)
        YCamToActX = math.sqrt(YOriToActX ** 2 + self.distance ** 2)
        YCamToTarY = math.sqrt(YOriToTarY ** 2 + self.distance ** 2)
        YTarToAct = abs(actualy - targety)

        # Cosine theorem
        YgammaRad = math.acos((YCamToActX ** 2 + YCamToTarY ** 2 - YTarToAct ** 2) /
                             (2 * YCamToActX * YCamToTarY))
        YgammaDeg = math.degrees(YgammaRad)
        return int(gammaDeg), int(YgammaDeg)

#____PID____
# 位置式PID
class PID:
    def __init__(self, kp=1.0, ki=0, kd=0):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.Error = 0
        self.Error_sum = 0
        self.Error_last = 0

    def update(self, setpoint, current_value):
        self.Error = setpoint - current_value
        self.Error_sum += self.Error
        output = (self.kp * self.Error +
                  self.ki * self.Error_sum +
                  self.kd * (self.Error - self.Error_last))
        self.Error_last = self.Error
        return output
#____END____

import sensor, image, time, pyb, math
from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)  # must be turned off for color tracking
sensor.set_auto_whitebal(False)  # must be turned off for color tracking
clock = time.clock()

#____Initialize____
cx_list = []
cy_list = []

i = 0

cx = 0
cy = 0
dx = 0
dy = 0

leftUpX   , leftUpY    = 0, 0
rightUpX  , rightUpY   = 0, 0
rightDownX, rightDownY = 0, 0
leftDownX , leftDownY  = 0, 0

center_pointx = 0
center_pointy = 0

red_threshold   = (67, 100, -33, -10, -128, 127)  # 红色激光阈值
black_threshold = (1, 29, -36, 8, -35, 18)  # 黑色线框阈值
#____END____

#____USART____         # 帧头：2C, 04   帧尾: 5B
# 波特率:9600 数据位:8 停止位:1 检验位:None
uart = UART(1, 9600)  # 定义串口3变量
uart.init(9600, bits=8, parity=None, stop=1)  # init with given parameters

# 接收数据
# if(接受到标志: 9) -> 记录此时的cx, cy坐标, 返回转动角度
# if(接受到标志: 8) -> 定位矩形四角并进行运算,返回转动角度
def recive_data():
    global uart
    while uart.any():
        char = uart.readchar()
        if char == 8:
            check_rectangle()
            dx, dy = record()
            Running_8(dx, dy)
        elif char == 9:
            record_incood(cx, cy)


# 拍照记录坐标
# 调用时截图一张图片,返回红色激光此时的坐标值
def record():
    global dx, dy
    clock.tick()                        # Turn on the clock
    img = sensor.snapshot()             # Turn on the sensor
    dx = cx
    dy = cy
    return dx, dy

# 记录红色激光数据
# if(记录次数小于4次) -> 重复记录
# if(i大于等于4)     -> 在终端中打印出记录的数据
#                      计算出中心点x(y)
def record_incood(cx, cy):
    global cx_list, cy_list, i, center_pointx, center_pointy, distance
    if i < 4:
        print("Record " + str(i))
        cx_list.append(cx)
        cy_list.append(cy)
        i = i + 1
    elif i == 4:
        for j in range(4):
            print(cx_list[j], cy_list[j])
        center_pointx = (cx_list[1] - cx_list[0]) / 2
        center_pointy = (cy_list[2] - cy_list[0]) / 2

        dx, dy = record()
        Running_9(dx, dy)

# 寻找最大色块
# 进行判断,筛选出最大色块
def find_max(blobs):
    max_size = 0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob

#____END____

#____Angle_calculations____
# 检测矩形
# 拍照检测矩形四个角, 以y大小进行升序排序, 较大二者为上角, 较小二者为下脚
#                 再以x大小进行判断排序, 较大者为右角  , 较小者为左角
# return: 左上, 右上, 左下, 右下
def check_rectangle():
    global img, leftUpX, leftUpY, rightUpX, rightUpY, rightDownX, rightDownY, leftDownX, leftDownY
    for r in img.find_rects(threshold=10000):
        # 绘制矩形轮廓
       img.draw_rectangle(r.rect(), color=(255, 0, 0))

       # 获取并绘制矩形角点
       corners = r.corners()
       corners = sorted(corners, key=lambda c: (c[1], c[0]))  # 按 y 坐标排序，如果 y 坐标相同按 x 坐标排序

       # 左上角和右上角
       if corners[0][0] > corners[1][0]:
           corners[0], corners[1] = corners[1], corners[0]

       # 左下角和右下角
       if corners[2][0] > corners[3][0]:
           corners[2], corners[3] = corners[3], corners[2]

       labels = ['zx1', 'zy2', 'zx2', 'zy1']  # 顺时针顺序：左上、右上、右下、左下
       for i, corner in enumerate(corners):
           img.draw_circle(corner[0], corner[1], 5, color=(0, 255, 0))
           print(f"{labels[i]}: ({corner[0]}, {corner[1]})")

       leftUpX   , leftUpY    = corners[0][0], corners[0][1]
       rightUpX  , rightUpY   = corners[1][0], corners[1][1]
       rightDownX, rightDownY = corners[3][0], corners[3][1]
       leftDownX , leftDownY  = corners[2][0], corners[2][1]



def Running_9(dx, dy):
    mot = Motion_Path(117)
    theta1x, theta1y = mot.PathX(dx , dy , cx_list[0], cy_list[0])      #chushihua
    theta2x, theta2y = mot.PathX(cx_list[0], cy_list[0], cx_list[1], cy_list[1])      #you
    theta3x, theta3y = mot.PathX(cx_list[1], cy_list[1], cx_list[2], cy_list[2])      #xia
    theta4x, theta4y = mot.PathX(cx_list[2], cy_list[2], cx_list[3], cy_list[3])      #zuo
    theta5x, theta5y = mot.PathX(cx_list[3], cy_list[3], cx_list[0], cy_list[0])      #shang

    theta2x = ~theta2x
    theta3y = ~theta3y

    # 将角度值转换为补码表示法的无符号整数
    def to_byte(val):
        if val < 0:
            val = 256 + val
        return val

    theta_values = [0x2C, 4, to_byte(theta1x), to_byte(theta1y), to_byte(theta2x), to_byte(theta2y), to_byte(theta3x),
                    to_byte(theta3y), to_byte(theta4x), to_byte(theta4y), to_byte(theta5x), to_byte(theta5y), 0x5B]


    # 将角度值打包成字节数组
    data = bytes(theta_values)

    # 将数据写入串口
    uart.write(data)

    print("Send9End")

def Running_8(dx, dy):
    mot = Motion_Path(117)

    if leftUpY > rightUpY:              # 左上在右上上面
        theta1x, theta1y = mot.PathX(dx, dy, leftUpX, leftUpY)  # chushihua
        theta2x, theta2y = mot.PathX(leftUpX, leftUpY, rightUpX, rightUpY)  # xia
        theta3x, theta3y = mot.PathX(rightUpX, rightUpY, rightDownX, rightDownY)  # zuo
        theta4x, theta4y = mot.PathX(rightDownX, rightDownYq, leftDownX, leftDownY)
        theta5x, theta5y = mot.PathX(leftDownX, leftDownY, leftUpX, leftUpY)

    elif leftUpY < rightUpY:
        theta1x, theta1y = mot.PathX(dx, dy, rightUpY, rightUpX)  # chushihua
        theta2x, theta2y = mot.PathX(rightUpX, rightUpY, rightDownX, rightDownY)  # xia
        theta3x, theta3y = mot.PathX(rightDownX, rightDownY, leftDownX, leftDownY)  # zuo
        theta4x, theta4y = mot.PathX(leftDownX, leftDownY, leftUpX, leftUpY)
        theta5x, theta5y = mot.PathX(leftUpX, leftUpY, rightUpY, rightUp)
        theta1x = ~theta1x
    # 取反
    theta2x = ~theta2x
    theta5x = ~theta5x
    theta2y = ~theta2y
    theta3y = ~theta3y

    theta_values = [0x2C, 4, int(theta1x), int(theta1x), int(theta2x), int(theta2y), int(theta3x),
                             int(theta3y), int(theta4x), int(theta4y), int(theta5x), int(theta5y), 0x5B]

    # 将角度值打包成字节数组
    data = bytes(theta_values)

    # 将数据写入串口
    uart.write(data)

    print("Send8End")
#____END____

# 循环寻找红色激光点
while True:
    clock.tick()                        # Turn on the clock
    img = sensor.snapshot()             # Turn on the sensor
    recive_data()                       # reciving data

    #____FindRedLaser____
    blobs = img.find_blobs([red_threshold])
    if blobs:
        # 如果找到了目标颜色
        max_b = find_max(blobs)
        # Draw a rect around the blob.
        img.draw_rectangle(max_b[0:4])  # rect
        #img.draw_rectangle(max_green_blob.rect())  # rect
        # 用矩形标记出目标颜色区域
        img.draw_cross(max_b[5], max_b[6])  # cx, cy
        # 在目标颜色区域的中心画十字形标记
        cx = max_b[5]
        cy = max_b[6]
    #____END____

