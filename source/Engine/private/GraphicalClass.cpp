#include "stdafx.h"
#include "../public/GraphicalClass.h"
#include "../public/D3dclass.h"

GraphicsClass::GraphicsClass()
{
    m_D3D = nullptr;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    // Direct3D ��ü ����
    m_D3D = new D3DClass;
    if (!m_D3D)
    {
        return false;
    }

    // Direct3D ��ü�� �ʱ�ȭ �Ѵ�.
    if (!m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
    {
        return false;
    }

    return true;
}

void GraphicsClass::Shutdown()
{
    // D3D ��ü�� ��ȯ�մϴ�.
    if (m_D3D)
    {
        m_D3D->Shutdown();
        delete m_D3D;
        m_D3D = nullptr;
    }
}

bool GraphicsClass::Frame()
{

    //�׷��� �������� �����մϴ�.
    if (!Render())
    {
        return false;
    }
    return true;
}

bool GraphicsClass::Render()
{
    // �� �׸��⸦ �����ϱ� ���� ������ ������ ����ϴ�.
    m_D3D->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);

    // ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
    m_D3D->EndScene();

    return true;
}