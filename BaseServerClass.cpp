//
//  BaseServerClass.cpp
//  DNSServer
//
//  Created by Prathamesh N. Saraf on 4/10/15.
//  Copyright (c) 2015 Prathamesh N. Saraf. All rights reserved.
//

#include "BaseServerClass.h"

bool BaseServerClass::initializeTCPServices()
{
    bool flag = false;
    addrinfo *pointerAddrInfo =  createSocket("tcp");
    if(!pointerAddrInfo){
        return flag;
    } else {
        socklen_t socklen = sizeof(sockaddr);
        int _bind = bind(this->tcpSockDescp, (sockaddr *)pointerAddrInfo->ai_addr, socklen);
        if(_bind < -1) {
            return flag;
        } else {
            int _listen = listen(this->tcpSockDescp, 10);
            if(_listen < 0) {
                return flag;
            } else
                flag = true;
        }
    }
    
    return flag;
}


addrinfo* BaseServerClass::createSocket(std::string type)
{
    addrinfo details, *pointerDetails = NULL;
    protoent *protocol = getprotobyname(type.c_str());
    
    details.ai_family = AF_INET;
    details.ai_flags = AI_PASSIVE;
    details.ai_socktype = (!strcmp(type.c_str(), "tcp")) ? SOCK_STREAM : SOCK_DGRAM;
    details.ai_protocol = protocol->p_proto;
    
    if(getaddrinfo(NULL, PORTNUMBER, &details, &pointerDetails) != -1) {
        if(!strcmp(type.c_str(),"tcp")){
            this->tcpSockDescp = socket(pointerDetails->ai_family, pointerDetails->ai_socktype, pointerDetails->ai_protocol);
        } else {
            this->udpSckDesp = socket(pointerDetails->ai_family, pointerDetails->ai_socktype, pointerDetails->ai_protocol);
        }
    }
    
    return pointerDetails;
}


bool BaseServerClass::initializeUDPServices()
{
    bool flag = false;
    addrinfo *pointer = createSocket("udp");
    if(!pointer) {
        return flag;
    } else {
        socklen_t socklen = sizeof(sockaddr);
        int _bind = bind(this->udpSckDesp, pointer->ai_addr, socklen);
        if(_bind != -1) {
            flag = true;
        } else {
            return flag;
        }
    }
    return flag;
}

void* BaseServerClass::receiveTCPNameResolutionRequest(void * param)
{
    sockaddr_storage client;
    socklen_t socklen = sizeof(sockaddr_storage);
    BaseServerClass *obj = (BaseServerClass *)param;
    int ssock = accept(obj->getTCPSock(), (sockaddr*)&client, &socklen);
    if(ssock < 0) {
        std::cout<<"Error accepting connection"<<std::endl;
        pthread_exit(NULL);
    } else {
        char buffer[1024] = {'\0'};
        size_t _recv = 0;
        _recv = recv(ssock, buffer, sizeof(buffer),0);
        if(_recv == 0) {
            std::cout<<"nothing recieved"<<std::endl;
        } else {
            std::cout<<buffer<<std::endl;
        }
    }
    
    pthread_exit(NULL);
}

void BaseServerClass::acceptconnection(std::string connectype)
{
    
    if (!strcmp("tcp", connectype.c_str())) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, &BaseServerClass::receiveTCPNameResolutionRequest, this);
    } else if (!strcmp("udp", connectype.c_str())) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, &BaseServerClass::receiveUDPNameResolutionRequest, this);
    }
}

void * BaseServerClass::receiveUDPNameResolutionRequest(void *param)
{
    sockaddr_storage client;
    char buffer[1024] = {'\0'};
    socklen_t socklen = sizeof(sockaddr_storage);
    BaseServerClass *obj = (BaseServerClass *)param;
    size_t size = 0;
    size = recvfrom(obj->getUDPSock(), buffer, sizeof(buffer), 0, (sockaddr*)&client, &socklen);
    if(size == 0) {
        std::cout<<"Nothing is received"<<std::endl;
    } else {
        std::cout<<buffer<<std::endl;
    }
    pthread_exit(NULL);
}

void BaseServerClass:: serverInit()
{
    this->tcpService = initializeTCPServices();
    this->udpService = initializeUDPServices();
}


