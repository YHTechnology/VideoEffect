
// TestClientDoc.h : CTestClientDoc ��Ľӿ�
//


#pragma once


class CTestClientDoc : public CDocument
{
protected: // �������л�����
	CTestClientDoc();
	DECLARE_DYNCREATE(CTestClientDoc)

// ����
public:

// ����
public:

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

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


