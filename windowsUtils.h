#pragma once
#ifdef  _WIN32 
#ifdef __cplusplus
extern "C" {
#endif
    __declspec(dllexport) wchar_t* nativeSelectFolderDialog(
    wchar_t const* aTitle,
    wchar_t const* aDefaultPath);
#ifdef __cplusplus
}
#endif
#endif
