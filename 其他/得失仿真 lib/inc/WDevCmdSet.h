#ifndef _WDEVCMDSET_H
#define _WDEVCMDSET_H

#define HCTRL_CMD_DATLEN			255

//---ͨ��Э��------------
#define DEV_GET_MODEL			_T("CTRL_CMDGET_MODEL")		//��ȡ�豸�ͺ�
#define DEV_GET_DEVNO			_T("CTRL_CMDGET_DEVNO")		//��ȡ�豸���к�
#define DEV_GET_PROTVER			_T("CTRL_CMDGET_PROTVER")	//��ȡ��ʵ����淶�汾��
#define DEV_CMD_CONNT			_T("CTRL_CMD_CONNT")		//�豸����              
#define DEV_CMD_UNCONNT			_T("CTRL_CMD_UNCONNT")		//�豸�Ͽ�

#define DEV_SET_PSW				_T("CTRL_CMDSET_PSW")		//��������
#define DEV_GET_USERDAT			_T("CTRL_CMDGET_USERDAT")   //��ȡ�Զ����ʶ
#define DEV_SET_USERDAT			_T("CTRL_CMDSET_USERDAT")   //�����Զ����ʶ
#define DEV_GET_DEVSTAT			_T("CTRL_CMDGET_DEVSTAT")   //��ȡ�豸״̬
#define DEV_GET_PWSSTAT			_T("CTRL_CMDGET_PWSSTAT")   //��ȡ����״̬
#define DEV_SET_ENCRYPT			_T("CTRL_CMDSET_ENCRYPT")   //���ü���
#define DEV_GET_DEVINFO			_T("CTRL_CMDGET_DEVINFO")   //��ȡ�豸��Ϣ
#define DEV_CMD_RESETCFG		_T("CTRL_CMD_RESETCFG")		//�ָ���������
#define DEV_CMD_CLSBUF			_T("CTRL_CMD_CLSBUF")		//�������
#define DEV_GET_STATISINFO		_T("CTRL_CMDGET_STATISINFO")	//��ȡ����ͳ��
#define DEV_GET_MAINTAININFO	_T("CTRL_CMDGET_MAINTAININFO")  //��ȡ�豸ά����Ϣ      
#define DEV_CMD_RESTART			_T("CTRL_CMD_DEVRESTART")	//�����豸����
#define	DEV_CMD_CHKSLF			_T("CTRL_CMD_DEVCHKSLF")    //�豸�Լ�
#define DEV_GET_WORKMODE		_T("CTRL_CMDGET_WORKMODE")  //��ȡ����ģʽ
#define DEV_SET_WORKMODE		_T("CTRL_CMDSET_WORKMODE")  //���ù���ģʽ
#define DEV_GET_VERINFO			_T("CTRL_CMDGET_VERINFO")   //��ȡ�̼��汾��

#define DEV_GET_CFGINFOS		_T("CTRL_CMDGET_CFGINFOS")  //��ȡ�豸������Ϣ  
#define DEV_SET_CFGINFOS		_T("CTRL_CMDSET_CFGINFOS")	//�豸����
#define DEV_GET_CFGFMT			_T("CTRL_CMDGET_CFGFMT")	//
#define DEV_SET_SYSPARAM		_T("CTRL_CMDSET_SYSPARAM")	//�����豸ϵͳ����
#define DEV_GET_SYSPARAM		_T("CTRL_CMDGET_SYSPARAM")	//��ȡ�豸ϵͳ����
#define DEV_SET_OPER			_T("CTRL_CMDSET_OPER")		//�豸���Ʋ���

//--�豸Э��------------
#define DEV_CMD_CUSTOMIZE		_T("CTRL_DEVCMD_ST")	//�豸ר��������

//---------------------------------
#define DSEMUL_PVER			0x0100	//Э��汾��
#define DSEMUL_DVER			0x0001  //�豸�汾��

//----------------work mode--------
#define DSINFO_MODE_NORMAL		0
#define DSINFO_MODE_SAMPLE		1 //���ݲ���
#define DSINFO_MODE_BOOT		2 //boot
#define DSINFO_MODE_FACTORY		3 //
#define DSINFO_MODE_UDF			4 //fw�汾����

//-----------MODEL TYPE--------------
#define DS_DEVTYPE_PRINTER		0x01
#define DS_DEVTYPE_HEALTH		0x02
#define DS_DEVTYPE_LED			0x03

//-----------DEVNO TYPE--------------
#define DS_DATTYPE_STR			0x01
#define DS_DATTYPE_HEX			0x02


//--�豸Ӧ����-----------
#define HCTRL_ACK_OK			0x00
#define HCTRL_ERR_UNSUPPORT		0x01	//��֧�ֵ�ָ��
#define HCTRL_ERR_SUM			0x02	//У��Ͳ�ƥ��
#define HCTRL_ERR_UNCONNT		0x03	//�豸��δ����
#define HCTRL_ERR_PARAM			0x04	//��������
#define HCTRL_ERR_LEN			0x05	//���ݳ��ȴ���
#define HCTRL_ERR_MATCH			0x06	//�豸δ������Ӧģ��
#define HCTRL_ERR_PASSWD		0x07	//�������
#define HCTRL_ERR_BUSY			0x08	//�豸æ
#define HCTRL_ERR_MODE			0x80	//mode error
#define HCTRL_ERR_CMDFAIL		0x81	//ִ��ʧ��

#endif
