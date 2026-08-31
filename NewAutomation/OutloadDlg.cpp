// OutloadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "OutloadDlg.h"
#include "afxdialogex.h"
#include "SubDlgMain.h"

// COutloadDlg dialog

IMPLEMENT_DYNAMIC(COutloadDlg, CDialogEx)

COutloadDlg::COutloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_OUTLOAD, pParent)
{

}

COutloadDlg::~COutloadDlg()
{
}

void COutloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COutloadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RUNALL, &COutloadDlg::OnBnClickedButtonRunall)
END_MESSAGE_MAP()

static CString  strCallFile1(R"(
// ================================================================
// PSO Drilling Motion Program -- Validated Baseline (v1)
// 已验证基线版本 (v1)
//
// ================================================================

program
    var $X_axis as axis = X1
    var $Y_axis as axis = Y1
    Enable([$X_axis, $Y_axis])
	Home([$X_axis, $Y_axis])
	WaitForMotionDone([$X_axis, $Y_axis])

    var $X_speed as real = %.2f
    var $Y_speed as real = %.2f
    var $posSpeed as real = %.2f
    var $TotalTime as integer = %d
    var $OnTime as integer = %d
    var $FixedCount as integer = %d
    var $fileBegin as integer = %d
    var $fileEnd as integer = %d

    var $type as integer
    var $count as integer
    var $line as real
    var $header[2] as integer

    var $R_positions[10000] as real
    var $distances[10000] as real
    var $index as integer
    var $file as integer
    var $fileHandle as handle

    var $adjust as real = %.2f
    var $posStart as real
    var $posEnd as real
    var $increment as real = 0
    var $lastType as integer = -1

    var $countsDivider as real
    var $countsPerUnit as real
    $countsDivider = ParameterGetAxisValue($X_axis, AxisParameter.PrimaryEmulatedQuadratureDivider)
    $countsPerUnit = ParameterGetAxisValue($X_axis, AxisParameter.CountsPerUnit)
    var $scaleFactor as real = $countsPerUnit / $countsDivider

    TimerClear(0)

    PsoReset($X_axis)
    PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4PrimaryFeedback])

    PsoWaveformConfigureMode($X_axis, PsoWaveformMode.Pulse)
    PsoWaveformConfigurePulseFixedTotalTime($X_axis, $TotalTime)
    PsoWaveformConfigurePulseFixedOnTime($X_axis, $OnTime)
    PsoWaveformConfigurePulseFixedCount($X_axis, $FixedCount)
    PsoWaveformApplyPulseConfiguration($X_axis)

    PsoOutputConfigureSource($X_axis, PsoOutputSource.Waveform)
    PsoOutputConfigureOutput($X_axis, PsoOutputPin.iXC4DedicatedOutput)

    // ============================================================
    // Single File Open Outside the Loop
    // ============================================================
    var $masterFileName as string = "/all_positions.rd"
    $fileHandle = FileOpenBinary($masterFileName, FileMode.Read)

    for $file = $fileBegin to $fileEnd

        FileBinaryReadUInt32Array($fileHandle, $header, 2)
        $type = $header[0]
        $count = $header[1]
        $line = FileBinaryReadFloat64($fileHandle)
        FileBinaryReadFloat64Array($fileHandle, $R_positions, $count)

        if ($R_positions[0] < $R_positions[$count-1])
            $posStart = $R_positions[0] - $adjust
            $posEnd = $R_positions[$count-1] + $adjust
        else
            $posStart = $R_positions[0] + $adjust
            $posEnd = $R_positions[$count-1] - $adjust
        end

        if $type == 0
            if $lastType == 1
                // Coming back from a Y-drive scan block: restore primary feedback once.
                PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4PrimaryFeedback])
                DriveEncoderOutputOff($Y_axis, EncoderOutputChannel.SyncPortB)
            end
        end

        if $type == 1
            if $lastType != 1
                // Entering a Y-drive scan block: configure sync port once.
                DriveEncoderOutputConfigureInput($Y_axis, EncoderOutputChannel.SyncPortB, EncoderInputChannel.PrimaryEncoder)
                DriveEncoderOutputConfigureDivider($Y_axis, EncoderOutputChannel.SyncPortB, 1)
                DriveEncoderOutputOn($Y_axis, EncoderOutputChannel.SyncPortB)
                PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4SyncPortA])
            end
        end

        if $type == 0
            MoveAbsolute([$Y_axis, $X_axis], [$line, $posStart], [$posSpeed, $posSpeed])
        end
        if $type == 1
            MoveAbsolute([$X_axis, $Y_axis], [$line, $posStart], [$posSpeed, $posSpeed])
        end

        CriticalSectionStart()
            for $index = 0 to $count - 1
                if $index == 0
                    $increment = $adjust
                else
                    $increment = Abs($R_positions[$index] - $R_positions[$index-1])
                end
                $distances[$index] = $increment * $scaleFactor
            end
        CriticalSectionEnd()

        WaitForMotionDone([$Y_axis, $X_axis])

        DriveArrayWrite($X_axis, $distances, 0, $count, DriveArrayType.PsoDistanceEventDistances)
        PsoDistanceConfigureArrayDistances($X_axis, 0, $count, false)

        PsoDistanceCounterOn($X_axis)
        PsoDistanceEventsOn($X_axis)
        PsoWaveformOn($X_axis)

        if $type == 0
            SetupAxisSpeed($X_axis, $X_speed)
            MoveRapid($X_axis, $posEnd - $posStart)
            WaitForMotionDone($X_axis)
        end

        if $type == 1
            SetupAxisSpeed($Y_axis, $Y_speed)
            MoveRapid($Y_axis, $posEnd - $posStart)
            WaitForMotionDone($Y_axis)
        end

        PsoWaveformOff($X_axis)
        PsoDistanceCounterOff($X_axis)
        PsoDistanceEventsOff($X_axis)

        $lastType = $type
    end

    if $lastType == 1
        PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4PrimaryFeedback])
        DriveEncoderOutputOff($Y_axis, EncoderOutputChannel.SyncPortB)
    end

    FileClose($fileHandle)

    AppMessageDisplay("Total time (minutes): " + RealToString(TimerRead(0, TimerMode.Precise) / 60000.0))
end)");


BOOL COutloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pLoader = new COutsideLoad();

	CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
	pList->InsertColumn(0, _T("编号"), 0, 60);
	pList->InsertColumn(1, _T("类型"), 0, 60);
	pList->InsertColumn(2, _T("位置数量"), 0, 80);

	SetDlgItemFont(IDC_RICHEDIT21, 12, 400, _T("Fixedsys"));

	CheckDlgButton(IDC_CHECK_AUTORUN, 0);

	StartThread(0);
	StartThread(1);

	SaveLoadConfig(FALSE);

	return TRUE;
}

void COutloadDlg::SaveLoadConfig(BOOL bToSave)
{
	CIniAX Set(_T("WorkConfig"));
	if (bToSave)
	{
		Set.SetFloat(_T("ShiftX"), GetDlgItemFloat(IDC_EDITX));
		Set.SetFloat(_T("ShiftY"), GetDlgItemFloat(IDC_EDITY));
		Set.SetFloat(_T("SpeedX"), GetDlgItemFloat(IDC_EDIT_SPEEDX));
		Set.SetFloat(_T("SpeedY"), GetDlgItemFloat(IDC_EDIT_SPEEDY));
		Set.SetFloat(_T("SpeedPos"), GetDlgItemFloat(IDC_EDIT_SPEEDPOS));
		Set.SetFloat(_T("Adjust"), GetDlgItemFloat(IDC_EDIT_ADJUST));
		Set.SetFloat(_T("TotalTime"), GetDlgItemFloat(IDC_EDIT_TPLUSTIME));
		Set.SetFloat(_T("OnTime"), GetDlgItemFloat(IDC_EDIT_PLUSDUR));
		Set.SetFloat(_T("PlusCount"), GetDlgItemFloat(IDC_EDIT_PLUSCOUNT));
	}
	else
	{
		SetDlgItemFloat(IDC_EDITX, Set.GetFloat(_T("ShiftX"), 50));
		SetDlgItemFloat(IDC_EDITY, Set.GetFloat(_T("ShiftY"), 50));
		SetDlgItemFloat(IDC_EDIT_SPEEDX, Set.GetFloat(_T("SpeedX"), 100));
		SetDlgItemFloat(IDC_EDIT_SPEEDY, Set.GetFloat(_T("SpeedY"), 100));
		SetDlgItemFloat(IDC_EDIT_SPEEDPOS, Set.GetFloat(_T("SpeedPos"), 100));
		SetDlgItemFloat(IDC_EDIT_ADJUST, Set.GetFloat(_T("Adjust"), 50));
		SetDlgItemFloat(IDC_EDIT_TPLUSTIME, Set.GetFloat(_T("TotalTime"), 5000));
		SetDlgItemFloat(IDC_EDIT_PLUSDUR, Set.GetFloat(_T("OnTime"), 2000));
		SetDlgItemFloat(IDC_EDIT_PLUSCOUNT, Set.GetFloat(_T("PlusCount"), 2));
	}
}

CString &COutloadDlg::MakeScript(int nIndex)
{
	static CString strScript;
	strScript.Empty();

	CLoader *pLoad = m_pLoader->GetData(nIndex);
	if (!pLoad)
		return strScript;
	pLoad->SetOffset(GetDlgItemFloat(IDC_EDITX), GetDlgItemFloat(IDC_EDITY));

	int nPosCount = pLoad->GetCount();
	double dbStart = pLoad->GetStart();
	int nType = pLoad->GetType();
	if (nPosCount == 0)
		return strScript;

	CString strFile;
	strFile.Format(_T("/positions-%d.rd"), nIndex);

	m_strFile = strFile;

	strScript.Format(_T(R"(
program

	var $count as integer = %d
	var $fileHandle as handle
	var $positions[%d] as real = %s

	$fileHandle = FileOpenBinary("%s", FileMode.Overwrite)

	FileBinaryWriteUInt32($fileHandle, %d)      // type
	FileBinaryWriteUInt32($fileHandle, $count)  // count
	FileBinaryWriteFloat64($fileHandle, %s)     // line
	FileBinaryWriteFloat64Array($fileHandle, $positions, $count)

	FileClose($fileHandle)

end )"), nPosCount, nPosCount, pLoad->ToArray(), strFile, nType, Double2String(dbStart));

	return strScript;
}

BOOL COutloadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_CHECK_RETURN:
	{
		CRichEditCtrl *pEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);

		if (IsDlgButtonChecked(IDC_CHECK_RETURN))
		{
			pEdit->ModifyStyle(0, WS_HSCROLL);
			pEdit->SetTargetDevice(nullptr, 0);
		}
		else
		{
			pEdit->ModifyStyle(WS_HSCROLL, 0);
			pEdit->SetTargetDevice(nullptr, 1);
		}
		pEdit->SetWindowPos(nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		pEdit->Invalidate(TRUE);
	}
		break;

	case IDC_BUTTON_OPEN:
	{
		CFileDialog  dlg(true, _T("txt"));
		if (dlg.DoModal() == IDOK)
		{
			m_pLoader->LoadFile(dlg.GetPathName());
			int nCount = m_pLoader->GetCount();
			CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
			pList->SetRedraw(FALSE);
			pList->SetCheckBoxCol(0);
			pList->DeleteAllItems();
			for (int i = 0; i < nCount; i++)
			{
				CLoader *pLoad = m_pLoader->GetData(i);
				int nPosCount = pLoad->GetCount();
				double dbStart = pLoad->GetStart();
				int nType = pLoad->GetType();
				pList->InsertItem(i, _T("0"));
				pList->SetItemInt(i, 0, i);

				pList->SetItemInt(i, 1, nType);
				pList->SetItemInt(i, 2, nPosCount);

				pList->SetCheck(i, TRUE);
			}

			pList->SetRedraw(TRUE);
		}
	}
		break;

	case CMD_LISTCTRL_COLCLK:
	{
		CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
		if (pList)
		{
			int nItem = pList->GetClickItem();
			SetDlgItemText(IDC_RICHEDIT21, MakeScript(nItem));
		}
		SaveLoadConfig(TRUE);
	}
	break;

	case IDC_EDITX:
	case IDC_EDITY:
		if (HIWORD(wParam) == EN_CHANGE)
		{
			SendCmdMsg(CMD_LISTCTRL_COLCLK);
		}
		break;
	
	case IDC_BUTTON_SEND:
	{
		CString strScript = GetLargeText((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT21));
		CString  strFile = GetCurrentPath() + _T("writefile.ascript");

		if (SaveTextAsUTF8(strScript, strFile))
		{
			CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
			int nItem = pList->GetClickItem();
			CString  strCall ;
			strCall.Format(strCallFile1, GetDlgItemFloat(IDC_EDIT_SPEEDX), GetDlgItemFloat(IDC_EDIT_SPEEDY), GetDlgItemFloat(IDC_EDIT_SPEEDPOS),
				GetDlgItemInt(IDC_EDIT_TPLUSTIME), GetDlgItemInt(IDC_EDIT_PLUSDUR), GetDlgItemInt(IDC_EDIT_PLUSCOUNT), nItem, nItem, GetDlgItemFloat(IDC_EDIT_ADJUST));
			strFile = GetCurrentPath() + _T("callOneFile.ascript");
			SaveTextAsUTF8(strCall, strFile);

			if (m_pMain->RunTask(_T("writefile.ascript")))
			{
				if (IsDlgButtonChecked(IDC_CHECK_AUTORUN) || IDYES == MessageBox(_T("成功写入 1 条（组）数据！\n需要立即运行(调用)吗?"), _T("提示"), MB_ICONINFORMATION | MB_YESNO))
				{
					Sleep(100);
					m_pMain->RunTask(_T("callOneFile.ascript"));
				}
			}
			else
			{
				MessageBox(_T("控制器未连接，写入失败！"), _T("提示"), MB_ICONERROR);
			}
		}
	}
	break;

	case IDC_BUTTON_SENDALL:
		if (m_bSendAll)
		{
			m_bSendAll = FALSE;
			break;
		}
		SimpleFire(0);
		break;

	case IDC_BUTTON_STOP:
		m_pMain->StopTask();
		break;

	case IDC_CHECK_PAUSE:
		m_pMain->PauseTask(IsDlgButtonChecked(IDC_CHECK_PAUSE));
		break;

	case IDC_BUTTON_RUNALL:
	{
		CIniAX Set(_T("WorkConfig"));
		int nCount = Set.GetInt(_T("WriteCount"), 0);
		if (nCount == 0)
		{
			MessageBox(_T("请首先写入全部数据！"), _T("提示"), MB_ICONERROR);
			break;
		}
			
		CString  strCall;
		strCall.Format(strCallFile1, GetDlgItemFloat(IDC_EDIT_SPEEDX), GetDlgItemFloat(IDC_EDIT_SPEEDY), GetDlgItemFloat(IDC_EDIT_SPEEDPOS),
			GetDlgItemInt(IDC_EDIT_TPLUSTIME), GetDlgItemInt(IDC_EDIT_PLUSDUR), GetDlgItemInt(IDC_EDIT_PLUSCOUNT), 0, nCount - 1, GetDlgItemFloat(IDC_EDIT_ADJUST));

		CString strFile = GetCurrentPath() + _T("callAllFiles.ascript");
		SaveTextAsUTF8(strCall, strFile);
		m_pMain->RunTask(_T("callAllFiles.ascript"));
		break;
	}
	default:
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}


int COutloadDlg::OnSimpleThreadLoopRun(int nID)
{
	switch (nID)
	{
	case 0:
		for (;;)
		{
			SimpleWait(0);
			{
				m_bSendAll = TRUE;
				CString strFile;
				CString strInfo;
				int nCount = m_pLoader->GetCount();
				CString strTmpFile = GetCurrentPath() + _T("All-postions.rd");
				CFile TmpFile(strTmpFile, CFile::modeCreate | CFile::modeWrite);
				for (int i = 0; i < nCount; i++)
				{
					if (!m_bSendAll)
						break;

					CLoader *pLoad = m_pLoader->GetData(i);
					pLoad->SetOffset(GetDlgItemFloat(IDC_EDITX), GetDlgItemFloat(IDC_EDITY));

					strInfo.Format(_T("正在写入: %d / %d"), i + 1, nCount);
					SetDlgItemText(IDC_STATIC_INFO, strInfo);

					int nLen = 0;
					BYTE *data = pLoad->ToBinary(nLen);
					TmpFile.Write(data, nLen);
				}
				TmpFile.Close();
				if (!m_bSendAll)
					continue;
				TmpFile.Open(strTmpFile, CFile::modeRead);
				int nLength = TmpFile.GetLength();
				BYTE *pBuffer = new BYTE[nLength];
				TmpFile.Read(pBuffer, nLength);
				TmpFile.Close();

				if (!m_pMain->WriteFile(_T("/all_positions.rd"), pBuffer, nLength))
				{
					MessageBox(_T("控制器未连接，写入失败！"), _T("提示"), MB_ICONERROR);
				}
				delete[]pBuffer;

				m_bSendAll = FALSE;

				{
					CString  strCall;
					strCall.Format(strCallFile1, GetDlgItemFloat(IDC_EDIT_SPEEDX), GetDlgItemFloat(IDC_EDIT_SPEEDY), GetDlgItemFloat(IDC_EDIT_SPEEDPOS),
						GetDlgItemInt(IDC_EDIT_TPLUSTIME), GetDlgItemInt(IDC_EDIT_PLUSDUR), GetDlgItemInt(IDC_EDIT_PLUSCOUNT), 0, nCount - 1, GetDlgItemFloat(IDC_EDIT_ADJUST));

					CString strFile = GetCurrentPath() + _T("callAllFiles.ascript");
					SaveTextAsUTF8(strCall, strFile);
					TmpFile.Open(strFile, CFile::modeRead);
					nLength = TmpFile.GetLength();
					BYTE *pBuffer = new BYTE[nLength];
					TmpFile.Read(pBuffer, nLength);
					TmpFile.Close();
					m_pMain->WriteFile(_T("/callAllFiles.ascript"), pBuffer, nLength);
					delete[]pBuffer;
				}

				CIniAX Set(_T("WorkConfig"));
				Set.SetInt(_T("WriteCount"), nCount);
				SetDlgItemText(IDC_STATIC_INFO, _T("写入完成"));
				strInfo.Format(_T("成功写入 %d 条（组）数据！"), nCount);
				if (IDYES == MessageBox(strInfo, _T("提示"), MB_ICONINFORMATION | MB_YESNO))
				{
					//SendCmdMsg(IDC_BUTTON_RUNALL); \n需要立即运行(调用)吗?
				}
				continue;
			}
		}
		break;
	default:
		break;
	}
	return 0;
}


void COutloadDlg::OnBnClickedButtonRunall()
{
	// TODO: Add your control notification handler code here
}
