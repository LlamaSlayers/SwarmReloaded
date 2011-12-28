#ifndef _INCLUDED_ASW_OBJECTIVE_COUNTER_H
#define _INCLUDED_ASW_OBJECTIVE_COUNTER_H
#pragma once

#include "asw_objective.h"

// An objective controlled by mapper inputs

class CASW_Objective_Counter : public CASW_Objective
{
public:
	DECLARE_CLASS( CASW_Objective_Counter, CASW_Objective );
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

	CASW_Objective_Counter();
	virtual ~CASW_Objective_Counter();

	// inputs
	void InputAdd( inputdata_t &inputdata );
	void InputSubtract( inputdata_t &inputdata );
	void InputSetFailed( inputdata_t &inputdata );

	CNetworkVar(int, m_iTargetCount);
	CNetworkVar(int, m_iCurrentCount);
};

#endif /* _INCLUDED_ASW_OBJECTIVE_COUNTER_H */