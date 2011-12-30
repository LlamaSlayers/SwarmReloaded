//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "c_basedoor.h"
#include "c_asw_player.h"
#include "c_asw_marine.h"
#include "asw_input.h"
#include <vgui/ISurface.h>
#include <vgui_controls/Panel.h>
#include <vgui/ILocalize.h>
#include "asw_util_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef CBaseDoor
#undef CBaseDoor
#endif

IMPLEMENT_CLIENTCLASS_DT(C_BaseDoor, DT_BaseDoor, CBaseDoor)
	RecvPropFloat(RECVINFO(m_flWaveHeight)),
	RecvPropBool (RECVINFO(m_bLocked)),
END_RECV_TABLE()

int C_BaseDoor::s_nUseActionIconTextureIDLocked = -1;
int C_BaseDoor::s_nUseActionIconTextureIDUnlocked = -1;

C_BaseDoor::C_BaseDoor( void ) :
	m_GlowObject( this, Vector( 0.0f, 0.4f, 0.75f ), 1.0f, false, true )
{
	m_flWaveHeight = 0.0f;

	if (s_nUseActionIconTextureIDLocked == -1)
	{
		s_nUseActionIconTextureIDLocked = vgui::surface()->CreateNewTextureID();
		vgui::surface()->DrawSetTextureFile( s_nUseActionIconTextureIDLocked, "VGUI/swarm/UseIcons/PanelLocked", true, false);
		s_nUseActionIconTextureIDUnlocked = vgui::surface()->CreateNewTextureID();
		vgui::surface()->DrawSetTextureFile( s_nUseActionIconTextureIDUnlocked, "VGUI/swarm/UseIcons/PanelUnlocked", true, false);
	}
}

C_BaseDoor::~C_BaseDoor( void )
{
}

bool C_BaseDoor::GetUseAction(ASWUseAction &action, C_ASW_Marine *pUser)
{
	action.UseTarget = this;

	if ( m_bLocked )
	{
		TryLocalize( "#asw_door_locked", action.wszText, sizeof( action.wszText ) );
		action.iUseIconTexture = s_nUseActionIconTextureIDLocked;

		action.fProgress = -1;

		action.UseIconRed = 255;
		action.UseIconGreen = 0;
		action.UseIconBlue = 0;
		action.TextRed = 164;
		action.TextGreen = 164;
		action.TextBlue = 164;
		action.bTextGlow = false;
		action.bShowUseKey = false;
		action.iInventorySlot = -1;
	}
	else
	{
		TryLocalize( "#asw_door_usable", action.wszText, sizeof( action.wszText ) );
		action.iUseIconTexture = s_nUseActionIconTextureIDUnlocked;

		action.fProgress = -1;

		action.UseIconRed = 255;
		action.UseIconGreen = 255;
		action.UseIconBlue = 255;
		action.bShowUseKey = true;
		action.iInventorySlot = -1;
	}

	return true;
}

bool C_BaseDoor::IsUsable(C_BaseEntity *pUser)
{
	return (pUser && pUser->GetAbsOrigin().DistTo(GetAbsOrigin()) < ASW_MARINE_USE_RADIUS);	// near enough?
}

void C_BaseDoor::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );

	if ( updateType == DATA_UPDATE_CREATED )
	{
		SetNextClientThink( CLIENT_THINK_ALWAYS );
	}
}

void C_BaseDoor::ClientThink()
{
	bool bShouldGlow = false;
	float flDistanceToMarineSqr = 0.0f;
	float flWithinDistSqr = (ASW_MARINE_USE_RADIUS*4)*(ASW_MARINE_USE_RADIUS*4);

	C_ASW_Player *pLocalPlayer = C_ASW_Player::GetLocalASWPlayer();
	if ( pLocalPlayer && pLocalPlayer->GetMarine() && ASWInput()->GetUseGlowEntity() != this )
	{
		flDistanceToMarineSqr = (pLocalPlayer->GetMarine()->GetAbsOrigin() - WorldSpaceCenter()).LengthSqr();
		if ( flDistanceToMarineSqr < flWithinDistSqr )
			bShouldGlow = true;
	}

	m_GlowObject.SetRenderFlags( bShouldGlow, bShouldGlow );

	if ( m_GlowObject.IsRendering() )
	{
		m_GlowObject.SetAlpha( MIN( 0.7f, (1.0f - (flDistanceToMarineSqr / flWithinDistSqr)) * 1.0f) );
	}
}