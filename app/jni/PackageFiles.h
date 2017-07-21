//
// Created by Administrator on 2017/7/21.
//

#ifndef EGLDEMO_PACKAGEFILES_H
#define EGLDEMO_PACKAGEFILES_H
#include "../../thirdparty/minizip/unzip.h"


class PackageFiles
{
public:
    unsigned int LoadTextureFromFile(const char* filename);

    void SetZipFilePath(const char* filePath);
    void OpenZipFile(const char* filePath);

    bool ReadFileFromApplicationPackage(const char * nameInZip, int & length, void * & buffer );

    static PackageFiles* GetInstance();



private:
    char zipFilePath[1024];
    unzFile zipFile;

};



#endif //EGLDEMO_PACKAGEFILES_H
