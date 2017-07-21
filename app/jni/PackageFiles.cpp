//
// Created by Administrator on 2017/7/21.
//

#include "PackageFiles.h"
#include "Log.h"
#include "Texture.h"

PackageFiles* PackageFiles::GetInstance()
{
    static PackageFiles instance;
    return &instance;
}

unsigned int  PackageFiles::LoadTextureFromFile(const char* filename)
{
    int length = 0;
    void* buffer = NULL;
    unsigned int textID = 0;
    if(ReadFileFromApplicationPackage(filename, length, buffer) && buffer != NULL)
    {
        textID = Texture::LoadTextureFromBuffer(buffer, length);
    }

    free(buffer);
    return textID;
}

void PackageFiles::SetZipFilePath(const char* filePath)
{
    sprintf(zipFilePath, "%s", filePath);
    OpenZipFile(zipFilePath);
}

void PackageFiles::OpenZipFile(const char* filePath)
{
    zipFile = unzOpen( filePath );
}


bool PackageFiles::ReadFileFromApplicationPackage(const char * nameInZip, int & length, void * & buffer )
{   LOGD("ReadFileFromOtherApplicationPackageeee %s %d ", nameInZip, length);
	length = 0;
	buffer = NULL;
	if ( zipFile == 0 )
	{
		return false;
	}

	const int locateRet = unzLocateFile( zipFile, nameInZip, 2 /* case insensitive */ );
	if ( locateRet != UNZ_OK )
	{
		LOGD( "File '%s' not found in apk!", nameInZip );
		return false;
	}

	unz_file_info	info;
	const int getRet = unzGetCurrentFileInfo( zipFile, &info, NULL,0, NULL,0, NULL,0);
	if ( getRet != UNZ_OK )
	{
		LOGD( "File info error reading '%s' from apk!", nameInZip );
		return false;
	}
	const int openRet = unzOpenCurrentFile( zipFile );
	if ( openRet != UNZ_OK )
	{
		LOGD( "Error opening file '%s' from apk!", nameInZip );
		return false;
	}

	length = info.uncompressed_size;
	buffer = malloc( length );

	const int readRet = unzReadCurrentFile( zipFile, buffer, length );
	if ( readRet <= 0 )
	{
		LOGD( "Error reading file '%s' from apk!", nameInZip );
		free( buffer );
		length = 0;
		buffer = NULL;
		return false;
	}

	unzCloseCurrentFile( zipFile );

	return true;
}