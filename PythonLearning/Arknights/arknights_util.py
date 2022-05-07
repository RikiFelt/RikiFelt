import time
import random
import pyautogui
from arknights_config import *


class ArkUtil:
    @staticmethod
    def click(region, sleep=0, recovery=True, msg=False):
        if region is None or region == zeroRegion:
            return False

        current_mouse_x, current_mouse_y = pyautogui.position()
        move_point_x = region[0] + region[2] * random.random()
        move_point_y = region[1] + region[3] * random.random()
        move_point = (move_point_x, move_point_y)
        pyautogui.moveTo(move_point)
        pyautogui.leftClick()
        if recovery:
            pyautogui.moveTo(current_mouse_x, current_mouse_y)
        if msg:
            print(f'点击:{move_point}')
        time.sleep(sleep + random.random())
        return True

    @staticmethod
    def getImageLocation(img, find_region=zeroRegion):
        if find_region == zeroRegion:
            btm = pyautogui.locateOnScreen(img, grayscale=True, confidence=0.9)
        else:
            btm = pyautogui.locateOnScreen(
                img, region=find_region, grayscale=True, confidence=0.9)
        return btm

    @staticmethod
    def findAndClick(img, find_region=zeroRegion, sleep=0, recovery=True, msg=False):
        btm = ArkUtil.getImageLocation(img, find_region)
        if btm is None:
            return False
        else:
            return ArkUtil.click(btm, sleep=sleep, recovery=recovery, msg=msg)

    @staticmethod
    def findImage(img, find_region=zeroRegion):
        btm = ArkUtil.getImageLocation(img, find_region)
        return True if btm is not None else False

    @staticmethod
    def findImageT(img, name, find_region=zeroRegion):
        btm = ArkUtil.getImageLocation(img, find_region)
        if btm is not None:
            print(f'{name}:{btm}')
        else:
            print(f'找不到{name}')
