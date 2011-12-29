//--------------------------------------------------------------------------------------------------------
// Copyright (c) 2007 Turtle Rock Studios, Inc.

#include "cbase.h"
#include "c_basetoggle.h"
#include "c_asw_player.h"
#include "c_asw_marine.h"
#include "asw_input.h"
#include <vgui/ISurface.h>
#include <vgui_controls/Panel.h>
#include <vgui/ILocalize.h>
#include "asw_util_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT( C_BaseToggle, DT_BaseToggle, CBaseToggle )
END_RECV_TABLE()


//--------------------------------------------------------------------------------------------------------
// Returns the velocity imparted to players standing on us.
void C_BaseToggle::GetGroundVelocityToApply( Vector &vecGroundVel )
{
	vecGroundVel = GetLocalVelocity();
	vecGroundVel.z = 0.0f; // don't give upward velocity, or it could predict players into the air.
}


int C_BaseButton::s_nUseActionIconTextureID = -1;

//--------------------------------------------------------------------------------------------------------
IMPLEMENT_CLIENTCLASS_DT( C_BaseButton, DT_BaseButton, CBaseButton )
	RecvPropBool( RECVINFO( m_usable ) ),
END_RECV_TABLE()

C_BaseButton::C_BaseButton( void ) :
	m_GlowObject( this, Vector( 0.0f, 0.4f, 0.75f ), 1.0f, false, true )
{
	if (s_nUseActionIconTextureID == -1)
	{
		s_nUseActionIconTextureID = vgui::surface()->CreateNewTextureID();		
		vgui::surface()->DrawSetTextureFile( s_nUseActionIconTextureID, "vgui/swarm/UseIcons/PanelUnlocked", true, false);
	}
}

//--------------------------------------------------------------------------------------------------------
bool C_BaseButton::IsPotentiallyUsable( void )
{
	return true;
}

bool C_BaseButton::GetUseAction(ASWUseAction &action, C_ASW_Marine *pUser)
{
	action.UseTarget = this;

	TryLocalize( "#asw_use_panel", action.wszText, sizeof( action.wszText ) );
	action.iUseIconTexture = s_nUseActionIconTextureID;

	action.fProgress = -1;

	action.UseIconRed = 255;
	action.UseIconGreen = 255;
	action.UseIconBlue = 255;
	action.bShowUseKey = true;
	action.iInventorySlot = -1;

	return true;
}

bool C_BaseButton::IsUsable(C_BaseEntity *pUser)
{
	return (pUser && pUser->GetAbsOrigin().DistTo(GetAbsOrigin()) < ASW_MARINE_USE_RADIUS);	// near enough?
}

void C_BaseButton::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );

	if ( updateType == DATA_UPDATE_CREATED )
	{
		SetNextClientThink( CLIENT_THINK_ALWAYS );
	}
}

void C_BaseButton::ClientThink()
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

	m_GlowObject.SetRenderFlags( false, bShouldGlow );

	if ( m_GlowObject.IsRendering() )
	{
		m_GlowObject.SetAlpha( MIN( 0.7f, (1.0f - (flDistanceToMarineSqr / flWithinDistSqr)) * 1.0f) );
	}
}