#include <server_ftp.h>
#include <user_config.h>
#include <SmingCore/SmingCore.h>

FTPServer ftp;

void startFTP() {
  if (!fileExist("index.html"))
    fileSetContent("index.html",
                   "<h3>Please connect to FTP and upload files</h3>");
  // Start FTP server
  ftp.listen(21);
  ftp.addUser("1", "1"); // FTP account
  Serial.println("\r\n=== FTP SERVER STARTED ===");
}
