import requests

if __name__ == "__main__":
    # UA伪装
    headers = {
        'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36'
    }
    # 指定url
    url = "https://www.sogou.com/web"
    # 处理url携带的参数：封装到字典中
    keyword = input('enter a world:')
    param = {
        'query':keyword
    }
    # 对指定的url发起的请求是携带参数的，并且请求过程中处理了参数
    response = requests.get(url=url,params=param,headers=headers)
    page_text = response.text
    # 持久化数据
    fileName = keyword + '.html'
    with open(fileName,'w',encoding='utf-8') as fp:
        fp.write(page_text)
    print(fileName + '保存成功!!!')
