import ctypes
import ctypes.wintypes
import time

class POINT(ctypes.Structure):
    _fields_ = [("x", ctypes.c_long), ("y", ctypes.c_long)]

def get_mouse_position():
    pt = POINT()
    ctypes.windll.user32.GetCursorPos(ctypes.byref(pt))
    return pt.x, pt.y

print("5초 후부터 마우스 위치를 출력합니다. Ctrl+C로 종료")

time.sleep(5)

try:
    while True:
        x, y = get_mouse_position()
        print(f"정확한 마우스 좌표: x={x}, y={y}    ", end="\r")
        time.sleep(0.1)
except KeyboardInterrupt:
    print("\n종료되었습니다.")
