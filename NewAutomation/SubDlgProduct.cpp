// SubDlgProduct.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgProduct.h"
#include "afxdialogex.h"
#include "SubDlgMain.h"

// CSubDlgProduct dialog

IMPLEMENT_DYNAMIC(CSubDlgProduct, CDialogEx)

CSubDlgProduct::CSubDlgProduct(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PRODUCT, pParent)
{

}

CSubDlgProduct::~CSubDlgProduct()
{
}

void CSubDlgProduct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgProduct, CDialogEx)
END_MESSAGE_MAP()

// 基于COM接口读取超大文本
static CString strAllText;
static TCHAR strLineBuf[4096] = { 0 };
static CString GetLargeText(CRichEditCtrl* richEdit)
{
	strAllText.Empty();
	try
	{
		richEdit->SetSel(0, 0xFFFFFF);
		richEdit->Copy();

		if(::OpenClipboard(nullptr))
		{
			HANDLE hData = ::GetClipboardData(CF_TEXT);
			CHAR *pTmp = (CHAR *)::GlobalLock(hData);
			strAllText = CA2W(pTmp);
			::GlobalUnlock(pTmp);
			::CloseClipboard();
		}
	}
	catch (const std::exception&)
	{
	}
	return strAllText;
}

static BOOL SaveTextAsUTF8(const CString&strText, const CString&strFile)
{
	CFile UF;
	if(UF.Open(strFile,CFile::modeCreate|CFile::modeWrite))
	{ 
		const char *pUTF8 = UTF8Encode(CW2A(strText));
		UF.Write(pUTF8,strlen(pUTF8));
		UF.Close();
		return TRUE;
	}
	return FALSE;
}

// CSubDlgProduct message handlers
BOOL CSubDlgProduct::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemInt(IDC_EDIT_POSCOUNT, 1000);
	SetDlgItemFloat(IDC_EDIT_STEPLEN, 0.5);
	SetDlgItemFloat(IDC_EDIT_POS0, 0);
	CheckDlgButton(IDC_RADIO1, true);

	CheckDlgButton(IDC_RADIO3, true);
	SetDlgItemFloat(IDC_EDIT_POS1, 0);
	SetDlgItemFloat(IDC_EDIT_POS2, 150);
	SetDlgItemFloat(IDC_EDIT_SPEED, 50);
	SetDlgItemFloat(IDC_EDIT_TPLUSTIME, 10);
	SetDlgItemFloat(IDC_EDIT_PLUSDUR, 10);
	SetDlgItemFloat(IDC_EDIT_PLUSCOUNT, 1);
	SetDlgItemFont(IDC_RICHEDIT21, 12, 400,_T("Fixedsys"));

	CMyListCtrl *pList = GetMyListCtrl(IDC_LIST_FILE);
	m_pList = pList;

	pList->InsertColumn(0, _T("序号"), 0, 60);
	pList->InsertColumn(1, _T("位置值"), 0, 100);

	SendCmdMsg(IDC_BUTTON_LIST);

	return TRUE;
}

BOOL CSubDlgProduct::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case CMD_LISTCTRL_COLCLK:
	{
		if (m_pList->GetClickSubItem() == 1)
		{
			m_pList->ShowEdit();
		}
	}
	break;

	case IDC_BUTTON_CLEAR:
		m_pList->DeleteAllItems();
		break;

	case IDC_BUTTON_LIST:
	{
		if (!IsDlgButtonChecked(IDC_CHECK_APPEND))
			m_pList->DeleteAllItems();

		int nCount = GetDlgItemInt(IDC_EDIT_POSCOUNT);
		float fStep = GetDlgItemFloat(IDC_EDIT_STEPLEN);
		float fStart = GetDlgItemFloat(IDC_EDIT_POS0);
		int nBegin = m_pList->GetItemCount();
		m_pList->SetRedraw(false);
		for (int i = nBegin; i < nCount + nBegin; i++)
		{
			m_pList->InsertItem(i, _T(""));
			m_pList->SetItemInt(i, 0, i + 1);
			m_pList->SetItemFloat(i, 1, fStart + (i - nBegin) * fStep, 3);
		}
		m_pList->SetRedraw(true);

		static BOOL bFirst = TRUE;
		if (bFirst) SendCmdMsg(IDC_BUTTON_CREATE);
		bFirst = FALSE;
	}
	break;

	case IDC_BUTTON_CREATE:
	{
		CString strLine;
		CString strScript;

		int nCount = m_pList->GetItemCount();
		strLine.Format(_T("#define  NUM_DISTANCES %d\n\nprogram\n\n\tvar $axis as axis = %s\n\n\tvar $distances[NUM_DISTANCES] as real\n\n"), nCount, IsDlgButtonChecked(IDC_RADIO1) ? _T("X1") : _T("Y1"));
		strScript += strLine;

		strLine.Format(_T("\tvar $posStart as real = %.3f\n\tvar $posEnd as real = %.3f\n\n"), GetDlgItemFloat(IDC_EDIT_POS1), GetDlgItemFloat(IDC_EDIT_POS2));
		strScript += strLine;

		strLine.Format(_T("\tEnable($axis)\n\tHome($axis)\n\tSetupTaskTargetMode(TargetMode.%s)\n\n\tMoveAbsolute($axis,$posStart,100)\n\tWaitForMotionDone($axis)\n\n\tPsoReset($axis)\n\n\tPsoDistanceConfigureInputs($axis, [PsoDistanceInput.iXC4ePrimaryFeedback]);\n\n"), IsDlgButtonChecked(IDC_RADIO3) ? _T("Absolute"): _T("Incremental"));
		strScript += strLine;

		for (int i = 0; i < nCount; i++)
		{
			strLine.Format(_T("\t$distances[%d] = UnitsToCounts($axis, %s) / ParameterGetAxisValue($axis, AxisParameter.PrimaryEmulatedQuadratureDivider)\n"), i, m_pList->GetItemText(i, 1));
			strScript += strLine;
		}

		int v1 = GetDlgItemInt(IDC_EDIT_TPLUSTIME);
		int v2 = GetDlgItemInt(IDC_EDIT_PLUSDUR);
		int v3 = GetDlgItemInt(IDC_EDIT_PLUSCOUNT);
		int v4 = GetDlgItemInt(IDC_EDIT_SPEED) ;

		strLine.Format(_T(R"(
	DriveArrayWrite($axis, $distances, 0, NUM_DISTANCES, DriveArrayType.PsoDistanceEventDistances)
	
	// Configure the distance module to generate an event at the distances specified in the drive array.
	PsoDistanceConfigureArrayDistances($axis, 0, NUM_DISTANCES, false)

	// Enable the distance counter.
	PsoDistanceCounterOn($axis)

	// Enable distance events.
	PsoDistanceEventsOn($axis);

	PsoWaveformConfigureMode($axis, PsoWaveformMode.Pulse)
	PsoWaveformConfigurePulseFixedTotalTime($axis, %d)     // 脉冲固定总时间
	PsoWaveformConfigurePulseFixedOnTime($axis, %d)        // 脉冲开启时间
	PsoWaveformConfigurePulseFixedCount($axis, %d)         // 脉冲次数
	PsoWaveformApplyPulseConfiguration($axis)

	// Enable the distance counter.               // 启用距离计数器
	PsoDistanceCounterOn($axis)

	// Enable distance events.                    // 启用距离事件
	PsoDistanceEventsOn($axis);
	PsoWaveformOn($axis)

	// Select the waveform module output as the PSO output source.
	// 选择波形模块作为 PSO 输出源
	PsoOutputConfigureSource($axis, PsoOutputSource.Waveform)

	// Setup the physical output (optional)        // 设置物理输出（可选）
	PsoOutputConfigureOutput($axis, PsoOutputPin.iXC4eDedicatedOutput)  // What Pin do we want output to come out on.
	                                                                    // 指定使用哪个输出引脚
	// Trigger Data Collection.                    // 触发数据采集
	//AppDataCollectionSnapshot()

	// Move the axis 35 units, expecting 3 events. // 移动轴 35 单位，预计产生 3 个事件
	MoveLinear($axis, $posEnd, %d)   // 50是速度
	WaitForMotionDone($axis)

	PsoWaveformOff($axis)                          // 停止 PSO 功能
	//AppDataCollectionStop()                      // 停止数据采集
	PsoDistanceCounterOff($axis)
	//Enable the PSO Distance  Event module        // 禁用 PSO 距离事件模块
	PsoDistanceEventsOff($axis)

	// Stop Data Collection.                       // 停止数据采集
	//AppDataCollectionStop()

end
)"), v1, v2, v3, v4 );

		strScript += strLine;
		SetDlgItemText(IDC_RICHEDIT21, strScript);

		SetDlgItemText(IDC_EDIT_NAME, CString(_T("PSOScript")) + FormatTime(1));
	}
	break;

	case IDC_BUTTON_RUN:
	{
		CString strText = GetLargeText((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21));

		CString strFile = GetCurrentPath() + _T("tmp.ascript");
		if(SaveTextAsUTF8(strText,strFile))
		{
			if (MessageBox(CString(_T("确定运行脚本吗？")), _T("提示"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			{
				m_pMain->SendCmdMsg(9981);
			}
		}
	}
	break;

	case IDC_BUTTON_SAVE:
	{
		CString strName;
		GetDlgItemText(IDC_EDIT_NAME, strName);

		CString strText = GetLargeText((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21));
		CString strFile = GetCurrentPath() + CString(_T("\\ascript\\")) + strName + _T(".ascript");
		::CreateMultiLayerDir(strFile);
		if (SaveTextAsUTF8(strText, strFile))
		{
			CString strInfo;
			strInfo.Format(_T("%d"),strText.GetLength());
			OutputDebugString(strInfo);
			MessageBox(CString(_T("脚本保存成功！")) + strFile, _T("提示"), MB_ICONINFORMATION);
		}
	}
	break;

	case IDC_BUTTON_SAVEAS:
	{
		CString strText = GetLargeText((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21));

		CFileDialog dlg(true, _T("*.ascript"));
		if (dlg.DoModal() == IDOK)
		{
			CString strFile = dlg.GetPathName();
			if (SaveTextAsUTF8(strText, strFile))
			{
				MessageBox(CString(_T("脚本保存成功！\n")) + strFile, _T("提示"), MB_ICONINFORMATION);
			}
		}
	}
	break;

	case IDC_BUTTON_COPY:
	{
		((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21))->SetSel(0, 0xFFFFFF);
		((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21))->Copy();

		MessageBox(CString(_T("脚本已复制到剪贴板！")), _T("提示"), MB_ICONINFORMATION);
	}
	break;
	default:
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}