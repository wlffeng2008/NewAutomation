// SubDlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgMain.h"
#include "afxdialogex.h"


#include "Automation1.h"

static Automation1Controller controller = NULL;

// CSubDlgMain dialog

IMPLEMENT_DYNAMIC(CSubDlgMain, CDialogEx)

CSubDlgMain::CSubDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

CSubDlgMain::~CSubDlgMain()
{
}

void CSubDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgMain, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSubDlgMain message handlers

void CSubDlgMain::SaveLoadSetting(BOOL bToSave)
{
	CIniAX Set(_T("Automation.ini"), _T("Config"));
	SetDlgItemText(IDC_EDIT_USER, Set.GetString(_T("Account"), _T("Admin")));
	SetDlgItemText(IDC_EDIT_PWORD, Set.GetString(_T("PWord"), _T("123")));
	SetDlgItemText(IDC_EDIT_SPEEDX, Set.GetString(_T("SpeedX"), _T("50")));
	SetDlgItemText(IDC_EDIT_SPEEDY, Set.GetString(_T("SpeedY"), _T("80")));
}


BOOL CSubDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(1, 20, nullptr);

	SaveLoadSetting(false);

	SetSpecialID(IDC_CHECK_AUTOSTART, IDC_CHECK_SETTOP);
	SetDlgItemFloat(IDC_EDIT_POSX, 0);
	SetDlgItemFont(IDC_STATIC_STATUS, 16, 700);
	SetDlgItemFont(IDC_STATIC_RUNING, 16, 700);
	SetDlgItemColor(IDC_STATIC_ALARMX, -1, RGB(0, 255, 0));
	SetDlgItemColor(IDC_STATIC_ALARMY, -1, RGB(0, 255, 0));
	SetDlgItemColor(IDC_STATIC_STATUS, 255);
	SetDlgItemColor(IDC_STATIC_RUNING, 255);
	return TRUE;
}


void CSubDlgMain::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1 && controller)
	{
		{
			int nAxis = 0;
			Automation1StatusConfig statusConfig;
			Automation1_StatusConfig_Create(&statusConfig);

			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramPositionFeedback, 0);
			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_DriveStatus, 0);
			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisStatus, 0);

			double result[3];
			if (Automation1_Status_GetResults(controller, statusConfig, result, 3))
			{
				SetDlgItemFloat(IDC_EDIT_POSX, result[0]);

				bool isEnabled = (Automation1DriveStatus_Enabled & (int64_t)result[1]) == Automation1DriveStatus_Enabled;
				printf("Enabled: %s\n", isEnabled ? "true" : "false");


				bool isHomed = (Automation1AxisStatus_Homed & (int64_t)result[2]) == Automation1AxisStatus_Homed;
				printf("Homed: %s\n", isHomed ? "true" : "false");

				bool calibrationEnabled1D = (Automation1AxisStatus_CalibrationEnabled1D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled1D;
				bool calibrationEnabled2D = (Automation1AxisStatus_CalibrationEnabled2D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled2D;
				printf("Calibration State: %s\n", (calibrationEnabled1D || calibrationEnabled2D) ? "true" : "false");
			}
			Automation1_StatusConfig_Destroy(statusConfig);
		}

		{
			int nAxis = 1;
			Automation1StatusConfig statusConfig;
			Automation1_StatusConfig_Create(&statusConfig);

			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramPositionFeedback, 0);
			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_DriveStatus, 0);
			Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisStatus, 0);

			double result[3];
			if (Automation1_Status_GetResults(controller, statusConfig, result, 3))
			{
				SetDlgItemFloat(IDC_EDIT_POSY, result[0]);

				bool isEnabled = (Automation1DriveStatus_Enabled & (int64_t)result[1]) == Automation1DriveStatus_Enabled;
				printf("Enabled: %s\n", isEnabled ? "true" : "false");


				bool isHomed = (Automation1AxisStatus_Homed & (int64_t)result[2]) == Automation1AxisStatus_Homed;
				printf("Homed: %s\n", isHomed ? "true" : "false");

				bool calibrationEnabled1D = (Automation1AxisStatus_CalibrationEnabled1D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled1D;
				bool calibrationEnabled2D = (Automation1AxisStatus_CalibrationEnabled2D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled2D;
				printf("Calibration State: %s\n", (calibrationEnabled1D || calibrationEnabled2D) ? "true" : "false");
			}
			Automation1_StatusConfig_Destroy(statusConfig);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CSubDlgMain::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int nAxis = 0;
	switch (wParam)
	{
	case IDC_CHECK_CONNECT:
		CheckDlgButton(IDC_CHECK_RUN, FALSE);
		if (IsDlgButtonChecked(IDC_CHECK_CONNECT))
		{
			CString strUser;
			CString strPWd;
			GetDlgItemText(IDC_EDIT_USER, strUser);
			GetDlgItemText(IDC_EDIT_PWORD, strPWd);
			BOOL bRet = Automation1_ConnectWithHostAndUser("169.254.8.208", CW2A(strUser), CW2A(strPWd), &controller);
			if (bRet)
			{
				bRet = Automation1_Controller_Start(controller);
				CheckDlgButton(IDC_CHECK_RUN, TRUE);
				nAxis = 0;
				//Automation1_Command_Enable(controller, 1, &nAxis, 1);
				nAxis = 1;
				//Automation1_Command_Enable(controller, 1, &nAxis, 1);
			}
			SetDlgItemText(IDC_STATIC_STATUS, bRet ? _T("已连接") : _T("未连接"));
			SetDlgItemColor(IDC_STATIC_STATUS, RGB(0, 255, 0));
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
			SetDlgItemColor(IDC_STATIC_STATUS, RGB(255, 0, 0));
		}
		SendCmdMsg(IDC_CHECK_RUN);
		break;

	case IDC_CHECK_RUN:
	{
		BOOL bIsRun = IsDlgButtonChecked(IDC_CHECK_RUN);
		if (controller)
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
		SetDlgItemColor(IDC_STATIC_RUNING, bIsRun ? RGB(0, 255, 0) : RGB(255, 0, 0));
	}
	break;

	case IDC_BUTTON_HOMEX:
		if (controller)
		{
			Automation1_Command_HomeAsync(controller, 1, &nAxis, 1);
		}
		break;

	case IDC_BUTTON_HOMEY:
		if (controller)
		{
			nAxis = 1;
			Automation1_Command_HomeAsync(controller, 1, &nAxis, 1);
		}
		break;

	case IDC_CHECKENABLEX:
		if (controller)
		{
			if (IsDlgButtonChecked(IDC_BUTTON_HOMEX))
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
			else
				Automation1_Command_Disable(controller, &nAxis, 1);
		}
		break;

	case IDC_CHECKENABLEY:
		if (controller)
		{
			nAxis = 1;
			if (IDC_CHECKENABLEY)
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
			else
				Automation1_Command_Disable(controller, &nAxis, 1);
		}
		break;
	default:
		break;
	}


	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CSubDlgMain::PreTranslateMessage(MSG* pMsg)
{
	int nAxis = 0;

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX1)->GetSafeHwnd())
		{
			double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX);
			speed *= -1;
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX2)->GetSafeHwnd())
		{
			double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX);
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY1)->GetSafeHwnd())
		{
			nAxis = 1;
			double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY);
			Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY2)->GetSafeHwnd())
		{
			double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY);
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