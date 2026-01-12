#include "stdafx.h"
#include "OutsideLoad.h"

static CString s_strPath;

static inline double strToDouble(LPCTSTR lpValue) {

	CString strValue(lpValue);
	strValue.Trim();
	int nFind = strValue.Find(_T("="));
	strValue = strValue.Mid(nFind + 1);
	strValue.Trim();
	return atof(CW2A(strValue));
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

double CLoader::GetStart() { return m_dbStart; }

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