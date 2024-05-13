import sensor, image, time
from pyb import UART

# 定义红色和绿色的阈值
red_threshold = (71, 100, -74, -20, -11, 33)
green_threshold = (80, 100, -13, 12, -39, 21)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()

uart = UART(1, 9600)  # 初始化串口1
uart.init(9600, bits=8, parity=None, stop=1)

def find_max(blobs):
    max_size = 0
    max_blob = None
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob

while True:
    clock.tick()
    img = sensor.snapshot()

    cx_red, cy_red, cx_green, cy_green = 0, 0, 0, 0

    # 检测红色色块
    blobs_red = img.find_blobs([red_threshold])
    if blobs_red:
        max_red_blob = find_max(blobs_red)
        if max_red_blob:
            cx_red = max_red_blob.cx()
            cy_red = max_red_blob.cy()
            img.draw_rectangle(max_red_blob.rect())
            img.draw_cross(cx_red, cy_red)

    # 检测绿色色块
    blobs_green = img.find_blobs([green_threshold])
    if blobs_green:
        max_green_blob = find_max(blobs_green)
        if max_green_blob:
            cx_green = max_green_blob.cx()
            cy_green = max_green_blob.cy()
            img.draw_rectangle(max_green_blob.rect())
            img.draw_cross(cx_green, cy_green)

    # 判断是否检测到红色色块和绿色色块，如果都检测到了才发送数据
    if cx_red != 0 and cy_red != 0 and cx_green != 0 and cy_green != 0:
        # 构造要发送的数据
        data = bytearray([0x2C, 0x04, cx_green, cy_green, cx_red, cy_red, 0x5B])
        # 通过串口发送数据
        uart.write(data)
        # 打印检测到的坐标信息和帧率
        print("Red Blob: ({}, {}) - Green Blob: ({}, {})".format(cx_red, cy_red, cx_green, cy_green))

    # 打印帧率

