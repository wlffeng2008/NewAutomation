#pragma once


// CubDlgConfig dialog

class CSubDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgConfig)

public:
	CSubDlgConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgConfig();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIG };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
