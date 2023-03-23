#include "stdafx.h"
#include "../public/D3dclass.h"
#include <iostream>

D3DClass::D3DClass()
{
}

D3DClass::D3DClass(const D3DClass&)
{
}

D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
    // ��������ȭ ���¸� �����Ѵ�.
    m_vsync_enabled = vsync;

    // DirectX �׷��� �������̽� ���丮�� �����Ѵ�.
    IDXGIFactory* factory = nullptr;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory))))
    {
        return false;
    }

    // ���丮 ��ü�� ����Ͽ� ù��° �׷��� ī�� �������̽� ��͸� �����Ѵ�.
    IDXGIAdapter* adapter = nullptr;
    if (FAILED(factory->EnumAdapters(0, &adapter)))  // 0 �� ù��° �׷���ī�� // ��ǻ�Ϳ� ���� 0���� ���� �׷����ϼ� �� �ְ� ������ �� �� �ִ�.
    {
        return false;
    }

    // ���(�����)�� ���� ù��° ��͸� �����Ѵ�.
    IDXGIOutput* adapterOutput = nullptr;
    if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
    {
        return false;
    }

    // ���(�����)�� ���� DXGI_FORMAT_R8G8B8A8_UNORM ǥ�� ���Ŀ� �´� ������ �����ɴϴ�.
    unsigned int numModes = 0;
    if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
    {
        return false;
    }

    // ������ ��� ����Ϳ� �׷���ī�� ������ ������ ����Ʈ�� �����Ѵ�.
    DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
    if (!displayModeList)
    {
        return false;
    }

    // ���� ���÷��� ��忡 ���� ����Ʈ�� ä���.
    if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
    {
        return false;
    }


    // ���� ��� ���÷��� ��忡 ���� ȭ�� �ʺ�/���̿� �´� ���÷��� ��带 ã�´�.
    // ������ ���� ã���� ������� ���ΰ�ħ ������ �и�� ���ڰ��� �����Ѵ�.
    unsigned int numerator = 0;
    unsigned int denominator = 0;
    for (unsigned int i = 0; i < numModes; i++)
    {
        if (displayModeList[i].Width == static_cast<unsigned>(screenWidth))
        {
            if (displayModeList[i].Height == static_cast<unsigned>(screenHeight))
            {
                numerator = displayModeList[i].RefreshRate.Numerator;
                denominator = displayModeList[i].RefreshRate.Denominator;
            }
        }
    }

    // ����ī���� ����ü�� ��´�.
    DXGI_ADAPTER_DESC adapterDesc;
    if (FAILED(adapter->GetDesc(&adapterDesc)))
    {
        return false;
    }

    // ����ī�� �޸� �뷮 ������ �ް�����Ʈ ������ �����Ѵ�.
    m_videoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);


    // ����ī���� �̸��� �����մϴ�.
    size_t stringLength = 0;
    if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128) != 0)
    {
        return false;
    }


    // �׷��� ī�� Ȯ�� �뵵.
    const WCHAR* pwcsName; //LPCWSTR

    // required size
    int size = MultiByteToWideChar(CP_ACP, 0, m_videoCardDescription, -1, NULL, 0);
    // allocate it
    pwcsName = new WCHAR[stringLength];
    MultiByteToWideChar(CP_ACP, 0, m_videoCardDescription, -1, (LPWSTR)pwcsName, size);
    // use it....

    OutputDebugString(pwcsName);
    // delete it
    delete[] pwcsName;



    // ���÷��� ��� ����Ʈ�� �����Ѵ�.
    delete[] displayModeList;
    displayModeList = nullptr;

    // ��� ��͸� �����Ѵ�.
    adapterOutput->Release();
    adapterOutput = nullptr;

    // ��͸� �����Ѵ�.
    adapter->Release();
    adapter = nullptr;

    // ����ü�� ����ü�� �ʱ�ȯ�Ѵ�.
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

    // ����۸� 1���� ����ϵ��� �����Ѵ�.
    swapChainDesc.BufferCount = 1;

    // ������� ���̿� ���̸� �����Ѵ�.
    swapChainDesc.BufferDesc.Width = screenWidth;
    swapChainDesc.BufferDesc.Height = screenHeight;

    // 33bit ���ǽ��� �����Ѵ�.
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    // ������� ���ΰ�ħ ������ �����Ѵ�.
    if (m_vsync_enabled)
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }


    // ������� ���뵵�� �����Ѵ�.
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    // �������� ���� ������ �ڵ��� �����Ѵ�.
    swapChainDesc.OutputWindow = hwnd;

    // ��Ƽ���ø��� ����.
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;

    // â��� or Ǯ��ũ�� ��带 �����Ѵ�.
    swapChainDesc.Windowed = !fullscreen;
    
    // ��ĵ ���� ���� �� ũ�⸦ �������� �������� �����Ѵ�.
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // ��µ� ���� ����۸� ��쵵�� �����Ѵ�.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // �߰� �ɼ� �÷��׸� ������� �ʴ´�.
    swapChainDesc.Flags = 0;
    
    // ��ó������ DirectX11�� �����Ѵ�.
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
   
    UINT createDeviceFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

    //�̰� �� ��?
    //if(FAILED(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION, &m_device, &featureLevel, &m_deviceContext))

    // ���� ü��, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ�� �����.
    if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, &featureLevel, 0,
                                        D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext)))
    {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return false;
    }
    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
        return false;
    }
    MessageBox(0, L"D3D11CreateDevice is succeed", 0, 0);

    // ����� �����͸� ���´�.
    ID3D11Texture2D* backBufferPtr = nullptr;
    if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&(backBufferPtr)))))
    {
        return false;
    }


    // �� ���� �����ͷ� ���� Ÿ�� �並 �����Ѵ�.
    if (FAILED(m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView)))
    {
        return false;
    }


    // ����� �����͸� �����Ѵ�.
    backBufferPtr->Release();
    backBufferPtr = nullptr;


    // ���� ���� ����ü�� �ʱ�ȭ �մϴ�.
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

    // ���� ���� ����ü�� �ۼ��մϴ�.
    depthBufferDesc.Width = screenWidth;
    depthBufferDesc.Height = screenHeight;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    // ������ ���̹��� ����ü�� ����Ͽ� ���� ���� �ؽ��ĸ� �����Ѵ�.
    if (FAILED(m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer)))
    {
        return false;
    }

    // ���ٽ� ���� ����ü�� �ʱ�ȭ �մϴ�.
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

    // ���ٽ� ���� ����ü�� �ۼ��մϴ�.
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // �ȼ� ������ ���ٽ� �����Դϴ�.
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // �ȼ� �޸��� ���ٽ� �����Դϴ�.
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // ���� ���ٽ� ���¸� �����մϴ�.
    m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);


    // ���� ���ٽ� ���� ����ü�� �ʱ�ȭ�մϴ�.
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

    // ���� ���ٽ� �� ����ü�� �����Ѵ�.
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // ���� ���ٽ� �並 �����Ѵ�.
    if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView)))
    {
        return false;
    }

    // ������ ��� ��� ���� ���ٽ� ���۸�  ��� ���� ������ ���ο� ���ε� �Ѵ�.
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    // �׷����� ������� ����� ������ ������ ����ü�� �����Ѵ�.
    D3D11_RASTERIZER_DESC rasterDesc;
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // ��� �ۼ��� ����ü���� ������ ������ ���¸� �����.
    if (FAILED(m_device->CreateRasterizerState(&rasterDesc, &m_rasterState)))
    {
        return false;
    }

    // ���� ������ ������ ���¸� �����Ѵ�.
    m_deviceContext->RSSetState(m_rasterState);

    // �������� ���� ����Ʈ�� �����Ѵ�.
    D3D11_VIEWPORT viewport;
    viewport.Width = static_cast<float>(screenWidth);
    viewport.Height = static_cast<float>(screenHeight);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    // ����Ʈ�� �����Ѵ�.
    m_deviceContext->RSSetViewports(1, &viewport);

    // ���� ����� �����Ѵ�.
    float fieldOfView = 3.141592654 / 4.0f;
    float screenAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

    // 3D �������� ���� ���� ����� �����.
    m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

    // ���� ����� �׵� ��ķ� �ʱ�ȭ �Ѵ�.
    m_worldMatrix = XMMatrixIdentity();

    // 2D������������ ���� ���� ����� �����.
    m_orthoMatrix = XMMatrixOrthographicLH(static_cast<float>(screenWidth), static_cast<float>(screenHeight), screenNear, screenDepth);

    return true;
}

void D3DClass::Shutdown()
{
    // �����ϱ� ���� �̷��� ������ ���� �ٲ��� ������ ����ü���� �Ҵ� ������ �� ���ܰ� �߻��մϴ�.
    if (m_swapChain)
    {
        m_swapChain->SetFullscreenState(false, nullptr);
    }

    if (m_rasterState)
    {
        m_rasterState->Release();
        m_rasterState = nullptr;
    }

    if (m_depthStencilView)
    {
        m_depthStencilView->Release();
        m_depthStencilView = nullptr;
    }

    if (m_depthStencilState)
    {
        m_depthStencilState->Release();
        m_depthStencilState = nullptr;
    }

    if (m_depthStencilBuffer)
    {
        m_depthStencilBuffer->Release();
        m_depthStencilBuffer = nullptr;
    }

    if (m_renderTargetView)
    {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }

    if (m_deviceContext)
    {
        m_deviceContext->Release();
        m_deviceContext = nullptr;
    }

    if (m_device)
    {
        m_device->Release();
        m_device = nullptr;
    }

    if (m_swapChain)
    {
        m_swapChain->Release();
        m_swapChain = nullptr;
    }

}

void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{

    // ���۸� ���� ���� �����Ѵ�.
    float color[4] = { red, green, blue, alpha };

    // ����۸� �����.
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

    // ���� ���۸� �����.
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3DClass::EndScene()
{
    // �������� �Ϸ�Ǿ����Ƿ� ȭ�鿡 �� ���۸� ǥ���Ѵ�.
    if (m_vsync_enabled)
    {
        // ȭ�� ���� ��ħ ������ �����Ѵ�.
        m_swapChain->Present(1, 0);
    }
    else
    {
        // ������ ������ ����Ѵ�.
        m_swapChain->Present(0, 0);
    }
}

ID3D11Device* D3DClass::GetDevice()
{
    return m_device;
}

ID3D11DeviceContext* D3DClass::GetDeviceContext()
{
    return m_deviceContext;
}

void D3DClass::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
    // �̹� ���������� ��� ����.
    projectionMatrix = m_projectionMatrix;
}

void D3DClass::GetWorldMatrix(XMMATRIX& worldMatrix)
{
    // �̹� ���������� ��� ����.
    worldMatrix = m_worldMatrix;
}

void D3DClass::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
    // �̹� ���������� ��� ����.
    orthoMatrix = m_orthoMatrix;
}

void D3DClass::GetVideoCardInfo(char* cardname, int& memory)
{
    strcpy_s(cardname, 128, m_videoCardDescription);
    memory = m_videoCardMemory;
}