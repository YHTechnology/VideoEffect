#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEffectBar 对话框

class CEffectBar : public CDialog
{
	DECLARE_DYNAMIC(CEffectBar)

public:
	CEffectBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEffectBar();

// 对话框数据
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlEffects;
	CSliderCtrl m_ctrlProgress;
	afx_msg void OnBnClickedParameters();
	virtual BOOL OnInitDialog();
};
