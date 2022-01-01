import pyautogui
import win32gui
import os
import time
import random
from PIL import Image
from enum import Enum

zeroRegion = (0, 0, 0, 0)
FrameCaption = "arknights"
FrameClass = "com.hypergryph.arknights"
IconFolder = 'picture_2160x1360'


class State(Enum):
    Unknown = 0
    Action = 1
    Prepare = 2
    Operation = 3
    End = 4
    LevelUp = 5
    NoSanity = 6
    Error = 7


class ArkWin:
    LoTRegion = zeroRegion
    LoBRegion = zeroRegion
    RoTRegion = zeroRegion
    RoBRegion = zeroRegion
    gameRegion = zeroRegion
    endClickRegion = zeroRegion
    hwnd = 0

    def __init__(self, caption, class_):
        self.hwnd = win32gui.FindWindow(class_, caption)
        self.firstMsg = True
        if self.isValid():
            self._getGameRegion()

    def isValid(self):
        if self.hwnd is 0:
            if self.firstMsg:
                print("找不到窗口句柄")
                self.firstMsg = False
            return False
        else:
            return True

    @classmethod
    def _getGameRegion(cls):
        if cls.gameRegion is not zeroRegion:
            return cls.gameRegion

        left, top, right, bottom = win32gui.GetWindowRect(cls.hwnd)
        if left < 0:
            right = right + left
            left = 0
        if top < 0:
            bottom = bottom + top
            top = 0
        length = right - left
        height = bottom - top
        cls.gameRegion = (left, top, length, height)
        cls._division()
        return cls.gameRegion

    @classmethod
    def _division(cls):
        left = cls.gameRegion[0]
        top = cls.gameRegion[1]
        length = cls.gameRegion[2]
        height = cls.gameRegion[3]
        right = left + length
        bottom = top + height
        half_length = int(length / 2)
        half_height = int(height / 2)
        mid_x = left + half_length
        mid_y = top + half_height
        cls.LoTRegion = (left, top, half_length, half_height)
        cls.LoBRegion = (left, mid_y, half_length, half_height)
        cls.RoTRegion = (mid_x, top, half_length, half_height)
        cls.RoBRegion = (mid_x, mid_y, half_length, half_height)
        x = left + int(length * (8 / 10))
        y = top + int(height * (1 / 10))
        w = int(length * (1 / 10))
        h = int(height * (2 / 10))
        cls.endClickRegion = (x, y, w, h)

    def Display(self):
        print(f'hwnd:{self.hwnd}')
        print(f'gameRegion:{self.gameRegion}')
        print(f'LoTRegion:{self.LoTRegion}')
        print(f'LoBRegion:{self.LoBRegion}')
        print(f'RoTRegion:{self.RoTRegion}')
        print(f'RoBRegion:{self.RoBRegion}')


class ArkImg:
    iconBin = Image.Image
    iconCross = Image.Image
    iconGear = Image.Image
    iconStar = Image.Image
    iconSanity = Image.Image
    iconNoSanity = Image.Image
    iconLevelUp = Image.Image
    iconAgentOff = Image.Image
    iconPrepare = Image.Image
    iconLock = Image.Image

    def __init__(self, folder):
        self.valid = self.__LoadImage(folder)

    def isValid(self):
        return self.valid

    def __LoadImage(self, folder):
        if not os.path.exists(folder):
            print(f'文件夹{folder}不存在!')
            return False
        self.iconBin = self.__OpenImage(folder, 'iconBin')
        if self.iconBin is None:
            return False
        self.iconCross = self.__OpenImage(folder, 'iconCross')
        if self.iconCross is None:
            return False
        self.iconGear = self.__OpenImage(folder, 'iconGear')
        if self.iconGear is None:
            return False
        self.iconStar = self.__OpenImage(folder, 'iconStar')
        if self.iconStar is None:
            return False
        self.iconSanity = self.__OpenImage(folder, 'iconSanity')
        if self.iconSanity is None:
            return False
        self.iconNoSanity = self.__OpenImage(folder, 'iconNoSanity')
        if self.iconNoSanity is None:
            return False
        self.iconLevelUp = self.__OpenImage(folder, 'iconLevelUp')
        if self.iconLevelUp is None:
            return False
        self.iconAgentOff = self.__OpenImage(folder, 'iconAgentOff')
        if self.iconAgentOff is None:
            return False
        self.iconPrepare = self.__OpenImage(folder, 'iconPrepare')
        if self.iconPrepare is None:
            return False
        self.iconLock = self.__OpenImage(folder, 'iconLock')
        if self.iconLock is None:
            return False
        return True

    @staticmethod
    def __OpenImage(folder, name):
        file_path = f'{folder}/{name}.png'
        if os.path.exists(file_path):
            img = Image.open(file_path)
            return img
        else:
            print(f'图片{file_path}不存在!')
            return None


class ArkUtil:
    @staticmethod
    def click(region, sleep=0, recovery=True, msg=False):
        if region is None or region == zeroRegion:
            return

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

    @staticmethod
    def getImageLocation(img, find_region=zeroRegion):
        if find_region == zeroRegion:
            btm = pyautogui.locateOnScreen(img, grayscale=True, confidence=0.9)
        else:
            btm = pyautogui.locateOnScreen(
                img, region=find_region, grayscale=True, confidence=0.9)
        return btm

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


class ArkTest:
    def __init__(self, arkWin, arkImg):
        self.arkWin = arkWin
        self.arkImg = arkImg

    def isValid(self):
        return self.arkWin.isValid() & self.arkImg.isValid()

    def checkImagePosition(self, find_region=zeroRegion):
        ArkUtil.findImageT(self.arkImg.iconBin, 'iconBin', find_region)
        ArkUtil.findImageT(self.arkImg.iconCross, 'iconCross', find_region)
        ArkUtil.findImageT(self.arkImg.iconGear, 'iconGear', find_region)
        ArkUtil.findImageT(self.arkImg.iconStar, 'iconStar', find_region)
        ArkUtil.findImageT(self.arkImg.iconSanity, 'iconSanity', find_region)
        ArkUtil.findImageT(
            self.arkImg.iconNoSanity,
            'iconNoSanity',
            find_region)
        ArkUtil.findImageT(self.arkImg.iconLevelUp, 'iconLevelUp', find_region)
        ArkUtil.findImageT(
            self.arkImg.iconAgentOff,
            'iconAgentOff',
            find_region)
        ArkUtil.findImageT(self.arkImg.iconPrepare, 'iconPrepare', find_region)
        ArkUtil.findImageT(self.arkImg.iconLock, 'iconLock', find_region)


class ArkState:
    def __init__(self, arkWin, arkImg):
        self.arkWin = arkWin
        self.arkImg = arkImg

    def isValid(self):
        return self.arkWin.isValid() & self.arkImg.isValid()

    def getGameState(self, msg=False):
        state = State.Unknown
        if ArkUtil.findImage(self.arkImg.iconStar, self.arkWin.RoTRegion):
            state = State.Action
        elif ArkUtil.findImage(self.arkImg.iconBin, self.arkWin.RoTRegion):
            state = State.Prepare
        elif ArkUtil.findImage(self.arkImg.iconGear, self.arkWin.LoTRegion):
            state = State.Operation
        elif ArkUtil.findImage(self.arkImg.iconStar, self.arkWin.LoBRegion):
            state = State.End
        elif ArkUtil.findImage(self.arkImg.iconLevelUp, self.arkWin.gameRegion):
            state = State.LevelUp
        elif ArkUtil.findImage(self.arkImg.iconNoSanity, self.arkWin.gameRegion):
            state = State.NoSanity
        else:
            state = State.Unknown

        if msg:
            print(f'当前状态:{state}')
        return state


class ArkLogic:
    def __init__(self, arkWin, arkImg, arkState):
        self.arkWin = arkWin
        self.arkImg = arkImg
        self.arkState = arkState

    def isValid(self):
        return self.arkWin.isValid() & self.arkImg.isValid() & self.arkState.isValid()

    def getGameState(self):
        return self.arkState.getGameState()

    def precheck(self):
        if not self.isValid():
            return False
        state = self.arkState.getGameState()
        if state == State.Unknown or \
                state == State.NoSanity:
            print(f"当前游戏状态{state}不正，脚本关闭")
            return False
        return True

    def enableAgent(self):
        if self.arkState.getGameState() == State.Action:
            count = 0
            while True:
                if ArkUtil.findImage(self.arkImg.iconCross,
                                     self.arkWin.RoBRegion):
                    if count > 0:
                        print('开启代理指挥成功')
                    return True
                else:
                    btm_lock = ArkUtil.getImageLocation(
                        self.arkImg.iconLock, self.arkWin.RoBRegion)
                    btm_agent = ArkUtil.getImageLocation(
                        self.arkImg.iconAgentOff, self.arkWin.RoBRegion)
                    if btm_lock is not None:
                        print("该关卡无法代理指挥，请确认关卡信息")
                        return False
                    elif btm_agent is None:
                        print("未找到代理指挥确认框，请查看游戏分辨率是否正常")
                        return False
                    else:
                        count = count + 1
                        print(f"第{count}次尝试开启代理指挥")
                        ArkUtil.click(btm_agent, sleep=1)
                        if count >= 3:
                            print(f"尝试{count}次开启代理指挥失败，脚本关闭")
                            return False
        else:
            print("未处于开始行动界面，脚本关闭")
            return False

    def actionStart(self):
        print("关卡界面")
        state = State.Action
        if self.enableAgent():
            btm = ArkUtil.getImageLocation(
                self.arkImg.iconSanity, self.arkWin.RoBRegion)
            if btm is None:
                state = State.Error
                print("未找到'开始行动'，请查看游戏分辨率是否正常")
            else:
                ArkUtil.click(btm, sleep=1)
        else:
            state = State.Error
        return state

    def prepareStart(self):
        print("编队界面")
        state = State.Prepare
        btm = ArkUtil.getImageLocation(
            self.arkImg.iconPrepare,
            self.arkWin.RoBRegion)
        if btm is None:
            state = State.Error
            print("未找到'开始行动'，请查看游戏分辨率是否正常")
        else:
            ArkUtil.click(btm, sleep=1)
        return state

    def operation(self):
        print(f'代理指挥中：{time.ctime()}')
        time.sleep(10.0)
        return State.Operation

    def operationEnd(self):
        print("结算界面")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)
        return State.End

    def level_up(self):
        print("升级啦!!!")
        ArkUtil.click(self.arkWin.endClickRegion, sleep=2)

    def noSanity(self):
        print("没有理智")
        return State.Error

    def unknown(self):
        print(f'未知界面，等待下一个画面中：{time.ctime()}')
        time.sleep(5)


class ArkMainFlow:
    def __init__(self, arkLogic):
        self.arkLogic = arkLogic

    def isValid(self):
        return self.arkLogic.isValid()

    def ActionLoop(self):
        state = State.Unknown
        while True:
            pre_state = state
            state = self.arkLogic.getGameState()
            if pre_state == State.End and state == State.Action:
                break

            if state == State.Action:
                state = self.arkLogic.actionStart()
            elif state == State.Prepare:
                state = self.arkLogic.prepareStart()
            elif state == State.Operation:
                state = self.arkLogic.operation()
            elif state == State.End:
                state = self.arkLogic.operationEnd()
            elif state == State.LevelUp:
                self.arkLogic.level_up()
            elif state == State.NoSanity:
                state = self.arkLogic.noSanity()
            elif state == State.Unknown:
                self.arkLogic.unknown()

            if state == State.Error:
                return False
        return True

    def StartAction(self, loopcount):
        if not self.arkLogic.precheck():
            return
        for count in range(loopcount):
            print(f'第{count + 1}次代理指挥开始')
            if not self.ActionLoop():
                break
            print(f'第{count + 1}次代理指挥结束')
        print("代理指挥结束")

    def StartActionInput(self):
        count = 0
        while True:
            print('请输入一个大于0的整数')
            try:
                count = int(input())
                if count > 0:
                    break
            except BaseException:
                count = 0
        self.StartAction(count)
        input()


arkWin = ArkWin(FrameCaption, FrameClass)
arkImg = ArkImg(IconFolder)
arkTest = ArkTest(arkWin, arkImg)
arkState = ArkState(arkWin, arkImg)
arkLogic = ArkLogic(arkWin, arkImg, arkState)
arkMainFlow = ArkMainFlow(arkLogic)


def Test():
    if not arkLogic.isValid():
        return
    # arkLogic.EnableAgent()
    # arkState.GetGameState(True)
    # arkTest.CheckImagePosition()


if __name__ == "__main__":
    print('脚本开始')
    if arkMainFlow.isValid():
        # Test()
        arkMainFlow.StartAction(2)
        # arkMainFlow.StartActionInput()
    print('脚本结束')
