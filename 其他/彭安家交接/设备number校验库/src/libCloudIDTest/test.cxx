// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "../libCloudID/libCloudID.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"



TEST_CASE( "validateCloudID are computed", "[validateCloudID]" ) {

    REQUIRE( validateCloudID(0) != 0 );
	REQUIRE( validateCloudID("1234") != 0 );
	REQUIRE( validateCloudID("1234567890abcde#") != 0 );

	//�汾��δ����
	REQUIRE( validateCloudID("1234567890abcdef") != 0 ); 

	//CRC8 ����
	REQUIRE( validateCloudID("0034567890abcdef") != 0 );

	// IDGenerator������ɵ�
	REQUIRE( validateCloudID("002DF92CE7010400") == 0 );
	REQUIRE( validateCloudID("002A519DEC010F00") == 0 );
	REQUIRE( validateCloudID("004AF79BEC010000") == 0 );
}