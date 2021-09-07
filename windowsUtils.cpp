#include "windowsUtils.h"
#include "shobjidl_core.h"
#include <atlstr.h>

wchar_t* nativeSelectFolderDialog(
    wchar_t const* aTitle, // NULL or ""
    wchar_t const* aDefaultPath) {

    wchar_t* result = NULL;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            FILEOPENDIALOGOPTIONS ops;

            IShellItem* pSI;
            hr = SHCreateItemFromParsingName(aDefaultPath, NULL, IID_IShellItem, (void**)&pSI);

            if (SUCCEEDED(hr)) {
                pFileOpen->SetFolder(pSI);
                pSI->Release();
            }

            pFileOpen->SetTitle(aTitle);
            pFileOpen->GetOptions(&ops);
            pFileOpen->SetOptions(ops | FOS_PICKFOLDERS);
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        result = pszFilePath;
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
    }
    return result;
}
