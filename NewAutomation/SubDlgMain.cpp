// SubDlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgMain.h"
#include "afxdialogex.h"

#include "ColorSlider.h"
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
	if (bToSave)
	{
		Set.SetString(_T("HostIP"), GetDlgItemTextEx(IDC_EDIT_HOSTIP));
		Set.SetString(_T("Account"), GetDlgItemTextEx(IDC_EDIT_USER));
		Set.SetString(_T("PWord"), GetDlgItemTextEx(IDC_EDIT_PWORD));
		Set.SetString(_T("SpeedX"), GetDlgItemTextEx(IDC_EDIT_SPEEDX));
		Set.SetString(_T("SpeedY"), GetDlgItemTextEx(IDC_EDIT_SPEEDY));
		Set.SetString(_T("ZeroX"), GetDlgItemTextEx(IDC_EDIT_ZEROX));
		Set.SetString(_T("ZeroY"), GetDlgItemTextEx(IDC_EDIT_ZEROY));
		Set.SetString(_T("Laser1"), GetDlgItemTextEx(IDC_EDIT_SET1));
		Set.SetString(_T("Laser2"), GetDlgItemTextEx(IDC_EDIT_SET2));
		Set.SetString(_T("Laser3"), GetDlgItemTextEx(IDC_EDIT_SET3));
	}
	else
	{
		SetDlgItemText(IDC_EDIT_HOSTIP, Set.GetString(_T("HostIP"), _T("169.254.254.244")));
		SetDlgItemText(IDC_EDIT_USER, Set.GetString(_T("Account"), _T("Admin")));
		SetDlgItemText(IDC_EDIT_PWORD, Set.GetString(_T("PWord"), _T("123")));
		SetDlgItemText(IDC_EDIT_SPEEDX, Set.GetString(_T("SpeedX"), _T("50")));
		SetDlgItemText(IDC_EDIT_SPEEDY, Set.GetString(_T("SpeedY"), _T("80")));
		SetDlgItemText(IDC_EDIT_ZEROX, Set.GetString(_T("ZeroX"), _T("0")));
		SetDlgItemText(IDC_EDIT_ZEROY, Set.GetString(_T("ZeroY"), _T("0")));
		SetSliderPos(IDC_SLIDER1,Set.GetInt(_T("SpeedX"), 50));
		SetSliderPos(IDC_SLIDER2,Set.GetInt(_T("SpeedY"), 50));
		SetDlgItemText(IDC_EDIT_SET1, Set.GetString(_T("Laser1"), _T("5")));
		SetDlgItemText(IDC_EDIT_SET2, Set.GetString(_T("Laser2"), _T("6")));
		SetDlgItemText(IDC_EDIT_SET3, Set.GetString(_T("Laser3"), _T("7")));
	}

}


BOOL CSubDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(1, 20, nullptr);

	SetSliderRange(IDC_SLIDER1,1, 500);
	SetSliderRange(IDC_SLIDER2,1, 500);
	SaveLoadSetting(false);

	SetSpecialID(IDC_CHECK_AUTOSTART, IDC_CHECK_SETTOP);
	SetDlgItemFloat(IDC_EDIT_POSX, 0);
	SetDlgItemFloat(IDC_EDIT_POSY, 0);
	SetDlgItemFont(IDC_STATIC_STATUS, 16, 700);
	SetDlgItemFont(IDC_STATIC_RUNING, 16, 700);
	SetDlgItemFont(IDC_STATIC_GX, 16, 700);
	SetDlgItemFont(IDC_STATIC_GY, 16, 700);
	SetDlgItemFont(IDC_STATIC_CTRL, 16, 700);
	SetDlgItemFont(IDC_STATIC_LS, 16, 700);
	SetDlgItemColor(IDC_STATIC_ALARMX, -1, RGB(0, 255, 0));
	SetDlgItemColor(IDC_STATIC_ALARMY, -1, RGB(0, 255, 0));
	SetDlgItemColor(IDC_STATIC_STATUS, 255);
	SetDlgItemColor(IDC_STATIC_RUNING, 255);

	SetDlgItemFont(IDC_STATIC_LASER1, 20, 700);
	SetDlgItemFont(IDC_STATIC_LASER2, 20, 700);
	SetDlgItemColor(IDC_STATIC_LASER1, RGB(255,255,255), RGB(0, 255, 0));
	SetDlgItemColor(IDC_STATIC_LASER2, RGB(255,255,255), RGB(0, 0, 255));

	SetDlgItemColor(IDC_STATIC_READ1, RGB(255, 255, 255), RGB(0, 0, 255));
	SetDlgItemColor(IDC_STATIC_READ2, RGB(255, 255, 255), RGB(0, 0, 255));
	SetDlgItemColor(IDC_STATIC_READ3, RGB(255, 255, 255), RGB(0, 0, 255));

	CLabel *pSTLab = GetMyLabel(IDC_STATIC_ALARMX);
	pSTLab->SetFontSize(20);
	pSTLab->SetLabelText(_T("●"));
	pSTLab->SetTextColor(RGB(0, 255, 0));
	pSTLab->ModifyStyleEx(SS_SUNKEN,0);

	pSTLab = GetMyLabel(IDC_STATIC_ALARMY);
	pSTLab->SetFontSize(20);
	pSTLab->SetLabelText(_T("●"));
	pSTLab->SetTextColor(RGB(0, 255, 0));

	GetMySliderCtrl(IDC_SLIDER1)->UnsubclassWindow();
	GetMySliderCtrl(IDC_SLIDER2)->UnsubclassWindow();
	GetMySliderCtrl(IDC_SLIDER3)->UnsubclassWindow();

	CColorSlider *AX1 = new CColorSlider();
	AX1->SubclassDlgItem(IDC_SLIDER1,this);

	CColorSlider *AX2 = new CColorSlider();
	AX2->SubclassDlgItem(IDC_SLIDER2,this);
	AX2->SetColor(~0, 0xFDFFC3, 0xDCE139, 0xDCE139,~0);

	CColorSlider *AX3 = new CColorSlider();
	AX3->SubclassDlgItem(IDC_SLIDER3,this);
	AX3->SetColor(~0, 0xFDFFC3, 0xDCE139, 0xDCE139,~0);

	SetSliderBindItem(IDC_SLIDER1,IDC_EDIT_SPEEDX);
	SetSliderBindItem(IDC_SLIDER2,IDC_EDIT_SPEEDY);
	SetSliderBindItem(IDC_SLIDER3,IDC_EDIT_SET1);
	SetDlgItemWheelValue(IDC_EDIT_SPEEDX);
	SetDlgItemWheelValue(IDC_EDIT_SPEEDY);
	SetDlgItemWheelValue(IDC_EDIT_ZEROX);
	SetDlgItemWheelValue(IDC_EDIT_ZEROY);
	SetDlgItemWheelValue(IDC_EDIT_POSX);
	SetDlgItemWheelValue(IDC_EDIT_POSY);
	SetDlgItemWheelValue(IDC_EDIT_SET1);
	SetDlgItemWheelValue(IDC_EDIT_SET2);
	SetDlgItemWheelValue(IDC_EDIT_SET3);

	SetButtonBmp(IDC_BUTTON_JOGX1,_T("left.png"),_T("left.png"));
	SetButtonBmp(IDC_BUTTON_JOGX2,_T("right.png"),_T("right.png"));
	SetButtonBmp(IDC_BUTTON_JOGY1,_T("down.png"),_T("down.png"));
	SetButtonBmp(IDC_BUTTON_JOGY2,_T("up.png"),_T("up.png"));

	SetButtonBmp(IDC_BUTTON_SETZEROX,_T("AddLocation.png"));
	SetButtonBmp(IDC_BUTTON_SETZEROY,_T("AddLocation.png"));
	SetButtonBmp(IDC_BUTTON_SETPOSX,_T("goto.png"));
	SetButtonBmp(IDC_BUTTON_SETPOSY,_T("goto.png"));
	SetButtonBmp(IDC_BUTTON_HOMEX,_T("home.png"));
	SetButtonBmp(IDC_BUTTON_HOMEY,_T("home.png"));
	SetButtonBmp(IDC_BUTTON_GOTOZEROX,_T("zero.png"));
	SetButtonBmp(IDC_BUTTON_GOTOZEROY,_T("zero.png"));
	SetButtonBmp(IDC_BUTTON_CLEARALARMX,_T("refresh.png"));
	SetButtonBmp(IDC_BUTTON_CLEARALARMY,_T("refresh.png"));

	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	_tccpy(lf.lfFaceName, _T("微软雅黑"));
	lf.lfWeight = 700;
	lf.lfHeight = -100;
	static CFont newFont;
	newFont.CreatePointFontIndirect(&lf);
	//SetDlgFont(&newFont);

	m_pDlgPSO = new CDlgPSOEdit();
	m_pDlgPSO->Create(this);
	m_pDlgPSO->m_pMain = this;

	StartThread(0);
	StartThread(1);
	StartThread(2);
	StartThread(3);
	StartThread(4);

	return TRUE;
}

static bool taskCallback(Automation1TaskCallbackArguments callbackArguments, Automation1TaskCallbackReturn callbackReturn)
{
	TRACE("taskCallback......\n");
	// Call the Automation1_Task_CallbackGetArguments() function one time to get the size of each array.
	int32_t taskIndex;
	int32_t callbackId;
	int32_t integerInputsLen;
	int32_t realInputsLen;
	int32_t stringInputsLen;
	int32_t maxStringInputLen;
	if (!Automation1_Task_CallbackGetArguments(callbackArguments,
		&taskIndex, &callbackId,
		NULL, &integerInputsLen,
		NULL, &realInputsLen,
		NULL, &stringInputsLen, &maxStringInputLen))
	{
	}

	// Allocate space for the arrays and call the Automation1_Task_CallbackGetArguments() function again to populate them. AeroScript strings are stored in succession based on the stringInputsLen and maxStringInputLen values. The total space that an array of AeroScript strings requires is stringInputsLen * maxStringInputLen.
	int64_t* integerInputs = (int64_t*)malloc(sizeof(int64_t) * integerInputsLen);
	double* realInputs = (double*)malloc(sizeof(double) * realInputsLen);
	char* stringInputs = (char*)malloc(sizeof(char) * stringInputsLen * maxStringInputLen);
	if (!Automation1_Task_CallbackGetArguments(callbackArguments,
		NULL, NULL,
		integerInputs, &integerInputsLen,
		realInputs, &realInputsLen,
		stringInputs, &stringInputsLen, &maxStringInputLen))
	{
	}

	// Loop over and print the results.
	for (int i = 0; i < integerInputsLen; i++)
	{
		TRACE("%d\n", integerInputs[i]);
	}

	for (int i = 0; i < realInputsLen; i++)
	{
		TRACE("%f\n", realInputs[i]);
	}

	for (int i = 0; i < stringInputsLen; i++)
	{
		TRACE("%s\n", &stringInputs[i * maxStringInputLen]);
	}

	free(integerInputs);
	free(realInputs);
	free(stringInputs);

	// Set the values to return to an AeroScript program.
	int64_t integerOutputs[4] = { 5, 2, 9, 102 };
	double realOutputs[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	const char* stringOutputs[3] = { "Hello", "From", "C!" };
	if (!Automation1_Task_CallbackSetReturn(callbackReturn,
		integerOutputs, 4,
		realOutputs, 5,
		stringOutputs, 3))
	{
		/* handle error */
	}

	return true;
}

int CSubDlgMain::OnSimpleThreadLoopRun(int nID)
{
	switch (nID)
	{
	case 0:

		for (;;)
		{
			SimpleWait(0);

			CheckDlgButton(IDC_CHECK_RUN, FALSE);
			if (IsDlgButtonChecked(IDC_CHECK_CONNECT))
			{
				CString strUser = GetDlgItemTextEx(IDC_EDIT_USER);
				CString strPWd = GetDlgItemTextEx(IDC_EDIT_PWORD);
				CString strIP = GetDlgItemTextEx(IDC_EDIT_HOSTIP);
				BOOL bRet = Automation1_ConnectWithHostAndUser(CW2A(strIP), CW2A(strUser), CW2A(strPWd), &controller);
				if (bRet)
				{
					//Automation1_Controller_Start(controller);
					if (!Automation1_Task_CallbackRegister(controller, 1, 1, taskCallback)) {
						TRACE("Automation1_Task_CallbackRegister FAILED\n");
					}

					CheckDlgButton(IDC_CHECK_RUN, TRUE);
					CheckDlgButton(IDC_CHECKENABLEX, TRUE);
					CheckDlgButton(IDC_CHECKENABLEY, TRUE);
					SendCmdMsg(IDC_CHECKENABLEX);
					SendCmdMsg(IDC_CHECKENABLEY);
				}
			}
			else
			{
				if (controller)
				{
					Automation1_Controller_Stop(controller);
					Automation1_Disconnect(controller);
					controller = nullptr;
				}
				CheckDlgButton(IDC_CHECKENABLEX, false);
				CheckDlgButton(IDC_CHECKENABLEY, false);
				CheckDlgButton(IDC_CHECK_RUN, false);
			}
			SetDlgItemText(IDC_STATIC_STATUS, controller ? _T("已连接") : _T("未连接"));
			SetDlgItemColor(IDC_STATIC_STATUS, controller ? RGB(0, 255, 0) : RGB(255, 0, 0));
			SendCmdMsg(IDC_CHECK_RUN);
			SaveLoadSetting(true);
		}
		break;
	case 1:
	{
		for (;;)
		{
			{
				int nAxis = 0;
				Automation1StatusConfig statusConfig;
				Automation1_StatusConfig_Create(&statusConfig);

				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramPositionFeedback, 0);
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_DriveStatus, 0);
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisStatus, 0);
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisFault, 0);
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramVelocityFeedback, 0);

				double result[10];
				if (Automation1_Status_GetResults(controller, statusConfig, result, 5))
				{
					SetDlgItemFloat(IDC_STATIC_POSX, result[0],4);
					SetDlgItemFloat(IDC_STATIC_SPEEDX, result[4],4);
					m_dbXPos = result[0];

					CLabel *pSTLab = GetMyLabel(IDC_STATIC_ALARMX);
					if (result[3] > 0)
						pSTLab->SetTextColor(RGB(255, 0, 0));
					else
						pSTLab->SetTextColor(RGB(0, 255, 0));

					bool isEnabled = (Automation1DriveStatus_Enabled & (int64_t)result[1]) == Automation1DriveStatus_Enabled;
					//TRACE("Enabled: %s\n", isEnabled ? "true" : "false");


					bool isHomed = (Automation1AxisStatus_Homed & (int64_t)result[2]) == Automation1AxisStatus_Homed;
					//TRACE("Homed: %s\n", isHomed ? "true" : "false");

					bool calibrationEnabled1D = (Automation1AxisStatus_CalibrationEnabled1D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled1D;
					bool calibrationEnabled2D = (Automation1AxisStatus_CalibrationEnabled2D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled2D;
					//TRACE("Calibration State: %s\n", (calibrationEnabled1D || calibrationEnabled2D) ? "true" : "false");
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
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_AxisFault, 0);
				Automation1_StatusConfig_AddAxisStatusItem(statusConfig, nAxis, Automation1AxisStatusItem_ProgramVelocityFeedback, 0);

				double result[10];
				if (Automation1_Status_GetResults(controller, statusConfig, result, 5))
				{
					SetDlgItemFloat(IDC_STATIC_POSY, result[0],4);
					SetDlgItemFloat(IDC_STATIC_SPEEDY, result[4], 4);
					m_dbYPos = result[0];
					CLabel *pSTLab = GetMyLabel(IDC_STATIC_ALARMY);
					if (result[3] > 0)
						pSTLab->SetTextColor(RGB(255, 0, 0));
					else
						pSTLab->SetTextColor(RGB(0, 255, 0));

					bool isEnabled = (Automation1DriveStatus_Enabled & (int64_t)result[1]) == Automation1DriveStatus_Enabled;
					//TRACE("Enabled: %s\n", isEnabled ? "true" : "false");


					bool isHomed = (Automation1AxisStatus_Homed & (int64_t)result[2]) == Automation1AxisStatus_Homed;
					//TRACE("Homed: %s\n", isHomed ? "true" : "false");

					bool calibrationEnabled1D = (Automation1AxisStatus_CalibrationEnabled1D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled1D;
					bool calibrationEnabled2D = (Automation1AxisStatus_CalibrationEnabled2D & (int64_t)result[2]) == Automation1AxisStatus_CalibrationEnabled2D;
					//TRACE("Calibration State: %s\n", (calibrationEnabled1D || calibrationEnabled2D) ? "true" : "false");
				}
				Automation1_StatusConfig_Destroy(statusConfig);
			}
			Sleep(20);
		}
	}
		break;
	default:
		break;
	}
	return 0;
}


void CSubDlgMain::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1 && controller)
	{
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CSubDlgMain::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int nAxis = 0;
	switch (wParam)
	{
	case IDC_CHECK_CONNECT:
		SimpleFire(0);
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

	case IDC_BUTTON_CLEARALARMX:
		if (controller)
		{
			Automation1_Command_FaultAcknowledge(controller, 1, &nAxis, 1);
		}
		break;
	case IDC_BUTTON_CLEARALARMY:
		if (controller)
		{
			nAxis = 1;
			Automation1_Command_FaultAcknowledge(controller, 1, &nAxis, 1);
		}
		break;

	case IDC_CHECKENABLEX:
		if (controller)
		{
			if (IsDlgButtonChecked(IDC_CHECKENABLEX))
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
			else
				Automation1_Command_Disable(controller, &nAxis, 1);
		}
		break;

	case IDC_CHECKENABLEY:
		if (controller)
		{
			nAxis = 1;
			if (IsDlgButtonChecked(IDC_CHECKENABLEY))
				Automation1_Command_Enable(controller, 1, &nAxis, 1);
			else
				Automation1_Command_Disable(controller, &nAxis, 1);
		}
		break;

	case IDC_BUTTON_SETPOSX:
	{
		double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX);
		double pos = GetDlgItemFloat(IDC_EDIT_POSX);
		Automation1_Command_MoveAbsolute(controller, 1, &nAxis, 1, &pos, 1, &speed, 1);
	}
		break;

	case IDC_BUTTON_GOTOZEROX:
	{
		double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX);
		double pos = GetDlgItemFloat(IDC_EDIT_ZEROX);
		Automation1_Command_MoveAbsolute(controller, 1, &nAxis, 1, &pos, 1, &speed, 1);
	}
		break;

	case IDC_BUTTON_SETPOSY:
	{
		nAxis = 1;
		double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY);
		double pos = GetDlgItemFloat(IDC_EDIT_POSY);
		Automation1_Command_MoveAbsolute(controller, 1, &nAxis, 1, &pos, 1, &speed, 1);
	}
		break;

	case IDC_BUTTON_GOTOZEROY:
	{
		nAxis = 1;
		double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY);
		double pos = GetDlgItemFloat(IDC_EDIT_ZEROY);
		Automation1_Command_MoveAbsolute(controller, 1, &nAxis, 1, &pos, 1, &speed, 1);
	}
		break;

	case IDC_BUTTON_SETZEROX:
	case IDC_BUTTON_SETZEROY:
		SaveLoadSetting(true);
		break;

	case IDC_BUTTON_SCRIPT:
	{
		CFileDialog dlg(true,_T("*.ascript"));
		if (dlg.DoModal() == IDOK)
		{
			if (MessageBox(CString(_T("确定运行以下脚本吗？\n"))+dlg.GetPathName(), _T("提示"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				const char *strLoad = "manul.ascript";
				Automation1_Files_Upload(controller,CW2A(dlg.GetPathName()), strLoad);
				Automation1_Task_ProgramLoad(controller, 1, strLoad);
				Automation1_Task_ProgramRun(controller, 1, strLoad);
			}
		}
	}
		break;

	case 9981:
	{
		const char *strLoad = "tmp.ascript";
		CString strFile = GetCurrentPath() + _T("\\tmp.ascript");
		Automation1_Files_Upload(controller, CW2A(strFile), strLoad);
		Automation1_Task_ProgramLoad(controller, 1, strLoad);
		Automation1_Task_ProgramRun(controller, 1, strLoad);
	}
	return true;

	case 9982:
	{
		const char *strLoad = "writefile.ascript";
		CString strFile = GetCurrentPath() + _T("\\writefile.ascript");
		Automation1_Files_Upload(controller, CW2A(strFile), strLoad);
		Automation1_Task_ProgramLoad(controller, 1, strLoad);
		Automation1_Task_ProgramRun(controller, 1, strLoad);
	}
		return true;

	case IDC_BUTTON_PSO:
		m_pDlgPSO->CenterWindow((this));
		m_pDlgPSO->Show();
		break;

	default:
		break;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CSubDlgMain::PreTranslateMessage(MSG* pMsg)
{
	if(controller)
	{
		int nAxis = 0;
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX1)->GetSafeHwnd())
			{
				double speed = GetDlgItemFloat(IDC_EDIT_SPEEDX) * -1;
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
				double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY) * -1;
				Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
			}

			if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY2)->GetSafeHwnd())
			{
				nAxis = 1;
				double speed = GetDlgItemFloat(IDC_EDIT_SPEEDY);
				Automation1_Command_MoveFreerun(controller, 1, &nAxis, 1, &speed, 1);
			}
		}

		if (pMsg->message == WM_LBUTTONUP)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX2)->GetSafeHwnd() ||
				pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGX1)->GetSafeHwnd())
			{
				SaveLoadSetting(true);
				Automation1_Command_MoveFreerunStop(controller, 1, &nAxis, 1);
			}

			if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY2)->GetSafeHwnd() ||
				pMsg->hwnd == GetDlgItem(IDC_BUTTON_JOGY1)->GetSafeHwnd())
			{
				nAxis = 1;
				SaveLoadSetting(true);
				Automation1_Command_MoveFreerunStop(controller, 1, &nAxis, 1);
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
