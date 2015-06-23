
// TestClientDoc.h : CTestClientDoc ��Ľӿ�
//
#include <vector>
#include "../VideoBuffer.h"

#pragma once


class CTestClientDoc : public CDocument
{
protected: // �������л�����
	CTestClientDoc();
	DECLARE_DYNCREATE(CTestClientDoc)

// ����
public:
	void SetImage(UINT level, LPCTSTR pszFilename);

// ����
public:
	bool InitEffect();
	void UninitEffect();
	bool UpdateBuffer(UINT level);
	bool UpdateBuffer(UINT level, const BYTE* pBits, int w, int h, int pitch);

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CTestClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<CString> m_ImageFiles;
	std::vector<IVideoBuffer*> m_SrcImages;
	IVideoBuffer* m_pDestImage;

	IVideoBufferManager* m_pBufferMgr;

	IEffect* m_pEffect;
	ITransEffect* m_pTransEffect;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


