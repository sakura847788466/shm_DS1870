
#ifdef _MSC_VER
	#define LIBID_API extern "C" _declspec(dllexport)
#else
	#define LIBID_API extern "C"
#endif	

#include "libCloudID.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>


static const unsigned char CRC7_POLY = 0x91; 
unsigned char getCRC(unsigned char message[], unsigned char length)
{
  unsigned char i, j, crc = 0;
 
  for (i = 0; i < length; i++)
  {
    crc ^= message[i];
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc ^= CRC7_POLY;
      crc >>= 1;
    }
  }
  return crc;
}

bool isHexstring(const char* id)
{
	const char* p = id;
	for(;*p;p++){
		if( !isdigit(*p) && !isalpha(*p) ){
			return false;
		}
	}
	return true;
}

#define BITVALUE(v,bit) ((v >> bit)&0x01)
LIBID_API long validateCloudID(char* id)
{
	long res = 0;

	//初步校验

	if( !id )
		return ++res;
	if(strlen(id) != 16)
		return ++res;	
	if( !isHexstring(id) )
		return ++res;

	//根据版本号校验
	
	const char* pos = id;
	unsigned char buf[8];
	for (size_t count = 0; count < 8; count++) {
        char item[5] = {'0', 'x', pos[0], pos[1], 0};
		buf[count] = strtol(item, NULL, 0);
        pos += 2;
    }

	if( BITVALUE(*buf,7)==0 && BITVALUE(*buf,6)==0 && BITVALUE(*buf,5)==0 && BITVALUE(*buf,4)==0 ){
		
		// byte1

		unsigned char crcSrc = *(buf+1);
		*(buf+1) = 0x6B;
		if( crcSrc != getCRC(buf,8) )
			return ++res;

		//byte2~byte5,最小值>0，最大值<当前时间-起始时间

		long timelen = 0;
		memcpy(&timelen,buf+2,4);
		if( timelen < 0 )
			return ++res;
	}else{ // undefined version
		return ++res;
	}

	return 0;
}



