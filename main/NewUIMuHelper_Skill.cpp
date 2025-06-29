// FILE: NewUIMuHelper_Skill.cpp

#include "stdafx.h"
#include "NewUIMuHelper_Skill.h"
#include "NewUISystem.h"

using namespace SEASON3B;

CNewUIMuHelper_Skill::CNewUIMuHelper_Skill()
{
	m_pNewUIMng = NULL;
	m_Pos.x = m_Pos.y = 0;
}

CNewUIMuHelper_Skill::~CNewUIMuHelper_Skill()
{
	Release();
}

bool CNewUIMuHelper_Skill::Create(CNewUIManager* pNewUIMng, int x, int y)
{
	if (NULL == pNewUIMng) return false;
	m_pNewUIMng = pNewUIMng;
	SetPos(x, y);
	LoadImages();

	// Nút đóng cửa sổ
	m_btnClose.ChangeButtonImgState(true, CNewUIMyInventory::IMAGE_INVENTORY_EXIT_BTN, false);
	m_btnClose.ChangeButtonInfo(m_Pos.x + 13, m_Pos.y + 391, 36, 29);
	m_btnClose.ChangeToolTipText(GlobalText[1002], true);

	Show(false); // Mặc định là ẩn
	return true;
}

void CNewUIMuHelper_Skill::Release()
{
	UnloadImages();
	if (m_pNewUIMng)
	{
		m_pNewUIMng = NULL;
	}
}

void CNewUIMuHelper_Skill::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	// Cập nhật vị trí của các thành phần con nếu cần
	m_btnClose.ChangeButtonInfo(m_Pos.x + 13, m_Pos.y + 391, 36, 29);
}

bool CNewUIMuHelper_Skill::UpdateMouseEvent()
{
	if (IsVisible() == false) return true;

	if (m_btnClose.UpdateMouseEvent())
	{
		Show(false); // Ẩn cửa sổ này đi
		return false;
	}

	// "Ăn" sự kiện chuột để không bị click xuyên qua
	if (CheckMouseIn(m_Pos.x, m_Pos.y, 190, 429))
	{
		return false;
	}

	return true;
}

bool CNewUIMuHelper_Skill::UpdateKeyEvent()
{
	if (IsVisible() && IsPress(VK_ESCAPE))
	{
		Show(false); // Ẩn cửa sổ khi nhấn ESC
		return false;
	}
	return true;
}

bool CNewUIMuHelper_Skill::Render()
{
	if (IsVisible() == false) return true;

	EnableAlphaTest();
	glColor4f(1.f, 1.f, 1.f, 1.f);

	// Vẽ nền cửa sổ (sử dụng ảnh từ các UI khác để tiết kiệm)
	RenderImage(CNewUIMyInventory::IMAGE_INVENTORY_BACK_TOP, m_Pos.x, m_Pos.y, 190, 64);
	RenderImage(CNewUIMyInventory::IMAGE_INVENTORY_BACK_LEFT, m_Pos.x, m_Pos.y + 64, 21, 320);
	RenderImage(CNewUIMyInventory::IMAGE_INVENTORY_BACK_RIGHT, m_Pos.x + 190 - 21, m_Pos.y + 64, 21, 320);
	RenderImage(CNewUIMyInventory::IMAGE_INVENTORY_BACK_BOTTOM, m_Pos.x, m_Pos.y + 429 - 45, 190, 45);

	// Vẽ tiêu đề
	g_pRenderText->SetFont(g_hFontBold);
	g_pRenderText->RenderText(m_Pos.x, m_Pos.y + 13, "Skill Settings", 190, 0, RT3_SORT_CENTER);

	// Vẽ nút đóng
	m_btnClose.Render();

	DisableAlphaBlend();
	return true;
}

bool CNewUIMuHelper_Skill::Update()
{
	if (!IsVisible())
	{
		return true; // Nếu không hiển thị thì không cần làm gì
	}

	// Bạn có thể thêm logic cập nhật trạng thái cho cửa sổ skill ở đây nếu cần
	// Ví dụ: cập nhật thời gian, v.v.

	return true;
}
float CNewUIMuHelper_Skill::GetLayerDepth() { return 3.5f; } // Lớp cao hơn cửa sổ chính
void CNewUIMuHelper_Skill::LoadImages() {}
void CNewUIMuHelper_Skill::UnloadImages() {}