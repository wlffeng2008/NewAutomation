#include "stdafx.h"
#include "OutsideLoad.h"

CString GetLargeText(CRichEditCtrl* richEdit)
{
	static CString strAllText;
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

BOOL SaveTextAsUTF8(const CString&strText, const CString&strFile)
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




static CString s_strPath;

inline double strToDouble(LPCTSTR lpValue) {

	CString strValue(lpValue);
	strValue.Trim();
	int nFind = strValue.Find(_T("="));
	strValue = strValue.Mid(nFind + 1);
	strValue.Trim();
	return atof(CW2A(strValue));
}

inline CString& doubleToStr(double value)
{
	static  CString strVal;
	strVal.Format(_T("%f"), value);
	strVal.TrimRight('0');
	strVal.TrimRight('.');
	return strVal;
}


CLoader::CLoader(int nIndex, int nType, double dbStart)
{
	CString strFile;
	strFile.Format(_T("%s\\%s%d.rd"), s_strPath, nType == 0 ?_T("x"):_T("y"), nIndex);
	m_nIndex = nIndex;
	m_nType = nType;
	m_dbStart = dbStart;
	m_nCount = 0;

	CFile LFile;
	if (LFile.Open(strFile, CFile::modeRead))
	{
		uint32 nLen = LFile.GetLength();
		ASSERT(nLen % 8 == 0);
		m_nCount = nLen / 8;
		m_buf = new double[nLen];
		LFile.Read(m_buf, nLen);
		LFile.Close();

		TRACE(_T("Load: %s,%.4f,%.4f,%.4f\n"), strFile, m_buf[0],m_buf[10], m_buf[12]);
	}
}

double CLoader::GetData(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_nCount)
		return m_buf[nIndex];
	return 0;
}

CString & CLoader::ToArray()
{
	static CString strArray;
	strArray = _T("[");
	CString strVal;

	for (int i = 0; i < m_nCount; i++)
	{
		double value = m_buf[i];
		if(m_nIndex % 2) value = m_buf[m_nCount-1-i];
		value += (m_nType == 0 ? m_offsetY: m_offsetX);

		strVal = doubleToStr(value);
		strArray.Append(strVal);
		if(i < m_nCount -1)
			strArray.Append(_T(","));
	}
	strArray.Append(_T("]"));
	return strArray;
}

void  CLoader::SetOffset(double x, double y)
{
	m_offsetX = x;
	m_offsetY = y;
}

double CLoader::GetStart() { return m_dbStart + (m_nType == 0 ? m_offsetY : m_offsetX); }

int CLoader::GetCount() { return m_nCount; }

int CLoader::GetType() { return m_nType; }

CLoader::~CLoader()
{
	delete []m_buf;
}


/////////////////////////////////////////////////////

COutsideLoad::COutsideLoad(LPCTSTR lpFile)
{
	LoadFile(lpFile);
}

COutsideLoad::~COutsideLoad()
{
	Reset();
}

void COutsideLoad::Reset()
{
	for (int i = 0; i < m_data.GetCount(); i++)
	{
		delete m_data[i];
	}
	m_data.RemoveAll();
	
	m_nCount = 0;
}

void COutsideLoad::Reload()
{
	LoadFile(m_strFile);
}

int COutsideLoad::GetCount()
{
	return m_nCount;
}

CLoader* COutsideLoad::GetData(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_nCount)
		return m_data[nIndex];
	return nullptr;
}

void COutsideLoad::LoadFile(LPCTSTR lpFile)
{
	Reset();

	CStdioFile  DFile;
	if (lpFile && DFile.Open(lpFile,CFile::modeRead))
	{
		m_nCount = 0;
		m_strFile = lpFile;
		s_strPath = lpFile;
		s_strPath = s_strPath.Left(s_strPath.ReverseFind(_T('\\')));

		CString strLine;
		while (DFile.ReadString(strLine))
		{
			strLine.Trim();
			if (strLine.Find(_T("Xstripesnumber")) >= 0)
			{
				int nCount = strToDouble(strLine);
				m_nCount += nCount;
				for (int i = 0; i < nCount; i++)
				{
					DFile.ReadString(strLine);
					double dbStart = strToDouble(strLine);
					m_data.Add(new CLoader(i, 0, dbStart));
				}
			}

			if (strLine.Find(_T("Ystripesnumber")) >= 0)
			{
				int nCount = strToDouble(strLine);
				m_nCount += nCount;
				for (int i = 0; i < nCount; i++)
				{
					DFile.ReadString(strLine);
					double dbStart = strToDouble(strLine);
					m_data.Add(new CLoader(i, 1, dbStart));
				}
			}
		}

		DFile.Close();
	}
}