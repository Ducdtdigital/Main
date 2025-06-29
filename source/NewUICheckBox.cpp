#include "stdafx.h"
#include "NewUICheckBox.h"
#include "NewUISystem.h" // Thêm include này để dùng g_pRenderText và các hàm khác

namespace SEASON3B
{
    CNewUICheckBox::CNewUICheckBox()
    {
        s_ImgIndex = -1;
        m_Pos.x = 0; m_Pos.y = 0;
        m_Size.x = 15; m_Size.y = 15;
        m_Name.clear();
        m_hTextFont = g_hFont;
        m_NameColor = 0xFFFFFFFF;
        m_NameBackColor = 0x00000000;
        m_ImgWidth = 0.0;
        m_ImgHeight = 15.f;
        State = false;
    }

    CNewUICheckBox::~CNewUICheckBox()
    {

    }

    void CNewUICheckBox::CheckBoxImgState(int imgindex)
    {
        s_ImgIndex = imgindex;
    }

    void CNewUICheckBox::RegisterBoxState(bool eventstate)
    {
        State = eventstate;
    }

    void CNewUICheckBox::ChangeText(unicode::t_string btname)
    {
        m_Name = btname;
    }

    void CNewUICheckBox::CheckBoxInfo(int x, int y, int sx, int sy)
    {
        m_Pos.x = x; m_Pos.y = y;
        m_Size.x = sx; m_Size.y = sy;
    }

    bool CNewUICheckBox::GetBoxState()
    {
        return State;
    }

    void CNewUICheckBox::Render()
    {
        EnableAlphaTest();
        glColor4f(1.f, 1.f, 1.f, 1.f);

        if (State)
        {
            RenderImage(s_ImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0, 0);
        }
        else
        {
            RenderImage(s_ImgIndex, m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, 0, m_Size.y);
        }

        g_pRenderText->SetFont(m_hTextFont);
        g_pRenderText->SetTextColor(m_NameColor);
        g_pRenderText->SetBgColor(m_NameBackColor);
        g_pRenderText->RenderText(m_Pos.x + m_Size.x + 1, m_Pos.y + 4, m_Name.c_str(), 0, 0);
    }

    bool CNewUICheckBox::UpdateMouseEvent()
    {
        if (CheckMouseIn(m_Pos.x, m_Pos.y, m_Size.x, m_Size.y))
        {
            if (IsRelease(VK_LBUTTON))
            {
                State = !State;
                return TRUE;
            }
        }
        return false;
    }
}