#pragma once
#include "EuroScopePlugIn.h"
#include <string>
#include "pch.h"

class CEGKKHoldingPointsPlugin : public EuroScopePlugIn::CPlugIn {

public:
    CEGKKHoldingPointsPlugin();
    virtual ~CEGKKHoldingPointsPlugin();
    //virtual void OnFunctionCall(int FunctionId, const char* ItemString, POINT Pt, RECT Area);
    //virtual bool Enabled(EuroScopePlugIn::CFlightPlan flightPlan);
    virtual void OnRefreshFpListContent(EuroScopePlugIn::CFlightPlanList AcList);
    /*virtual void OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
        EuroScopePlugIn::CRadarTarget RadarTarget,
        int ItemCode,
        int TagData,
        char sItemString[16],
        int* pColorCode,
        COLORREF* pRGB,
        double* pFontSize
    );*/
    virtual bool OnCompileCommand(const char* sCommandLine);

private:
    virtual void sendMessage(std::string message);
};

