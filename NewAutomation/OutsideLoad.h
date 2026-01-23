#pragma once


class CLoader
{
public:
	CLoader(int nIndex,int nType, double dbStart);
	~CLoader();

	double GetData(int nIndex);
	double GetStart();
	int GetCount();
	int GetType();
	CString & ToArray();
private:
	double *m_buf=nullptr;
	int m_nType=0;  // X Y
	int m_nIndex=0; // 0 1 2 3 ........
	double m_dbStart=0;
	int m_nCount=0;
};

class COutsideLoad
{
public:
	COutsideLoad(LPCTSTR lpFile=nullptr);
	~COutsideLoad();
	void LoadFile(LPCTSTR lpFile);
	void Reload();

	CLoader* GetData(int nIndex);
	int GetCount();


private:
	void Reset();
	CString m_strFile;
	int m_nCount=0;
	CArray<CLoader*,CLoader*>m_data;

};