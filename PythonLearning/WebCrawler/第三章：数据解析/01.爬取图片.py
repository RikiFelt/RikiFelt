import requests
#糗图百科 https://www.qiushibaike.com/
if __name__ == "__main__":
    url = "https://pic.qiushibaike.com/system/pictures/12495/124959285/medium/TWTN7LCR2D85HDXM.jpg"
    # content返回的事二进制形式的图片数据
    img_data = requests.get(url=url).content
    # 写入模式为二进制写入wb,不需要utf-8
    with open('./糗图.jpg','wb') as fp:
        fp.write(img_data)