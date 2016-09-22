#include <L1Trigger/CSCTriggerPrimitives/src/CSCGEMMotherboardConfig.h>

CSCGEMMotherboardConfig::CSCGEMMotherboardConfig() :   lut_wg_eta_odd(0), lut_wg_eta_even(0), lut_pt_vs_dphi_gemcsc(0)
{

}

CSCGEMMotherboardConfig::~CSCGEMMotherboardConfig(){
  if(lut_wg_eta_odd       ) delete lut_wg_eta_odd       ;
  if(lut_wg_eta_even      ) delete lut_wg_eta_even      ;
  if(lut_pt_vs_dphi_gemcsc) delete lut_pt_vs_dphi_gemcsc;
}


CSCGEMMotherboardConfigME11::CSCGEMMotherboardConfigME11() :   CSCGEMMotherboardConfig()
{

  lut_wg_eta_odd = new std::vector<std::vector<double>> {
  {0, 2.44005, 2.44688},
  {1, 2.38863, 2.45035},
  {2, 2.32742, 2.43077},
  {3, 2.30064, 2.40389},
  {4, 2.2746, 2.37775},
  {5, 2.24925, 2.35231},
  {6, 2.22458, 2.32754},
  {7, 2.20054, 2.30339},
  {8, 2.1771, 2.27985},
  {9, 2.15425, 2.25689},
  {10, 2.13194, 2.23447},
  {11, 2.11016, 2.21258},
  {12, 2.08889, 2.19119},
  {13, 2.06809, 2.17028},
  {14, 2.04777, 2.14984},
  {15, 2.02788, 2.12983},
  {16, 2.00843, 2.11025},
  {17, 1.98938, 2.09108},
  {18, 1.97073, 2.0723},
  {19, 1.95246, 2.0539},
  {20, 1.93456, 2.03587},
  {21, 1.91701, 2.01818},
  {22, 1.8998, 2.00084},
  {23, 1.88293, 1.98382},
  {24, 1.86637, 1.96712},
  {25, 1.85012, 1.95073},
  {26, 1.83417, 1.93463},
  {27, 1.8185, 1.91882},
  {28, 1.80312, 1.90329},
  {29, 1.788, 1.88803},
  {30, 1.77315, 1.87302},
  {31, 1.75855, 1.85827},
  {32, 1.74421, 1.84377},
  {33, 1.7301, 1.8295},
  {34, 1.71622, 1.81547},
  {35, 1.70257, 1.80166},
  {36, 1.68914, 1.78807},
  {37, 1.67592, 1.77469},
  {38, 1.66292, 1.76151},
  {39, 1.65011, 1.74854},
  {40, 1.63751, 1.73577},
  {41, 1.62509, 1.72319},
  {42, 1.61287, 1.71079},
  {43, 1.60082, 1.69857},
  {44, 1.59924, 1.68654},
  {45, 1.6006, 1.67467},
  {46, 1.60151, 1.66297},
  {47, 1.60198, 1.65144} };

  lut_wg_eta_even = new std::vector<std::vector<double>> {
  {0, 2.3917, 2.39853},
  {1, 2.34037, 2.40199},
  {2, 2.27928, 2.38244},
  {3, 2.25254, 2.35561},
  {4, 2.22655, 2.32951},
  {5, 2.20127, 2.30412},
  {6, 2.17665, 2.27939},
  {7, 2.15267, 2.25529},
  {8, 2.12929, 2.2318},
  {9, 2.1065, 2.20889},
  {10, 2.08425, 2.18652},
  {11, 2.06253, 2.16468},
  {12, 2.04132, 2.14334},
  {13, 2.0206, 2.12249},
  {14, 2.00033, 2.1021},
  {15, 1.98052, 2.08215},
  {16, 1.96113, 2.06262},
  {17, 1.94215, 2.04351},
  {18, 1.92357, 2.02479},
  {19, 1.90538, 2.00645},
  {20, 1.88755, 1.98847},
  {21, 1.87007, 1.97085},
  {22, 1.85294, 1.95357},
  {23, 1.83614, 1.93662},
  {24, 1.81965, 1.91998},
  {25, 1.80348, 1.90365},
  {26, 1.78761, 1.88762},
  {27, 1.77202, 1.87187},
  {28, 1.75672, 1.85641},
  {29, 1.74168, 1.84121},
  {30, 1.72691, 1.82628},
  {31, 1.7124, 1.8116},
  {32, 1.69813, 1.79716},
  {33, 1.68411, 1.78297},
  {34, 1.67032, 1.769},
  {35, 1.65675, 1.75526},
  {36, 1.64341, 1.74174},
  {37, 1.63028, 1.72844},
  {38, 1.61736, 1.71534},
  {39, 1.60465, 1.70245},
  {40, 1.59213, 1.68975},
  {41, 1.57981, 1.67724},
  {42, 1.56767, 1.66492},
  {43, 1.55572, 1.65278},
  {44, 1.55414, 1.64082},
  {45, 1.55549, 1.62903},
  {46, 1.5564, 1.61742},
  {47, 1.55686, 1.60596} };


  lut_pt_vs_dphi_gemcsc = new std::vector<std::vector<double>> {
    {3, 0.03971647, 0.01710244},
    {5, 0.02123785, 0.00928431},
    {7, 0.01475524, 0.00650928},
    {10, 0.01023299, 0.00458796},
    {15, 0.00689220, 0.00331313},
    {20, 0.00535176, 0.00276152},
    {30, 0.00389050, 0.00224959},
    {40, 0.00329539, 0.00204670}};

  lut_wg_vs_hs_me1a  = new std::vector<std::vector<double>> {
    {0, 95},{0, 95},{0, 95},{0, 95},{0, 95},
    {0, 95},{0, 95},{0, 95},{0, 95},{0, 95},
    {0, 95},{0, 95},{0, 77},{0, 61},{0, 39},
    {0, 22},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1} };
  lut_wg_vs_hs_me1ag = new std::vector<std::vector<double>> {
    {0, 31},{0, 31},{0, 31},{0, 31},{0, 31},
    {0, 31},{0, 31},{0, 31},{0, 31},{0, 31},
    {0, 31},{0, 31},{0, 31},{0, 31},{0, 31},
    {0, 22},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1} };
  lut_wg_vs_hs_me1b  = new std::vector<std::vector<double>> {
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
    {100, 127},{73, 127},{47, 127},{22, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 127},
    {0, 127},{0, 127},{0, 127},{0, 127},{0, 105},
    {0, 93},{0, 78},{0, 63} };

}

CSCGEMMotherboardConfigME11::~CSCGEMMotherboardConfigME11() {
 if(lut_wg_vs_hs_me1a) delete lut_wg_vs_hs_me1a;
 if(lut_wg_vs_hs_me1ag) delete lut_wg_vs_hs_me1ag;
 if(lut_wg_vs_hs_me1b) delete lut_wg_vs_hs_me1b;
}


CSCGEMMotherboardConfigME21::CSCGEMMotherboardConfigME21() :   CSCGEMMotherboardConfig()
{

  lut_wg_eta_odd = new std::vector<std::vector<double>> {
    { 0,2.441},{ 1,2.435},{ 2,2.425},{ 3,2.414},{ 4,2.404},{ 5,2.394},{ 6,2.384},{ 7,2.374},
    { 8,2.365},{ 9,2.355},{10,2.346},{11,2.336},{12,2.327},{13,2.317},{14,2.308},{15,2.299},
    {16,2.290},{17,2.281},{18,2.273},{19,2.264},{20,2.255},{21,2.247},{22,2.238},{23,2.230},
    {24,2.221},{25,2.213},{26,2.205},{27,2.197},{28,2.189},{29,2.181},{30,2.173},{31,2.165},
    {32,2.157},{33,2.149},{34,2.142},{35,2.134},{36,2.127},{37,2.119},{38,2.112},{39,2.104},
    {40,2.097},{41,2.090},{42,2.083},{43,2.075},{44,2.070},{45,2.059},{46,2.054},{47,2.047},
    {48,2.041},{49,2.034},{50,2.027},{51,2.020},{52,2.014},{53,2.007},{54,2.000},{55,1.994},
    {56,1.988},{57,1.981},{58,1.975},{59,1.968},{60,1.962},{61,1.956},{62,1.950},{63,1.944},
    {64,1.937},{65,1.931},{66,1.924},{67,1.916},{68,1.909},{69,1.902},{70,1.895},{71,1.888},
    {72,1.881},{73,1.875},{74,1.868},{75,1.861},{76,1.854},{77,1.848},{78,1.841},{79,1.835},
    {80,1.830},{81,1.820},{82,1.815},{83,1.809},{84,1.803},{85,1.796},{86,1.790},{87,1.784},
    {88,1.778},{89,1.772},{90,1.766},{91,1.760},{92,1.754},{93,1.748},{94,1.742},{95,1.736},
    {96,1.731},{97,1.725},{98,1.719},{99,1.714},{100,1.708},{101,1.702},{102,1.697},{103,1.691},
    {104,1.686},{105,1.680},{106,1.675},{107,1.670},{108,1.664},{109,1.659},{110,1.654},{111,1.648},
    };

  lut_wg_eta_even = new std::vector<std::vector<double>> {
    { 0,2.412},{ 1,2.405},{ 2,2.395},{ 3,2.385},{ 4,2.375},{ 5,2.365},{ 6,2.355},{ 7,2.345},
    { 8,2.335},{ 9,2.325},{10,2.316},{11,2.306},{12,2.297},{13,2.288},{14,2.279},{15,2.270},
    {16,2.261},{17,2.252},{18,2.243},{19,2.234},{20,2.226},{21,2.217},{22,2.209},{23,2.200},
    {24,2.192},{25,2.184},{26,2.175},{27,2.167},{28,2.159},{29,2.151},{30,2.143},{31,2.135},
    {32,2.128},{33,2.120},{34,2.112},{35,2.105},{36,2.097},{37,2.090},{38,2.082},{39,2.075},
    {40,2.068},{41,2.060},{42,2.053},{43,2.046},{44,2.041},{45,2.030},{46,2.025},{47,2.018},
    {48,2.011},{49,2.005},{50,1.998},{51,1.991},{52,1.985},{53,1.978},{54,1.971},{55,1.965},
    {56,1.958},{57,1.952},{58,1.946},{59,1.939},{60,1.933},{61,1.927},{62,1.921},{63,1.915},
    {64,1.909},{65,1.902},{66,1.895},{67,1.887},{68,1.880},{69,1.873},{70,1.866},{71,1.859},
    {72,1.853},{73,1.846},{74,1.839},{75,1.832},{76,1.826},{77,1.819},{78,1.812},{79,1.806},
    {80,1.801},{81,1.792},{82,1.787},{83,1.780},{84,1.774},{85,1.768},{86,1.762},{87,1.756},
    {88,1.750},{89,1.744},{90,1.738},{91,1.732},{92,1.726},{93,1.720},{94,1.714},{95,1.708},
    {96,1.702},{97,1.697},{98,1.691},{99,1.685},{100,1.680},{101,1.674},{102,1.669},{103,1.663},
    {104,1.658},{105,1.652},{106,1.647},{107,1.642},{108,1.636},{109,1.631},{110,1.626},{111,1.621},
    };



  lut_pt_vs_dphi_gemcsc = new std::vector<std::vector<double>> {
    {3, 0.01832829, 0.01003643 },
    {5, 0.01095490, 0.00631625 },
    {7, 0.00786026, 0.00501017 },
    {10, 0.00596349, 0.00414560 },
    {15, 0.00462411, 0.00365550 },
    {20, 0.00435298, 0.00361550 },
    {30, 0.00465160, 0.00335700 },
    {40, 0.00372145, 0.00366262 }
  };

}

CSCGEMMotherboardConfigME21::~CSCGEMMotherboardConfigME21() {}
