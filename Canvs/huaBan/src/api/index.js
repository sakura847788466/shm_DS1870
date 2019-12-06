import ajax from './ajax'


export const getAll = () => ajax(URL + '/whitelist/getAll')//获取所有白名单列表

export const getSearch = (data) => ajax(URL + '/whitelist/search', data, 'POST')//搜索单个白名单

export const importData = (name,data) => ajax(URL + `/mongodata/importdata?collection=${name}`,data,'POST','form')//获取数据导入的数组











