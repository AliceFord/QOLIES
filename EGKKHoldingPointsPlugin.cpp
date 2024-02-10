#include "pch.h"
#include "EGKKHoldingPointsPlugin.h"
#include "Constant.h"


#define FORCAP(G) for (const char* cap : G) {if (strcmp(dest, cap) == 0) {return true;}} break;


CEGKKHoldingPointsPlugin::CEGKKHoldingPointsPlugin(void) : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, "QOLIES", "1.0.0", "Alice Ford","GPL v3") {
	sendMessage("Hello!");

	/*RegisterTagItemType("EGKK Plugin HP", TAG_ITEM_EGKK_HP);
	RegisterTagItemType("EGKK Plugin LVL", TAG_ITEM_EGKK_LVL);*/
}

void CEGKKHoldingPointsPlugin::OnRefreshFpListContent(EuroScopePlugIn::CFlightPlanList AcList) {
	sendMessage("1");
}

CEGKKHoldingPointsPlugin::~CEGKKHoldingPointsPlugin() {
	sendMessage("Bye!");
}

/*void CEGKKHoldingPointsPlugin::OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
	EuroScopePlugIn::CRadarTarget RadarTarget,
	int ItemCode,
	int TagData,
	char sItemString[16],
	int* pColorCode,
	COLORREF* pRGB,
	double* pFontSize
) {

	char buf[] = {'a', 'a'};
	_itoa_s(ItemCode, buf, 10);
	sendMessage(buf);
	const char* cs = FlightPlan.GetCallsign();
	sendMessage(cs);
}*/

bool CEGKKHoldingPointsPlugin::OnCompileCommand(const char* sCommandLine) {
	if (strcmp(sCommandLine, ".handoff") == 0) {
		EuroScopePlugIn::CFlightPlan fp = FlightPlanSelectFirst();
		EuroScopePlugIn::CFlightPlanControllerAssignedData controllerData = fp.GetControllerAssignedData();
		const char* spad = controllerData.GetScratchPadString();
		if (fp.GetClearenceFlag()) controllerData.SetScratchPadString("CLEA");
		controllerData.SetScratchPadString(spad);
		
		
		while (strcmp((fp = FlightPlanSelectNext(fp)).GetCallsign(), "") != 0) {
			if (!fp.IsValid()) {
				continue;
			}

			controllerData = fp.GetControllerAssignedData();
			const char* spad = controllerData.GetScratchPadString();
			if (fp.GetClearenceFlag()) controllerData.SetScratchPadString("CLEA");
			const char* groundState = fp.GetGroundState();
			sendMessage(groundState);
			if (strcmp(groundState, "") != 0) {
				controllerData.SetScratchPadString(groundState);
			}
			controllerData.SetScratchPadString(spad);
		}
		return true;
	}
	return false;
}

void CEGKKHoldingPointsPlugin::sendMessage(std::string message) {
	try {
		DisplayUserMessage("QOLIES", "QOLIES", message.c_str(), true, true, true, false, false);
	}
	catch (...) {
		DisplayUserMessage("QOLIES", "QOLIES", "ERROR", true, true, true, true, false);
	}
}