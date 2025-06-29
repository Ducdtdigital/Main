#pragma once
#include "Protocol.h" // Cần thiết cho các struct

// -> KHÔNG CẦN #define cho các hàm hook nữa

class cMuOffHelper
{
public:
	// --- Các biến trạng thái để giao diện mới có thể điều khiển ---
	bool m_bAutoPotionEnabled;
	bool m_bAutoHealEnabled;
	// Thêm các biến khác nếu cần (ví dụ: m_bAutoAttackEnabled)

	// --- Hàm khởi tạo để gán giá trị mặc định ---
	cMuOffHelper() {
		m_bAutoPotionEnabled = false;
		m_bAutoHealEnabled = false;
	}

	// --- Các hàm Set... để giao diện "ra lệnh" ---
	void SetAutoPotion(bool bEnable) { this->m_bAutoPotionEnabled = bEnable; }
	void SetAutoHeal(bool bEnable) { this->m_bAutoHealEnabled = bEnable; }

	// --- Hàm xử lý logic chính, sẽ được gọi mỗi frame ---
	void Process();
};

extern cMuOffHelper gMuHelper;