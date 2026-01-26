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
/*

int nLoadCount = GetDlgItemInt(IDC_COMBO_OUTSIZE);
int nLoadStart = GetDlgItemInt(IDC_COMBO_START);

for (int i = 0; i < nLoadCount; i++)
{
int nToLoad = i + nLoadStart;
CLoader *pLoad = m_pLoader->GetData(nToLoad);
int nPosCount = pLoad->GetCount();
double dbStart = pLoad->GetStart();
int nType = pLoad->GetType();

CString strFile;
strFile.Format(_T("/postions-%d.rd"), nToLoad);
CString strScript;
strScript.Format(_T(R"(
program

var $fileHandle as handle
var $positions[%d] as real = %s

$fileHandle = FileOpenBinary("%s", FileMode.Overwrite)

FileBinaryWriteUInt32($fileHandle, %d) // type
FileBinaryWriteUInt32($fileHandle, %d) // count
FileBinaryWriteFloat64($fileHandle, %f)// start
FileBinaryWriteFloat64Array($fileHandle, $positions, %d)

FileClose($fileHandle)

end )"), nPosCount, pLoad->ToArray(), strFile, nType, nPosCount, dbStart, nPosCount);

strFile = GetCurrentPath() + _T("writefile.ascript");
if (SaveTextAsUTF8(strScript, strFile))
{
m_pMain->SendCmdMsg(9982);
}
Sleep(500);
}
*/

CString &COutloadDlg::MakeScript(int nIndex)
{
	static CString strScript;

	CLoader *pLoad = m_pLoader->GetData(nIndex);
	pLoad->SetOffset(GetDlgItemFloat(IDC_EDITX), GetDlgItemFloat(IDC_EDITY));

	int nPosCount = pLoad->GetCount();
	double dbStart = pLoad->GetStart();
	int nType = pLoad->GetType();

	CString strFile;
	strFile.Format(_T("/postions-%d.rd"), nIndex);

	strScript.Format(_T(R"(
program

	var $count as integer = %d
	var $fileHandle as handle
	var $positions[$count] as real = %s

	$fileHandle = FileOpenBinary("%s", FileMode.Overwrite)

	FileBinaryWriteUInt32($fileHandle, %d)      // type
	FileBinaryWriteUInt32($fileHandle, $count)  // count
	FileBinaryWriteFloat64($fileHandle, %s)     // start
	FileBinaryWriteFloat64Array($fileHandle, $positions, $count)

	FileClose($fileHandle)

end )"), nPosCount, pLoad->ToArray(), strFile, nType, Double2String(dbStart));

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
			m_pMain->SendCmdMsg(9982);

			CString stInfo;
			stInfo.Format(_T("成功写入 %d 条（组）数据！"), 1);
			MessageBox(_T("提示"), stInfo, MB_ICONINFORMATION);
		}
	}
	break;

	case IDC_BUTTON_SENDALL:
	{
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
			CMyListCtrl *pList = GetMyListCtrl(IDC_LIST1);
			int nCount = pList->GetItemCount();

			int i = 0;
			CString stInfo;
			CString  strFile = GetCurrentPath() + _T("writefile.ascript");
			for (i = 0; i < nCount; i++)
			{
				CString strScript = MakeScript(i);
				if (SaveTextAsUTF8(strScript, strFile))
				{
					m_pMain->SendCmdMsg(9982);
				}
				Sleep(200);
				stInfo.Format(_T("正在写入: %d / %d"), i+1, nCount);
				SetDlgItemText(IDC_STATIC_INFO,stInfo);
			}

			stInfo.Format(_T("成功写入 %d 条（组）数据！"),i+1);
			MessageBox(_T("提示"), stInfo, MB_ICONINFORMATION);
		}
		break;
	default:
		break;
	}
	return 0;
}
