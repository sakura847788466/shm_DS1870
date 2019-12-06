DLL_API  uint32_t __stdcall  DAS_Search_TcpPrinter(char *TcpPrinter,int *TcPrinterLength)
{
	//memset(TcpPrinter,0,*TcPrinterLength);
	bool findDesPrinter = false;
	long long start_seconds = time(NULL	);
	auto udpsocket = GetUdpSockfd::getSocket(NULL);

	std::string pathlist;
	//int ret=sendto(s,(char *)Printer_UDP_Search_Cmd,4,0,(sockaddr*)&addrto,sizeof(addrto));    
	auto LocalIps = udpsocket->GetLocalIps();
	for(auto i = LocalIps.begin(); i!= LocalIps.end(); ++i)
	{
		IP_ADDR_STRING *pIpAddrString =&(i->IpAddressList);
		do 
		{
			udpsocket->InitSocket(pIpAddrString->IpAddress.String, 1901);
			int ret=udpsocket->UdpSend((char *)Printer_UDP_Search_Cmd,4);
			if(ret==SOCKET_ERROR){    
				return  DS_CPSDK_UDP_Request_Failure;
			}

			Sleep(100); //Waiting UDP response

			char buf[256];   

			while(1) 
			{
				memset(buf,0,sizeof buf);
				//int slen=recvfrom(s,buf,256,0,(struct sockaddr FAR *)&from,(int FAR *)&fromlength);  
				int slen=udpsocket->UdpRecv(buf,256,100);
				if  ( slen == -1 ) break;

				if ( IsSearchResponse((unsigned char *)buf,slen))
				{
					char ldev[36];
					unsigned char umac[7];
					char mac[20];

					uint64_t fire=0;
					memset(ldev,0,sizeof ldev);
					memset(umac,0,sizeof umac);
					memset(mac,0,sizeof mac);
					struct in_addr  iip;
					memcpy(&iip,buf+5,4);
					memcpy(umac,buf+9,6);
					memcpy(&fire,buf+15,4);
					memcpy(ldev,buf+19,16);
					bcd_to_asc((unsigned char *)mac,umac,12,0);
					{
						if  ( pathlist.length() > 0 ) 	pathlist.append("\n");
						pathlist.append("tcp://");
						pathlist.append(inet_ntoa(iip));
						pathlist.append(":9100:");
						pathlist.append(mac);
						pathlist.append(":");
						pathlist.append(ldev);
						pathlist.append(":");
						memset(mac,0,sizeof mac);
						_ui64toa_s(fire,mac  ,10,10);
						pathlist.append(mac);
						findDesPrinter = true;
					}
				}
				if  ( time(NULL) - start_seconds > Printer_UDP_Wait_Seconds)
				{
					break;
				}
				else Sleep(10);
			}  
			if(findDesPrinter)
				break;


			pIpAddrString=pIpAddrString->Next;
		} while (pIpAddrString);

		if(findDesPrinter)
			break;

	}
	if ( *TcPrinterLength <  (int)pathlist.length() ){
		*TcPrinterLength = (int)pathlist.length();
		return  DS_CPSDK_INVALID_ARG_BUFFER_TOO_LOW;
	}else{
		memset(TcpPrinter,0,*TcPrinterLength);
		*TcPrinterLength = (int)pathlist.length();
		memcpy(TcpPrinter,pathlist.c_str(),*TcPrinterLength);
		return DS_CPSDK_OK;
	}
}