// DlgPSOEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "DlgPSOEdit.h"
#include "afxdialogex.h"
#include "SubDlgMain.h"

// CDlgPSOEdit dialog

IMPLEMENT_DYNAMIC(CDlgPSOEdit, CDialogEx)

CDlgPSOEdit::CDlgPSOEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PSOSCRIPT, pParent)
{

}

CDlgPSOEdit::~CDlgPSOEdit()
{
}

void CDlgPSOEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPSOEdit, CDialogEx)
END_MESSAGE_MAP()


static CString strAllText;
static CString GetLargeText(CRichEditCtrl* richEdit)
{
	strAllText.Empty();
	try
	{
		richEdit->SetSel(0, 0xFFFFFF);
		richEdit->Copy();

		if (::OpenClipboard(nullptr))
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
	if (UF.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		const char *pUTF8 = UTF8Encode(CW2A(strText));
		UF.Write(pUTF8, strlen(pUTF8));
		UF.Close();
		return TRUE;
	}
	return FALSE;
}
// CDlgPSOEdit message handlers

BOOL CDlgPSOEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	SetDlgItemInt(IDC_EDIT_POSCOUNTX, 100);
	SetDlgItemFloat(IDC_EDIT_STEPLENX, 0.5);
	SetDlgItemFloat(IDC_EDIT_POSAX, 0);
	SetDlgItemFloat(IDC_EDIT_POSBX, 100);

	SetDlgItemInt(IDC_EDIT_POSCOUNTY, 10);
	SetDlgItemFloat(IDC_EDIT_STEPLENY, 0.5);
	SetDlgItemFloat(IDC_EDIT_POSAY, 0);
	SetDlgItemFloat(IDC_EDIT_POSBY, 100);

	CheckDlgButton(IDC_RADIO3, true);
	SetDlgItemFloat(IDC_EDIT_SPEED, 50);
	SetDlgItemFloat(IDC_EDIT_TPLUSTIME, 10);
	SetDlgItemFloat(IDC_EDIT_PLUSDUR, 10);
	SetDlgItemFloat(IDC_EDIT_PLUSCOUNT, 1);
	SetDlgItemFont(IDC_RICHEDIT21, 12, 400, _T("Fixedsys"));

	CMyListCtrl *pList = GetMyListCtrl(IDC_LIST_FILE);
	m_pList = pList;

	pList->InsertColumn(0, _T("序号"), 0, 60);
	pList->InsertColumn(1, _T("X 位置"), 0, 80);
	pList->InsertColumn(2, _T("Y 位置"), 0, 80);

	SendCmdMsg(IDC_BUTTON_LIST);

	return true;
}

BOOL CDlgPSOEdit::OnCommand(WPARAM wParam, LPARAM lParam)
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

	case IDC_CHECK_WORKY:
	case IDC_CHECK_BACKWORK:
	case IDC_CHECK_APPEND:
	case IDC_BUTTON_LIST:
	{
		if (!IsDlgButtonChecked(IDC_CHECK_APPEND))
			m_pList->DeleteAllItems();

		int nCountX = GetDlgItemInt(IDC_EDIT_POSCOUNTX);
		float fStepX = GetDlgItemFloat(IDC_EDIT_STEPLENX);
		float fStartX = GetDlgItemFloat(IDC_EDIT_POSAX);

		int nCountY = GetDlgItemInt(IDC_EDIT_POSCOUNTY);
		float fStepY = GetDlgItemFloat(IDC_EDIT_STEPLENY);
		float fStartY = GetDlgItemFloat(IDC_EDIT_POSAY);

		int nBegin = m_pList->GetItemCount();
		m_pList->SetRedraw(false);

		if (IsDlgButtonChecked(IDC_CHECK_WORKY))
		{
			for (int i = 0; i < nCountX; i++)
			{
				for (int j = 0; j < nCountY; j++)
				{
					int nItem = m_pList->GetItemCount();
					m_pList->InsertItem(nItem, _T(""));
					m_pList->SetItemInt(nItem, 0, nItem + 1);
					m_pList->SetItemFloat(nItem, 1, fStartX + (i)* fStepX, 4);

					if (IsDlgButtonChecked(IDC_CHECK_BACKWORK) && i % 2)
					{
						m_pList->SetItemFloat(nItem, 2, fStartY + (nCountY - 1 - j)* fStepY, 4);
					}
					else
					{
						m_pList->SetItemFloat(nItem, 2, fStartY + (j)* fStepY, 4);
					}

				}
			}
		}
		else
		{
			for (int j = 0; j < nCountY; j++)
			{
				for (int i = 0; i < nCountX; i++)
				{
					int nItem = m_pList->GetItemCount();
					m_pList->InsertItem(nItem, _T(""));
					m_pList->SetItemInt(nItem, 0, nItem + 1);

					if (IsDlgButtonChecked(IDC_CHECK_BACKWORK) && j % 2)
					{
						m_pList->SetItemFloat(nItem, 1, fStartX + (nCountX - 1 - i)* fStepX, 4);
					}
					else
					{
						m_pList->SetItemFloat(nItem, 1, fStartX + (i)* fStepX, 4);
					}

					m_pList->SetItemFloat(nItem, 2, fStartY + (j)* fStepY, 4);
				}
			}
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
		strLine.Format(_T("#define  NUM_DISTANCES %d\n\nprogram\n\n\tvar $axisX as axis = X1\n\tvar $axisY as axis = Y1\n\n\tvar $distances[NUM_DISTANCES] as real\n\n"), nCount * 2);
		strScript += strLine;

		strLine.Format(_T("\tvar $posStartX as real = %.3f\n\tvar $posEndX as real = %.3f\n\n"), GetDlgItemFloat(IDC_EDIT_POSAX), GetDlgItemFloat(IDC_EDIT_POSBX));
		strScript += strLine;

		strLine.Format(_T("\tvar $posStartY as real = %.3f\n\tvar $posEndY as real = %.3f\n\n"), GetDlgItemFloat(IDC_EDIT_POSAY), GetDlgItemFloat(IDC_EDIT_POSBY));
		strScript += strLine;

		strLine.Format(_T("\tEnable([$axisX,$axisY])\n\tHome([$axisX,$axisY])\n\tSetupTaskTargetMode(TargetMode.%s)\n\n\tMoveAbsolute($axisX,$posStartX,100)\n\tMoveAbsolute($axisY,$posStartY,100)\n\tWaitForMotionDone([$axisX,$axisY])\n\n\tPsoReset([$axisX,$axisY])\n\n\tPsoDistanceConfigureInputs([$axisX,$axisY], [PsoDistanceInput.iXC4ePrimaryFeedback]);\n\n"), IsDlgButtonChecked(IDC_RADIO3) ? _T("Absolute") : _T("Incremental"));
		strScript += strLine;

		for (int i = 0; i < nCount; i++)
		{
			strLine.Format(_T("\t$distances[%d] = UnitsToCounts($axisX, %s) / ParameterGetAxisValue($axisX, AxisParameter.PrimaryEmulatedQuadratureDivider)\n"), i * 2, m_pList->GetItemText(i, 1));
			strScript += strLine;
			strLine.Format(_T("\t$distances[%d] = UnitsToCounts($axisY, %s) / ParameterGetAxisValue($axisY, AxisParameter.PrimaryEmulatedQuadratureDivider)\n"), i * 2 + 1, m_pList->GetItemText(i, 2));
			strScript += strLine;
		}

		int v1 = GetDlgItemInt(IDC_EDIT_TPLUSTIME);
		int v2 = GetDlgItemInt(IDC_EDIT_PLUSDUR);
		int v3 = GetDlgItemInt(IDC_EDIT_PLUSCOUNT);
		int v4 = GetDlgItemInt(IDC_EDIT_SPEED);

		strLine.Format(_T(R"(
	DriveArrayWrite($axis, $distances, 0, NUM_DISTANCES, DriveArrayType.PsoDistanceEventDistances)
	
	// Configure the distance module to generate an event at the distances specified in the drive array.
	PsoDistanceConfigureArrayDistances($axis, 0, NUM_DISTANCES, false)

	// Enable the distance counter.
	PsoDistanceCounterOn($axis)

	// Enable distance events.
	PsoDistanceEventsOn($axis);

	PsoWaveformConfigureMode($axis, PsoWaveformMode.Pulse)
	PsoWaveformConfigurePulseFixedTotalTime($axisX, %d)     // 脉冲固定总时间
	PsoWaveformConfigurePulseFixedOnTime($axisX, %d)        // 脉冲开启时间
	PsoWaveformConfigurePulseFixedCount($axisX, %d)         // 脉冲次数
	PsoWaveformApplyPulseConfiguration($axisX)

	// Enable the distance counter.               // 启用距离计数器
	PsoDistanceCounterOn($axisX)
	PsoDistanceCounterOn($axisY)

	// Enable distance events.                    // 启用距离事件
	PsoDistanceEventsOn($axisX);
	PsoWaveformOn($axisX)
	PsoDistanceEventsOn($axisY);
	PsoWaveformOn($axisY)

	// Select the waveform module output as the PSO output source.
	// 选择波形模块作为 PSO 输出源
	PsoOutputConfigureSource($axisX, PsoOutputSource.Waveform)
	PsoOutputConfigureSource($axisY, PsoOutputSource.Waveform)

	// Setup the physical output (optional)        // 设置物理输出（可选）
	PsoOutputConfigureOutput($axisX, PsoOutputPin.iXC4eDedicatedOutput)  // What Pin do we want output to come out on.
	PsoOutputConfigureOutput($axisY, PsoOutputPin.iXC4eDedicatedOutput)  // What Pin do we want output to come out on.
	                                                                    // 指定使用哪个输出引脚
	// Trigger Data Collection.                    // 触发数据采集
	//AppDataCollectionSnapshot()

	MoveLinear($axisX, $posEndX, %d)   // 50是速度
	WaitForMotionDone($axisX)

	MoveLinear($axisY, $posEndY, %d)   // 50是速度
	WaitForMotionDone($axisY)

	PsoWaveformOff($axisX)                          // 停止 PSO 功能
	PsoWaveformOff($axisY)           
	//AppDataCollectionStop()                      // 停止数据采集
	PsoDistanceCounterOff($axisX)
	PsoDistanceCounterOff($axisY)
	//Enable the PSO Distance  Event module        // 禁用 PSO 距离事件模块
	PsoDistanceEventsOff($axisX)
	PsoDistanceEventsOff($axisY)

	// Stop Data Collection.                       // 停止数据采集
	//AppDataCollectionStop()

end
)"), v1, v2, v3, v4);

		strScript += strLine;
		SetDlgItemText(IDC_RICHEDIT21, strScript);

		SetDlgItemText(IDC_EDIT_NAME, CString(_T("PSOScript")) + FormatTime(1));
	}
	break;

	case IDC_BUTTON_RUN:
	{
		CString strText = GetLargeText((CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21));

		CString strFile = GetCurrentPath() + _T("tmp.ascript");
		if (SaveTextAsUTF8(strText, strFile))
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
			strInfo.Format(_T("%d"), strText.GetLength());
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