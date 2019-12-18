﻿/*
 * MIT License
 *
 * Copyright (c) 2019 xiongziliang <771730766@qq.com>
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MK_COMMON_H
#define MK_COMMON_H

#include <stdint.h>

#if defined(_WIN32)
#if defined(MediaKitApi_EXPORTS)
		#define API_EXPORT __declspec(dllexport)
	#else
		#define API_EXPORT __declspec(dllimport)
	#endif

	#define API_CALL __cdecl
#else
#define API_EXPORT
#define API_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    // 线程数
    int thread_num;
    // 日志级别,支持0~4
    int log_level;

    // 配置文件是内容还是路径
    int ini_is_path;
    // 配置文件内容或路径，可以为NULL
    const char *ini;

    // ssl证书是内容还是路径
    int ssl_is_path;
    // ssl证书内容或路径，可以为NULL
    const char *ssl;
    // 证书密码，可以为NULL
    const char *ssl_pwd;
} config;

/**
 * 初始化环境，调用该库前需要先调用此函数
 * @param cfg 库运行相关参数
 */
API_EXPORT void API_CALL mk_env_init(const config *cfg);

/**
 * 设置配置项
 * @param key 配置项名
 * @param val 配置项值
 */
API_EXPORT void API_CALL mk_set_option(const char *key, const char *val);

/**
 * 创建http[s]服务器
 * @param port htt监听端口，推荐80，传入0则随机分配
 * @param ssl 是否为ssl类型服务器
 * @return 0:失败,非0:端口号
 */
API_EXPORT uint16_t API_CALL mk_http_server_start(uint16_t port, int ssl);

/**
 * 创建rtsp[s]服务器
 * @param port rtsp监听端口，推荐554，传入0则随机分配
 * @param ssl 是否为ssl类型服务器
 * @return 0:失败,非0:端口号
 */
API_EXPORT uint16_t API_CALL mk_rtsp_server_start(uint16_t port, int ssl);

/**
 * 创建rtmp[s]服务器
 * @param port rtmp监听端口，推荐1935，传入0则随机分配
 * @param ssl 是否为ssl类型服务器
 * @return 0:失败,非0:端口号
 */
API_EXPORT uint16_t API_CALL mk_rtmp_server_start(uint16_t port, int ssl);

/**
 * 创建rtp服务器
 * @param port rtp监听端口(包括udp/tcp)
 * @return 0:失败,非0:端口号
 */
API_EXPORT uint16_t API_CALL mk_rtp_server_start(uint16_t port);

/**
 * 打印日志
 * @param level 日志级别,支持0~4
 * @param file __FILE__
 * @param function __FUNCTION__
 * @param line __LINE__
 * @param fmt printf类型的格式控制字符串
 * @param ... 不定长参数
 */
API_EXPORT void API_CALL mk_log_printf(int level, const char *file, const char *function, int line, const char *fmt, ...);

// 以下宏可以替换printf使用
#define log_trace(fmt,...) mk_log_printf(0,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define log_debug(fmt,...) mk_log_printf(1,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define log_info(fmt,...) mk_log_printf(2,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define log_warn(fmt,...) mk_log_printf(3,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define log_error(fmt,...) mk_log_printf(4,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define log_printf(lev,fmt,...) mk_log_printf(lev,__FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)

#ifdef __cplusplus
}
#endif


#endif /* MK_COMMON_H */
