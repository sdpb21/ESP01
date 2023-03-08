/*
  ESP01.h
*/
#ifndef __ESP01_h__
#define __ESP01_h__
 
//#include <Arduino.h>
#include <SoftwareSerial.h>

class ESP01
{

  public:

	/*
     * Constuctor. 
     *
     * @param uart - an reference of SoftwareSerial object. 
     * @param baud - the buad rate to communicate with ESP8266(default:9600). 
     *
     * @warning parameter baud depends on the AT firmware. 9600 is an common value. 
     */
    ESP01(SoftwareSerial &uart, uint32_t baud = 9600);

    /*
     * Verify ESP-01 whether live or not. 
     *
     * Actually, this method will send command "AT" to ESP-01 and waiting for "OK". 
     * 
     * @retval true - alive.
     * @retval false - dead.
     */
    bool kick(void);

	/*
     * Join in AP. 
     *
     * @param ssid - SSID of AP to join in. 
     * @param pwd - Password of AP to join in. 
     * @retval true - success.
     * @retval false - failure.
     */
    bool joinAP(String ssid, String pwd);

	/*
     * Leave AP joined before. 
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool leaveAP(void);

	/*
     * Create TCP connection in single mode. 
     * 
     * @param addr - the IP or domain name of the target host. 
     * @param port - the port number of the target host. 
     * @retval true - success.
     * @retval false - failure.
     */
    bool createTCP(String addr, uint32_t port);

	/*
     * Create TCP connection in multiple mode. 
     * 
     * @param mux_id - the identifier of this TCP(available value: 0 - 4). 
     * @param addr - the IP or domain name of the target host. 
     * @param port - the port number of the target host. 
     * @retval true - success.
     * @retval false - failure.
     */
    bool createTCP(uint8_t mux_id, String addr, uint32_t port);

	/*
     * Send data based on TCP or UDP builded already in single mode. 
     * 
     * @param buffer - the buffer of data to send. 
     * @param len - the length of data to send. 
     * @retval true - success.
     * @retval false - failure.
     */
    bool send(const uint8_t *buffer, uint32_t len);

    /*
     * Send data based on one of TCP or UDP builded already in multiple mode. 
     * 
     * @param mux_id - the identifier of this TCP(available value: 0 - 4). 
     * @param buffer - the buffer of data to send. 
     * @param len - the length of data to send. 
     * @retval true - success.
     * @retval false - failure.
     */
    bool send(uint8_t mux_id, const uint8_t *buffer, uint32_t len);

	/*
     * Close TCP connection in single mode. 
     * 
     * @retval true - success.
     * @retval false - failure.
     */
    bool closeTCP(void);

	/*
     * Close TCP connection in multiple mode. 
     * 
     * @param mux_id - the identifier of this TCP(available value: 0 - 4). 
     * @retval true - success.
     * @retval false - failure.
     */
    bool closeTCP(uint8_t mux_id);

	/*
     * ping to a valid host. 
     * 
     * @param host - host to ping 
     * @retval true - success.
     * @retval false - failure.
     */
	bool ping(String host)

  private:
    /* 
     * Empty the buffer or UART RX.
     */
    void rx_empty(void);

    SoftwareSerial *m_puart; /* The UART to communicate with ESP8266 */

    /* 
     * Receive data from uart. Return all received data if target found or timeout. 
     */
    String recvString(String target, uint32_t timeout = 1000);
    
    /* 
     * Recvive data from uart. Return all received data if one of target1 and target2 found or timeout. 
     */
    String recvString(String target1, String target2, uint32_t timeout = 1000);
    
    /* 
     * Recvive data from uart. Return all received data if one of target1, target2 and target3 found or timeout. 
     */
    String recvString(String target1, String target2, String target3, uint32_t timeout = 1000);

    /* 
     * Recvive data from uart and search first target. Return true if target found, false for timeout.
     */
    bool recvFind(String target, uint32_t timeout = 1000);

	/*
     * Send AT command to ESP-01.
     */
    bool eAT(void);

	/*
     * Send AT+CWJAP command with ssid and wifi password to ESP-01 to join to an access point.
     */
	bool sATCWJAP(String ssid, String pwd);

	/*
     * Send AT+CIPSTART command with the type, address and port number to ESP-01 to start a connection in single mode.
     */
	bool sATCIPSTARTSingle(String type, String addr, uint32_t port);

	/*
     * Send AT+CIPSTART command with the id, type, address and port number to ESP-01 to start a connection in single multiple.
     */
    bool sATCIPSTARTMultiple(uint8_t mux_id, String type, String addr, uint32_t port);

	/*
     * Send AT+CWQAP command to ESP-01 to quit access point.
     */
	bool eATCWQAP(void);

	/*
     * Send AT+CIPSEND command with the buffer's lenght to ESP-01 to send buffer content in single mode.
     */
	bool sATCIPSENDSingle(const uint8_t *buffer, uint32_t len);

	/*
     * Send AT+CIPSEND command with the buffer's lenght and it's id to ESP-01 to send buffer content in multiple mode.
     */
    bool sATCIPSENDMultiple(uint8_t mux_id, const uint8_t *buffer, uint32_t len);

	/*
     * Send AT+CIPCLOSE command and it's id to ESP-01 to close a connection in multiple mode.
     */
    bool sATCIPCLOSEMulitple(uint8_t mux_id);

	/*
     * Send AT+CIPCLOSE command to ESP-01 to close a connection in single mode.
     */
    bool eATCIPCLOSESingle(void);

	/*
     * Send AT+PING command to ESP-01 to ping a host.
     */
	bool sATPING(String host);

};

#endif
