//
//  QueryManager.h
//  DNSServer
//
//  Created by Prathamesh N. Saraf on 4/10/15.
//  Copyright (c) 2015 Prathamesh N. Saraf. All rights reserved.
//

#ifndef __DNSServer__QueryManager__
#define __DNSServer__QueryManager__

#include <stdio.h>
#include <string>
#include <iostream>

class QueryManager
{
    std::string domainName;
    public:
        void processRequest();
};

#endif /* defined(__DNSServer__QueryManager__) */
