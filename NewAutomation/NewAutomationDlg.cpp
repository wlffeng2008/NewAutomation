
// NewAutomationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "NewAutomationDlg.h"
#include "afxdialogex.h"


#include "Automation1.h"

#if defined _M_X64
#pragma comment(lib,"Automation1C64.lib")
#else
#pragma comment(lib,"Automation1C.lib")
#endif


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
BOOL CNewAutomationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	SetSkinsPath(_T("/images/"));

	int v0, v1, v2;
	Automation1_GetApiVersion(&v0, &v1, &v2);
	
	CString strTxt;
	strTxt.Format(_T("AeroTech Automation: V%d.%d.%d"), v0, v1, v2);
	SetWindowText(strTxt);

	m_pDlgMn = new CSubDlgMain();
	m_pDlgMt = new CSubDlgMaterial();
	m_pDlgPr = new CSubDlgProduct();
	m_pDlgVi = new CSubDlgVision();
	m_pDlgCl = new CSubDlgCalibration ();
	m_pDlgCf = new CSubDlgConfig();
	m_pDlgWi = new CSubDlgWorkinfo();

	m_pDlgMn->Create(this);
	m_pDlgPr->Create(this);
	m_pDlgMt->Create(this);
	m_pDlgVi->Create(this);
	m_pDlgCl->Create(this);
	m_pDlgCf->Create(this);
	m_pDlgWi->Create(this);

	m_pDlgPr->m_pMain = m_pDlgMn;

	CRect rc;
	GetDlgItem(IDC_STATIC_FRAME)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	SetDlgItemPos(m_pDlgMn, 0, rc.top);
	SetDlgItemPos(m_pDlgPr, 0, rc.top);
	SetDlgItemPos(m_pDlgMt, 0, rc.top);
	SetDlgItemPos(m_pDlgVi, 0, rc.top);
	SetDlgItemPos(m_pDlgCl, 0, rc.top);
	SetDlgItemPos(m_pDlgCf, 0, rc.top);
	SetDlgItemPos(m_pDlgWi, 0, rc.top);

	SetDlgItemSize(m_pDlgMn, 1024, 675);
	SetDlgItemSize(m_pDlgPr, 1024, 675);
	SetDlgItemSize(m_pDlgMt, 1024, 675);
	SetDlgItemSize(m_pDlgVi, 1024, 675);
	SetDlgItemSize(m_pDlgCl, 1024, 675);
	SetDlgItemSize(m_pDlgCf, 1024, 675);
	SetDlgItemSize(m_pDlgWi, 1024, 675);

	ShowSubDlg(0);

	SetButtonIcon(IDC_BUTTON1, _T("Icon_1.png"));
	SetButtonIcon(IDC_BUTTON2, _T("Icon_2.png"));
	SetButtonIcon(IDC_BUTTON3, _T("Icon_3.png"));
	SetButtonIcon(IDC_BUTTON4, _T("Icon_4.png"));
	SetButtonIcon(IDC_BUTTON5, _T("Icon_5.png"));
	SetButtonIcon(IDC_BUTTON6, _T("Icon_6.png"));
	SetButtonIcon(IDC_BUTTON7, _T("Icon_7.png"));
	SetDlgItemFont(IDC_BUTTON1, 16, 700);
	SetDlgItemFont(IDC_BUTTON2, 16, 700);
	SetDlgItemFont(IDC_BUTTON3, 16, 700);
	SetDlgItemFont(IDC_BUTTON4, 16, 700);
	SetDlgItemFont(IDC_BUTTON5, 16, 700);
	SetDlgItemFont(IDC_BUTTON6, 16, 700);
	SetDlgItemFont(IDC_BUTTON7, 16, 700);

	//AddDrawImage(0, 0, _T("Rocket.png"));
	//SetBKGradColors(1, RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(240, 240, 0), -1);

	MoveWindow(0,0,1024, 768);
	CenterWindow();
	return TRUE;  
}

void CNewAutomationDlg::ShowSubDlg(int nIndex)
{
	CMyDialog *pDlgs[] =
	{
		m_pDlgMn,
		m_pDlgPr,
		m_pDlgMt,
		m_pDlgWi,
		m_pDlgVi,
		m_pDlgCl,
		m_pDlgCf
	};

	UINT nBtns[] = {
		IDC_BUTTON1,
		IDC_BUTTON2,
		IDC_BUTTON3,
		IDC_BUTTON4,
		IDC_BUTTON5,
		IDC_BUTTON6,
		IDC_BUTTON7
	};

	for (int i = 0; i < 7; i++)
	{
		pDlgs[i]->Show(nIndex == i);
		GetMyButton(nBtns[i])->SetHold(nIndex == i);
	}
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

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CNewAutomationDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDC_BUTTON1: ShowSubDlg(0); break;
	case IDC_BUTTON2: ShowSubDlg(1); break;
	case IDC_BUTTON3: ShowSubDlg(2); break;
	case IDC_BUTTON4: ShowSubDlg(3); break;
	case IDC_BUTTON5: ShowSubDlg(4); break;
	case IDC_BUTTON6: ShowSubDlg(5); break;
	case IDC_BUTTON7: ShowSubDlg(6); break;
	default:
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}

