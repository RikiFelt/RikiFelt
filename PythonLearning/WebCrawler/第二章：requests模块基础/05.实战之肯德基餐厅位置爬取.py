import requests

#肯德基餐厅查询网址：http://www.kfc.com.cn/kfccda/storelist/index.aspx

if __name__ == "__main__":
    get_url = 'http://www.kfc.com.cn/kfccda/ashx/GetStoreList.ashx'
    headers = {
        'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36'
    }
    param = {
        'op': 'keyword'
    }
    keyword = input('查询餐厅地点:')
    data = {
        'cname'     : '',
        'pid'       : '',
        'keyword'   : keyword,
        'pageIndex' : '1',
        'pageSize'  : '10'
    }
    response = requests.post(url=get_url, params=param, data=data, headers=headers)
    page_text = response.text
    with open( keyword+'肯德基餐厅位置.txt','w',encoding='utf-8') as fp:
        fp.write(page_text)
    print('Over!!!')