#ifndef _LIBID_H_
#define _LIBID_H_

#ifndef LIBID_API 
	#ifdef _MSC_VER
		#define LIBID_API extern "C" _declspec(dllimport)
	#else
		#define LIBID_API extern "C"
	#endif	
#endif




//˵����У���ƴ�ӡID�ŵĺϷ���
//������
//	@id��ʮ�����ƻ����ַ�����16���ַ����ȣ����磺002DF92CE7010400
//����ֵ��
//	0��ʾ�Ϸ��������ʾ�Ƿ�
//
LIBID_API long validateCloudID(char* id);


#endif