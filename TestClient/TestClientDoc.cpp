
// TestClientDoc.cpp : CTestClientDoc ���ʵ��
//

#include "stdafx.h"
#include "TestClient.h"

#include "TestClientDoc.h"
//#include "CommonMessage.h"
#include "../FreeImage/FreeImage.h"
#include <d3dx9.h>
#include "../D3D9Render/VideoBuffer.h"
#include "../D3D9Render/VideoBufferManager.h"
#include "../EffNegative/NegativeRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestClientDoc

IMPLEMENT_DYNCREATE(CTestClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestClientDoc, CDocument)
END_MESSAGE_MAP()


// CTestClientDoc ����/����

CTestClientDoc::CTestClientDoc()
: m_pRenderEngine(NULL)
//, m_pResourceManager(NULL)
, m_pBufferMgr(NULL)
, m_pDestImage(NULL)
{
	memset(&m_DestVideoBufferInfo, 0, sizeof(VideoBufferInfo));
	m_DestVideoBufferInfo.eType = VBT_D3D9_MEM;
	m_DestVideoBufferInfo.format = D3DFMT_A8B8G8R8;
	m_DestVideoBufferInfo.nWidth = 1920;
	m_DestVideoBufferInfo.nHeight = 1080;
}

CTestClientDoc::~CTestClientDoc()
{
}

BOOL CTestClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	BOOL bOK = FALSE;
	//AfxGetMainWnd()->
	POSITION pos = GetFirstViewPosition();
	if(pos)
	{
		CView* pView = GetNextView(pos);
		if(pView)
		{
			HWND hWnd = (pView->GetSafeHwnd());
			if(hWnd)
			{
				bOK = InitEffect(hWnd, 1920, 1080);
			}
		}
	}

	return bOK;
}




// CTestClientDoc ���л�

void CTestClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CTestClientDoc ���

#ifdef _DEBUG
void CTestClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

void CTestClientDoc::SetImage( UINT level, LPCTSTR pszFilename )
{
	if(m_ImageFiles.size() <= level)
	{
		m_ImageFiles.resize(level + 1);
	}
	m_ImageFiles[level] = pszFilename;
}

bool CTestClientDoc::UpdateBuffer( UINT level )
{
	bool bOK = false;
	if(m_ImageFiles.size() > level)
	{
		FIBITMAP* pBmp = FreeImage_LoadU(FIF_BMP, CT2CW(m_ImageFiles[level]));
		if(pBmp)
		{
			FIBITMAP* p32Bmp = FreeImage_ConvertTo32Bits(pBmp);
			if(p32Bmp)
			{
				int w = FreeImage_GetWidth(p32Bmp);
				int h = FreeImage_GetHeight(p32Bmp);
				int p = FreeImage_GetPitch(p32Bmp);
				BYTE* pBits = FreeImage_GetBits(p32Bmp);

				 bOK = UpdateBuffer(level, pBits, w, h, p);
			}
		}
	}
	return bOK;
}

bool CTestClientDoc::UpdateBuffer( UINT level, const BYTE* pBits, int w, int h, int pitch )
{
	bool bOK = false;
	if(m_SrcImages.size() <= level)
	{
		m_SrcImages.resize(level + 1);
	}
	CVideoBuffer*& pBuf = m_SrcImages[level];
	if(pBuf)
	{
		const VideoBufferInfo& bi = pBuf->GetVideoBufferInfo();
		if(bi.nHeight != h || bi.nWidth != w)
		{
			m_pBufferMgr->ReleaseVideoBuffer(pBuf);
			pBuf = NULL;
		}
	}
	if(!pBuf)
	{
		VideoBufferInfo bi = {VBT_D3D9_MEM, w, h, D3DFMT_A8B8G8R8};
		pBuf = m_pBufferMgr->CreateVideoBuffer(bi);
	}
	if(pBuf)
	{
		int vbpitch = 0;
		BYTE* pd = (BYTE*)pBuf->LockBuffer(vbpitch);
		const BYTE* ps = pBits;
		for(int i = 0; i < h; ++i)
		{
			int copysize = min(pitch, vbpitch);
			int zerosize = max(pitch, vbpitch) - copysize;
			memcpy(pd, ps, copysize);
			memset(pd + copysize, 0, zerosize);
			pd += vbpitch;
			ps += pitch;
		}
		pBuf->UnLockBuffer();
		bOK = true;
	}
	return bOK;
}

bool CTestClientDoc::InitEffect(HWND hDeviceWnd, int nBackBufferWidth, int nBackBufferHeight)
{
	m_pRenderEngine = InitEffectModule(hDeviceWnd, nBackBufferWidth, nBackBufferHeight);
	if(m_pRenderEngine)
		m_pBufferMgr = CreateVideoBufferManager(m_pRenderEngine);
	if(m_pBufferMgr)
		SetBackBufferSize(nBackBufferWidth, nBackBufferHeight);
	return !!m_pBufferMgr;
}

void CTestClientDoc::UninitEffect()
{
	ReleaseVideoBufferManager(m_pBufferMgr);
	m_pBufferMgr = NULL;
	UninitEffectModule(m_pRenderEngine);
	m_pRenderEngine = NULL;
}

bool CTestClientDoc::SetBackBufferSize( UINT w, UINT h )
{
	if(m_pBufferMgr)
	{
		if(m_pDestImage)
		{
			m_pBufferMgr->ReleaseVideoBuffer(m_pDestImage);
			m_pDestImage = NULL;
		}
		m_DestVideoBufferInfo.nWidth = w;
		m_DestVideoBufferInfo.nHeight = h;
		m_pDestImage = m_pBufferMgr->CreateVideoBuffer(m_DestVideoBufferInfo);

		UpdateAllViews(NULL);
	}
	return !!m_pDestImage;
}

#endif //_DEBUG


// CTestClientDoc ����

void CTestClientDoc::OnCloseDocument()
{
	UninitEffect();

	CDocument::OnCloseDocument();
}

bool CTestClientDoc::Render()
{
	bool bOK = false;
	if(m_pRenderEngine)
	{
		if(m_pDestImage)
		{
			if(!m_SrcImages.empty())
			{
				if(m_SrcImages[0])
				{
					CVideoBuffer* pSrc = m_SrcImages[0];
					CVideoBuffer* pDest = m_pDestImage;
					const VideoBufferInfo& destBufferInfo = pDest->GetVideoBufferInfo();
					const VideoBufferInfo& srcBufferInfo = pSrc->GetVideoBufferInfo();
					//CopyBuffer(m_pDestImage, m_SrcImages[0]);

					CNegativeRender eff;
					if(eff.Init(m_pRenderEngine->GetDevice(), m_pRenderEngine->GetResourceManager()))
					{
						NegativeFxParam param;
						bOK = eff.Render(pSrc, pDest, &param);
					}
				}
			}
		}
	}
	return bOK;
}

bool CTestClientDoc::CopyBuffer( CVideoBuffer* pDest, CVideoBuffer* pSrc )
{
	if(pSrc && pDest)
	{
		const VideoBufferInfo& destBufferInfo = pDest->GetVideoBufferInfo();
		const VideoBufferInfo& srcBufferInfo = pSrc->GetVideoBufferInfo();
		int pitch = 0;
		const BYTE* ps = (const BYTE*)pSrc->LockBuffer(pitch);
		int vbpitch = 0;
		BYTE* pd = (BYTE*)pDest->LockBuffer(vbpitch);
		int h = min(destBufferInfo.nHeight, srcBufferInfo.nHeight);
		for(int i = 0; i < h; ++i)
		{
			int copysize = min(pitch, vbpitch);
			int zerosize = max(pitch, vbpitch) - copysize;
			memcpy(pd, ps, copysize);
			memset(pd + copysize, 0, zerosize);
			pd += vbpitch;
			ps += pitch;
		}
		pSrc->UnLockBuffer();
		pDest->UnLockBuffer();
		return true;
	}
	return false;
}
