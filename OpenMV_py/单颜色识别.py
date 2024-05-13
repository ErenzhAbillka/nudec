import time, image,sensor,math,pyb,ustruct
from image import SEARCH_EX, SEARCH_DS
from pyb import Pin, Timer,LED

#从imgae模块引入SEARCH_EX和SEARCH_DS。使用from import仅仅引入SEARCH_EX,
#SEARCH_DS两个需要的部分，而不把image模块全部引入。


sensor.reset()

# Set sensor settings
sensor.set_contrast(1)
sensor.set_gainceiling(16)
# Max resolution for template matching with SEARCH_EX is QQVGA
sensor.set_framesize(sensor.QQVGA)
# You can set windowing to reduce the search image.

sensor.set_pixformat(sensor.GRAYSCALE)

sensor.set_windowing(0, 40, 160, 40)  #观察窗口  后面ROI设置也会以这个为新的基准

rx_buff=[]
state = 0
tx_flag = 0

x = 0

Find_Task =1       #1
Target_Num =0
data = [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00]


uart = pyb.UART(3, 115200, timeout_char = 1000)     #定义串口1变量
blue_led = LED(2)


########串口接收数据函数处理#########
def Receive_Prepare():      #data
    global state
    global x
    global tx_flag
    global data
    global Find_Task
    global Target_Num
    if state==0:
        data[0]=uart.readchar()
        if data[0] == 0x0d:#帧头
            state = 1
        else:
            state = 0
            rx_buff.clear()
    elif state==1:
        data[1]=uart.readchar()
        Target_Num=data[x+1]
        state = 2
    elif state==2:
        data[2]=uart.readchar()
        Find_Task=data[x+2]
        state = 3
    elif state == 3:
        data[4]=uart.readchar()
        if data[4] == 0x5b:
            state = 4
    elif state == 4:
        state=0

    else:
        state = 0
        rx_buff.clear()





clock = time.clock()
# Run template matching
while (True):
    clock.tick()
    img = sensor.snapshot()# 镜头初始化
    if(uart.any()>0):
       Receive_Prepare()

    print(clock.fps(),Find_Task, Target_Num)

