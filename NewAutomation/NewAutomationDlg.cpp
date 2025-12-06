
// NewAutomationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "NewAutomationDlg.h"
#include "afxdialogex.h"

#pragma comment(lib,"Automation1C.lib")
Automation1Controller controller = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewAutomationDlg dialog



CNewAutomationDlg::CNewAutomationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWAUTOMATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewAutomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewAutomationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNewAutomationDlg message handlers

void CNewAutomationDlg::SaveLoadSetting(BOOL bToSave)
{
	CIniAX Set(_T("Automation.ini"),_T("Config"));
	SetDlgItemText(IDC_EDIT_USER,Set.GetString(_T("Account"), _T("Admin")));
	SetDlgItemText(IDC_EDIT_PWORD,Set.GetString(_T("PWord"), _T("123")));
	SetDlgItemText(IDC_EDIT_SPEEDX,Set.GetString(_T("SpeedX"), _T("50")));
}

BOOL CNewAutomationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	int v0, v1, v2;
	Automation1_GetApiVersion(&v0, &v1, &v2);
	
	CString strTxt;
	strTxt.Format(_T("AeroTech Automation: V%d.%d.%d"), v0, v1, v2);
	SetWindowText(strTxt);
	SetTimer(1, 20, nullptr);

	SaveLoadSetting(false);

	SetSpecialID(IDC_CHECK_AUTOSTART, IDC_CHECK_SETTOP);
	SetDlgItemFloat(IDC_EDIT_POSX, 0);
	SetDlgItemFont(IDC_STATIC_STATUS, 16, 700);
	SetDlgItemFont(IDC_STATIC_RUNING, 16, 700);
	SetDlgItemColor(IDC_STATIC_ALARMX,-1,RGB(0,255,0));
	SetDlgItemColor(IDC_STATIC_ALARMY,-1,RGB(0,255,0));
	SetDlgItemColor(IDC_STATIC_STATUS, 255);
	SetDlgItemColor(IDC_STATIC_RUNING, 255);

	return TRUE;  
}

void CNewAutomationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNewAutomationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNewAutomationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNewAutomationDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1 && controller)
	{
		int nAxis = 0;

		Automation1StatusConfig statusConfig;
		Automation1_StatusConfig_Create(&statusConfig);

		Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramPositionFeedback, 0);
		Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_DriveStatus, 0);
		Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisStatus, 0);

		double result[3];
		if (!Automation1_Status_GetResults(controller, statusConfig, result, 3))
		{
		}
		CString strVal;
		strVal.Format(_T("%f"), result[0]);
		SetDlgItemText(IDC_STATIC_POS, strVal);

		bool isEnabled = (Automation1DriveStatus_Enabled & (int64_t)result[1]) == Automation1DriveStatus_Enabled;
		printf("Enabled: %s\n", isEnabled ? "true" : "false");


		bool isHomed = (Automation1AxisStatus_Homed & (int64_t)result[2]) == Automation1AxisStatus_Homed;
		printf("Homed: %s\n", isHomed ? "true" : "false");

		bool calibrationEnabled1D = (Automation1AxisStatus_CalibrationEnabled1D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled1D;
		bool calibrationEnabled2D = (Automation1AxisStatus_CalibrationEnabled2D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled2D;
		printf("Calibration State: %s\n", (calibrationEnabled1D || calibrationEnabled2D) ? "true" : "false");

		Automation1_StatusConfig_Destroy(statusConfig);
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CNewAutomationDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int nAxis = GetDlgItemInt(IDC_EDIT_AXIS);
	switch (wParam)
	{
	case IDC_CHECK_CONNECT:
		CheckDlgButton(IDC_CHECK_RUN, FALSE);
		if(IsDlgButtonChecked(IDC_CHECK_CONNECT))
		{
			BOOL bRet = Automation1_ConnectWithHost("169.254.8.208",&controller);
			if (bRet)
			{
				bRet = Automation1_Controller_Start(controller);
				CheckDlgButton(IDC_CHECK_RUN, TRUE);
				nAxis = 0;
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
				nAxis = 1;
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
			}
			SetDlgItemText(IDC_STATIC_STATUS, bRet ? _T("已连接") :  _T("未连接"));
		}
		else
		{
			if (controller)
			{
				Automation1_Controller_Stop(controller);
				Automation1_Disconnect(controller);
				controller = nullptr;
			}
			SetDlgItemText(IDC_STATIC_STATUS, _T("未连接"));
			SetDlgItemColor(IDC_STATIC_STATUS, RGB(0, 255, 0) );
		}
		SendCmdMsg(IDC_CHECK_RUN);
		break;

	case IDC_CHECK_RUN:
	{
		BOOL bIsRun = IsDlgButtonChecked(IDC_CHECK_RUN);
		if(controller)
		{
			if (bIsRun)
				Automation1_Controller_Start(controller);
			else
				Automation1_Controller_Stop(controller);
		}
		else
		{
			bIsRun = false;
		}

		SetDlgItemText(IDC_STATIC_RUNING, bIsRun ? _T("正在运行") : _T("未运行"));
		SetDlgItemColor(IDC_STATIC_RUNING, bIsRun ? RGB(0,255,0) : RGB(255, 0, 0));
	}
		break;
	case IDC_BUTTON_HOME:
		if (controller)
		{
			Automation1_Command_Home(controller, 1, &nAxis, 1);
		}
	default:
		break;
	}


	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CNewAutomationDlg::PreTranslateMessage(MSG* pMsg)
{
	int nAxis = 0;
	double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX);

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX1)->GetSafeHwnd())
		{
			Automation1_Command_MoveFreerun(controller,1, &nAxis,1,&speed,1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX2)->GetSafeHwnd())
		{
			speed *= -1;
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY1)->GetSafeHwnd())
		{
			nAxis = 1;
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY2)->GetSafeHwnd())
		{
			nAxis = 1;
			speed *= -1;
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}
	}

	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX2)->GetSafeHwnd() ||
			pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX1)->GetSafeHwnd())
		{
			Automation1_Command_MoveFreerunStop(controller, 1, &nAxis, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY2)->GetSafeHwnd() ||
			pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY1)->GetSafeHwnd())
		{
			nAxis = 1;
			Automation1_Command_MoveFreerunStop(controller, 1, &nAxis, 1);
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}