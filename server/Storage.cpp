//
// Created by oujiangping on 2019/12/19.
//
#include "Storage.h"
#include "Util/logger.h"
#include "Util//base64.h"

using namespace toolkit;

void Storage::connect(string ip, unsigned short port, int timeout_sec) {
    this->ip = ip;
    this->port = port;
    this->timeout = timeout_sec;

    struct timeval t = {timeout};
    mRedisContext = redisConnectWithTimeout((const char*) ip.c_str(), port, t);

    if(NULL == mRedisContext || mRedisContext->err) {
        throw RedisException("connect to redis error", REDIS::CONNECT_ERROR);
    }
    InfoL << "连接Redis 成功";
}

list<Value> Storage::hGet(string key) {
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, "HVALS %s", key.c_str());
    auto reply = make_shared<RedisReplay>(mRedisReply);
    if(reply->getReply() == NULL || reply->getReply()->type != REDIS_REPLY_ARRAY) {
        throw RedisException(("HVALS error key : " + key).c_str(), REDIS::CMD_RUN_ERROR);
    }
    list<Value> mList;
    Reader reader;
    for(std::size_t i = 0; i < mRedisReply->elements; i++) {
        Value value;
        if(reader.parse(decodeBase64(reply->getReply()->element[i]->str), value)) {
            WarnL<<"parse ok "<< value.toStyledString();
            value["src"].isInt();
        }
        mList.push_back(value);
    }
    return mList;
}

void Storage::hSet(string key, string filed, Value value) {
    Json::StreamWriterBuilder builder;
    const std::string val = Json::writeString(builder, value);
    
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, "HSET %s %s %s", key.c_str(), filed.c_str(), encodeBase64(val).c_str());
    auto reply = make_shared<RedisReplay>(mRedisReply);
    if(reply->getReply() == NULL || reply->getReply()->type != REDIS_REPLY_INTEGER) {
        throw RedisException(("redis set value error : " + val).c_str(), REDIS::CMD_RUN_ERROR);
    }
}


void Storage::hDel(string key, string filed) {
    redisReply *mRedisReply = (redisReply*) redisCommand(mRedisContext, "HDEL %s %s", key.c_str(), filed.c_str());
    auto reply = make_shared<RedisReplay>(mRedisReply);
    if(reply->getReply() == NULL || reply->getReply()->type != REDIS_REPLY_INTEGER) {
        throw RedisException(("redis set value error : " + filed).c_str(), REDIS::CMD_RUN_ERROR);
    }
}
Storage & Storage::Instance() {
    static Storage instance;
    return instance;
}

