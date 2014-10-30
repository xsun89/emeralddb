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
#include <stdio.h>
#include "../include/ossSocket.hpp"

_ossSocket::_ossSocket(unsigned int port, int timeout)
{
    _init = false;
    _fd = 0;
    _timeout = timeout;
    memset(&_sockAddress, 0, sizeof(sockaddr_in));
    memset(&_peerAddress, 0, sizeof(sockaddr_in));
    _peerAddressLen = sizeof(_peerAddress);

    _sockAddress.sin_family = AF_INET;
    _sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    _sockAddress.sin_port = htons(port);
    _addressLen = sizeof(_sockAddress);
}

_ossSocket::_ossSocket()
{
    _init = false;
    _timeout = 0;
    _fd = 0;
    memset(&_sockAddress, 0, sizeof(sockaddr_in));
    memset(&_sockAddress, 0, sizeof(sockaddr_in));
    _peerAddressLen = sizeof(_peerAddress);
}

_ossSocket::_ossSocket(const char *pHostname, unsigned int port, int timeout)
{
    struct hostent *hp;
    _init = false;
    _timeout = timeout;
    _fd = 0;
    memset(&_sockAddress, 0, sizeof(sockaddr_in));
    memset(&_peerAddress, 0, sizeof(sockaddr_in));
    _peerAddressLen = sizeof(_peerAddress);

    _sockAddress.sin_family = AF_INET;
    if( (hp = gethostbyname(pHostname)))
        _sockAddress.sin_addr.s_addr = *((int *)hp->h_addr_list[0]);
    else
        _sockAddress.sin_addr.s_addr = inet_addr(pHostname);
    _sockAddress.sin_port = htons(port);
    _addressLen = sizeof(_sockAddress);
}

_ossSocket::_ossSocket(int *sock, int timeout)
{
    int rc = EDB_OK;
    _fd = *sock;
    _init = true;
    _timeout = timeout;
    _addressLen = sizeof(_sockAddress);
    memset(&_peerAddress, 0, sizeof(sockaddr_in));
    _peerAddressLen = sizeof(_peerAddress);

    rc = getsockname(_fd, (sockaddr*)&_sockAddress, &_addressLen);
    if(rc)
    {
        printf("Failed to get sock name, error = %d", SOCKET_GETLASTERROR);
        _init = false;
    } else{
        rc = getpeername ( _fd, (sockaddr*)&_peerAddress, &_peerAddressLen ) ;
        if ( rc )
        {
            printf ( "Failed to get peer name, error = %d",
                    SOCKET_GETLASTERROR ) ;
        }
    }
}

int _ossSocket::initSocket()
{
    int rc = EDB_OK;
    if(_init)
    {
        goto done;
    }
    memset(&_peerAddress, 0, sizeof(sockaddr_in));
    _peerAddressLen = sizeof(_peerAddress);
    _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( -1 == _fd)
    {
        printf("Failed to initialize socket, error = %d",
                SOCKET_GETLASTERROR);
        rc = EDB_NETWORK;
        goto error;
    }
    _init = true;
    setTimeout(_timeout);
done:
    return rc;
error:
    goto done;
}

int _ossSocket::setTimeout(int seconds)
{
    int rc = EDB_OK;
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;

    rc = setsockopt(_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv));
    if(rc)
        printf("Failed to setsockopt, rc=%d", SOCKET_GETLASTERROR);
    rc = setsockopt ( _fd, SOL_SOCKET, SO_SNDTIMEO, ( char* ) &tv,
            sizeof ( tv ) ) ;
    if ( rc )
    {
        printf ( "Failed to setsockopt, rc = %d", SOCKET_GETLASTERROR ) ;
    }

    return rc ;

}
