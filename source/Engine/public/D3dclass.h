#pragma once
#pragma once


#include "stdafx.h"

#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

#include "../../Core/public/GameTimer.h"

class D3DClass
{
public:
    D3DClass();

    D3DClass(HINSTANCE hInstance);

    ~D3DClass();

    bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
    
    void Shutdown();

    int Run();

//-------- Scene -----------------------
public:
    virtual void OnResize();
    
    void BeginScene(float red, float green, float blue, float alpha);

    virtual void DrawScene();

    virtual void UpdateScene(float dt);

    void EndScene();

    void CalculateFrameStats();

//--------- Win32 ----------------------
public:
    HINSTANCE AppInst()const;
    HWND MainWnd()const;

    bool InitMainWindow();

    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
    virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
    virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

//--------- Getter ---------------------
public:
    ID3D11Device* GetDevice();

    ID3D11DeviceContext* GetDeviceContext();

    void GetProjectionMatrix(XMMATRIX& projectionMatrix);

    void GetWorldMatrix(XMMATRIX& worldMatrix);

    void GetOrthoMatrix(XMMATRIX& orthoMatrix);

    void GetVideoCardInfo(char* cardname, int& memory);

//--------- Properties --------------------
protected:
    HINSTANCE mhAppInst;
    HWND mhMainWnd;
    std::wstring mMainWndCaption;

    GameTimer mTimer;

    bool m_vsync_enabled = false;
    bool mAppPaused;
    bool mMinimized;
    bool mMaximized;
    bool mResizing;
    UINT m4xMsaaQuality;

private:
    int m_videoCardMemory = 0;
    char m_videoCardDescription[128] = { 0, };

    D3D_DRIVER_TYPE md3dDriverType;
    D3D11_VIEWPORT mScreenViewport;

    IDXGISwapChain* m_swapChain = nullptr;
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_deviceContext = nullptr;

    ID3D11RenderTargetView* m_renderTargetView = nullptr;
    ID3D11Texture2D* m_depthStencilBuffer = nullptr;
    ID3D11DepthStencilState* m_depthStencilState = nullptr;
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
    ID3D11RasterizerState* m_rasterState = nullptr;

    XMMATRIX m_projectionMatrix;
    XMMATRIX m_worldMatrix;
    XMMATRIX m_orthoMatrix;
};
#endif // _D3DCLASS_H_
