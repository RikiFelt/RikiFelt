from arknights_config import *
from arknights_win import ArkWin
from arknights_img import ArkImg
from arknights_state import ArkState
from arknights_logic import ArkLogic
from arknights_flow import ArkFlow

#编译
# 安装pyinstaller : pip install pyinstaller
# 编译成exe文件 : pyinstaller --console --onefile arknights_main.py

arkWin = ArkWin(FrameCaption, FrameClass)
arkImg = ArkImg(IconFolder)
arkState = ArkState(arkWin, arkImg)
arkLogic = ArkLogic(arkWin, arkImg, arkState)
arkFlow = ArkFlow(arkLogic)


def Test():
    print('测试开始')
    if arkLogic.isValid():
        # arkWin.display()
        # arkLogic.enableAgent()
        arkState.getGameState(True)
        arkImg.checkImagePosition()
    print('测试结束')


if __name__ == "__main__":
    #Test()
    arkFlow.Start(0)
