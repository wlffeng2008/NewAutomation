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
    // Axis definitions
    var $X_axis as axis = X1
    var $Y_axis as axis = Y1
	var $isXHomed as real                                      // X1轴回零
	var $isYHomed as real                                      // //X1轴回零
	$isXHomed = (StatusGetAxisItem($X_axis, AxisStatusItem.AxisStatus, AxisStatus.Homed) == AxisStatus.Homed)
	$isYHomed = (StatusGetAxisItem($Y_axis, AxisStatusItem.AxisStatus, AxisStatus.Homed) == AxisStatus.Homed)
	
    
    // X-axis PSO variables
    var $posStart as real = 0.000
    var $posEnd as real = 520.000
    
	//...........................................
    var $Y_speed as real = 100
    var $y_index as integer
	
    // .........................................................................................................................................
    Enable([$X_axis, $Y_axis])
	if StatusGetAxisItem($Y_axis,AxisStatusItem.AxisStatus,AxisStatus.Homed) != $isYHomed       // 检查Y1轴状态是否回零
	Home($Y_axis)
	end
	if StatusGetAxisItem($X_axis,AxisStatusItem.AxisStatus,AxisStatus.Homed) != $isXHomed       // // 检查X1轴状态是否回零
	Home($X_axis)
	end
	// .........................................................................................................................................
    SetupTaskTargetMode(TargetMode.Absolute)
	
	var $type as integer
	var $count as integer
	var $index as integer
	var $start as real
	var $offset as real = 260 
	var $fileHandle as handle
	var $R_positions[5000] as real // will read from file
    var $distances[5000] as real
	
	var $fileName as string = "%--filename--%"
	
	$fileHandle = FileOpenBinary($fileName, FileMode.Read)
	
	$type = FileBinaryReadUInt32($fileHandle)  // type
	$count = FileBinaryReadUInt32($fileHandle) // count
	$start = FileBinaryReadFloat64($fileHandle)// start
	FileBinaryReadFloat64Array($fileHandle, $R_positions, $count)
	FileBinaryReadFloat64Array($fileHandle, $R_positions, 20)
	
	FileClose($fileHandle)
	
	MoveAbsolute($Y_axis, $start, $Y_speed)
    WaitForMotionDone($Y_axis)
        
    // Wait a moment for Y-axis to settle 请稍等片刻，待Y轴稳定
     Dwell(0.100)
	
	MoveAbsolute($X_axis, $R_positions[0] + $offset  -2, 100)
    WaitForMotionDone($X_axis)
        
    // Configure PSO 配置 PSO
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
        	$distances[$index] = UnitsToCounts($X_axis, $R_positions[$index] + $offset) / ParameterGetAxisValue($X_axis, AxisParameter.PrimaryEmulatedQuadratureDivider)
		end
    CriticalSectionEnd()
		
        DriveArrayWrite($X_axis, $distances, 0, $count, DriveArrayType.PsoDistanceEventDistances)
        PsoDistanceConfigureArrayDistances($X_axis, 0, $count, false)
        
        // Configure PSO waveform 配置PSO波形
        PsoWaveformConfigureMode($X_axis, PsoWaveformMode.Pulse)
        PsoWaveformConfigurePulseFixedTotalTime($X_axis, 5000)
        PsoWaveformConfigurePulseFixedOnTime($X_axis, 2000)
        PsoWaveformConfigurePulseFixedCount($X_axis, 2)
        PsoWaveformApplyPulseConfiguration($X_axis)
        
        // Enable PSO functions 启用PSO功能
        PsoDistanceCounterOn($X_axis)
        PsoDistanceEventsOn($X_axis)
        PsoWaveformOn($X_axis)
        
        // Configure PSO output 配置PSO输出
        PsoOutputConfigureSource($X_axis, PsoOutputSource.Waveform)
        PsoOutputConfigureOutput($X_axis, PsoOutputPin.iXC4eDedicatedOutput)
        
		if $type == 0
        // Perform X-axis scan with PSO 执行基于粒子群优化算法的X轴扫描
        MoveLinear($X_axis, $R_positions[$count-1], 100)
        WaitForMotionDone($X_axis)
		end
		
		if $type == 1
		    // Perform X-axis scan with PSO
        	MoveLinear($Y_axis, $R_positions[$count-1], 100)
        	WaitForMotionDone($Y_axis)
		end
        
        // Disable PSO functions 禁用PSO功能
        PsoWaveformOff($X_axis)
        PsoDistanceCounterOff($X_axis)
        PsoDistanceEventsOff($X_axis)
	
end

)");


// COutloadDlg message handlers
BOOL COutloadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
	pList->InsertColumn(0, _T("编号"), 0, 60);
	pList->InsertColumn(1, _T("类型"), 0, 60);
	pList->InsertColumn(2, _T("位置数量"), 0, 80);

	SetDlgItemFont(IDC_RICHEDIT21, 12, 400, _T("Fixedsys"));

	SetDlgItemFloat(IDC_EDITX, 0);
	SetDlgItemFloat(IDC_EDITY, 0);

	m_pLoader = new COutsideLoad();

	StartThread(0);
	StartThread(1);

	return TRUE;
}

CString &COutloadDlg::MakeScript(int nIndex)
{
	static CString strScript;

	CLoader *pLoad = m_pLoader->GetData(nIndex);
	pLoad->SetOffset(GetDlgItemFloat(IDC_EDITX), GetDlgItemFloat(IDC_EDITY));

	int nPosCount = pLoad->GetCount();
	double dbStart = pLoad->GetStart();
	int nType = pLoad->GetType();

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
		int nItem = pList->GetClickItem();
		SetDlgItemText(IDC_RICHEDIT21, MakeScript(nItem));
	}
	break;

	case IDC_BUTTON_SEND:
	{
		CString strScript = GetLargeText((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT21));
		CString  strFile = GetCurrentPath() + _T("writefile.ascript");

		if (SaveTextAsUTF8(strScript, strFile))
		{
			if (m_pMain->RunTask(_T("writefile.ascript")))
			{
				if (IDYES == MessageBox(_T("成功写入 1 条（组）数据！\n需要立即运行(调用)吗?"), _T("提示"), MB_ICONINFORMATION | MB_YESNO))
				{
					CString  strCall = strCallFile;
					strCall.Replace(_T("%--filename--%"), m_strFile);
					SaveTextAsUTF8(strCall, _T("callfile.ascript"));
					m_pMain->RunTask(_T("callfile.ascript"));
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

				SetDlgItemText(IDC_RICHEDIT21, strScript);
				if (SaveTextAsUTF8(strScript, strFile))
				{
					if(!m_pMain->RunTask(_T("writefile.ascript")))
						break;
					nWrite++;
				}
				Sleep(200);
				stInfo.Format(_T("正在写入: %d / %d"), i+1, nCount);
				SetDlgItemText(IDC_STATIC_INFO,stInfo);
			}
			m_bSendAll = FALSE;
			SetDlgItemText(IDC_BUTTON_SENDALL, _T("全部写入"));

			if (nWrite != nCount)
			{
				MessageBox(_T("控制器未连接，写入失败！"), _T("提示"), MB_ICONERROR);
			}
			else
			{
				stInfo.Format(_T("成功写入 %d 条（组）数据！"), nWrite);
				MessageBox(stInfo, _T("提示"), MB_ICONINFORMATION);
			}
		}
		break;
	default:
		break;
	}
	return 0;
}
