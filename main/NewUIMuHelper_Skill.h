// FILE: NewUIMuHelper_Skill.h

#pragma once
#include "NewUIBase.h"
#include "NewUIManager.h"
#include "NewUIButton.h"

namespace SEASON3B
{
	class CNewUIMuHelper_Skill : public CNewUIObj
	{
	public:
		CNewUIMuHelper_Skill();
		virtual ~CNewUIMuHelper_Skill();

		bool Create(CNewUIManager* pNewUIMng, int x, int y);
		void Release();

		void SetPos(int x, int y);

		// THÊM KHAI BÁO HÀM UPDATE VÀO ĐÂY
		bool Update();

		bool UpdateMouseEvent();
		bool UpdateKeyEvent();
		bool Render();

		float GetLayerDepth();

	private:
		void LoadImages();
		void UnloadImages();

		CNewUIManager* m_pNewUIMng;
		POINT m_Pos;
		CNewUIButton m_btnClose;
	};
}