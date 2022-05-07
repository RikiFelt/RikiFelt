import os
from PIL import Image
from arknights_config import *
from arknights_util import ArkUtil


class ArkImg:
    def __init__(self, folder):
        self.folder = folder
        self.images = {}
        self.valid = self.__loadImage()

    def isValid(self):
        return self.valid

    def __loadImage(self):
        if not os.path.exists(self.folder):
            print(f'文件夹{self.folder}不存在!')
            return False
        try:
            # 关卡界面-开始演习打叉，右上角星星，右下角开始行动下面的理智，右上角理智，代理开关，代理锁
            self.iconCross = self.__openImage('iconCross')
            self.iconStar = self.__openImage('iconStar')
            self.iconSanity = self.__openImage('iconSanity')
            self.iconSanityRoT = self.__openImage('iconSanityRoT')
            self.iconAgentOff = self.__openImage('iconAgentOff')
            self.iconAgentLock = self.__openImage('iconAgentLock')

            # 编队界面-右上角删除编队,右下角开始行动
            self.iconBin = self.__openImage('iconBin')
            self.iconPrepare = self.__openImage('iconPrepare')

            # 战斗界面-左上角的齿轮图标
            self.iconGear = self.__openImage('iconGear')

            # 补充理智界面-左边理智图标，勾叉图标
            self.iconNoSanity = self.__openImage('iconNoSanity')
            self.iconClearSelect = self.__openImage('iconClearSelect')
            self.iconStone = self.__openImage('iconStone')
            self.iconX = self.__openImage('iconX')
            self.iconY = self.__openImage('iconY')

            # 升级界面-等级提升图标
            self.iconLevelUp = self.__openImage('iconLevelUp')

            # 测试用，无实际作用
            self.iconTest = self.__openImage('iconTest')

            # 愚人号活动对应
            old_folder = self.folder
            self.folder = old_folder + '/StultiferaNavis'
            self.iconCross_SN = self.__openImage('iconCross_SN')
            self.iconAgentOff_SN = self.__openImage('iconAgentOff_SN')
            self.iconAgentLock_SN = self.__openImage('iconAgentLock_SN')
            self.iconSanity_SN = self.__openImage('iconSanity_SN')
            self.folder = old_folder

        except NameError:
            return False
        return True

    def __openImage(self, name):
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
