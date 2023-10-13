
// DS4Reader.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDS4ReaderApp:
// Сведения о реализации этого класса: DS4Reader.cpp
//

class CDS4ReaderApp : public CWinApp
{
public:
	CDS4ReaderApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDS4ReaderApp theApp;
