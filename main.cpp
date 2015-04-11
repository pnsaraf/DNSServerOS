//
//  main.cpp
//  DNSServer
//
//  Created by Prathamesh N. Saraf on 4/10/15.
//  Copyright (c) 2015 Prathamesh N. Saraf. All rights reserved.
//

#include "BaseServerClass.h"


int main(int argc, const char * argv[]) {

    static BaseServerClass baseServerObj;
    baseServerObj.serverInit();
    if(baseServerObj.tcpService && baseServerObj.udpService) {
        std::cout<<"Both services up and running"<<std::endl;
    } else if(baseServerObj.tcpService){
        std::cout<<"Only TCP service up and running"<<std::endl;
    } else if(baseServerObj.udpService) {
        std::cout<<"Only UDP service up and running"<<std::endl;
    }

    fd_set rfds;
    FD_ZERO(&rfds);
    
    int tcpSock = baseServerObj.getTCPSock();
    int udpSock = baseServerObj.getUDPSock();
    
    int nfds = (tcpSock > udpSock) ? tcpSock + 1 : udpSock + 1;
    
    while (1) {
        
        FD_SET(tcpSock,&rfds);
        FD_SET(udpSock,&rfds);
        
        if(select(nfds,&rfds, NULL, NULL, NULL) < 0) {
            std::cout<<"Select called failed with error number:  "<<errno<<std::endl;
            FD_ZERO(&rfds);
            continue;
        }
        
        if (FD_ISSET(tcpSock,&rfds)) {
            baseServerObj.acceptconnection("tcp");
        }
        
        if(FD_ISSET(udpSock,&rfds)) {
            baseServerObj.acceptconnection("udp");
        }
    }
    
    return 0;
}
