//
// Created by oujiangping on 2019/12/19.
//
#include "Storage.h"
#include "Util/logger.h"
#include "Util//base64.h"

using namespace sw::redis;
using namespace toolkit;

void Storage::connect(string ip, unsigned short port, int timeout_sec) {
    this->ip = ip;
    this->port = port;
    this->timeout = timeout_sec;

    struct timeval t = {timeout};
}

list<Value> Storage::hGet(string key) {
    Redis redis = getRedis();
    vector<std::string> vals;
    redis.hvals(key, back_inserter(vals));
    list<Value> mList;
    Reader reader;
    for(string json : vals) {
        Value value;
        if(reader.parse(json, value)) {
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
    Redis redis = getRedis();
    redis.hset(key, filed, value.toStyledString());
}


void Storage::hDel(string key, string filed) {
    getRedis().hdel(key, filed);
}

Storage & Storage::Instance() {
    static Storage instance;
    return instance;
}

Redis Storage::getRedis() {
    return Redis(StrPrinter << "tcp://" << ip << ":" << port);
}

