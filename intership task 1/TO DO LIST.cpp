#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

#define ID_ADD   1
#define ID_CLEAR 2
#define ID_SAVE  3
#define ID_LIST  100

HWND hInput, hList;
std::vector<HWND> checkboxes;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            // Input box
            hInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                  20, 20, 200, 25, hwnd, NULL, NULL, NULL);

            // Add button
            CreateWindow("BUTTON", "Add", WS_CHILD | WS_VISIBLE,
                         230, 20, 50, 25, hwnd, (HMENU)ID_ADD, NULL, NULL);

            // Clear button
            CreateWindow("BUTTON", "Clear", WS_CHILD | WS_VISIBLE,
                         290, 20, 50, 25, hwnd, (HMENU)ID_CLEAR, NULL, NULL);

            // Save button
            CreateWindow("BUTTON", "Save", WS_CHILD | WS_VISIBLE,
                         230, 50, 110, 25, hwnd, (HMENU)ID_SAVE, NULL, NULL);

            // Task listbox
            hList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
                                 40, 90, 300, 300, hwnd, (HMENU)ID_LIST, NULL, NULL);
        }
        break;

        case WM_COMMAND:
        {
            if(LOWORD(wParam) == ID_ADD)
            {
                char task[256];
                GetWindowText(hInput, task, 256);
                if(strlen(task) > 0)
                {
                    int index = SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)task);

                    HWND hCheck = CreateWindow("BUTTON", "", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                                               20, 90 + index * 20, 15, 15, hwnd, (HMENU)(200 + index), NULL, NULL);
                    checkboxes.push_back(hCheck);

                    SetWindowText(hInput, "");
                }
            }
            else if(LOWORD(wParam) == ID_CLEAR)
            {
                int selIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if(selIndex != LB_ERR)
                {
                    SendMessage(hList, LB_DELETESTRING, selIndex, 0);
                    DestroyWindow(checkboxes[selIndex]);
                    checkboxes.erase(checkboxes.begin() + selIndex);

                    for(size_t i = selIndex; i < checkboxes.size(); ++i)
                        SetWindowPos(checkboxes[i], NULL, 20, 90 + i * 20, 15, 15, SWP_NOZORDER);
                }
            }
            else if(LOWORD(wParam) == ID_SAVE)
            {
                std::ofstream file("tasks.txt");
                for(size_t i = 0; i < checkboxes.size(); ++i)
                {
                    char task[256];
                    SendMessage(hList, LB_GETTEXT, i, (LPARAM)task);
                    BOOL checked = SendMessage(checkboxes[i], BM_GETCHECK, 0, 0);
                    file << task << "\t" << (checked ? "Done" : "Pending") << "\n";
                }
                file.close();
                MessageBox(hwnd, "Tasks saved to tasks.txt", "Saved", MB_OK);
            }
            else if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) >= 200)
            {
                int index = LOWORD(wParam) - 200;
                BOOL checked = SendMessage(checkboxes[index], BM_GETCHECK, 0, 0);

                char task[256];
                SendMessage(hList, LB_GETTEXT, index, (LPARAM)task);

                std::string updated = task;
                if(checked)
                {
                    if(updated.find("[Done]") == std::string::npos)
                        updated += " [Done]";
                }
                else
                {
                    size_t pos = updated.find(" [Done]");
                    if(pos != std::string::npos)
                        updated.erase(pos);
                }

                SendMessage(hList, LB_DELETESTRING, index, 0);
                SendMessage(hList, LB_INSERTSTRING, index, (LPARAM)updated.c_str());
            }
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ToDoListClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("ToDoListClass", "To-Do List", 
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             380, 450, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
