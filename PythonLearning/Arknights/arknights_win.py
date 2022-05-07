import pyautogui
import win32gui
from arknights_config import *


class ArkWin:
    def __init__(self, caption, class_):
        self.hwnd = win32gui.FindWindow(class_, caption)
        self.LoTRegion = zeroRegion
        self.LoBRegion = zeroRegion
        self.RoTRegion = zeroRegion
        self.RoBRegion = zeroRegion
        self.leftRegion = zeroRegion
        self.rightRegion = zeroRegion
        self.gameRegion = zeroRegion
        self.endClickRegion = zeroRegion
        self.firstMsg = True
        if self.isValid():
            self.__getGameRegion()

    def isValid(self):
        if self.hwnd is 0:
            if self.firstMsg:
                print("找不到窗口句柄")
                self.firstMsg = False
            return False
        else:
            return True

    def __getGameRegion(self):
        if self.gameRegion is not zeroRegion:
            return self.gameRegion

        left, top, right, bottom = win32gui.GetWindowRect(self.hwnd)
        if left < 0:
            right = right + left
            left = 0
        if top < 0:
            bottom = bottom + top
            top = 0
        length = right - left
        height = bottom - top
        self.gameRegion = (left, top, length, height)
        self.__division()
        return self.gameRegion

    def __division(self):
        left = self.gameRegion[0]
        top = self.gameRegion[1]
        length = self.gameRegion[2]
        height = self.gameRegion[3]
        right = left + length
        bottom = top + height
        half_length = int(length / 2)
        half_height = int(height / 2)
        mid_x = left + half_length
        mid_y = top + half_height
        self.LoTRegion = (left, top, half_length, half_height)
        self.LoBRegion = (left, mid_y, half_length, half_height)
        self.RoTRegion = (mid_x, top, half_length, half_height)
        self.RoBRegion = (mid_x, mid_y, half_length, half_height)
        self.leftRegion = (left, top, half_length, height)
        self.rightRegion = (half_length, top, half_length, height)
        x = left + int(length * (8 / 10))
        y = top + int(height * (1 / 10))
        w = int(length * (1 / 10))
        h = int(height * (2 / 10))
        self.endClickRegion = (x, y, w, h)

    def display(self):
        print(f'hwnd:{self.hwnd}')
        print(f'gameRegion:{self.gameRegion}')
        print(f'LoTRegion:{self.LoTRegion}')
        print(f'LoBRegion:{self.LoBRegion}')
        print(f'RoTRegion:{self.RoTRegion}')
        print(f'RoBRegion:{self.RoBRegion}')
        print(f'leftRegion:{self.leftRegion}')
        print(f'rightRegion:{self.rightRegion}')
        print(f'endClickRegion:{self.endClickRegion}')

    def getGameImg(self):
        return pyautogui.screenshot(region=self.gameRegion)
