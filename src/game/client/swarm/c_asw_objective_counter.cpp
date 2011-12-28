#include "cbase.h"
#include "c_asw_objective_counter.h"
#include <vgui/ILocalize.h>
#include <vgui_controls/Panel.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT(C_ASW_Objective_Counter, DT_ASW_Objective_Counter, CASW_Objective_Counter)
	RecvPropInt		(RECVINFO(m_iTargetCount)),
	RecvPropInt		(RECVINFO(m_iCurrentCount)),
END_RECV_TABLE()

C_ASW_Objective_Counter::C_ASW_Objective_Counter()
{
	m_dest_buffer[0] = '\0';
	m_iCountLeft = -1;
}

bool C_ASW_Objective_Counter::NeedsTitleUpdate()
{	
	int iCountLeft = m_iTargetCount - m_iCurrentCount;
	if (iCountLeft == 0)
		iCountLeft = m_iTargetCount;
	return (iCountLeft != m_iCountLeft);
}

const wchar_t* C_ASW_Objective_Counter::GetObjectiveTitle()
{
	int iCount = MIN( m_iTargetCount.Get(), m_iCurrentCount.Get() );

	if ( iCount != m_iCountLeft )	// update the string
	{
		m_iCountLeft = iCount;
		char buf[32];
		Q_snprintf(buf, sizeof(buf), "%s (%d/%d)", BaseClass::GetObjectiveTitle(), iCount, m_iTargetCount);
		g_pVGuiLocalize->ConvertANSIToUnicode(buf, m_dest_buffer, sizeof( m_dest_buffer ));
	}
	return m_dest_buffer;
}

float C_ASW_Objective_Counter::GetObjectiveProgress()
{
	if ( m_iTargetCount <= 0 )
		return BaseClass::GetObjectiveProgress();

	float flProgress = (float) m_iCurrentCount.Get() / (float) m_iTargetCount.Get();
	flProgress = clamp<float>( flProgress, 0.0f, 1.0f );

	return flProgress;
}