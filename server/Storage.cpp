//
// Created by oujiangping on 2019/12/19.
//
#include "Storage.h"
#include "Util/util.h"

using namespace toolkit;

Storage::Storage(string ip, unsigned short port, int timeout_sec) {
    this->ip = ip;
    this->port = port;
    this->timeout = timeout_sec;
    connect();
}

void Storage::connect() {
    struct timeval t = {timeout};
    mRedisContext = redisConnectWithTimeout((const char*) ip.c_str(), port, t);

    if(NULL == mRedisContext || mRedisContext->err) {
        throw RedisException("connect to redis error", REDIS::CONNECT_ERROR);
    }
}

string Storage::hGet(string key, string filed) {
    string cmd = StrPrinter << "HGET " << key << " " << filed;
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, (const char*) cmd.c_str());
    if(mRedisReply == NULL || mRedisReply->type != REDIS_REPLY_STRING) {
        throw RedisException(("run cmd error : " + cmd).c_str(), REDIS::CMD_RUN_ERROR);
    }
    return mRedisReply->str;
}

list<string> Storage::hGet(string key) {
    string cmd = StrPrinter << "HGET " << key;
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, (const char*) cmd.c_str());
    if(mRedisReply == NULL || mRedisReply->type != REDIS_REPLY_ARRAY) {
        throw RedisException(("run cmd error : " + cmd).c_str(), REDIS::CMD_RUN_ERROR);
    }
    list<string> mList;
    for(std::size_t i = 0; i < mRedisReply->elements; i++) {
        mList.push_back(mRedisReply->element[i]->str);
    }
    return mList;
}

void Storage::hSet(string key, string filed, string value) {
    string cmd = StrPrinter << "HSET " << key << " " << filed << " " << value;
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, (const char*) cmd.c_str());
    if(mRedisReply == NULL || mRedisReply->type != REDIS_REPLY_STATUS || strcasecmp(mRedisReply->str,"OK") == 0) {
        throw RedisException(("run cmd error : " + cmd).c_str(), REDIS::CMD_RUN_ERROR);
    }
}

