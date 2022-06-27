from pyautocad import Autocad, APoint
from operator import itemgetter
import serial
import serial.tools.list_ports
import time

#遍历CAD图形，面积排序，剔除最大值，返回对象列表
def cad_obj():
    acad = Autocad(create_if_not_exists=True)

    obj_dict = {}

    for obj in acad.iter_objects():
        print(obj.ObjectName)
        obj_dict[obj.Area] = obj

    obj_dict = sorted(obj_dict.items(), key=itemgetter(0), reverse=False)

    del obj_dict[-1]

    obj_arr = []
    for obj in obj_dict:
        obj_arr.append(obj[1])

    coor_arr = []
    for obj in obj_arr:

        if obj.ObjectName == "AcDbCircle":
            coor_arr.append(
                (0XFA, 0XFF, ((int)(obj.Center[0]), (int)(obj.Center[1]),
                              (int)(obj.Radius)), 0XFF, 0XFA))

        elif obj.ObjectName == "AcDbPolyline":
            if obj.Closed == True:
                coor_arr.append(
                    (0XEA, 0XEE, tuple([int(num) for num in obj.Coordinates]),
                     0XEE, 0XEA))

            elif obj.Closed == False:
                coor_arr.append(
                    (0XDA, 0XDD, tuple([int(num) for num in obj.Coordinates]),
                     0XDD, 0XDA))

    #print(coor_arr)
    coor_arr.insert(0,(0XAA,0XBB))
    coor_arr.append((0XCC,0XDD))

    return coor_arr

#数据转换，将CAD图形数据转换为一列表
def data_analy(data):
    cad_data = []
    for i in data:
        for j in i:
            if type(j) == tuple:
                for k in j:
                    cad_data.append(k)
        
            else:
                cad_data.append(j)

    return cad_data          

#串口初始化函数
def uart_init():
    port_list = list(serial.tools.list_ports.comports())
    if len(port_list) == 0:
        print('找不到串口')
    else:
        plist_0 = list(port_list[0])
        serialName = plist_0[0]
        print("可用端口名>>>", serialName)
        ser = serial.Serial(serialName, 115200, timeout=60)
    return  ser      


ser = uart_init()
data = cad_obj()
cad_data = data_analy(data)

while True:
    for i in cad_data:
        ser.write(i)
    time.sleep(1)



