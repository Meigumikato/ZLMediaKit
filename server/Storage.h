//
// Created by oujiangping on 2019/12/19.
//

#ifndef ZLMEDIAKIT_STORAGE_H
#define ZLMEDIAKIT_STORAGE_H

#include <iostream>
#include <list>
#include "jsoncpp/json.h"
#include <sw/redis++/redis++.h>

using namespace sw::redis;
using namespace Json;
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
    string ip;
    unsigned short port;
    int timeout;
    Redis getRedis();
public:
    Storage(){};
    void connect(string ip, unsigned short port, int timeout_sec = 10000);
    list<Value> hGet(string key);
    void hSet(string key, string filed, Value value);
    void hDel(string key, string filed);
    static Storage &Instance();
};

#endif //ZLMEDIAKIT_STORAGE_H