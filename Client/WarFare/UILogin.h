#pragma once

#include <string>
#include <vector>
#include <memory>
#include "N3UIBase.h"

// Sunucu bilgilerini tutan yapı
struct __GameServerInfo {
    std::string szName; // Sunucu adı
    std::string szIP;   // Sunucu IP adresi
    int iConcurrentUserCount; // Sunucuda eşzamanlı kullanıcı sayısı

    void Init() {
        szName.clear();
        szIP.clear();
        iConcurrentUserCount = 0;
    }

    __GameServerInfo() { Init(); }
    __GameServerInfo(const std::string& szName2, const std::string& szIP2, int iConcurrentUserCount2)
        : szName(szName2), szIP(szIP2), iConcurrentUserCount(iConcurrentUserCount2) {
    }
};

// Kullanıcı giriş arayüzünü temsil eden sınıf
class CUILogIn : public CN3UIBase {
protected:
    // Giriş kutuları
    std::unique_ptr<CN3UIEdit> m_pEdit_id; // Kullanıcı adı giriş kutusu
    std::unique_ptr<CN3UIEdit> m_pEdit_pw; // Şifre giriş kutusu

    // Düğmeler
    std::unique_ptr<CN3UIButton> m_pBtn_LogIn;
    std::unique_ptr<CN3UIButton> m_pBtn_Connect;
    std::unique_ptr<CN3UIButton> m_pBtn_Cancel;
    std::unique_ptr<CN3UIButton> m_pBtn_Option;
    std::unique_ptr<CN3UIButton> m_pBtn_Join;

    // UI grupları
    CN3UIBase* m_pGroup_ServerList;
    CN3UIBase* m_pGroup_LogIn;

    // UI bileşenleri
    CN3UIBase* m_pText_Rights;
    CN3UIBase* m_pImg_MGameLogo;
    CN3UIBase* m_pImg_DaumLogo;
    CN3UIBase* m_pImg_GradeLogo;

    // Sunucu listesi ve bilgileri
    std::unique_ptr<CN3UIList> m_pList_Server;
    std::vector<__GameServerInfo> m_ListServerInfos; // Sunucu bilgilerini tutar

    // UI durumu ve animasyon değişkenleri
    bool m_bOpenningNow; // UI açılıyor mu?
    float m_fMoveDelta;  // Hareket delta değeri
    bool m_bLogIn;       // Giriş yapıldı mı?

public:
    // Yapıcı ve yıkıcı
    CUILogIn();
    virtual ~CUILogIn();

    // Giriş kutuları ve sunucu bilgileri ile ilgili işlevler
    void InitEditControls();
    void FocusCircular();
    void FocusToID();

    // UI durumunu kontrol eden işlevler
    void SetRequestedLogIn(bool bLogIn) { m_bLogIn = bLogIn; }
    void SetVisibleLogInUIs(bool bEnable);
    void OpenServerList();
    void Tick();

    // Sunucu bilgilerini işleyen işlevler
    int ServerInfoCount() const { return static_cast<int>(m_ListServerInfos.size()); }
    bool ServerInfoAdd(const __GameServerInfo& GSI);
    bool ServerInfoGet(size_t iIndex, __GameServerInfo& GSI);
    bool ServerInfoGetCur(__GameServerInfo& GSI);
    void ServerInfoUpdate();

    // Kullanıcı giriş bilgilerini işleyen işlevler
    void AccountIDGet(std::string& szID) const;
    void AccountPWGet(std::string& szPW) const;

    // UI bileşenlerini etkinleştirme veya devre dışı bırakma
    void ConnectButtonSetEnable(bool bEnable);

    // UI'dan gelen mesajları işleme
    virtual bool ReceiveMessage(CN3UIBase* pSender, uint32_t dwMsg);

    // UI'nın çeşitli konumlarını ve görünümlerini yeniden hesaplama
    void RecalcGradePos();

    // Dosyadan yükleme
    virtual bool Load(HANDLE hFile);
};
