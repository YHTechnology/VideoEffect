// EffectSettingsPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "EffectSettingsPane.h"


// CEffectSettingsPane

IMPLEMENT_DYNAMIC(CEffectSettingsPane, CDockablePane)

CEffectSettingsPane::CEffectSettingsPane()
{

}

CEffectSettingsPane::~CEffectSettingsPane()
{
}


BEGIN_MESSAGE_MAP(CEffectSettingsPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CEffectSettingsPane ��Ϣ�������



int CEffectSettingsPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_wndEffectBar.Create(IDD_DIALOGBAR, this);
	CRect rc;
	m_wndEffectBar.GetClientRect(rc);
	SetMinSize(CSize(rc.Width(), rc.Height()));
	m_wndEffectBar.ShowWindow(SW_SHOW);

	return 0;
}

void CEffectSettingsPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(rc);
	m_wndEffectBar.MoveWindow(rc);
}
