#include <iostream>
#include <Windows.h>
#include <fileapi.h>
#include <TlHelp32.h>
#include <strsafe.h>

int main()
{   
    // Check files.
    WIN32_FIND_DATAW findFileData; // WIN32_FIND_DATAW yapısına yönelik bir işaretci.
    HANDLE file; // API'ı tutar.
    file = FindFirstFileW( // FindFirstFileW verdiğiniz ada uygun dosya veya alt dizin arar.
        L"C:\\Windows\\System32\\vm3dgl.dll", // bu parametre dizinin, path'in adı olabilir.
        &findFileData // WIN32_FIND_DATAW yapısına yönelik bir işaretci. Dizin veya dosya hakkında bilgi alır.
    );

    if (file != INVALID_HANDLE_VALUE) // kontrol
        std::cout << "Virtual machine detected.\n";
    else
        std::cout << "Virtual machine not detected.\n";

    Sleep(5000);

    
    // Check registry key.
    HKEY hkResult;
    LONG key;
    key = RegOpenKeyExW( // RegOpenKeyExW API'ı belirtilen kayıt defteri keyini açar.
        HKEY_LOCAL_MACHINE, // Key handle'ı. Arayacağımız yer burası.
        L"System\\ControlSet001\\Services\\VMTools", // Path
        0, // Anahtar açılırken uygulanacak seçenek.
        KEY_QUERY_VALUE, // Açılacak keyin istenen erişim hakkı.
        &hkResult // Açılan keye bir pointer.
    );
    
    if (key == ERROR_SUCCESS)
        std::cout << "Virtual machine detected.\n";
    else
        std::cout << "Virtual machine not detected.\n";
        
    Sleep(5000);
    
    

    // Check computer name.
    BOOL pcName;
    const int buffer_size = MAX_COMPUTERNAME_LENGTH + 1;
    wchar_t lpBuffer[buffer_size];
    DWORD nSize;
    nSize = buffer_size;
    pcName = GetComputerNameW(
        lpBuffer,
        &nSize
    );

    if (pcName == FALSE) {
        throw std::runtime_error("Something went wrong.");
    }
    wprintf(L"Computer Name: %s\n", lpBuffer);
    Sleep(3000);

    if (wcsstr(lpBuffer, L"WIN-"))
        std::cout << "Virtual machine detected.";
    Sleep(5000);



    // Check window name.
    LPCWSTR windowName = L"x32dbg";
    if (FindWindow(NULL, windowName)) { // iki parametre alıyor. ilki null olabilir, null olursa tüm pencere adlarını alır. ikinci parametremiz pencere ismi
        MessageBoxA(NULL, "Debugger detected.", "Notification", MB_OK);
    }
    else
        MessageBoxA(NULL, "Debugger not detected.", "Notification", MB_OK);
    

    Sleep(5000);

    // Are you a robot ?
    int response = MessageBoxW(NULL, L"Bilgisayarınızı şimdi yeniden başlatmak istiyor musunuz?", L"Yeniden başlatmak gerekir", MB_YESNOCANCEL);
    if (response == IDYES || response == IDNO ||response == IDCANCEL)
        std::cout << "Virtual machine not detected.\n";
    else
        std::cout << "Virtual machine detected.\n";

        

   

    return 0;
}

