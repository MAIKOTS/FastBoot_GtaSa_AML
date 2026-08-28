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
	// 1. Aplica o patch seguro da EULA no libSCAnd.so (mesma lógica do AcceptEULA)
	if(g_pLibSCAnd)
	{
		pEULAAccepted = cfg->Bind("AcceptEULA", true);
		
		// Nota: Certifique-se de que o offset 0x31C149 corresponde à versão do libSCAnd.so que você usa
		aml->Unprot(g_pLibSCAnd + 0x31C149, 1);
		*(bool*)(g_pLibSCAnd + 0x31C149) = true;
		
		cfg->Save();

		// Se quiser manter a rotina antiga de remoção do social club caso exista no seu socialclub.hpp
		if(RemoveSocialClub) {
			RemoveSocialClub();
		}
	}

	// 2. Inicia o modo configurado (ex: carregar save game direto)
	if(g_pLibGTASA)
	{
		StartMode(startMode, slotList);
	}
}
