/*******************************************************************************
   Copyright (C) 2013 SequoiaDB Software Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.
*******************************************************************************/

#ifndef OSSNETWORK_HPP_
#define OSSNETWORK_HPP_
#include "core.hpp"
#include "core.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <string.h>
#define SOCKET_GETLASTERROR errno

//by default 10ms timout
#define OSS_SOCKET_DFT_TIMEOUT 10000

//max hostname
#define OSS_MAX_HOSTNAME NI_MAXHOST
#define OSS_MAX_SERVICENAME NI_MAXSERV

class _ossSocket
{
private:
    int _fd;
    socket_t addressLen;
    socket_t _peerAddressLen;
    struct sockaddr_in _sockAddress;
    struct sockaddr_in _peerAddress;

    bool _init;
    int _timeout;
protected:
    unsigned int _getPort( sockaddr_in *addr);
    int _getAddress(sockaddr_in *addr, char *pAddress, unsigned int length);
public:
    
};

typedef class _ossSocket ossSocket ;

#endif