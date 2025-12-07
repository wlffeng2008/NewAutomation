#pragma once


// CSubDlgProduct dialog

class CSubDlgProduct : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgProduct)

public:
	CSubDlgProduct(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgProduct();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRODUCT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
