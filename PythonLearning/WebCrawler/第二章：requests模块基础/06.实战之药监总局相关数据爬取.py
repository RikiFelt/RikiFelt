import requests
import json

# 许可证查询网址: http://scxk.nmpa.gov.cn:81/xk/

if __name__ == "__main__":
    post_url = 'http://scxk.nmpa.gov.cn:81/xk/itownet/portalAction.do'
    headers = { 'User-Agent' : 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36' }
    param = { 'method': 'getXkzsList' }
    data = {
        'on'             : 'true',
        'page'           : '1',
        'pageSize'       : '15',
        'productName'    : '',
        'conditionType'  : '1',
        'applyname'      : '',
        'applysn'        : '',
    }
    json_ids = requests.post(url=post_url, params=param, data=data, headers=headers).json()
    id_list = []
    for dic in json_ids['list']:
        id_list.append(dic['ID'])

    all_data_list = []
    param = { 'method': 'getXkzsById' }
    for id in id_list:
        data = { 'id' : id }
        detail_json = requests.post(url=post_url, params=param, data=data, headers=headers).json()
        all_data_list.append(detail_json)
        #print(detail_json)
    fp = open('./化妆品许可证列表.json', 'w', encoding='utf-8')
    json.dump(all_data_list, fp=fp, ensure_ascii=False)
    print('Over!!!')


