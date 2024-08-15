#include "utils.h"
#include <string>
#ifdef _WIN32 // Opening files will be handled differently on Windows than on different OSes.
#include "CommonFileDialog.h"
#include <shlobj.h>
#include <objbase.h>
#include <shobjidl.h>
#endif

std::string OpenFile()
{
// Windows implementation based on Microsoft's sample usage
#ifdef _WIN32 // I'll make use of Component Object Model's IFileDialog available on Windows.
        IFileDialog *pfd = NULL;
        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(&pfd));
        if(SUCCEEDED(hr))
        {
            // Create an event handling object and hook it up to the dialog.
            IFileDialogEvents *pfde = NULL;
            hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
            if(SUCCEEDED(hr))
            {
                // Hook up the event handler
                DWORD dwCookie;
                hr = pfd->Advise(pfde, &dwCookie);
                if(SUCCEEDED(hr))
                {
                    // Set the options on the dialog
                    DWORD dwFlags;

                    hr = pfd->GetOptions(&dwFlags);
                    if(SUCCEEDED(hr))
                    {
                        // I'll ignore setting the file system items only.
                        // I'll also ignore the second step. 
                        // Not sure what "setting file types to display only" means.
                        // I also don't think file type index will be neccessary in this case.
                        
                        // Setting the default extension to the ".gb" and ".gbc" file.
                        hr = pfd->SetDefaultExtension(L"gb;gbc");
                        if(SUCCEEDED(hr))
                        {
                            // Show the Dialog
                            hr = pfd->Show(NULL);
                            if(SUCCEEDED(hr))
                            {
                                // Grabs the result upon clicking 'Open'.
                                // Result is the IShellItem object.
                                IShellItem *psiResult;
                                hr = pfd->GetResult(&psiResult);
                                if(SUCCEEDED(hr))
                                {
                                    // Only path to the file is important
                                    PWSTR pszFilePath = NULL;
                                    hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                                    if(SUCCEEDED(hr))
                                    {
                                        TaskDialog(NULL,
                                            NULL,
                                            L"Choose ROM to play",
                                            pszFilePath,
                                            NULL,
                                            TDCBF_OK_BUTTON,
                                            TD_INFORMATION_ICON,
                                            NULL);
                                            CoTaskMemFree(pszFilePath);
                                    }
                                    psiResult->Release();

                                }
                            }
                        }
                    }
                    pfd->Unadvise(dwCookie);
                }
                pfde->Release();
            }
            pfd->Release();
        }
#endif
    return "not implemented";
}