//
// Created by Administrator on 2017/7/21.
//

#ifndef EGLDEMO_PACKAGEFILES_H
#define EGLDEMO_PACKAGEFILES_H
#include "../../thirdparty/minizip/unzip.h"


class PackageFiles
{
public:
    static void SetZipFilePath(const char* filePath);
    static bool ReadFileFromApplicationPackage(const char * nameInZip, int & length, void * & buffer );

private:
    static void OpenZipFile(const char* filePath);
private:
    static char zipFilePath[1024];
    static unzFile zipFile;
};



#endif //EGLDEMO_PACKAGEFILES_H
