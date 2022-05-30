from arknights_config import *
from arknights_win import ArkWin
from arknights_img import ArkImg
from arknights_state import ArkState
from arknights_logic import ArkLogic
from arknights_flow import ArkFlow

#编译
# 安装pyinstaller : pip install pyinstaller
# 编译成exe文件 : pyinstaller --console --onefile --distpath .\ --name 明日方舟代理指挥脚本 --icon Icon\icon.ico arknights_main.py

arkWin = ArkWin(FrameCaption, FrameClass)
arkImg = ArkImg(IconFolder)
arkState = ArkState(arkWin, arkImg)
arkLogic = ArkLogic(arkWin, arkImg, arkState)
arkFlow = ArkFlow(arkLogic)


def test():
    print('测试开始')
    if arkLogic.isValid():
        # arkWin.display()
        # arkLogic.enableAgent()
        arkState.getGameState(True)
        arkImg.checkImagePosition()
    print('测试结束')


if __name__ == "__main__":
    #test()
    arkFlow.start(0)
