#include <iostream>
#include <Windows.h>
int main()
{
    // Tipik bir analistçinin analist yaptığı sanal makinede 2 çekirdekli bir işlemci ve 2 GB RAM bulunduğunu düşünürsek ;

    // Check CPU.
    SYSTEM_INFO lpSystemInfo; // SYSTEM_INFO struct'dan bir pointer tanımladık. Bu yapı mevcut olan bilgisayar sistemi hakkında bilgileri içerir.
    GetSystemInfo(&lpSystemInfo); // GetSystemInfo API'ı tek parametre alıyor. O da SYSTEM_INFO yapısından (structure) bir pointer.
    DWORD numberOfProcessors = lpSystemInfo.dwNumberOfProcessors; // Çekirdek sayısını değişkenimize atadık.
    if (numberOfProcessors < 2) // Eğer ikiden küçükse false döndürüyoruz.
        std::cout << "Virtual machine detected !\n";

    // Check RAM
    MEMORYSTATUSEX memoryStatus; // MEMORYSTATUSEX yapısından bir pointer tanımladık. Bu yapı genişletilmiş bellek dahil sanal ve fiziksel belleklerin mevcut durumunu içerir.
    memoryStatus.dwLength = sizeof(memoryStatus); // Byte cinsinden boyutunu, MEMORYSTATUSEX'den tanımladığımız değişkene atıyoruz.
    GlobalMemoryStatusEx(&memoryStatus); // GlobalMemoryStatusEx API'ı tek parametre alıyor. O da MEMORYSTATHSEX yapısından bir pointer.
    DWORD RAMMB = memoryStatus.ullTotalPhys / 1024 / 1024; // Byte cinsinden fiziksel memorynin miktarını alıyoruz. Byte cinsinden aldığımız için bölüyoruz.
    if (RAMMB < 2048) // Eğer 2GB'dan küçükse false döndürüyoruz.
        std::cout << "Virtual machine detected ! (RAM)\n";

    return 0;
}

