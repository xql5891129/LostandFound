
// LostandFound.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include <icrsint.h>
#include <windows.h>  
#include <sqltypes.h>  
#include <sql.h>  
#include <sqlext.h>
#include"stdafx.h"

// CLostandFoundApp:
// 有关此类的实现，请参阅 LostandFound.cpp
//

class CLostandFoundApp : public CWinApp
{
public:
	CLostandFoundApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CLostandFoundApp theApp;

struct GOODS
{
	char name[20];
	char time[50];
	char place[50];
};
