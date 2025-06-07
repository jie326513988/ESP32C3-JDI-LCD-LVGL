/*
  Asynchronous TCP library for Espressif MCUs

  Copyright (c) 2016 Hristo Gochkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ASYNCTCP_H_
#define ASYNCTCP_H_

#include "IPAddress.h"
#include "sdkconfig.h"
#include <functional>
extern "C" {
    #include "freertos/semphr.h"
    #include "lwip/pbuf.h"
}

// 如果没有定义核心，那么我们正在Arduino或PIO中运行
#ifndef CONFIG_ASYNC_TCP_RUNNING_CORE
#define CONFIG_ASYNC_TCP_RUNNING_CORE 0 // 任何可用的核心
#define CONFIG_ASYNC_TCP_USE_WDT 1      // 如果启用，每个事件增加33us到200us
#endif

class AsyncClient;

#define ASYNC_MAX_ACK_TIME 5000
#define ASYNC_WRITE_FLAG_COPY 0x01 // 将在发送时分配新的缓冲区来保存数据（否则将保存对给定数据的引用）
#define ASYNC_WRITE_FLAG_MORE 0x02 // 不会发送PSH标志，这意味着在应用程序做出反应之前，应该有更多的数据要发送。

typedef std::function<void(void*, AsyncClient*)> AcConnectHandler;
typedef std::function<void(void*, AsyncClient*, size_t len, uint32_t time)> AcAckHandler;
typedef std::function<void(void*, AsyncClient*, int8_t error)> AcErrorHandler;
typedef std::function<void(void*, AsyncClient*, void *data, size_t len)> AcDataHandler;
typedef std::function<void(void*, AsyncClient*, struct pbuf *pb)> AcPacketHandler;
typedef std::function<void(void*, AsyncClient*, uint32_t time)> AcTimeoutHandler;

struct tcp_pcb;
struct ip_addr;

class AsyncClient {
  public:
    AsyncClient(tcp_pcb* pcb = 0);
    ~AsyncClient();

    AsyncClient & operator=(const AsyncClient &other);
    AsyncClient & operator+=(const AsyncClient &other);

    bool operator==(const AsyncClient &other);

    bool operator!=(const AsyncClient &other) {
      return !(*this == other);
    }
    bool connect(IPAddress ip, uint16_t port);
    bool connect(const char* host, uint16_t port);
    void close(bool now = false);
    void stop();
    int8_t abort();
    bool free();

    bool canSend();//ack未挂起
    size_t space();//TCP窗口中的可用空间
    size_t add(const char* data, size_t size, uint8_t apiflags=ASYNC_WRITE_FLAG_COPY);//添加以发送
    bool send();//发送用上述方法添加的所有数据

    //write equals add()+send()
    size_t write(const char* data);
    size_t write(const char* data, size_t size, uint8_t apiflags=ASYNC_WRITE_FLAG_COPY); //only when canSend() == true

    uint8_t state();
    bool connecting();
    bool connected();
    bool disconnecting();
    bool disconnected();
    bool freeable();//disconnected or disconnecting

    uint16_t getMss();

    uint32_t getRxTimeout();
    void setRxTimeout(uint32_t timeout);//连接无RX数据超时（秒）

    uint32_t getAckTimeout();
    void setAckTimeout(uint32_t timeout);//最后发送的数据包没有ACK超时（毫秒）

    void setNoDelay(bool nodelay);
    bool getNoDelay();

    uint32_t getRemoteAddress();
    uint16_t getRemotePort();
    uint32_t getLocalAddress();
    uint16_t getLocalPort();

    //compatibility
    IPAddress remoteIP();
    uint16_t  remotePort();
    IPAddress localIP();
    uint16_t  localPort();

    void onConnect(AcConnectHandler cb, void* arg = 0);     //on successful connect
    void onDisconnect(AcConnectHandler cb, void* arg = 0);  //disconnected
    void onAck(AcAckHandler cb, void* arg = 0);             //ack received
    void onError(AcErrorHandler cb, void* arg = 0);         //unsuccessful connect or error
    void onData(AcDataHandler cb, void* arg = 0);           //data received (called if onPacket is not used)
    void onPacket(AcPacketHandler cb, void* arg = 0);       //data received
    void onTimeout(AcTimeoutHandler cb, void* arg = 0);     //ack timeout
    void onPoll(AcConnectHandler cb, void* arg = 0);        //every 125ms when connected

    void ackPacket(struct pbuf * pb);//ack pbuf from onPacket
    size_t ack(size_t len); //ack data that you have not acked using the method below
    void ackLater(){ _ack_pcb = false; } //will not ack the current packet. Call from onData

    const char * errorToString(int8_t error);
    const char * stateToString();

    //Do not use any of the functions below!
    static int8_t _s_poll(void *arg, struct tcp_pcb *tpcb);
    static int8_t _s_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *pb, int8_t err);
    static int8_t _s_fin(void *arg, struct tcp_pcb *tpcb, int8_t err);
    static int8_t _s_lwip_fin(void *arg, struct tcp_pcb *tpcb, int8_t err);
    static void _s_error(void *arg, int8_t err);
    static int8_t _s_sent(void *arg, struct tcp_pcb *tpcb, uint16_t len);
    static int8_t _s_connected(void* arg, void* tpcb, int8_t err);
    static void _s_dns_found(const char *name, struct ip_addr *ipaddr, void *arg);

    int8_t _recv(tcp_pcb* pcb, pbuf* pb, int8_t err);
    tcp_pcb * pcb(){ return _pcb; }

  protected:
    tcp_pcb* _pcb;
    int8_t  _closed_slot;

    AcConnectHandler _connect_cb;
    void* _connect_cb_arg;
    AcConnectHandler _discard_cb;
    void* _discard_cb_arg;
    AcAckHandler _sent_cb;
    void* _sent_cb_arg;
    AcErrorHandler _error_cb;
    void* _error_cb_arg;
    AcDataHandler _recv_cb;
    void* _recv_cb_arg;
    AcPacketHandler _pb_cb;
    void* _pb_cb_arg;
    AcTimeoutHandler _timeout_cb;
    void* _timeout_cb_arg;
    AcConnectHandler _poll_cb;
    void* _poll_cb_arg;

    bool _pcb_busy;
    uint32_t _pcb_sent_at;
    bool _ack_pcb;
    uint32_t _rx_ack_len;
    uint32_t _rx_last_packet;
    uint32_t _rx_since_timeout;
    uint32_t _ack_timeout;
    uint16_t _connect_port;

    int8_t _close();
    void _free_closed_slot();
    void _allocate_closed_slot();
    int8_t _connected(void* pcb, int8_t err);
    void _error(int8_t err);
    int8_t _poll(tcp_pcb* pcb);
    int8_t _sent(tcp_pcb* pcb, uint16_t len);
    int8_t _fin(tcp_pcb* pcb, int8_t err);
    int8_t _lwip_fin(tcp_pcb* pcb, int8_t err);
    void _dns_found(struct ip_addr *ipaddr);

  public:
    AsyncClient* prev;
    AsyncClient* next;
};

class AsyncServer {
  public:
    AsyncServer(IPAddress addr, uint16_t port);
    AsyncServer(uint16_t port);
    ~AsyncServer();
    void onClient(AcConnectHandler cb, void* arg);
    void begin();
    void end();
    void setNoDelay(bool nodelay);
    bool getNoDelay();
    uint8_t status();

    //Do not use any of the functions below!
    static int8_t _s_accept(void *arg, tcp_pcb* newpcb, int8_t err);
    static int8_t _s_accepted(void *arg, AsyncClient* client);

  protected:
    uint16_t _port;
    IPAddress _addr;
    bool _noDelay;
    tcp_pcb* _pcb;
    AcConnectHandler _connect_cb;
    void* _connect_cb_arg;

    int8_t _accept(tcp_pcb* newpcb, int8_t err);
    int8_t _accepted(AsyncClient* client);
};


#endif /* ASYNCTCP_H_ */
