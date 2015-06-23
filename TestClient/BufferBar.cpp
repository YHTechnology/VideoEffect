// BufferBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "BufferBar.h"
#include "CommonMessage.h"


// CBufferBar �Ի���

IMPLEMENT_DYNAMIC(CBufferBar, CDialog)

CBufferBar::CBufferBar(CWnd* pParent /*=NULL*/)
	: CDialog(CBufferBar::IDD, pParent)
	, m_strFirstLevelFileName(_T(""))
	, m_strSecondLevelFileName(_T(""))
	, m_uWidth(1920)
	, m_uHeight(1080)
{

}

CBufferBar::~CBufferBar()
{
}

void CBufferBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IMAGE1, m_strFirstLevelFileName);
	DDX_Text(pDX, IDC_IMAGE2, m_strSecondLevelFileName);
	DDX_Text(pDX, IDC_WIDTH, m_uWidth);
	DDX_Text(pDX, IDC_HEIGHT, m_uHeight);
}


BEGIN_MESSAGE_MAP(CBufferBar, CDialog)
	ON_BN_CLICKED(IDC_SELECT_IMAGE1, &CBufferBar::OnBnClickedSelectImage1)
	ON_BN_CLICKED(IDC_SELECT_IMAGE2, &CBufferBar::OnBnClickedSelectImage2)
END_MESSAGE_MAP()


// CBufferBar ��Ϣ�������

void CBufferBar::OnBnClickedSelectImage1()
{
	m_strFirstLevelFileName = GetFilePath();
	UpdateData(FALSE);
	AfxGetMainWnd()->PostMessage(UM_SET_IMAGE, 0, (LPARAM)(LPCTSTR)m_strFirstLevelFileName);
	//TODO: UM_SET_IMAGE
	//UM_SET_IMAGE��ͼ����Ϣ֪ͨ��Document�࣬Ȼ���ٰ�ͼ����ȡ��Buffer���ݸ�VideoEffect
	//�ٴ�VideoEffectȡ��Buffer����ʾ��View��
}

void CBufferBar::OnBnClickedSelectImage2()
{
	m_strSecondLevelFileName = GetFilePath();
	UpdateData(FALSE);
	AfxGetMainWnd()->PostMessage(UM_SET_IMAGE, 1, (LPARAM)(LPCTSTR)m_strSecondLevelFileName);
	//�����ؼ���Ҫ2��ͼ��
}

LPCTSTR CBufferBar::GetFilePath()
{
	static CString strPath=_T("");
	CFileDialog Dlg(TRUE,_T("*.bmp"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("ͼ��Files(*.bmp *.tga *.png *.tif *.jpg *.jpeg *.gif)|*.bmp;*.tga;*.png;*.tif;*.jpg;*.jpeg;*gif;||"),NULL);
	Dlg.m_ofn.lpstrInitialDir=strPath;
	if(Dlg.DoModal()==IDOK)
	{
		strPath=Dlg.GetPathName();
	}
	return strPath;
}

