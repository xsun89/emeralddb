#inclucde "../include/core.hpp"
#include "command.hpp"
#include "commandFactory.hpp"

COMMAND_BEGIN
COMMAND_ADD(COMMAND_CONNECT, ConnectCommand)
COMMAND_ADD(COMMAND_QUIT, QuitCommand)
COMMAND_ADD(COMMAND_HELP, HelpCommand)
COMMAND_END

extern int gQuit;
int ICommand::execute(ossSocket &sock, std::vector<std::string> &argVec)
{
    return EDB_OK;
}

int ICommand::getError(int code)
{
  switch(code)
   {
      case EDB_OK:
         break;
      case EDB_IO:
         std::cout << "io error is occurred" << std::endl;
         break;
      case EDB_INVALIDARG:
         std::cout << "invalid argument" << std::endl;
         break;
      case EDB_PERM:
         std::cout << "edb_perm" << std::endl;
         break;
      case EDB_OOM:
         std::cout << "edb_oom" << std::endl;
         break;
      case EDB_SYS:
         std::cout << "system error is occurred." << std::endl;
         break;
      case EDB_QUIESCED:
         std::cout << "EDB_QUIESCED" << std::endl;
         break;
      case EDB_NETWORK_CLOSE:
         std::cout << "net work is closed." << std::endl;
         break;
      case EDB_HEADER_INVALID:
         std::cout << "record header is not right." << std::endl;
         break;
      case EDB_IXM_ID_EXIST:
         std::cout << "record key is exist." << std::endl;
         break;
      case EDB_IXM_ID_NOT_EXIST:
         std::cout << "record is not exist" << std::endl;
         break;
      case EDB_NO_ID:
         std::cout << "_id is needed" << std::endl;
         break;
      case EDB_QUERY_INVALID_ARGUMENT:
         std::cout << "invalid query argument" << std::endl;
         break;
      case EDB_INSERT_INVALID_ARGUMENT:
         std::cout <<  "invalid insert argument" << std::endl;
         break;
      case EDB_DELETE_INVALID_ARGUMENT:
         std::cout << "invalid delete argument" << std::endl;
         break;
      case EDB_INVALID_RECORD:
         std::cout << "invalid record string" << std::endl;
         break;
      case EDB_SOCK_NOT_CONNECT:
         std::cout << "sock connection does not exist" << std::endl;
         break;
      case EDB_SOCK_REMOTE_CLOSED:
         std::cout << "remote sock connection is closed" << std::endl;
         break;
      case EDB_MSG_BUILD_FAILED:
         std::cout << "msg build failed" << std::endl;
         break;
      case EDB_SOCK_SEND_FAILD:
         std::cout << "sock send msg faild" << std::endl;
         break;
      case EDB_SOCK_INIT_FAILED:
         std::cout << "sock init failed" << std::endl;
         break;
      case EDB_SOCK_CONNECT_FAILED:
         std::cout << "sock connect remote server failed" << std::endl;
         break;
      default :
         break;
   }
   return code;
}

int ICommand::recvReply(ossSocket &sock)
{
    int length = 0;
    int ret = EDB_OK;
    memset(_recvBuf, 0, RECV_BUF_SIZE);
    if(!sock.isConnected())
    {
        return getError(EDB_SOCK_NOT_CONNECT);
    }
    while(1)
    {
        ret = sock.recv(_recvBuf, sizeof(int));
        if(EDB_TIMEOUT == ret){
            continue;
        }else if(EDB_NETWORK_CLOSE == ret){
            return getError(EDB_SOCK_REMOTE_CLOSED);
        }else{
            break;
        }
    }
    length = *((int *)_recvBuf);
    if(length > RECV_BUF_SIZE ){
        return getError(EDB_RECV_DATA_LENGTH_ERROR );
    }

    while(1)
    {
        ret = sock.recv(&_recvBuf[sizeof(int)], length-sizeof(int));
        if(ret == EDB_TIMEOUT ){
            continue;
        }else if(EDB_NETWORK_CLOSE == ret ){
            return getError(EDB_SOCK_REMOTE_CLOSED);
        }else{
            break;
        }
    }

    return ret;
}