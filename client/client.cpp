// client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>
#include <iostream>
#include <tchar.h>
int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwExitCode = 0;

	// 初始化结构体
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// 获取当前可执行文件所在的目录
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR* pszLastBackslash = _tcsrchr(szPath, '\\');
	if (pszLastBackslash) {
		*(pszLastBackslash + 1) = '\0'; // 保留目录部分，去掉文件名
	}
	_tcscat_s(szPath, MAX_PATH, _T("..\\server\\server.exe")); // 拼接得到 server.exe 的完整路径

	// 创建子进程
	if (!CreateProcess(
		szPath,   // 指向可执行文件完整路径的指针
		NULL,      // 命令行参数（如果需要可以在这里设置）
		NULL,      // 进程句柄不可继承
		NULL,      // 线程句柄不可继承
		FALSE,     // 不继承句柄
		0,         // 无创建标志
		NULL,      // 使用父进程的环境块
		NULL,      // 使用父进程的起始目录
		&si,       // 指向STARTUPINFO结构的指针
		&pi)       // 指向PROCESS_INFORMATION结构的指针
		) {
		std::cerr << "CreateProcess failed (" << GetLastError() << ")." << std::endl;
		return 1;
	}

	// 成功创建进程，保存进程句柄 (pi.hProcess)
	std::cout << "子进程已创建，PID: " << pi.dwProcessId << std::endl;
	std::cout << "进程句柄已保存: " << pi.hProcess << std::endl;

	CloseHandle(pi.hProcess);
	// 等待子进程结束
	std::cout << "等待子进程退出..." << std::endl;
	WaitForSingleObject(pi.hProcess, INFINITE);

	// 获取子进程的退出代码
	if (!GetExitCodeProcess(pi.hProcess, &dwExitCode)) {
		std::cerr << "GetExitCodeProcess failed (" << GetLastError() << ")." << std::endl;
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return 1;
	}

	// 打印退出代码
	std::cout << "子进程退出代码: " << dwExitCode << std::endl;

	// 关闭进程和线程句柄
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
