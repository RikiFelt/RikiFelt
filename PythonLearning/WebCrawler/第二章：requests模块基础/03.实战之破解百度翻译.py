import requests
import json

if __name__ == "__main__":
    post_url = 'https://fanyi.baidu.com/sug'
    headers = {
        'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36'
    }
    # post请求参数处理(同get请求一致)
    keyword = input('enter a world:')
    data = {
        'kw':keyword
    }
    response = requests.post(url=post_url, data=data, headers=headers)
    # 获取相应数据：json()方法返回的是obj(要确认响应数据是json类型，看 Content-Type: application/json)
    dic_obj = response.json()

    # 持久化
    fileName = keyword + '.json'
    fp = open(fileName, 'w', encoding='utf-8')
    json.dump(dic_obj, fp=fp, ensure_ascii=False)
    print('Over!!!')