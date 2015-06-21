#pragma once

enum VideoBufferType
{
	VBT_SYSTEM_MEM = 0x00,
	VBT_D3D9_MEM   = 0x01,
	VBT_D3D11_MEM   = 0x02,
};

struct VideoBufferInfo
{
	VideoBufferType eType;
	int nWidth;
	int nHeight;
	DWORD format;
};

class IVideoBuffer
{
public:
	virtual VideoBufferInfo* GetVideoBufferInfo() = 0;

	virtual void* LockBuffer(int &Pitch) = 0;
	virtual BOOL UnLockBuffer() = 0;
};

class IVideoBufferManager
{
public:
	virtual IVideoBuffer* CreateVideoBuffer(const VideoBufferInfo &info) = 0;
	virtual BOOL ReleaseVideoBuffer(IVideoBuffer*& pBuffer) = 0;
};


//�ؼ�������ÿ���ؼ����Լ��Ĳ���
struct tagFxParamBase
{
	unsigned int cbSize;
	char FxType[8];		//int64,����'ShapWipe',ע���ǵ�����
	char FxSubType[8];	//int64,such as 'left'
};

//�����ؼ�
class ITransEffect
{
public:
	 virtual int Process(IVideoBuffer* pSrcA, IVideoBuffer* pSrcB, IVideoBuffer* pDst, tagFxParamBase* pParam) = 0;
};
//�ڲ��ؼ�
class IEffect
{
public:
	virtual int Process(IVideoBuffer* pSrc,IVideoBuffer* pDst,tagFxParamBase* pParam) = 0;
};

AFX_EXT_API IVideoBufferManager* CreateVideoBufferManager();
AFX_EXT_API void ReleaseVideoBufferManager(IVideoBufferManager* p);

AFX_EXT_API bool InitEffects(IEffect*& pEffect, ITransEffect*& pTransEffect);
AFX_EXT_API void UninitEffects();