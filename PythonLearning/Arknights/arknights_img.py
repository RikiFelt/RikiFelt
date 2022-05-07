import os
from PIL import Image
from arknights_config import *
from arknights_util import ArkUtil


class ArkImg:
    def __init__(self, folder):
        self.folder = folder
        self.images = {}
        self.valid = self.__LoadImage()

    def isValid(self):
        return self.valid

    def __LoadImage(self):
        if not os.path.exists(self.folder):
            print(f'文件夹{self.folder}不存在!')
            return False
        try:
            # 关卡界面-开始演习打叉，右上角星星，右下角开始行动下面的理智，右上角理智，代理开关，代理锁
            self.iconCross = self.__OpenImage('iconCross')
            self.iconStar = self.__OpenImage('iconStar')
            self.iconSanity = self.__OpenImage('iconSanity')
            self.iconSanityRoT = self.__OpenImage('iconSanityRoT')
            self.iconAgentOff = self.__OpenImage('iconAgentOff')
            self.iconAgentLock = self.__OpenImage('iconAgentLock')

            # 编队界面-右上角删除编队,右下角开始行动
            self.iconBin = self.__OpenImage('iconBin')
            self.iconPrepare = self.__OpenImage('iconPrepare')

            # 战斗界面-左上角的齿轮图标
            self.iconGear = self.__OpenImage('iconGear')

            # 补充理智界面-左边理智图标，勾叉图标
            self.iconNoSanity = self.__OpenImage('iconNoSanity')
            self.iconX = self.__OpenImage('iconX')
            self.iconY = self.__OpenImage('iconY')

            # 升级界面-等级提升图标
            self.iconLevelUp = self.__OpenImage('iconLevelUp')

            # 测试用，无实际作用
            self.iconTest = self.__OpenImage('iconTest')

            # 愚人号活动对应
            old_folder = self.folder
            self.folder = old_folder + '/StultiferaNavis'
            self.iconCross_SN = self.__OpenImage('iconCross_SN')
            self.iconAgentOff_SN = self.__OpenImage('iconAgentOff_SN')
            self.iconAgentLock_SN = self.__OpenImage('iconAgentLock_SN')
            self.iconSanity_SN = self.__OpenImage('iconSanity_SN')
            self.folder = old_folder

        except NameError:
            return False
        return True

    def __OpenImage(self, name):
        file_path = f'{self.folder}/{name}.png'
        if os.path.exists(file_path):
            self.images[name] = Image.open(file_path)
            return self.images[name]
        else:
            print(f'图片{file_path}不存在!')
            raise NameError()

    def checkImagePosition(self, find_region=zeroRegion):
        for key in self.images:
            ArkUtil.findImageT(self.images[key], key, find_region)