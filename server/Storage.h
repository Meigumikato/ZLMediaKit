//
// Created by oujiangping on 2019/12/19.
//

#ifndef ZLMEDIAKIT_STORAGE_H
#define ZLMEDIAKIT_STORAGE_H

#include <hiredis/hiredis.h>
#include <iostream>
#include <list>
using namespace::std;

namespace REDIS {
    typedef enum {
        SUCCESS = 0,
        CONNECT_ERROR,
        CMD_RUN_ERROR
    } RedisErr;
}

class RedisException: public std::runtime_error {
public:
    RedisException(const char *str = "success" ,int code = REDIS::SUCCESS):runtime_error(str){
        _code = code;
    }
    ~RedisException() = default;
    int code(){ return _code; }
private:
    int _code;
};

class Storage {
private:
    redisContext *mRedisContext;
    string ip;
    unsigned short port;
    int timeout;
public:
    Storage(){};
    void connect(string ip, unsigned short port, int timeout_sec = 10000);
    string hGet(string key, string filed);
    list<string> hGet(string key);
    void hSet(string key, string filed, string value);

    static Storage &Instance();
};

#endif //ZLMEDIAKIT_STORAGE_H