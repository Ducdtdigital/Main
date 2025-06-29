#include "stdafx.h"
#include "MuHelper.h"
#include "ZzzOpenglUtil.h" // -> THÊM: Chứa các hàm và biến toàn cục của game
#include "ZzzObject.h"     // -> THÊM: Chứa định nghĩa OBJECT
#include "ZzzCharacter.h"  // -> THÊM: Chứa con trỏ Hero và định nghĩa CHARACTER
#include "ZzzInterface.h"  // -> THÊM: Chứa các hàm giao diện và kiểm tra cửa sổ
#include "Protocol.h"      // -> THÊM: Chứa các hàm gửi và nhận gói tin
#include "SkillManager.h"       // -> THÊM: Chứa các hàm quản lý skill

cMuOffHelper gMuHelper; // Khởi tạo biến toàn cục

// --- Các hàm xử lý logic con ---

void MuHelper_CheckAutoPotion()
{
	// Nếu tính năng không được bật, thoát
	if (!gMuHelper.m_bAutoPotionEnabled) return;

	// Lấy con trỏ đến struct của MuHelper trong bộ nhớ
	// oUserObjectStruct_ là con trỏ gốc, trong source mới nó có thể được truy cập qua Hero->p
	DWORD pHelper = *(DWORD*)((char*)Hero + 0x104); // Sử dụng con trỏ Hero
	if (!pHelper) return;

	// Lấy % máu đã cài đặt trong giao diện từ struct Helper
	int SettingHPPotion = *(BYTE*)(pHelper + 0xB1);

	// Sử dụng các trường dữ liệu từ con trỏ Hero để so sánh
	if (Hero->Life < (Hero->MaxLife * SettingHPPotion / 100) && Hero->Life > 0)
	{
		// Cần tìm hàm sử dụng máu trong source của bạn
		// Ví dụ, nó có thể là một hàm toàn cục hoặc một phương thức trong một class khác
		// UsePotion(SLOT_HEALING_POTION);
	}
}

void MuHelper_CheckAutoHealing()
{
	if (!gMuHelper.m_bAutoHealEnabled) return;

	DWORD pHelper = *(DWORD*)((char*)Hero + 0x104);
	if (!pHelper) return;

	int SettingHPHeal = *(BYTE*)(pHelper + 0xB3);

	// Sử dụng hàm toàn cục pGetSkillPos và con trỏ Hero
	if ((pGetSkillPos(SKILL_HEAL) != -1) &&
		(Hero->Life < (Hero->MaxLife * SettingHPHeal / 100)) && Hero->Life > 0)
	{
		// Sử dụng hàm SendRequestSkill để dùng skill
		SendRequestSkill(SKILL_HEAL, (Hero->m_Index & 0xFFFF));
	}
}

// --- Hàm xử lý chính, được gọi mỗi khung hình ---
void cMuOffHelper::Process()
{
	// Chỉ thực thi khi đang trong game và không mở các cửa sổ khác
	if (SceneFlag != GAME_SCENE || *(BYTE*)0x8793386 == 1) // Kiểm tra Scene và trạng thái Chat
	{
		return;
	}

	// Lấy con trỏ đến struct của MuHelper
	DWORD pHelper = *(DWORD*)((char*)Hero + 0x104);
	if (!pHelper) return;

	// Kiểm tra xem nút Play/Pause trong giao diện có đang được bật không
	bool isHelperOn = *(BYTE*)(pHelper + 0x08);
	if (!isHelperOn)
	{
		return;
	}

	// Nếu tất cả điều kiện đều thỏa mãn, bắt đầu chạy các logic auto
	MuHelper_CheckAutoPotion();
	MuHelper_CheckAutoHealing();

	// Các logic khác có thể được thêm vào đây
}