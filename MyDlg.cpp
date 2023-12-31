﻿
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DS4Reader.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DS4READER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, devList);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	GetDeviceHandle(&handls, &names);
	for (int i = 0; i < names.size(); i++) {
		devList.AddString(names[i]);
	}

	//ПРОБУЕМ ВЫТАЩИТЬ ХОТЬ ЧТО ТО


	

	//Получаем данные дескриптора отчета о коллекции верхнего уровня
	PHIDP_PREPARSED_DATA preparsData;
	if (!HidD_GetPreparsedData(handls[0], &preparsData))
		MessageBoxA(NULL, "ОШИБКА", "нагнулись данные дескриптора отчета", NULL);
	
	

	//получаем отчет о возможностях коллекции верхнего уровня
	HIDP_CAPS caps;
	if(!HidP_GetCaps(preparsData, &caps))
		MessageBoxA(NULL, "ОШИБКА", "нагнулся отчет о коллекции верхнего уровня", NULL);


	//PHIDP_DATA allOutData;
	//это говно принимает индекс и возвращает в себе инфу по кнопке
	HIDP_DATA outdata;
	outdata.DataIndex = 1;
	ULONG dataLength = 1;
	

	//получение репорта
	ULONG repLenght = caps.InputReportByteLength;
	CHAR* reportb = (CHAR *)malloc(repLenght);

	reportb[0] = 0;

	if(!HidD_GetInputReport(handls[0], (void *)reportb,	repLenght))
		MessageBoxA(NULL, "ОШИБКА", "нагнулся входной репорт", NULL);

	HidP_GetData(HidP_Input, &outdata, &dataLength, preparsData, reportb, repLenght);

	SetTimer(1, 1, NULL);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CDialogEx::OnTimer(nIDEvent);
}
