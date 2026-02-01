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
END_MESSAGE_MAP()


static CString  strCallFile(R"(
program
    var $X_axis as axis = X1
    var $Y_axis as axis = Y1

    var $Y_speed as real = %.2f
    var $X_speed as real = %.2f
	var $TotalTime as integer = %d
	var $OnTime as integer = %d
	var $FixedCount as integer = %d
	var $fileBegin as integer = %d
	var $fileEnd as integer = %d

	var $isXHomed as real
	var $isYHomed as real
	$isXHomed = (StatusGetAxisItem($X_axis, AxisStatusItem.AxisStatus, AxisStatus.Homed) == AxisStatus.Homed)
	$isYHomed = (StatusGetAxisItem($Y_axis, AxisStatusItem.AxisStatus, AxisStatus.Homed) == AxisStatus.Homed)
    Enable([$X_axis, $Y_axis])
	if StatusGetAxisItem($Y_axis,AxisStatusItem.AxisStatus,AxisStatus.Homed) != $isYHomed
		Home($Y_axis)
	end
	if StatusGetAxisItem($X_axis,AxisStatusItem.AxisStatus,AxisStatus.Homed) != $isXHomed
		Home($X_axis)
	end
	
    SetupTaskTargetMode(TargetMode.Absolute)
	
	var $type as integer
	var $count as integer
	var $index as integer
	var $line as real
	var $fileHandle as handle
	var $R_positions[10000] as real // will read from file
    var $distances[10000] as real
    var $file as integer
	
	for $file = $fileBegin to $fileEnd
		var $fileName as string = "/positions-" + IntegerToString($file) + ".rd"	
		$fileHandle = FileOpenBinary($fileName, FileMode.Read)
	
		$type = FileBinaryReadUInt32($fileHandle)  // type
		$count = FileBinaryReadUInt32($fileHandle) // count
		$line = FileBinaryReadFloat64($fileHandle)// start
		FileBinaryReadFloat64Array($fileHandle, $R_positions, $count)
	
		FileClose($fileHandle)
	
		//$type = 1 
		//$line = 100
		//$count = 20
		//for $index = 0 to $count-1
		//	$R_positions[$index]= $index *10
		//end
		var $adjust as real = 2
		if $R_positions[0] > $R_positions[1]
			$adjust *= -1
		end
		var $posStart as real = $R_positions[0] - $adjust
		var $posEnd as real = $R_positions[$count-1]  + $adjust
	
		if $type == 0	
			MoveAbsolute($Y_axis, $line, $Y_speed)
			WaitForMotionDone($Y_axis)
			Dwell(0.100)
		
			MoveAbsolute($X_axis, $posStart, $X_speed)
			WaitForMotionDone($X_axis)	
			Dwell(0.100)
		end 
	
		if $type == 1	
			MoveAbsolute($X_axis, $line, $X_speed)
			WaitForMotionDone($X_axis)
			Dwell(0.100)
		
			MoveAbsolute($Y_axis, $posStart, $Y_speed)
			WaitForMotionDone($Y_axis)	
			Dwell(0.100)
		end 
        
		PsoReset($X_axis)
	
		if $type == 0
			PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4ePrimaryFeedback])
		end
	
		if $type == 1
			DriveEncoderOutputConfigureInput($Y_axis, EncoderOutputChannel.SyncPortB, EncoderInputChannel.PrimaryEncoder)
			DriveEncoderOutputConfigureDivider($Y_axis, EncoderOutputChannel.SyncPortB, 1)   // 1: DIGITAL ENCODER 2: ANALOG ENCODER
			DriveEncoderOutputOn($Y_axis, EncoderOutputChannel.SyncPortB)
			PsoDistanceConfigureInputs($X_axis, [PsoDistanceInput.iXC4eSyncPortA]) 
		end
		
		CriticalSectionStart()
			for $index =0 to $count - 1
        		$distances[$index] = UnitsToCounts($X_axis, $R_positions[$index]) / ParameterGetAxisValue($X_axis, AxisParameter.PrimaryEmulatedQuadratureDivider)
			end
		CriticalSectionEnd()
		
		DriveArrayWrite($X_axis, $distances, 0, $count, DriveArrayType.PsoDistanceEventDistances)
		PsoDistanceConfigureArrayDistances($X_axis, 0, $count, false)
		AppMessageDisplay("PSO距离位置驱动写入完成")
    
		// Configure PSO waveform 配置PSO波形
		PsoWaveformConfigureMode($X_axis, PsoWaveformMode.Pulse)
		PsoWaveformConfigurePulseFixedTotalTime($X_axis, $TotalTime)
		PsoWaveformConfigurePulseFixedOnTime($X_axis, $OnTime)
		PsoWaveformConfigurePulseFixedCount($X_axis, $FixedCount)
		PsoWaveformApplyPulseConfiguration($X_axis)
    
		// Enable PSO functions 启用PSO功能
		PsoDistanceCounterOn($X_axis)
		PsoDistanceEventsOn($X_axis)
		PsoWaveformOn($X_axis)
    
		// Configure PSO output 配置PSO输出
		PsoOutputConfigureSource($X_axis, PsoOutputSource.Waveform)
		PsoOutputConfigureOutput($X_axis, PsoOutputPin.iXC4eDedicatedOutput)
    
		if $type == 0
			AppMessageDisplay("将X轴移动至目标位置")
			MoveLinear($X_axis, $posEnd, $X_speed)
			WaitForMotionDone($X_axis)
		end
	
		if $type == 1
			// Perform X-axis scan with PSO
			AppMessageDisplay("将X轴移动至目标位置")
    		MoveLinear($Y_axis, $posEnd, $Y_speed)
    		WaitForMotionDone($Y_axis)
		end
    
		// Disable PSO functions 禁用PSO功能
		PsoWaveformOff($X_axis)
		PsoDistanceCounterOff($X_axis)
		PsoDistanceEventsOff($X_axis)
	end

	//Home($X_axis)
	//Home($Y_axis)
	
end
)");


BOOL COutloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
	pList->InsertColumn(0, _T("编号"), 0, 60);
	pList->InsertColumn(1, _T("类型"), 0, 60);
	pList->InsertColumn(2, _T("位置数量"), 0, 80);

	SetDlgItemFont(IDC_RICHEDIT21, 12, 400, _T("Fixedsys"));

	SetDlgItemFloat(IDC_EDITX, 250);
	SetDlgItemFloat(IDC_EDITY, 250);
	SetDlgItemFloat(IDC_EDIT_SPEEDX, 100);
	SetDlgItemFloat(IDC_EDIT_SPEEDY, 100);
	SetDlgItemFloat(IDC_EDIT_TPLUSTIME, 5000);
	SetDlgItemFloat(IDC_EDIT_PLUSDUR, 2000);
	SetDlgItemFloat(IDC_EDIT_PLUSCOUNT, 2);
	CheckDlgButton(IDC_CHECK_AUTORUN, 1);

	m_pLoader = new COutsideLoad();

	StartThread(0);
	StartThread(1);

	return TRUE;
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
	FileBinaryWriteFloat64($fileHandle, %s)     // start
	FileBinaryWriteFloat64Array($fileHandle, $positions, $count)

	FileClose($fileHandle)

end )"), nPosCount, nPosCount, pLoad->ToArray(), strFile, nType, Double2String(dbStart));

	return strScript;
}

BOOL COutloadDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
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
				pList->InsertItem(i + 1, _T("0"));
				pList->SetItemInt(i, 0, i + 1);

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
			CString  strCall = strCallFile;
			strCall.Format(strCallFile, GetDlgItemFloat(IDC_EDIT_SPEEDX), GetDlgItemFloat(IDC_EDIT_SPEEDY),
				GetDlgItemInt(IDC_EDIT_TPLUSTIME), GetDlgItemInt(IDC_EDIT_PLUSDUR), GetDlgItemInt(IDC_EDIT_PLUSCOUNT), nItem, nItem
			);

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
	{
		if (m_bSendAll)
		{
			m_bSendAll = FALSE;
			break;
		}
		SimpleFire(0);
		break;
	}

	case IDC_BUTTON_RUNALL:
	{
		CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
		int nCount = pList->GetItemCount();
		CString  strCall = strCallFile;
		strCall.Format(strCallFile, GetDlgItemFloat(IDC_EDIT_SPEEDX), GetDlgItemFloat(IDC_EDIT_SPEEDY),
			GetDlgItemInt(IDC_EDIT_TPLUSTIME), GetDlgItemInt(IDC_EDIT_PLUSDUR), GetDlgItemInt(IDC_EDIT_PLUSCOUNT), 0, nCount - 1
		);

		CString strFile = GetCurrentPath() + _T("callAllFile.ascript");
		SaveTextAsUTF8(strCall, strFile);
		m_pMain->RunTask(_T("callAllFile.ascript"));
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
			m_bSendAll = TRUE;
			SetDlgItemText(IDC_BUTTON_SENDALL, _T("中断写入"));
			CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
			int nCount = pList->GetItemCount();

			int nWrite = 0;
			CString stInfo;
			CString  strFile = GetCurrentPath() + _T("writefile.ascript");
			for (int i = 0; i < nCount; i++)
			{
				if(!m_bSendAll)
					break;
				CString strScript = MakeScript(i);
				if(strScript.IsEmpty())
					continue;

				SetDlgItemText(IDC_RICHEDIT21, strScript);
				if (SaveTextAsUTF8(strScript, strFile))
				{
					if(!m_pMain->RunTask(_T("writefile.ascript")))
						break;
					nWrite++;
				}
				Sleep(20);
				stInfo.Format(_T("正在写入: %d / %d"), i+1, nCount);
				SetDlgItemText(IDC_STATIC_INFO,stInfo);
			}

			if(m_bSendAll) SetDlgItemText(IDC_STATIC_INFO, _T("写入被取消"));

			m_bSendAll = FALSE;
			SetDlgItemText(IDC_BUTTON_SENDALL, _T("全部写入"));


			if (nWrite != nCount)
			{
				MessageBox(_T("控制器未连接，写入失败！"), _T("提示"), MB_ICONERROR);
			}
			else
			{
				SetDlgItemText(IDC_STATIC_INFO, _T("写入完成"));
				stInfo.Format(_T("成功写入 %d 条（组）数据！\n需要立即运行(调用)吗?"), nWrite);
				if (IDYES == MessageBox(stInfo, _T("提示"), MB_ICONINFORMATION | MB_YESNO))
				{
					SendCmdMsg(IDC_BUTTON_RUNALL);
				};
			}
		}
		break;
	default:
		break;
	}
	return 0;
}
