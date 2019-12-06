// test.cpp : 定义控制台应用程序的入口点。
//

#include "../libCloudID/libCloudID.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"



TEST_CASE( "validateCloudID are computed", "[validateCloudID]" ) {

    REQUIRE( validateCloudID(0) != 0 );
	REQUIRE( validateCloudID("1234") != 0 );
	REQUIRE( validateCloudID("1234567890abcde#") != 0 );

	//版本号未定义
	REQUIRE( validateCloudID("1234567890abcdef") != 0 ); 

	//CRC8 错误
	REQUIRE( validateCloudID("0034567890abcdef") != 0 );

	// IDGenerator软件生成的
	REQUIRE( validateCloudID("002DF92CE7010400") == 0 );
	REQUIRE( validateCloudID("002A519DEC010F00") == 0 );
	REQUIRE( validateCloudID("004AF79BEC010000") == 0 );
}