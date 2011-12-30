#include "cbase.h"
#include "ASW_Horde_Mode.h"
#include "convar.h"
#include "asw_spawn_manager.h"

#include "memdbgon.h"

//LINK_ENTITY_TO_CLASS( asw_horde_mode, CASW_Horde_Mode );

//Ch1ckensCoop: External convars we need to have control over
extern ConVar asw_horde_class;
extern ConVar asw_horde_override;
extern ConVar asw_horde_size_min;
extern ConVar asw_horde_size_max;

//Ch1ckensCoop: Core hordemode settings.
ConVar asw_hordemode("asw_hordemode", "0", FCVAR_CHEAT, "Enables hordemode on the server.");
ConVar asw_hordemode_debug("asw_hordemode_debug", "0", FCVAR_CHEAT, "Show hordemode debug messages.");
ConVar asw_hordemode_update_mode("asw_hordemode_update_mode", "0", FCVAR_CHEAT, "0 - update after each horde spawn; >0 - Update every x seconds.");
ConVar asw_hordemode_mode("asw_hordemode_mode", "1", FCVAR_CHEAT, "0 = Health settings only; 1 = Binary + horde_size_max settings + health; 2 = Binary + horde_size_max settings");

//Ch1ckensCoop: Hordemode spawning settings
ConVar asw_hordemode_aliens("asw_hordemode_aliens", "65535", FCVAR_CHEAT, "Binary flag of allowed aliens. (65535 = all)");
//ConVar asw_hordemode_aliens_static("asw_hordemode_aliens_static", "0", FCVAR_CHEAT, "Single binary flag of aliens to spawn in static mode.");

//Ch1ckensCoop: Hordemode horde_size_max settings and alien health settings

//Drones
ConVar asw_hordemode_drone_max("asw_hordemode_drone_max", "1", FCVAR_CHEAT, "Maximum drones to spawn.");
ConVar asw_hordemode_drone_min("asw_hordemode_drone_min", "1", FCVAR_CHEAT, "Minimum drones to spawn.");
ConVar asw_hordemode_drone_health_max("asw_hordemode_drone_health_max", "50", FCVAR_CHEAT, "Maximum drone health.");
ConVar asw_hordemode_drone_health_min("asw_hordemode_drone_health_min", "25", FCVAR_CHEAT, "Minimum drone health.");

//Buzzers
ConVar asw_hordemode_buzzer_max("asw_hordemode_buzzer_max", "1", FCVAR_CHEAT, "Maximum buzzers to spawn.");
ConVar asw_hordemode_buzzer_min("asw_hordemode_buzzer_min", "1", FCVAR_CHEAT, "Minimum buzzers to spawn.");
ConVar asw_hordemode_buzzer_health_max("asw_hordemode_buzzer_health_max", "35", FCVAR_CHEAT, "Maximum buzzer health.");
ConVar asw_hordemode_buzzer_health_min("asw_hordemode_buzzer_health_min", "10", FCVAR_CHEAT, "Minimum buzzer health.");

//Parasites
ConVar asw_hordemode_parasite_max("asw_hordemode_parasite_max", "1", FCVAR_CHEAT, "Maximum parasites to spawn.");
ConVar asw_hordemode_parasite_min("asw_hordemode_parasite_min", "1", FCVAR_CHEAT, "Minimum parasites to spawn.");
ConVar asw_hordemode_parasite_health_max("asw_hordemode_parasite_health_max", "35", FCVAR_CHEAT, "Maximum parasite heatlh.");
ConVar asw_hordemode_parasite_health_min("asw_hordemode_parasite_health_min", "20", FCVAR_CHEAT, "Minimum parasite health.");

//Shieldbugs
ConVar asw_hordemode_shieldbug_max("asw_hordemode_shieldbug_max", "1", FCVAR_CHEAT, "Maximum shieldbugs to spawn.");
ConVar asw_hordemode_shieldbug_min("asw_hordemode_shieldbug_min", "1", FCVAR_CHEAT, "Minimum shieldbugs to spawn.");
ConVar asw_hordemode_shieldbug_health_max("asw_hordemode_shieldbug_health_max", "1500", FCVAR_CHEAT, "Maximum shieldbug heatlh.");
ConVar asw_hordemode_shieldbug_health_min("asw_hordemode_shieldbug_health_min", "750", FCVAR_CHEAT, "Minimum shieldbug health.");

//No grubs FFS.

//Drone Jumpers
ConVar asw_hordemode_drone_jumper_max("asw_hordemode_drone_jumper_max", "1", FCVAR_CHEAT, "Maximum drone jumpers to spawn.");
ConVar asw_hordemode_drone_jumper_min("asw_hordemode_drone_jumper_min", "1", FCVAR_CHEAT, "Minimum drone jumpers to spawn.");
ConVar asw_hordemode_drone_jumper_health_max("asw_hordemode_drone_jumper_health_max", "45", FCVAR_CHEAT, "Maximum drone jumper heatlh.");
ConVar asw_hordemode_drone_jumper_health_min("asw_hordemode_drone_jumper_health_min", "30", FCVAR_CHEAT, "Minimum drone jumper health.");

//Harvesters
ConVar asw_hordemode_harvester_max("asw_hordemode_harvester_max", "1", FCVAR_CHEAT, "Maximum harvesters to spawn.");
ConVar asw_hordemode_harvester_min("asw_hordemode_harvester_min", "1", FCVAR_CHEAT, "Minimum harvesters to spawn.");
ConVar asw_hordemode_harvester_health_max("asw_hordemode_harvester_health_max", "325", FCVAR_CHEAT, "Maximum harvester heatlh.");
ConVar asw_hordemode_harvester_health_min("asw_hordemode_harvester_health_min", "150", FCVAR_CHEAT, "Minimum harvester health.");

//Defanged parasites
ConVar asw_hordemode_parasite_safe_max("asw_hordemode_parasite_safe_max", "1", FCVAR_CHEAT, "Maximum defanged parasites to spawn.");
ConVar asw_hordemode_parasite_safe_min("asw_hordemode_parasite_safe_min", "1", FCVAR_CHEAT, "Minimum defanged parasites to spawn.");
ConVar asw_hordemode_parasite_safe_health_max("asw_hordemode_parasite_safe_health_max", "20", FCVAR_CHEAT, "Maximum defanged parasite heatlh.");
ConVar asw_hordemode_parasite_safe_health_min("asw_hordemode_parasite_safe_health_min", "10", FCVAR_CHEAT, "Minimum defanged parasite health.");

//Queen
ConVar asw_hordemode_queen_max("asw_hordemode_queen_max", "0", FCVAR_CHEAT, "Maximum queens to spawn.");
ConVar asw_hordemode_queen_min("asw_hordemode_queen_min", "0", FCVAR_CHEAT, "Minimum queens to spawn.");
ConVar asw_hordemode_queen_health_max("asw_hordemode_queen_health_max", "2500", FCVAR_CHEAT, "Maximum queen heatlh.");
ConVar asw_hordemode_queen_health_min("asw_hordemode_queen_health_min", "1000", FCVAR_CHEAT, "Minimum queen health.");

//Boomers
ConVar asw_hordemode_boomer_max("asw_hordemode_boomer_max", "1", FCVAR_CHEAT, "Maximum boomers to spawn.");
ConVar asw_hordemode_boomer_min("asw_hordemode_boomer_min", "1", FCVAR_CHEAT, "Minimum boomers to spawn.");
ConVar asw_hordemode_boomer_health_max("asw_hordemode_boomer_health_max", "900", FCVAR_CHEAT, "Maximum boomer heatlh.");
ConVar asw_hordemode_boomer_health_min("asw_hordemode_boomer_health_min", "750", FCVAR_CHEAT, "Minimum boomer health.");

//Rangers
ConVar asw_hordemode_ranger_max("asw_hordemode_ranger_max", "1", FCVAR_CHEAT, "Maximum rangers to spawn.");
ConVar asw_hordemode_ranger_min("asw_hordemode_ranger_min", "1", FCVAR_CHEAT, "Minimum rangers to spawn.");
ConVar asw_hordemode_ranger_health_max("asw_hordemode_ranger_health_max", "125", FCVAR_CHEAT, "Maximum ranger heatlh.");
ConVar asw_hordemode_ranger_health_min("asw_hordemode_ranger_health_min", "75", FCVAR_CHEAT, "Minimum ranger health.");

//Mortars
ConVar asw_hordemode_mortar_max("asw_hordemode_mortar_max", "1", FCVAR_CHEAT, "Maximum mortars to spawn.");
ConVar asw_hordemode_mortar_min("asw_hordemode_mortar_min", "1", FCVAR_CHEAT, "Minimum mortars to spawn.");
ConVar asw_hordemode_mortar_health_max("asw_hordemode_mortar_health_max", "425", FCVAR_CHEAT, "Maximum mortar heatlh.");
ConVar asw_hordemode_mortar_health_min("asw_hordemode_mortar_health_min", "300", FCVAR_CHEAT, "Minimum mortar health.");

//Shamen
ConVar asw_hordemode_shaman_max("asw_hordemode_shaman_max", "1", FCVAR_CHEAT, "Maximum shamans to spawn.");
ConVar asw_hordemode_shaman_min("asw_hordemode_shaman_min", "1", FCVAR_CHEAT, "Minimum shamans to spawn.");
ConVar asw_hordemode_shaman_health_max("asw_hordemode_shaman_health_max", "80", FCVAR_CHEAT, "Maximum shaman heatlh.");
ConVar asw_hordemode_shaman_health_min("asw_hordemode_shaman_health_min", "45", FCVAR_CHEAT, "Minimum shaman health.");

//Uber Drones
ConVar asw_hordemode_drone_uber_max("asw_hordemode_drone_uber_max", "1", FCVAR_CHEAT, "Maximum uber drones to spawn.");
ConVar asw_hordemode_drone_uber_min("asw_hordemode_drone_uber_min", "1", FCVAR_CHEAT, "Minimum uber drones to spawn.");
ConVar asw_hordemode_drone_uber_health_max("asw_hordemode_drone_uber_health_max", "350", FCVAR_CHEAT, "Maximum uber drone heatlh.");
ConVar asw_hordemode_drone_uber_health_min("asw_hordemode_drone_uber_health_min", "275", FCVAR_CHEAT, "Minimum uber drone health.");

//Beta Drones
ConVar asw_hordemode_drone_beta_max("asw_hordemode_drone_beta_max", "1", FCVAR_CHEAT, "Maximum beta drones to spawn.");
ConVar asw_hordemode_drone_beta_min("asw_hordemode_drone_beta_min", "1", FCVAR_CHEAT, "Minimum beta drones to spawn.");
ConVar asw_hordemode_drone_beta_health_max("asw_hordemode_drone_beta_health_max", "50", FCVAR_CHEAT, "Maximum beta drone heatlh.");
ConVar asw_hordemode_drone_beta_health_min("asw_hordemode_drone_beta_health_min", "25", FCVAR_CHEAT, "Minimum beta drone health.");

//Beta Shieldbugs
ConVar asw_hordemode_shieldbug_beta_max("asw_hordemode_shieldbug_beta_max", "0", FCVAR_CHEAT, "Maximum beta shieldbugs to spawn.");
ConVar asw_hordemode_shieldbug_beta_min("asw_hordemode_shieldbug_beta_min", "0", FCVAR_CHEAT, "Minimum beta shieldbugs to spawn.");
ConVar asw_hordemode_shieldbug_beta_health_max("asw_hordemode_shieldbug_beta_health_max", "1500", FCVAR_CHEAT, "Maximum beta shieldbug heatlh.");
ConVar asw_hordemode_shieldbug_beta_health_min("asw_hordemode_shieldbug_beta_health_min", "750", FCVAR_CHEAT, "Minimum beta shieldbug health.");

//Beta Harvesters
ConVar asw_hordemode_harvester_beta_max("asw_hordemode_harvester_beta_max", "1", FCVAR_CHEAT, "Maximum beta harvesters to spawn.");
ConVar asw_hordemode_harvester_beta_min("asw_hordemode_harvester_beta_min", "1", FCVAR_CHEAT, "Minimum beta harvesters to spawn.");
ConVar asw_hordemode_harvester_beta_health_max("asw_hordemode_harvester_beta_health_max", "325", FCVAR_CHEAT, "Maximum beta harvester heatlh.");
ConVar asw_hordemode_harvester_beta_health_min("asw_hordemode_harvester_beta_health_min", "150", FCVAR_CHEAT, "Minimum beta harvester health.");

CASW_Horde_Mode g_ASWHordeMode = CASW_Horde_Mode();
CASW_Horde_Mode* ASWHordeMode() 
{
	return &g_ASWHordeMode;
}

CASW_Horde_Mode::CASW_Horde_Mode()
{

}

CASW_Horde_Mode::~CASW_Horde_Mode()
{
	
}

void CASW_Horde_Mode::LevelInitPostEntity()
{
	//Init();
}

bool CASW_Horde_Mode::Init()
{
	//BaseClass::Spawn();

	i_LastAlienClass = 1;

	InitAlienData();
	UpdateHordeMode();
	fl_LastThinkTime = gpGlobals->curtime;

	return true;
}

void CASW_Horde_Mode::HordeFinishedSpawning()
{
	//Ch1ckensCoop: For now, all we have to do is think.
	if (asw_hordemode_debug.GetBool())
		Msg("Horde finished... updating horde mode!\n");

	if (asw_hordemode_update_mode.GetFloat() == 0)
	{
		if (asw_hordemode_mode.GetInt() == 1)
			UpdateHordeMode();
		else if (asw_hordemode_mode.GetInt() == 0)
			RandomizeHealth();
	}
}

void CASW_Horde_Mode::FrameUpdatePostEntityThink()
{
	if (!asw_hordemode.GetBool())
		return;

	asw_horde_override.SetValue(1);

	float thinkRate = asw_hordemode_update_mode.GetFloat();
	if (thinkRate > 0 && fl_LastThinkTime <= gpGlobals->curtime)	//Check if we're actually supposed to be updating on a timed basis.
	{
		UpdateHordeMode();
		fl_LastThinkTime = gpGlobals->curtime + thinkRate;
	}
}

void CASW_Horde_Mode::UpdateHordeMode()
{	
	if (asw_hordemode_debug.GetBool())
		Msg("Updating hordemode!\n");

	//Ch1ckensCoop: Turn off beta if it was on for the previous alien.
	if (AlienInfoArray[i_LastAlienClass].isBeta)
	{
		if (!AlienInfoArray[i_LastAlienClass].betaAlienConVar->GetLinkedConVar())
			Warning("Bad beta convar for alien class flag %i!\n", i_LastAlienClass);
		if (!AlienInfoArray[i_LastAlienClass].betaAlienCvarReversed)
			AlienInfoArray[i_LastAlienClass].betaAlienConVar->SetValue(1);
		else
			AlienInfoArray[i_LastAlienClass].betaAlienConVar->SetValue(0);
		
		if (asw_hordemode_debug.GetBool())
			Msg("Disabled beta spawning for %s.\n", AlienInfoArray[i_LastAlienClass].pAlienClassName);
	}
	
	//Ch1ckensCoop: Select the next random alien
	int alienIndex = GetRandomValidAlien();

	if (asw_hordemode_debug.GetBool())
		Msg("Alien index is %i.\n", alienIndex);

	const char *alienClassName = AlienInfoArray[alienIndex].pAlienClassName;
	//ConVarRef alienHealthMax = AlienInfoArray[alienIndex].healthMax;
	//ConVarRef alienHealthMin = AlienInfoArray[alienIndex].healthMin;
	ConVarRef *alienMax = AlienInfoArray[alienIndex].max;
	ConVarRef *alienMin = AlienInfoArray[alienIndex].min;
	ConVarRef *alienHealthCvar = AlienInfoArray[alienIndex].alienHealthCvar;
	ConVarRef *alienBetaCvar = AlienInfoArray[alienIndex].betaAlienConVar;
	bool alienBetaCvarReversed = AlienInfoArray[alienIndex].betaAlienCvarReversed;
	bool alienIsBeta = AlienInfoArray[alienIndex].isBeta;


	asw_horde_size_max.SetValue(alienMax->GetInt());
	asw_horde_size_min.SetValue(alienMin->GetInt());

	int mode = asw_hordemode_mode.GetInt();
	if (mode == 0 || mode == 1)
		RandomizeHealth();

	if (alienIsBeta && alienBetaCvar->GetLinkedConVar())
	{
		if (!alienBetaCvarReversed)
			alienBetaCvar->SetValue(0);
		else
			alienBetaCvar->SetValue(1);
	}
	else if (!alienIsBeta && alienBetaCvar->GetLinkedConVar())
	{
		if (!alienBetaCvarReversed)
			alienBetaCvar->SetValue(1);
		else
			alienBetaCvar->SetValue(0);
	}

	//Finally, set the classname and we're ready to go!
	asw_horde_class.SetValue(alienClassName);
	if (asw_hordemode_debug.GetBool())
	{
		const char *boolText;
		if (alienIsBeta)
			boolText = "true";
		else
			boolText = "false";

		engine->Con_NPrintf( 19, "Hordemode set alien class to %s, health to %i, isBeta = %s.\n", alienClassName, alienHealthCvar->GetInt(), boolText);
		Msg("Hordemode set alien class to %s, health to %i, isBeta = %s.\n", alienClassName, alienHealthCvar->GetInt(), boolText);
	}
}

int CASW_Horde_Mode::GetRandomValidAlien()
{
	int alienNum = 1;
	int allowedAliens = asw_hordemode_aliens.GetInt();
	int alienMax = 0;
	do 
	{
		alienNum = RandomInt(0, HIGHEST_INDEX - 1);
		
		if (asw_hordemode_debug.GetInt() == 2)
			Msg("Hordemode: alienNum = %i\n", alienNum);

		alienMax = AlienInfoArray[alienNum].max->GetInt();
	}
	while ((allowedAliens & AlienInfoArray[alienNum].flag) == 0 || (alienMax == 0));
	i_LastAlienClass = alienNum;
	return alienNum;
}

void CASW_Horde_Mode::RandomizeHealth(int alienNum)
{
	if (!(FStrEq(AlienInfoArray[alienNum].pAlienClassName, "asw_queen") && AlienInfoArray[alienNum].max->GetInt() == 0))
		AlienInfoArray[alienNum].alienHealthCvar->SetValue(RandomInt(AlienInfoArray[alienNum].healthMin->GetInt(), AlienInfoArray[alienNum].healthMax->GetInt()));
}

void CASW_Horde_Mode::RandomizeHealth()
{
	for (int i = 0; i < HIGHEST_INDEX; i++)
	{
		AlienInfoArray[i].alienHealthCvar->SetValue(RandomInt(AlienInfoArray[i].healthMin->GetInt(), AlienInfoArray[i].healthMax->GetInt()));
	}
}

void CASW_Horde_Mode::InitAlienData()
{
	//Alien Classnames
	AlienInfoArray[DRONE_INDEX].pAlienClassName = "asw_drone";
	AlienInfoArray[BUZZER_INDEX].pAlienClassName = "asw_buzzer";
	AlienInfoArray[PARASITE_INDEX].pAlienClassName = "asw_parasite";
	AlienInfoArray[SHIELDBUG_INDEX].pAlienClassName = "asw_shieldbug";
	AlienInfoArray[JUMPER_INDEX].pAlienClassName = "asw_drone_jumper";
	AlienInfoArray[HARVESTER_INDEX].pAlienClassName = "asw_harvester";
	AlienInfoArray[PARASITE_DEFANGED_INDEX].pAlienClassName = "asw_parasite_defanged";
	AlienInfoArray[QUEEN_INDEX].pAlienClassName = "asw_queen";
	AlienInfoArray[BOOMER_INDEX].pAlienClassName = "asw_boomer";
	AlienInfoArray[RANGER_INDEX].pAlienClassName = "asw_ranger";
	AlienInfoArray[MORTAR_INDEX].pAlienClassName = "asw_mortarbug";
	AlienInfoArray[SHAMAN_INDEX].pAlienClassName = "asw_shaman";
	AlienInfoArray[UBER_INDEX].pAlienClassName = "asw_drone_uber";
	AlienInfoArray[BETA_DRONE_INDEX].pAlienClassName = "asw_drone";
	AlienInfoArray[BETA_SHIELDBUG_INDEX].pAlienClassName = "asw_shieldbug";
	AlienInfoArray[BETA_HARVESTER_INDEX].pAlienClassName = "asw_harvester";

	//Alien Flags
	AlienInfoArray[DRONE_INDEX].flag = 1;
	AlienInfoArray[BUZZER_INDEX].flag = 2;
	AlienInfoArray[PARASITE_INDEX].flag = 4;
	AlienInfoArray[SHIELDBUG_INDEX].flag = 8;
	AlienInfoArray[JUMPER_INDEX].flag = 16;
	AlienInfoArray[HARVESTER_INDEX].flag = 32;
	AlienInfoArray[PARASITE_DEFANGED_INDEX].flag = 64;
	AlienInfoArray[QUEEN_INDEX].flag = 128;
	AlienInfoArray[BOOMER_INDEX].flag = 256;
	AlienInfoArray[RANGER_INDEX].flag = 512;
	AlienInfoArray[MORTAR_INDEX].flag = 1024;
	AlienInfoArray[SHAMAN_INDEX].flag = 2048;
	AlienInfoArray[UBER_INDEX].flag = 4096;
	AlienInfoArray[BETA_DRONE_INDEX].flag = 8192;
	AlienInfoArray[BETA_SHIELDBUG_INDEX].flag = 16384;
	AlienInfoArray[BETA_HARVESTER_INDEX].flag = 32768;

	//Beta Alien Flags
	AlienInfoArray[DRONE_INDEX].betaAlienConVar = new ConVarRef("asw_new_drone");

	AlienInfoArray[SHIELDBUG_INDEX].betaAlienConVar = new ConVarRef("asw_old_shieldbug");
	AlienInfoArray[SHIELDBUG_INDEX].betaAlienCvarReversed = true;

	AlienInfoArray[HARVESTER_INDEX].betaAlienConVar = new ConVarRef("asw_harvester_new");
	


	AlienInfoArray[BETA_DRONE_INDEX].betaAlienConVar = new ConVarRef("asw_new_drone");
	AlienInfoArray[BETA_DRONE_INDEX].isBeta = true;

	AlienInfoArray[BETA_SHIELDBUG_INDEX].betaAlienConVar = new ConVarRef("asw_old_shieldbug");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].betaAlienCvarReversed = true;
	AlienInfoArray[BETA_SHIELDBUG_INDEX].isBeta = true;

	AlienInfoArray[BETA_HARVESTER_INDEX].betaAlienConVar = new ConVarRef("asw_harvester_new");
	AlienInfoArray[BETA_HARVESTER_INDEX].isBeta = true;

	//Non beta alien flags
	AlienInfoArray[DRONE_INDEX].isBeta = false;
	AlienInfoArray[BUZZER_INDEX].isBeta = false;
	AlienInfoArray[PARASITE_INDEX].isBeta = false;
	AlienInfoArray[SHIELDBUG_INDEX].isBeta = false;
	AlienInfoArray[JUMPER_INDEX].isBeta = false;
	AlienInfoArray[HARVESTER_INDEX].isBeta = false;
	AlienInfoArray[PARASITE_DEFANGED_INDEX].isBeta = false;
	AlienInfoArray[QUEEN_INDEX].isBeta = false;
	AlienInfoArray[BOOMER_INDEX].isBeta = false;
	AlienInfoArray[RANGER_INDEX].isBeta = false;
	AlienInfoArray[MORTAR_INDEX].isBeta = false;
	AlienInfoArray[SHAMAN_INDEX].isBeta = false;
	AlienInfoArray[UBER_INDEX].isBeta = false;


	//Alien Maximum Healths
	AlienInfoArray[DRONE_INDEX].healthMax = new ConVarRef("asw_hordemode_drone_health_max");
	AlienInfoArray[BUZZER_INDEX].healthMax = new ConVarRef("asw_hordemode_buzzer_health_max");
	AlienInfoArray[PARASITE_INDEX].healthMax = new ConVarRef("asw_hordemode_parasite_health_max");
	AlienInfoArray[SHIELDBUG_INDEX].healthMax = new ConVarRef("asw_hordemode_shieldbug_health_max");
	AlienInfoArray[JUMPER_INDEX].healthMax = new ConVarRef("asw_hordemode_drone_jumper_health_max");
	AlienInfoArray[HARVESTER_INDEX].healthMax = new ConVarRef("asw_hordemode_harvester_health_max");
	AlienInfoArray[PARASITE_DEFANGED_INDEX].healthMax = new ConVarRef("asw_hordemode_parasite_safe_health_max");
	AlienInfoArray[QUEEN_INDEX].healthMax = new ConVarRef("asw_hordemode_queen_health_max");
	AlienInfoArray[BOOMER_INDEX].healthMax = new ConVarRef("asw_hordemode_boomer_health_max");
	AlienInfoArray[RANGER_INDEX].healthMax = new ConVarRef("asw_hordemode_ranger_health_max");
	AlienInfoArray[MORTAR_INDEX].healthMax = new ConVarRef("asw_hordemode_mortar_health_max");
	AlienInfoArray[SHAMAN_INDEX].healthMax = new ConVarRef("asw_hordemode_shaman_health_max");
	AlienInfoArray[UBER_INDEX].healthMax = new ConVarRef("asw_hordemode_drone_uber_health_max");
	AlienInfoArray[BETA_DRONE_INDEX].healthMax = new ConVarRef("asw_hordemode_drone_beta_health_max");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].healthMax = new ConVarRef("asw_hordemode_shieldbug_beta_health_max");
	AlienInfoArray[BETA_HARVESTER_INDEX].healthMax = new ConVarRef("asw_hordemode_harvester_beta_health_max");

	//Alien Minimum Healths
	AlienInfoArray[DRONE_INDEX].healthMin = new ConVarRef("asw_hordemode_drone_health_min");
	AlienInfoArray[BUZZER_INDEX].healthMin = new ConVarRef("asw_hordemode_buzzer_health_min");
	AlienInfoArray[PARASITE_INDEX].healthMin = new ConVarRef("asw_hordemode_parasite_health_min");
	AlienInfoArray[SHIELDBUG_INDEX].healthMin = new ConVarRef("asw_hordemode_shieldbug_health_min");
	AlienInfoArray[JUMPER_INDEX].healthMin = new ConVarRef("asw_hordemode_drone_jumper_health_min");
	AlienInfoArray[HARVESTER_INDEX].healthMin = new ConVarRef("asw_hordemode_harvester_health_min");
	AlienInfoArray[PARASITE_DEFANGED_INDEX].healthMin = new ConVarRef("asw_hordemode_parasite_safe_health_min");
	AlienInfoArray[QUEEN_INDEX].healthMin = new ConVarRef("asw_hordemode_queen_health_min");
	AlienInfoArray[BOOMER_INDEX].healthMin = new ConVarRef("asw_hordemode_boomer_health_min");
	AlienInfoArray[RANGER_INDEX].healthMin = new ConVarRef("asw_hordemode_ranger_health_min");
	AlienInfoArray[MORTAR_INDEX].healthMin = new ConVarRef("asw_hordemode_mortar_health_min");
	AlienInfoArray[SHAMAN_INDEX].healthMin = new ConVarRef("asw_hordemode_shaman_health_min");
	AlienInfoArray[UBER_INDEX].healthMin = new ConVarRef("asw_hordemode_drone_uber_health_min");
	AlienInfoArray[BETA_DRONE_INDEX].healthMin = new ConVarRef("asw_hordemode_drone_beta_health_max");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].healthMin = new ConVarRef("asw_hordemode_shieldbug_beta_health_min");
	AlienInfoArray[BETA_HARVESTER_INDEX].healthMin = new ConVarRef("asw_hordemode_harvester_beta_health_min");

	//Alien Maximums
	AlienInfoArray[DRONE_INDEX].max = new ConVarRef("asw_hordemode_drone_max");
	AlienInfoArray[BUZZER_INDEX].max = new ConVarRef("asw_hordemode_buzzer_max");
	AlienInfoArray[PARASITE_INDEX].max = new ConVarRef("asw_hordemode_parasite_max");
	AlienInfoArray[SHIELDBUG_INDEX].max = new ConVarRef("asw_hordemode_shieldbug_max");
	AlienInfoArray[JUMPER_INDEX].max = new ConVarRef("asw_hordemode_drone_jumper_max");
	AlienInfoArray[HARVESTER_INDEX].max = new ConVarRef("asw_hordemode_harvester_max");
	AlienInfoArray[PARASITE_DEFANGED_INDEX].max = new ConVarRef("asw_hordemode_parasite_safe_max");
	AlienInfoArray[QUEEN_INDEX].max = new ConVarRef("asw_hordemode_queen_max");
	AlienInfoArray[BOOMER_INDEX].max = new ConVarRef("asw_hordemode_boomer_max");
	AlienInfoArray[RANGER_INDEX].max = new ConVarRef("asw_hordemode_ranger_max");
	AlienInfoArray[MORTAR_INDEX].max = new ConVarRef("asw_hordemode_mortar_max");
	AlienInfoArray[SHAMAN_INDEX].max = new ConVarRef("asw_hordemode_shaman_max");
	AlienInfoArray[UBER_INDEX].max = new ConVarRef("asw_hordemode_drone_uber_max");
	AlienInfoArray[BETA_DRONE_INDEX].max = new ConVarRef("asw_hordemode_drone_beta_max");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].max = new ConVarRef("asw_hordemode_shieldbug_beta_max");
	AlienInfoArray[BETA_HARVESTER_INDEX].max = new ConVarRef("asw_hordemode_harvester_beta_max");

	//Alien Minimums
	AlienInfoArray[DRONE_INDEX].min = new ConVarRef("asw_hordemode_drone_min");
	AlienInfoArray[BUZZER_INDEX].min = new ConVarRef("asw_hordemode_buzzer_min");
	AlienInfoArray[PARASITE_INDEX].min = new ConVarRef("asw_hordemode_parasite_min");
	AlienInfoArray[SHIELDBUG_INDEX].min = new ConVarRef("asw_hordemode_shieldbug_min");
	AlienInfoArray[JUMPER_INDEX].min = new ConVarRef("asw_hordemode_drone_jumper_min");
	AlienInfoArray[HARVESTER_INDEX].min = new ConVarRef("asw_hordemode_harvester_min");
	AlienInfoArray[PARASITE_DEFANGED_INDEX].min = new ConVarRef("asw_hordemode_parasite_safe_min");
	AlienInfoArray[QUEEN_INDEX].min = new ConVarRef("asw_hordemode_queen_min");
	AlienInfoArray[BOOMER_INDEX].min = new ConVarRef("asw_hordemode_boomer_min");
	AlienInfoArray[RANGER_INDEX].min = new ConVarRef("asw_hordemode_ranger_min");
	AlienInfoArray[MORTAR_INDEX].min = new ConVarRef("asw_hordemode_mortar_min");
	AlienInfoArray[SHAMAN_INDEX].min = new ConVarRef("asw_hordemode_shaman_min");
	AlienInfoArray[UBER_INDEX].min = new ConVarRef("asw_hordemode_drone_uber_min");
	AlienInfoArray[BETA_DRONE_INDEX].min = new ConVarRef("asw_hordemode_drone_beta_min");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].min = new ConVarRef("asw_hordemode_shieldbug_beta_min");
	AlienInfoArray[BETA_HARVESTER_INDEX].min = new ConVarRef("asw_hordemode_harvester_beta_min");

	//Alien Health Cvar ConVarRefs
	AlienInfoArray[DRONE_INDEX].alienHealthCvar = new ConVarRef("asw_drone_health");
	AlienInfoArray[BUZZER_INDEX].alienHealthCvar = new ConVarRef("sk_asw_buzzer_health");
	AlienInfoArray[PARASITE_INDEX].alienHealthCvar = new ConVarRef("asw_parasite_health");
	AlienInfoArray[SHIELDBUG_INDEX].alienHealthCvar = new ConVarRef("asw_shieldbug_health");
	AlienInfoArray[JUMPER_INDEX].alienHealthCvar = new ConVarRef("asw_drone_jumper_health");
	AlienInfoArray[HARVESTER_INDEX].alienHealthCvar = new ConVarRef("asw_harvester_health");
	AlienInfoArray[PARASITE_DEFANGED_INDEX].alienHealthCvar = new ConVarRef("asw_parasite_defanged_health");
	AlienInfoArray[QUEEN_INDEX].alienHealthCvar = new ConVarRef("asw_queen_override_health");
	AlienInfoArray[BOOMER_INDEX].alienHealthCvar = new ConVarRef("asw_boomer_health");
	AlienInfoArray[RANGER_INDEX].alienHealthCvar = new ConVarRef("asw_ranger_health");
	AlienInfoArray[MORTAR_INDEX].alienHealthCvar = new ConVarRef("asw_mortarbug_health");
	AlienInfoArray[SHAMAN_INDEX].alienHealthCvar = new ConVarRef("asw_shaman_health");
	AlienInfoArray[UBER_INDEX].alienHealthCvar = new ConVarRef("asw_drone_uber_health");
	AlienInfoArray[BETA_DRONE_INDEX].alienHealthCvar = new ConVarRef("asw_drone_health");
	AlienInfoArray[BETA_SHIELDBUG_INDEX].alienHealthCvar = new ConVarRef("asw_shieldbug_health");
	AlienInfoArray[BETA_HARVESTER_INDEX].alienHealthCvar = new ConVarRef("asw_harvester_health");
}