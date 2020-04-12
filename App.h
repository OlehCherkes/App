
// App.h: основной файл заголовка для приложения App
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // основные символы


// CAppApp:
// Сведения о реализации этого класса: App.cpp
//

class CAppApp : public CWinApp
{
public:
	CAppApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAppApp theApp;
