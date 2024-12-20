#include <windows.h>
#include <tchar.h>
#include <stdio.h>

BOOL IsAdmin() {
    BOOL isAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID adminGroup;

    // 创建管理员组 SID
    if (AllocateAndInitializeSid(&NtAuthority, 2,
                                SECURITY_BUILTIN_DOMAIN_RID,
                                DOMAIN_ALIAS_RID_ADMINS,
                                0, 0, 0, 0, 0, 0,
                                &adminGroup
                               )) {
        // 检查当前进程是否属于管理员组
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin == TRUE;
}

void GainAdminPrivileges() {
    char path[128] = {0};
    GetModuleFileNameA(NULL, path, 128);

    SHELLEXECUTEINFOA execinfo;
    execinfo.cbSize = sizeof(SHELLEXECUTEINFOA);
    execinfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    execinfo.hwnd = NULL;
    execinfo.lpVerb = "runas";
    execinfo.lpFile = path;
    execinfo.lpParameters = NULL;
    execinfo.lpDirectory = NULL;
    execinfo.nShow = SW_SHOWNORMAL;

    ShellExecuteExA(&execinfo);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    printf("当前拥有管理员权限? %s\n", IsAdmin() ? "是" : "否");
    if (!IsAdmin()) {
        printf("正在申请管理员权限...");
        GainAdminPrivileges();
    }

}