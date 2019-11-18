// ESP32FtpServer.h

/*
   FTP SERVER FOR ESP32 WORKING WITH SPI FLASH MEMORY
   based on FTP Serveur for Arduino Due and Ethernet shield (W5100) or WIZ820io (W5200)
   based on Jean-Michel Gallego's work
   based on David Paiva (david@nailbuster.com)'s work

  Modifications :
  - only for ESP32
  - anonymous connections accepted (set uname = "anonymous" in begin method)
 */

#include <WiFi.h>
#include <WiFiClient.h>
#include <FS.h>
#include <SPIFFS.h>

/*******************************************************************************
 **                                                                            **
 **                       DEFINITIONS FOR FTP SERVER                           **
 **                                                                            **
 *******************************************************************************/

// Uncomment to print debugging info to console attached to ESP8266
//#define FTP_DEBUG

#ifndef FTP_SERVERESP_H
#define FTP_SERVERESP_H

#define FTP_DEBUG  // Verbose (uncomment to set OFF)

#define FTP_SERVER_VERSION "FTP-2017-10-18"

#define FTP_CTRL_PORT    21          // Command port on wich server is listening  
#define FTP_DATA_PORT_PASV 50009     // Data port in passive mode

#define FTP_TIME_OUT  5           // Disconnect client after 5 minutes of inactivity
#define FTP_CMD_SIZE 255 + 8 // max size of a command
#define FTP_CWD_SIZE 255 + 8 // max size of a directory name
#define FTP_FIL_SIZE 255     // max size of a file name
//#define FTP_BUF_SIZE 1024 //512   // size of file buffer for read/write
#define FTP_BUF_SIZE 2*1460 //512   // size of file buffer for read/write

class FtpServer
{
  public:
    void    begin(String uname, String pword);
    void    handleFTP();

  private:
    void    iniVariables();
    void    clientConnected();
    void    disconnectClient();
    boolean userIdentity();
    boolean userPassword();
    boolean processCommand();
    boolean dataConnect();
    boolean doRetrieve();
    boolean doStore();
    void    closeTransfer();
    void    abortTransfer();
    boolean makePath( char * fullname );
    boolean makePath( char * fullName, char * param );
    uint8_t getDateTime( uint16_t * pyear, uint8_t * pmonth, uint8_t * pday,
                         uint8_t * phour, uint8_t * pminute, uint8_t * second );
    char *  makeDateTimeStr( char * tstr, uint16_t date, uint16_t time );
    int8_t  readChar();

    IPAddress      dataIp;              // IP address of client for data
    WiFiClient client;
    WiFiClient data;

    File file;

    boolean  dataPassiveConn;
    uint16_t dataPort;
    char     buf[ FTP_BUF_SIZE ];       // data buffer for transfers
    char     cmdLine[ FTP_CMD_SIZE ];   // where to store incoming char from client
    char     cwdName[ FTP_CWD_SIZE ];   // name of current directory
    char     command[ 5 ];              // command sent by client
    boolean  rnfrCmd;                   // previous command was RNFR
    char *   parameters;                // point to begin of parameters sent by client
    uint16_t iCL;                       // pointer to cmdLine next incoming char
    int8_t   cmdStatus,                 // status of ftp command connexion
             transferStatus;            // status of ftp data transfer
    uint32_t millisTimeOut,             // disconnect after 5 min of inactivity
             millisDelay,
             millisEndConnection,       //
             millisBeginTrans,          // store time of beginning of a transaction
             bytesTransfered;           //
    String   _FTP_USER;
    String   _FTP_PASS;



};

#endif // FTP_SERVERESP_H
