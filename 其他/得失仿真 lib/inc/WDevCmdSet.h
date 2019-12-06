#ifndef _WDEVCMDSET_H
#define _WDEVCMDSET_H

#define HCTRL_CMD_DATLEN			255

//---通用协议------------
#define DEV_GET_MODEL			_T("CTRL_CMDGET_MODEL")		//获取设备型号
#define DEV_GET_DEVNO			_T("CTRL_CMDGET_DEVNO")		//获取设备序列号
#define DEV_GET_PROTVER			_T("CTRL_CMDGET_PROTVER")	//获取得实仿真规范版本号
#define DEV_CMD_CONNT			_T("CTRL_CMD_CONNT")		//设备连接              
#define DEV_CMD_UNCONNT			_T("CTRL_CMD_UNCONNT")		//设备断开

#define DEV_SET_PSW				_T("CTRL_CMDSET_PSW")		//设置密码
#define DEV_GET_USERDAT			_T("CTRL_CMDGET_USERDAT")   //获取自定义标识
#define DEV_SET_USERDAT			_T("CTRL_CMDSET_USERDAT")   //设置自定义标识
#define DEV_GET_DEVSTAT			_T("CTRL_CMDGET_DEVSTAT")   //获取设备状态
#define DEV_GET_PWSSTAT			_T("CTRL_CMDGET_PWSSTAT")   //获取加密状态
#define DEV_SET_ENCRYPT			_T("CTRL_CMDSET_ENCRYPT")   //设置加密
#define DEV_GET_DEVINFO			_T("CTRL_CMDGET_DEVINFO")   //获取设备信息
#define DEV_CMD_RESETCFG		_T("CTRL_CMD_RESETCFG")		//恢复出厂设置
#define DEV_CMD_CLSBUF			_T("CTRL_CMD_CLSBUF")		//清除缓存
#define DEV_GET_STATISINFO		_T("CTRL_CMDGET_STATISINFO")	//获取数据统计
#define DEV_GET_MAINTAININFO	_T("CTRL_CMDGET_MAINTAININFO")  //获取设备维修信息      
#define DEV_CMD_RESTART			_T("CTRL_CMD_DEVRESTART")	//设置设备重启
#define	DEV_CMD_CHKSLF			_T("CTRL_CMD_DEVCHKSLF")    //设备自检
#define DEV_GET_WORKMODE		_T("CTRL_CMDGET_WORKMODE")  //获取工作模式
#define DEV_SET_WORKMODE		_T("CTRL_CMDSET_WORKMODE")  //设置工作模式
#define DEV_GET_VERINFO			_T("CTRL_CMDGET_VERINFO")   //获取固件版本号

#define DEV_GET_CFGINFOS		_T("CTRL_CMDGET_CFGINFOS")  //获取设备配置信息  
#define DEV_SET_CFGINFOS		_T("CTRL_CMDSET_CFGINFOS")	//设备配置
#define DEV_GET_CFGFMT			_T("CTRL_CMDGET_CFGFMT")	//
#define DEV_SET_SYSPARAM		_T("CTRL_CMDSET_SYSPARAM")	//设置设备系统参数
#define DEV_GET_SYSPARAM		_T("CTRL_CMDGET_SYSPARAM")	//获取设备系统参数
#define DEV_SET_OPER			_T("CTRL_CMDSET_OPER")		//设备控制操作

//--设备协议------------
#define DEV_CMD_CUSTOMIZE		_T("CTRL_DEVCMD_ST")	//设备专用命令码

//---------------------------------
#define DSEMUL_PVER			0x0100	//协议版本号
#define DSEMUL_DVER			0x0001  //设备版本号

//----------------work mode--------
#define DSINFO_MODE_NORMAL		0
#define DSINFO_MODE_SAMPLE		1 //数据采样
#define DSINFO_MODE_BOOT		2 //boot
#define DSINFO_MODE_FACTORY		3 //
#define DSINFO_MODE_UDF			4 //fw版本更新

//-----------MODEL TYPE--------------
#define DS_DEVTYPE_PRINTER		0x01
#define DS_DEVTYPE_HEALTH		0x02
#define DS_DEVTYPE_LED			0x03

//-----------DEVNO TYPE--------------
#define DS_DATTYPE_STR			0x01
#define DS_DATTYPE_HEX			0x02


//--设备应答码-----------
#define HCTRL_ACK_OK			0x00
#define HCTRL_ERR_UNSUPPORT		0x01	//不支持的指令
#define HCTRL_ERR_SUM			0x02	//校验和不匹配
#define HCTRL_ERR_UNCONNT		0x03	//设备尚未连接
#define HCTRL_ERR_PARAM			0x04	//参数错误
#define HCTRL_ERR_LEN			0x05	//数据长度错误
#define HCTRL_ERR_MATCH			0x06	//设备未连接相应模块
#define HCTRL_ERR_PASSWD		0x07	//密码错误
#define HCTRL_ERR_BUSY			0x08	//设备忙
#define HCTRL_ERR_MODE			0x80	//mode error
#define HCTRL_ERR_CMDFAIL		0x81	//执行失败

#endif
