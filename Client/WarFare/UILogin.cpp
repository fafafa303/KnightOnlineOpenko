#include "UILogIn.h"
#include "GameProcLogIn.h"
#include "N3UIEdit.h"
#include "N3UIButton.h"
#include "N3UIList.h"
#include "UIMessageBoxManager.h"
#include <algorithm>
#include <shellapi.h>

// Yapıcı
CUILogIn::CUILogIn()
    : m_pEdit_id(nullptr), m_pEdit_pw(nullptr),
    m_pBtn_LogIn(nullptr), m_pBtn_Connect(nullptr), m_pBtn_Cancel(nullptr),
    m_pBtn_Option(nullptr), m_pBtn_Join(nullptr),
    m_pGroup_ServerList(nullptr), m_pGroup_LogIn(nullptr),
    m_pText_Rights(nullptr), m_pImg_MGameLogo(nullptr),
    m_pImg_DaumLogo(nullptr), m_pImg_GradeLogo(nullptr),
    m_pList_Server(nullptr), m_bOpenningNow(false),
    m_fMoveDelta(0), m_bLogIn(false) {
}

// Yıkıcı
CUILogIn::~CUILogIn() {}

// Mesaj alıcı
bool CUILogIn::ReceiveMessage(CN3UIBase* pSender, uint32_t dwMsg) {
    if (!pSender) return false;

    if (dwMsg == UIMSG_BUTTON_CLICK) {
        if (pSender == m_pBtn_LogIn.get() && m_pEdit_id && m_pEdit_pw) {
            CGameProcedure::s_pProcLogIn->MsgSend_AccountLogIn(LIC_KNIGHTONLINE);
            return true;
        }
        else if (pSender == m_pBtn_Connect.get()) {
            CGameProcedure::s_pProcLogIn->ConnectToGameServer();
            return true;
        }
        else if (pSender == m_pBtn_Cancel.get()) {
            CGameBase::s_bRunning = false;
            return true;
        }
        else if (pSender == m_pBtn_Option.get()) {
            std::string szMsg = "Do you want to open the options?";
            CGameProcedure::MessageBoxPost(szMsg, "", MB_YESNO, BEHAVIOR_EXECUTE_OPTION);
            return true;
        }
        else if (pSender == m_pBtn_Join.get()) {
            if (!CGameProcedure::s_pProcLogIn->m_szRegistrationSite.empty()) {
                ShellExecute(nullptr, "open",
                    CGameProcedure::s_pProcLogIn->m_szRegistrationSite.c_str(),
                    nullptr, nullptr, SW_SHOWNORMAL);
            }
            return true;
        }
    }
    else if (dwMsg == UIMSG_LIST_DBLCLK) {
        CGameProcedure::s_pProcLogIn->ConnectToGameServer();
        return true;
    }
    else if (dwMsg == UIMSG_EDIT_RETURN) {
        if (!m_bLogIn && m_pEdit_id && m_pEdit_pw) {
            CN3UIBase* pMsgBox = CGameProcedure::s_pMsgBoxMgr->GetFocusMsgBox();
            if (!(pMsgBox && pMsgBox->IsVisible())) {
                CGameProcedure::s_pProcLogIn->MsgSend_AccountLogIn(LIC_KNIGHTONLINE);
            }
        }
        else {
            return ReceiveMessage(m_pBtn_Connect.get(), UIMSG_BUTTON_CLICK);
        }
    }
    else if (dwMsg == UIMSG_EDIT_TAB) {
        FocusCircular();
        return true;
    }

    return false;
}

// Yükleme fonksiyonu
bool CUILogIn::Load(HANDLE hFile) {
    if (!CN3UIBase::Load(hFile)) return false;

    m_pGroup_LogIn = GetChildByID("Group_LogIn");
    if (m_pGroup_LogIn) {
        m_pBtn_LogIn.reset(dynamic_cast<CN3UIButton*>(m_pGroup_LogIn->GetChildByID("Btn_Login")));
        m_pBtn_Cancel.reset(dynamic_cast<CN3UIButton*>(m_pGroup_LogIn->GetChildByID("Btn_Cancel")));
        m_pBtn_Option.reset(dynamic_cast<CN3UIButton*>(m_pGroup_LogIn->GetChildByID("Btn_Option")));
        m_pBtn_Join.reset(dynamic_cast<CN3UIButton*>(m_pGroup_LogIn->GetChildByID("Btn_Join")));

        m_pEdit_id.reset(dynamic_cast<CN3UIEdit*>(m_pGroup_LogIn->GetChildByID("Edit_ID")));
        m_pEdit_pw.reset(dynamic_cast<CN3UIEdit*>(m_pGroup_LogIn->GetChildByID("Edit_PW")));
    }

    m_pGroup_ServerList = GetChildByID("Group_ServerList");
    if (m_pGroup_ServerList) {
        m_pList_Server.reset(dynamic_cast<CN3UIList*>(m_pGroup_ServerList->GetChildByID("List_Server")));
        m_pBtn_Connect.reset(dynamic_cast<CN3UIButton*>(m_pGroup_ServerList->GetChildByID("Btn_Connect")));
    }

    return true;
}

// Kullanıcı bilgilerini al
void CUILogIn::AccountIDGet(std::string& szID) const {
    if (m_pEdit_id) {
        szID = m_pEdit_id->GetString();
    }
    else {
        szID.clear();
    }
}

void CUILogIn::AccountPWGet(std::string& szPW) const {
    if (m_pEdit_pw) {
        szPW = m_pEdit_pw->GetString();
    }
    else {
        szPW.clear();
    }
}

// Düğme etkinleştirme
void CUILogIn::ConnectButtonSetEnable(bool bEnable) {
    if (m_pBtn_Connect) m_pBtn_Connect->SetState(bEnable ? UI_STATE_BUTTON_NORMAL : UI_STATE_BUTTON_DISABLE);
    if (m_pList_Server) m_pList_Server->SetState(bEnable ? UI_STATE_LIST_ENABLE : UI_STATE_LIST_DISABLE);
}

// Odaklama
void CUILogIn::FocusToID() {
    if (m_pEdit_id) m_pEdit_id->SetFocus();
}

void CUILogIn::FocusCircular() {
    if (!m_pEdit_id || !m_pEdit_pw) return;

    if (m_pEdit_id->HaveFocus()) {
        m_pEdit_pw->SetFocus();
    }
    else {
        m_pEdit_id->SetFocus();
    }
}

// Düzenleme kontrollerini başlat
void CUILogIn::InitEditControls() {
    if (m_pEdit_id) m_pEdit_id->SetString("");
    if (m_pEdit_pw) m_pEdit_pw->SetString("");
    FocusToID();
}

// Sunucu bilgilerini ekle
bool CUILogIn::ServerInfoAdd(const __GameServerInfo& GSI) {
    m_ListServerInfos.push_back(GSI);
    return true;
}

// Sunucu bilgilerini al
bool CUILogIn::ServerInfoGet(size_t iIndex, __GameServerInfo& GSI) {
    if (iIndex >= m_ListServerInfos.size()) return false;

    GSI = m_ListServerInfos[iIndex];
    return true;
}

bool CUILogIn::ServerInfoGetCur(__GameServerInfo& GSI) {
    if (!m_pList_Server) return false;

    int iIndex = m_pList_Server->GetCurSel();
    return ServerInfoGet(static_cast<size_t>(iIndex), GSI);
}

// Sunucu listesini güncelle
void CUILogIn::ServerInfoUpdate() {
    if (!m_pList_Server) return;

    m_pList_Server->ResetContent();
    for (const auto& server : m_ListServerInfos) {
        m_pList_Server->AddString(server.szName);
    }
}
