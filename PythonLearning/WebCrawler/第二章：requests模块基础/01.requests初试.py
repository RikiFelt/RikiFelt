import requests

if __name__ == "__main__":
    #1 指定url
    url = "https://www.sogou.com/"
    #2 发起请求
    response = requests.get(url=url)
    #3 获取相应数据
    page_text = response.text
    #4 持久化数据
    with open('./sogou.html','w',encoding='utf-8') as fp:
        fp.write(page_text)