// VideoEffect.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "../D3D9Render/VideoBufferManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVideoBufferManager g_pVideoBufferManager;

IVideoBufferManager* CreateVideoBufferManager()
{
	g_pVideoBufferManager = new CVideoBufferManager;
	return g_pVideoBufferManager;
}

void ReleaseVideoBufferManager(IVideoBufferManager* p)
{
}

bool InitEffects(IEffect*& pEffect, ITransEffect*& pTransEffect)
{
	return true;
}

void UninitEffects()
{

}
