#pragma once

#include "asw_player.h"
#include "asw_marine.h"

class CASW_Client_Effects : CAutoGameSystemPerFrame
{
public:
	CASW_Client_Effects(void);
	~CASW_Client_Effects(void);

#define ASW_PLAYERINFO_SIZE ASW_MAX_MARINE_RESOURCES

	struct CFX_Float
	{
		float m_flValue;
		float m_flLastUpdate;
	};

	struct CFX_Bool
	{
		bool m_bValue;
		float m_flLastUpdate;
	};

	struct PlayerInfo
	{
		CASW_Player *pPlayer;
		CASW_Marine *pMarine;

		//Settings for local contrast enhancement
		CFX_Bool LCE_isEnabled;
		CFX_Float LCE_vStrength;
		CFX_Float LCE_vStart;
		CFX_Float LCE_vEnd;
		
		bool playerWantsDisabled;

	} PlayerInfoArray[ASW_PLAYERINFO_SIZE];

	enum EffectType_t
	{
		EFFECT_LCE,
		EFFECT_BLOOM,
	};

	void OnSpawnedHorde(int num);

	bool ShouldUpdateCvar(CFX_Float PreviousValue, float NewValue, EffectType_t EffectType);
	bool ShouldUpdateCvar(CFX_Bool OldValue, bool NewValue);

	float IsMarineHurt(CASW_Marine *pMarine);
	float GetMarineIntensity(CASW_Marine *pMarine);
	int i_DebugThinks;
	
	bool PlayerAdd(CASW_Player *pPlayer);
	void PlayerRemove(CASW_Player *pPlayer);
	void PlayerSwitched(CASW_Player *pPlayer, CASW_Marine *pMarine_new);
	void ToggleForPlayer(CASW_Player *pPlayer, bool bEnabled);
	void ResetPlayers();

	bool SendClientCommand(edict_t *pPlayerEdict, const char *Command, float Value);
	bool SendClientCommand(edict_t *pPlayerEdict, const char *Command, bool Value);

	void FrameUpdatePostEntityThink();
};

CASW_Client_Effects* ASW_Client_Effects();