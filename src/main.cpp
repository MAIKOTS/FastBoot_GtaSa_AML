#include <mod/amlmod.h>
#include <mod/config.h>

#include "main.hpp"
#include "socialclub.hpp"
#include "startmode.hpp"

MYMODCFG(net.deviceblack.fastboot, FastBoot, 3.1.0.5, DeviceBlack);
NEEDGAME(com.rockstargames.gtasa)

uintptr_t g_pLibSCAnd = 0;
uintptr_t g_pLibGTASA = 0;

ConfigEntry* pEULAAccepted;
bool showVersion = true;
char startMode[16];
char slotList[128];

ON_MOD_PRELOAD()
{
	g_pLibSCAnd = aml->GetLib("libSCAnd.so");
	g_pLibGTASA = aml->GetLib("libGTASA.so");

	showVersion = cfg->GetBool("Show Version", showVersion);
	
	cfg->GetString(startMode, sizeof(startMode), "Start Mode", "auto");
	cfg->GetString(slotList, sizeof(slotList), "Slot List", "GTASAsf10.b GTASAsf9.b");
}

ON_MOD_LOAD()
{
	if(g_pLibSCAnd)
	{
		pEULAAccepted = cfg->Bind("AcceptEULA", true);
		
		uintptr_t eulaPatchAddress = g_pLibSCAnd + 0x31C149;
		aml->Unprot(eulaPatchAddress, 1);
		*(bool*)(eulaPatchAddress) = true;
		
		cfg->Save();

		// Executa a rotina do socialclub de forma direta
		RemoveSocialClub();
	}

	if(g_pLibGTASA)
	{
		StartMode(startMode, slotList);
	}
}
