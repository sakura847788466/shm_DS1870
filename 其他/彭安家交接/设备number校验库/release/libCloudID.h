#ifndef _LIBID_H_
#define _LIBID_H_

#ifndef LIBID_API 
	#ifdef _MSC_VER
		#define LIBID_API extern "C" _declspec(dllimport)
	#else
		#define LIBID_API extern "C"
	#endif	
#endif




//说明：校验云打印ID号的合法性
//参数：
//	@id：十六进制化的字符串，16个字符长度，比如：002DF92CE7010400
//返回值：
//	0表示合法，否则表示非法
//
LIBID_API long validateCloudID(char* id);


#endif