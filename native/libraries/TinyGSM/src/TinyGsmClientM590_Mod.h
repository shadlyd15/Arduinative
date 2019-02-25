/**
 * @file       TinyGsmClientM590.h
 * @author     Volodymyr Shymanskyy
 * @license    LGPL-3.0
 * @copyright  Copyright (c) 2016 Volodymyr Shymanskyy
 * @date       Nov 2016
 */

#ifndef TinyGsmClientM590_h
#define TinyGsmClientM590_h

#include "Arduino.h"
// #include "/media/shadlyd15/01D26C2707685C90/My_Folder/Repositories/__DLMS_MQTT/comm_module_dlms_xml/arduino_src/debug.h"

// #include <SoftwareSerial.h>
// extern SoftwareSerial debug_stream;
// #define TINY_GSM_DEBUG debug_stream

#define UNUSED(X)

#if !defined(TINY_GSM_RX_BUFFER)
  #define TINY_GSM_RX_BUFFER 512
#endif

#include <TinyGsmCommon.h>

/*! GSM Modem States for State Machine */ 
typedef enum
{
  GSM_STATE_TURN_ON_MODEM,                  /*!< This is the initial state*/
  GSM_STATE_CONFIG,             /*!< GSM modem regulator will be turned on*/
  GSM_STATE_CHCK_NET,                       /*!< In this state modem will be turned on*/
  GSM_STATE_GPRS_CONFIG,                    /*!< In this state modem will turn echo off*/
  GSM_STATE_SET_PPP_LINK,                   /*!< In this state modem will set ppp link*/
  GSM_STATE_MODEM_GPRS_READY,               /*!< In this state modem is ready to connect to TCP sockets*/
}gsmStateE;

typedef const __FlashStringHelper* FSH;   /*!< PROGMEM as argument suppot */

/*! GSM Modem Response Types */
const char OK[]                     PROGMEM  =  "OK" ;            /*!< GSM Modem Response : OK */
const char ERROR[]                  PROGMEM  =  "ERROR" ;         /*!< GSM Modem Response : ERROR*/
const char Error[]                  PROGMEM  =  "Error" ;         /*!< GSM Modem Response : ERROR*/
const char FAIL[]                   PROGMEM  =  "FAIL" ;          /*!< GSM Modem Response : : FAIL*/
const char CLOSE[]                  PROGMEM  =  "CLOSE" ;         /*!< GSM Modem String : CLOSE:*/
const char TRANS[]                  PROGMEM  =  "TRANS" ;         /*!< GSM Modem String : TRANS*/
const char MODEM_READY[]            PROGMEM  =  "+PBREADY" ;      /*!< GSM Modem Response : Startup Message*/
const char TRANSPARENT_OK[]         PROGMEM  =  "TRANS:OK" ;      /*!< GSM Modem Response : TRANSPARENT OK*/
const char QUIT[]                   PROGMEM  =  "Quit" ;          /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/
const char NETWORK_REG_SUCCESS[]    PROGMEM  =  "+CREG: 0,1" ;    /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/
const char GPRS_REG_SUCCESS[]       PROGMEM  =  "+CGREG: 0,1" ;   /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/
const char GPRS_ATTACHED_SUCCESS[]  PROGMEM  =  "+CGATT: 0,1" ;     /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/
const char GPRS_ATTACHED_FAILED[]   PROGMEM  =  "+CGATT: 0,0" ;     /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/
const char PPP_LINK_ERROR[]         PROGMEM  =  "0.0.0.0" ;       /*!< GSM Modem Response : When transparent TCP connection quits unexpectedly*/

/*! GSM Modem AT Commands */
const char AT_CMD[]                 PROGMEM  =  "AT" ;            /*!< GSM AT Command : AT*/ 
const char DISABLE_ECHO_AT_CMD[]    PROGMEM  =  "ATE0" ;          /*!< GSM AT Command : Echo Off*/
const char AT_SET_AUTO_BAUD[]       PROGMEM  =  "AT+IPR=0" ;      /*!< GSM AT Command : autobaud*/
//const char AT_SET_APN[]             PROGMEM  =  "AT+CGDCONT=1,\"IP\",\"gpinternet\"" ;     /*!< GSM AT Command : apn set GrameenPhone*/
const char AT_SET_APN[]             PROGMEM =   "AT+CGDCONT=1,\"IP\",\"INTERNET\"";     /*!< GSM AT Command : apn set Robi*/
const char AT_SAVE_CONFIG[]         PROGMEM  =  "AT&W" ;          /*!< GSM AT Command : save config*/
const char AT_CHCK_NET_REG[]        PROGMEM  =  "AT+CREG?" ;      /*!< GSM AT Command : is network registered? */                      
const char AT_CHCK_GPRS_REG[]       PROGMEM  =  "AT+CGREG?" ;     /*!< GSM AT Command : is gprs registered? */ 
const char AT_DELETE_MSG[]          PROGMEM  =  "AT+CMGD=4";    /*!< GSM AT Command : Delet All Message*/
const char AT_SET_PROTOCOL[]        PROGMEM  =  "AT+XISP=0" ;     /*!< GSM AT Command : set internal protocol*/
const char GET_IMEI[]               PROGMEM  =  "AT+CGSN" ;       /*!< GSM AT Command : Imei*/
const char PPP_LINK_AT_CMD[]        PROGMEM  =  "AT+XIIC=1" ;     /*!< GSM AT Command : Set PPP Link*/
const char TCP_TRANS_AT_CMD[]       PROGMEM  =  "AT+TCPTRANS=" ;  /*!< GSM AT Command : Setup Transparent TCP bridge*/
const char TCP_STOP[]              PROGMEM  =  "AT+TCPCLOSE=0" ; /*!< GSM AT Command : Close TCP connection*/
const char AT_ATTACH_GPRS[]         PROGMEM  =  "AT+CGATT=1" ;    /*!< GSM AT Command : attach gprs*/
const char AT_CHCK_GPRS_ATTACH[]    PROGMEM  =  "AT+CGATT?" ;     /*!< GSM AT Command : is gprs attached? */
const char AT_CHCK_PPP_LINK[]       PROGMEM  =  "AT+XIIC?" ;      /*!< GSM AT Command : is PPP link*/
const char AT_DETACH_GPRS[]         PROGMEM  =  "AT+CGATT=0" ;    /*!< GSM AT Command : detach gprs*/                               
const char AT_CHECK_SIGNAL[]        PROGMEM =   "AT+CSQ";         /*!< GSM AT Command : Get Signal Strength*/                       
const char AT_AUTH_SET[]            PROGMEM =   "AT+XGAUTH=1,1,\"\",\"\"";         /*!< GSM AT Command : Get Signal Strength*/


/*! GSM Modem Buffer Size Configuration */
#define RX_BUFFER_SIZE             512         // mightyCore RX TX buffer incresead to 128 [# major upgrade]
#define MAX_BYTE_LATENCY           300       //ms


class TinyGsmM590_Mod{

public:
class GsmClient : public Client{
    friend class TinyGsmM590_Mod;

  public:
    GsmClient() {}
    GsmClient(TinyGsmM590_Mod& modem) {
      this->init(&modem);
    }

    bool init(TinyGsmM590_Mod* modem) {
      this->gsm_modem = modem;
      this->sock_connected = false;
      return true;
    }

  public:
    virtual int connect(const char *host, uint16_t port) {
      // stop();
      TINY_GSM_YIELD();
      this->sock_connected = gsm_modem->modemConnect(host, port);
      return this->sock_connected;
    }

    virtual int connect(IPAddress ip, uint16_t port) {
      String host; host.reserve(16);
      host += ip[0];
      host += ".";
      host += ip[1];
      host += ".";
      host += ip[2];
      host += ".";
      host += ip[3];
      return connect(host.c_str(), port);
    }

    virtual void stop() {
      TINY_GSM_YIELD();
      gsm_modem->modemStop();
      this->sock_connected = false;
    }

    virtual size_t write(const uint8_t *buf, size_t size) {
      TINY_GSM_YIELD();
      return gsm_modem->modemWrite(buf, size);
    }

    virtual size_t write(uint8_t c) {
      return write(&c, 1);
    }

    virtual size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }

    virtual int available() {
      // TINY_GSM_YIELD();
      if (this->sock_connected) {
        return this->gsm_modem->modemAvailable();
      }
    }

    virtual int read(uint8_t *buf, size_t size) {
      // TODO
      return -1;
    }

    virtual int read() {
      return this->gsm_modem->modemRead();
    }

    virtual int peek() { 
      //TODO
      return -1; 
    } 
    
    virtual void flush() { 
      this->gsm_modem->modemFlush(); 
    }

    virtual uint8_t connected() {
      return this->gsm_modem->modemConnected();
    }

    virtual operator bool() { return connected(); }

private:
    bool  sock_connected;
    TinyGsmM590_Mod*  gsm_modem;
};

public:

#ifdef GSM_DEFAULT_STREAM
    TinyGsmM590_Mod(Stream& stream = GSM_DEFAULT_STREAM)
#else
    TinyGsmM590_Mod(Stream& stream)
#endif
    :_uart_stream(stream)
    {
      this->_tcp_connected = false;
      this->_gsmState = GSM_STATE_TURN_ON_MODEM;
    }

    bool init(){
      this->_tcp_connected = false;
      this->_gsmState = GSM_STATE_TURN_ON_MODEM;
      this->_waitForNetwork_state = 0;
      this->_gprsConnect_state = 0;
      this->_uart_stream.setTimeout(2000);
      delay(5000);
      return this->atTest();
    }

    bool atTest(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX, RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+CPIN?"),(FSH)OK,(FSH)ERROR, 5000); 
    }

    bool modemConnect(const char *host, uint16_t port){
      bool ret_val = false;
      if(host && port){
        char tcp_string[RX_BUFFER_SIZE];
        uint8_t buffPtr[RX_BUFFER_SIZE];
        memset(tcp_string, 0x00, RX_BUFFER_SIZE);
        memset(buffPtr, 0x00, RX_BUFFER_SIZE);
        if(sprintf(tcp_string, "AT+TCPSETUP=0,%s,%d\r\n", host, port)){
          cleanSerialBuf();
          this->_uart_stream.write((uint8_t*)tcp_string, strlen(tcp_string));
          this->_uart_stream.flush();
          if(fillBufUntilMatch(buffPtr, 10000, F("0,OK"), F("0,FAIL"))){
            this->_tcp_connected = true;
            ret_val = true;
            UNUSED(DEBUG_OK("Modem TCP Connected"));
          } else{
            UNUSED(DEBUG_ERROR("Not Connected"));
          }
          // DEBUG_OK("TCP Connect Response : %s", buffPtr);          
        }
      }
      return ret_val;
    }

    int modemWrite(const void* buff, size_t len) {
      bool ret_val = false;
      if(this->_tcp_connected){
        char tcp_string[RX_BUFFER_SIZE];
        uint8_t buffPtr[RX_BUFFER_SIZE];
        memset(tcp_string, 0x00, RX_BUFFER_SIZE);
        memset(buffPtr, 0x00, RX_BUFFER_SIZE);
        if(sprintf(tcp_string, "AT+TCPSEND=0,%d\r\n", len)){
          // DEBUG_OK("TCP Write %d Byte(s) Request : %s", strlen(tcp_string), tcp_string);
          this->_uart_stream.write((uint8_t*)tcp_string, strlen(tcp_string));
          this->_uart_stream.flush();
          if(fillBufUntilMatch(buffPtr, 5000, F(">"), (FSH)Error)){
            memset(buffPtr, 0x00, RX_BUFFER_SIZE);
            // DEBUG_OK("TCP Write %d Byte(s) Request : %s", len, buff);
            // DEBUG_OK("availableForWrite : %d", this->_uart_stream.availableForWrite());
            delay(100);
            this->_uart_stream.write((uint8_t*)buff, len);
            this->_uart_stream.write((char)0x0D);
            this->_uart_stream.flush();
            if(fillBufUntilMatch(buffPtr, 10000, F("+TCPSEND:"), (FSH)ERROR)){
              this->_uart_stream.readStringUntil('\n');
            }
            // DEBUG_OK("TCP Write Response : %s", buffPtr);
          }
        }
      }
      return ret_val;
    }

    bool waitForNetwork(){
      bool ret_val = false;
      for (unsigned long start = millis(); (millis() - start < 60000L) && !ret_val; ) {
        switch(_waitForNetwork_state){
          case 0:{
            if(disableEcho()){
              UNUSED(DEBUG_OK("Echo Disabled"));
              _waitForNetwork_state = 1;
            } else{
              UNUSED(DEBUG_ERROR("Echo Not Disabled"));
            }
            break;
          }
          case 1:{
            if(checkNetworkRegistration()){
              UNUSED(DEBUG_OK("Network Registered"));
              _waitForNetwork_state = 2;
            } else{
              UNUSED(DEBUG_ERROR("Network Not Registered"));
            }
            break;
          }
          case 2:{
            if(checkGprsRegistration()){
              UNUSED(DEBUG_OK("GPRS Registered"));
              _waitForNetwork_state = 0;
              ret_val = true;
            } else{
              UNUSED(DEBUG_ERROR("GPRS Not Registered"));
            }
            break;
          }
          default:
            break;
        }
        delay(500);
      }
      return ret_val;
    }

    bool gprsConnect(const char* apn = NULL, const char* user = NULL, const char* pwd = NULL){
      bool ret_val = false;
      for (unsigned long start = millis(); (millis() - start < 20000L) && !ret_val; ) {
        switch(_gprsConnect_state){
          case 0:{
            if(setInternetProtocol()){
              UNUSED(DEBUG_OK("Internal Protocol Set"));
              _gprsConnect_state = 1;
            } else{
              UNUSED(DEBUG_ERROR("Internal Protocol Not Set"));
            }
            break;
          }
          case 1:{
            if(setApn()){
              UNUSED(DEBUG_OK("APN Set"));
              _gprsConnect_state = 3;
            } else{
              UNUSED(DEBUG_ERROR("APN Not Set"));
            }
            break;
          }
          case 2:{
            if(setAuth()){
              UNUSED(DEBUG_OK("Authentication Set"));
              _gprsConnect_state = 3;
            } else{
              UNUSED(DEBUG_ERROR("Authentication Not Set"));
            }
            break;
          }
          case 3:{
            if(setupPPPLink()){
              UNUSED(DEBUG_OK("PPP Link Set"));
              _gprsConnect_state = 0;
              ret_val = true;
            } else{
              UNUSED(DEBUG_ERROR("PPP Link Not Set"));
            }
            break;
          }
          default:
            break;
        }
        delay(500);
      }
      return ret_val;
    }

    void modemFlush(){
      this->_uart_stream.flush();  
    }

    void modemStop(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX, RX_BUFFER_SIZE);
      sendATCommand(buffRX, (FSH)TCP_STOP, (FSH)OK, (FSH)ERROR, 2000); 
      cleanSerialBuf(); //buffer should be clear here
      this->_tcp_connected = false;
    }

    bool modemConnected(){
      return this->_tcp_connected;
    }

    int modemAvailable(){
      if(this->_tcp_connected){
        return this->_uart_stream.available();
      }
      return -1;
    }

    int modemRead(){
      if(this->_tcp_connected){
        if(this-_uart_stream.available()){
          return this->_uart_stream.read();
        }
      }
      UNUSED(DEBUG_ERROR("Modem Read Error"));
      return -1;
    }

    void cleanSerialBuf(){
      while(this->_uart_stream.available() > 0){  //wdt reset will break from this infinite loop
        this->_uart_stream.read();
      }
    }

    void clean(){
      cleanSerialBuf();
    }

    void cleanBuffer(uint8_t *myBuff, uint32_t bufferSize){
       memset(myBuff, 0x00, bufferSize);
    }

    bool sendATCommand(uint8_t * buffPtr, const FSH command, const FSH checkok, const FSH checkerror, const uint16_t timeout){ //[# minor upgrade]
      bool ret_val = false;
      cleanSerialBuf();
      this->_uart_stream.println(command);
      this->_uart_stream.flush();
      char temp_at_command[128];
      memset(temp_at_command, 0x00, 128);
      memcpy_P(temp_at_command, command, strlen_P((const char*)command));
      UNUSED(DEBUG_ALERT("Sent AT Command : %s", temp_at_command));
      if(fillBufUntilMatch(buffPtr, timeout, (FSH)checkok, (FSH)checkerror)){
        ret_val = findString(buffPtr, (FSH)checkok, RX_BUFFER_SIZE);
      }
      UNUSED(DEBUG_OK("Modem Reply : %s", buffPtr));
      return ret_val;
    }

    bool disableEcho(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)DISABLE_ECHO_AT_CMD,(FSH)OK,(FSH)ERROR,2000); 
    }

    bool setAutoBaud(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)AT_SET_AUTO_BAUD,(FSH)OK,(FSH)ERROR,1500);
    }

    bool setApn(){  
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+CGDCONT=1,\"IP\",\"gpinternet\""), F("OK"), F("ERROR"), 2000); //Ayz: timeout increased previously 1500
    }

    bool saveConfig(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)AT_SAVE_CONFIG,(FSH)OK,(FSH)ERROR,1500);
    }

    bool checkNetworkRegistration(){  
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+CREG?"), F("+CREG: 0,1"), F("ERROR"), 2000);
    }

    bool checkGprsRegistration(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+CGREG?"),F("+CGREG: 0,1"),F("ERROR"), 2000);
    }

    bool deleteAllMessage(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX, RX_BUFFER_SIZE);
      return sendATCommand(buffRX, (FSH)AT_DELETE_MSG, (FSH)OK, (FSH)ERROR, 1500);
    }

    bool setInternetProtocol(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+XISP=0"), F("OK"), F("ERROR"),1500);
    }

    bool attachGprs(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)AT_ATTACH_GPRS,(FSH)OK,(FSH)ERROR,1500);
    }

    bool isGprsAttached(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)AT_CHCK_GPRS_ATTACH,(FSH)GPRS_ATTACHED_SUCCESS,(FSH)GPRS_ATTACHED_FAILED,1500);
    }

    bool setAuth(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX, F("AT+XGAUTH=1,1,\"\",\"\""), F("OK"), F("ERROR"),1500);
    }

    bool setupPPPLink(){
      bool pppLinkIsSet = false;
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX, RX_BUFFER_SIZE);
      
      if(sendATCommand(buffRX,(FSH)PPP_LINK_AT_CMD,(FSH)OK,(FSH)ERROR, 3000)){
        cleanBuffer(buffRX, RX_BUFFER_SIZE);
        pppLinkIsSet = sendATCommand( buffRX, F("AT+XIIC?"), F("1,"), F("0,"), 3000);
      }
      return pppLinkIsSet;
    }

    bool detachGprs(){
      uint8_t buffRX[RX_BUFFER_SIZE];
      cleanBuffer(buffRX,RX_BUFFER_SIZE);
      return sendATCommand(buffRX,(FSH)AT_DETACH_GPRS,(FSH)OK,(FSH)ERROR,1500);
    }

    bool fillBufUntilMatch(uint8_t* buffPtr, uint16_t timeout, const FSH okTypeStr, const FSH errorTypeStr){
      //purpose of this code is read until OK , error or FAIL has arrived [# major change]

      unsigned long t = millis(); //take track of time now
      uint32_t bufIndex = 0;

      bool okTypeStrMatch = false;
      bool errorTypeStrMatch = false;
      bool failTypeStrMatch = false;

      bool matchGotFlag = false;

      do{
        if (this->_uart_stream.available() > 0){ // if there is something in serial 
          int inByte = this->_uart_stream.read();

          if (inByte > -1){  //if a valid byte 
            buffPtr[bufIndex] = (uint8_t)inByte;
            bufIndex++;
            if (bufIndex > (RX_BUFFER_SIZE-1)) 
              break;         //buffer overflowed so break now
          //possible that character could be missed if at the end of buffer 2 consecutive
          //character gets separated solution is to increse buffer size 
          }

          if(findString(buffPtr, (FSH)okTypeStr, RX_BUFFER_SIZE)){
            matchGotFlag = true;
            break;
          }
          if(findString(buffPtr, (FSH)errorTypeStr, RX_BUFFER_SIZE) || findString(buffPtr, (FSH)FAIL, RX_BUFFER_SIZE)){
            matchGotFlag = false;
            break;
          }
        }//if serial available
      } while ((unsigned long)(millis() - t) < timeout); //try to read & check until the timeout 
      return matchGotFlag;
    }

    bool findString(uint8_t * mainStr, const FSH subStr, uint32_t maxlen){
      if (mainStr == NULL)
        return false;

      uint8_t strTemp[32];

      uint32_t count = 0;
      uint32_t mainLen = 0;
      uint32_t subLen = 0;
      
      mainLen = strlen((char*)mainStr);
      subLen = strlen_P((char*)subStr);
      
      if(mainLen > maxlen){
        mainLen = maxlen;
      }

      memset(strTemp,'\0', 32);
      memcpy_P(strTemp,subStr,subLen);

      for(uint32_t i = 0; i < mainLen; i++){
        if(mainStr[i]== strTemp[count]) 
          count++;
        else
          count = 0;

        if(count == subLen){
          return true; 
        }
      }
      return false;
    }

  private:
      Stream&       _uart_stream;
      gsmStateE     _gsmState;
      bool          _tcp_connected; 
      uint8_t       _tcp_buffer[RX_BUFFER_SIZE];
      uint32_t      _tcp_buffer_read_index;
      uint32_t      _tcp_buffer_write_index;
      uint8_t       _waitForNetwork_state;
      uint8_t       _gprsConnect_state;      
};

#endif

