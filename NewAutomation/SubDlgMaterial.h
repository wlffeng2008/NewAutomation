#pragma once


// CSubDlgMaterial dialog

class CSubDlgMaterial : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgMaterial)

public:
	CSubDlgMaterial(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgMaterial();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MATERIAL };
#endif

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
