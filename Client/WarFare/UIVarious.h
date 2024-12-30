#ifndef AFX_UIVARIOUS_H__094F9A3E_1620_4E07_8726_82881B21B48C__INCLUDED_
#define AFX_UIVARIOUS_H__094F9A3E_1620_4E07_8726_82881B21B48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameDef.h"
#include "N3UIBase.h"
#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory> // Modern C++ için unique_ptr desteği

// CUIState sınıfı, oyuncu durum bilgilerini gösterir ve günceller
class CUIState : public CN3UIBase
{
public:
    std::unique_ptr<CN3UIString> m_pText_ID;
    std::unique_ptr<CN3UIString> m_pText_Level;
    std::unique_ptr<CN3UIString> m_pText_RealmPoint;

    std::unique_ptr<CN3UIString> m_pText_Class;
    std::unique_ptr<CN3UIString> m_pText_Race;
    std::unique_ptr<CN3UIString> m_pText_Nation;

    std::unique_ptr<CN3UIString> m_pText_HP;
    std::unique_ptr<CN3UIString> m_pText_MP;
    std::unique_ptr<CN3UIString> m_pText_Exp;
    std::unique_ptr<CN3UIString> m_pText_AP;
    std::unique_ptr<CN3UIString> m_pText_GP;
    std::unique_ptr<CN3UIString> m_pText_Weight;

    std::unique_ptr<CN3UIString> m_pText_BonusPoint;

    std::unique_ptr<CN3UIButton> m_pBtn_Strength;
    std::unique_ptr<CN3UIButton> m_pBtn_Stamina;
    std::unique_ptr<CN3UIButton> m_pBtn_Dexterity;
    std::unique_ptr<CN3UIButton> m_pBtn_MagicAttak;
    std::unique_ptr<CN3UIButton> m_pBtn_Intelligence;

    std::unique_ptr<CN3UIString> m_pText_Strength;
    std::unique_ptr<CN3UIString> m_pText_Stamina;
    std::unique_ptr<CN3UIString> m_pText_Dexterity;
    std::unique_ptr<CN3UIString> m_pText_MagicAttak;
    std::unique_ptr<CN3UIString> m_pText_Intelligence;

    std::unique_ptr<CN3UIString> m_pText_RegistFire;
    std::unique_ptr<CN3UIString> m_pText_RegistMagic;
    std::unique_ptr<CN3UIString> m_pText_RegistIce;
    std::unique_ptr<CN3UIString> m_pText_RegistCurse;
    std::unique_ptr<CN3UIString> m_pText_RegistLight;
    std::unique_ptr<CN3UIString> m_pText_RegistPoison;

    std::unique_ptr<CN3UIBase> m_pImg_MAP;
    std::unique_ptr<CN3UIBase> m_pImg_Sta;
    std::unique_ptr<CN3UIBase> m_pImg_Int;
    std::unique_ptr<CN3UIBase> m_pImg_Dex;
    std::unique_ptr<CN3UIBase> m_pImg_Str;

public:
    void UpdateBonusPointAndButtons(int iBonusPointRemain);

    void UpdateID(const std::string& szID);
    void UpdateLevel(int iVal);
    void UpdateRealmPoint(int iLoyalty, int iLoyaltyMonthly);

    void UpdateHP(int iVal, int iValMax);
    void UpdateMSP(int iVal, int iValMax);
    void UpdateExp(uint64_t iVal, uint64_t iValMax);
    void UpdateAttackPoint(int iVal, int iDelta);
    void UpdateGuardPoint(int iVal, int iDelta);
    void UpdateWeight(int iVal, int iValMax);
    void UpdateStrength(int iVal, int iDelta);
    void UpdateStamina(int iVal, int iDelta);
    void UpdateDexterity(int iVal, int iDelta);
    void UpdateIntelligence(int iVal, int iDelta);
    void UpdateMagicAttak(int iVal, int iDelta);

    void UpdateRegistFire(int iVal, int iDelta);
    void UpdateRegistCold(int iVal, int iDelta);
    void UpdateRegistLight(int iVal, int iDelta);
    void UpdateRegistMagic(int iVal, int iDelta);
    void UpdateRegistCurse(int iVal, int iDelta);
    void UpdateRegistPoison(int iVal, int iDelta);

    void MsgSendAblityPointChange(uint8_t byType, int16_t siValueDelta);

    virtual bool ReceiveMessage(CN3UIBase* pSender, uint32_t dwMsg);
    virtual bool Load(HANDLE hFile);
    virtual void Release();

    CUIState();
    virtual ~CUIState();
};

// Diğer sınıflar için benzer modernizasyon ve düzeltmeler burada yapılabilir...

#endif // AFX_UIVARIOUS_H__094F9A3E_1620_4E07_8726_82881B21B48C__INCLUDED_
