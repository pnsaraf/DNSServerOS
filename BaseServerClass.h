//
//  BaseServerClass.h
//  DNSServer
//
//  Created by Prathamesh N. Saraf on 4/10/15.
//  Copyright (c) 2015 Prathamesh N. Saraf. All rights reserved.
//

#ifndef __DNSServer__BaseServerClass__
#define __DNSServer__BaseServerClass__

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <errno.h>
#include "QueryManager.h"
#include <pthread/pthread.h>

#define PORTNUMBER "9000"

class BaseServerClass
{
 
    int tcpSockDescp;
    int udpSckDesp;
    
    bool initializeTCPServices();
    bool initializeUDPServices();

    addrinfo* createSocket(std::string type);
    public:
    BaseServerClass()
    {
        //Initialize to invalid state
        tcpSockDescp = -1;
        udpSckDesp = -1;
    }
    
    static void *receiveTCPNameResolutionRequest(void *);
    static void *receiveUDPNameResolutionRequest(void *);
    QueryManager query_manager;
    void serverInit();
    bool tcpService;
    bool udpService;
    int getTCPSock() {return tcpSockDescp;}
    int getUDPSock() {return udpSckDesp;}
    void acceptconnection(std::string);

};
#endif /* defined(__DNSServer__BaseServerClass__) */
