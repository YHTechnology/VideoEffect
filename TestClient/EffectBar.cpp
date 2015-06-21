// EffectBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "EffectBar.h"


// CEffectBar �Ի���

IMPLEMENT_DYNAMIC(CEffectBar, CDialog)

CEffectBar::CEffectBar(CWnd* pParent /*=NULL*/)
	: CDialog(CEffectBar::IDD, pParent)
{

}

CEffectBar::~CEffectBar()
{
}

void CEffectBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EFFECTS, m_ctrlEffects);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}


BEGIN_MESSAGE_MAP(CEffectBar, CDialog)
	ON_BN_CLICKED(IDC_PARAMETERS, &CEffectBar::OnBnClickedParameters)
END_MESSAGE_MAP()


// CEffectBar ��Ϣ�������

void CEffectBar::OnBnClickedParameters()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

BOOL CEffectBar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrlEffects.AddString("Negative");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
