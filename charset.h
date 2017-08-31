#include <string>
#include <cstdlib>
#include <cstring>

#include "charset.h"

using namespace std;

string UTF8ToGBK(const std::string & strUTF8) {
                    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
                    unsigned short * wszGBK = new unsigned short[len + 1];
                    memset(wszGBK, 0, len * 2 + 2);
                    MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);
                    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
                    char *szGBK = new char[len + 1];
                    memset(szGBK, 0, len + 1);
                    WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);
                    //strUTF8 = szGBK;
                    std::string strTemp(szGBK);
                    delete[]szGBK;
                    delete[]wszGBK;
                    return strTemp;
}

