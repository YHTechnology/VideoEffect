// BufferSettingsPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "BufferSettingsPane.h"


// CBufferSettingsPane

IMPLEMENT_DYNAMIC(CBufferSettingsPane, CDockablePane)

CBufferSettingsPane::CBufferSettingsPane()
{

}

CBufferSettingsPane::~CBufferSettingsPane()
{
}


BEGIN_MESSAGE_MAP(CBufferSettingsPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CBufferSettingsPane ��Ϣ�������



int CBufferSettingsPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_wndBar.Create(IDD_DIALOGBAR_IMAGE, this);
	CRect rc;
	m_wndBar.GetClientRect(rc);
	SetMinSize(CSize(rc.Width(), rc.Height()));
	m_wndBar.ShowWindow(SW_SHOW);

	return 0;
}

void CBufferSettingsPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(rc);
	m_wndBar.MoveWindow(rc);
}
