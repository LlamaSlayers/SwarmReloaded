#include "cbase.h"
#include "asw_objective_counter.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// An objective controlled by mapper inputs

LINK_ENTITY_TO_CLASS( asw_objective_counter, CASW_Objective_Counter );

BEGIN_DATADESC( CASW_Objective_Counter )
	DEFINE_KEYFIELD( m_iTargetCount, FIELD_INTEGER, "NumRequired" ),
	DEFINE_FIELD( m_iCurrentCount, FIELD_INTEGER ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Add", InputAdd ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Subtract", InputSubtract ),
	DEFINE_INPUTFUNC( FIELD_VOID, "SetFailed", InputSetFailed ),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CASW_Objective_Counter, DT_ASW_Objective_Counter)
	SendPropInt		(SENDINFO(m_iTargetCount)),
	SendPropInt		(SENDINFO(m_iCurrentCount)),
END_SEND_TABLE()

CASW_Objective_Counter::CASW_Objective_Counter() : CASW_Objective()
{

}


CASW_Objective_Counter::~CASW_Objective_Counter()
{
}

void CASW_Objective_Counter::InputAdd( inputdata_t &inputdata )
{
	m_iCurrentCount++;

	if ( m_iCurrentCount.Get() >= m_iTargetCount.Get() )
	{
		m_iCurrentCount = m_iTargetCount.Get();
		SetComplete(true);
	}
}

void CASW_Objective_Counter::InputSubtract( inputdata_t &inputdata )
{
	SetComplete(false);

	m_iCurrentCount--;
	if ( m_iCurrentCount.Get() < 0 )
		m_iCurrentCount = 0;
}

void CASW_Objective_Counter::InputSetFailed( inputdata_t &inputdata )
{
	SetFailed(true);
}