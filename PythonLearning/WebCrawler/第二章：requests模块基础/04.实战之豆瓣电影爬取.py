import requests
import json
# json格式化网站 https://www.bejson.com
# 豆瓣电影排行网站 https://movie.douban.com/chart

if __name__ == "__main__":
    get_url = 'https://movie.douban.com/j/chart/top_list'
    headers = {
        'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36'
    }
    params = {
        'type'       : '24',
        'interval_id': '100:90',
        'action'     :'',
        'start'      : '0',
        'limit'      : '20'
    }
    response = requests.get(url=get_url, params=params, headers=headers)
    list_data = response.json()
    fp = open('./豆瓣电影排名.json', 'w', encoding='utf-8')
    json.dump(list_data, fp=fp, ensure_ascii=False)
    print('Over!!!')