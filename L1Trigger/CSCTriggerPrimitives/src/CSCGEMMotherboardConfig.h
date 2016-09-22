#ifndef L1Trigger_CSCTriggerPrimitives_CSCGEMMotherboardConfig_h
#define L1Trigger_CSCTriggerPrimitives_CSCGEMMotherboardConfig_h


#include <vector>

class CSCGEMMotherboardConfig
{
public:

  CSCGEMMotherboardConfig();
  virtual ~CSCGEMMotherboardConfig();

  std::vector<std::vector<double>> * lut_wg_eta_odd;
  std::vector<std::vector<double>> * lut_wg_eta_even;
  // LUT with bending angles of the GEM-CSC high efficiency patterns (98%)
  // 1st index: pt value = {5,10,15,20,30,40}
  // 2nd index: bending angle for odd numbered chambers
  // 3rd index: bending angle for even numbered chambers
  std::vector<std::vector<double>> * lut_pt_vs_dphi_gemcsc;
};


class CSCGEMMotherboardConfigME11 : public CSCGEMMotherboardConfig
{
public:

  CSCGEMMotherboardConfigME11();
  virtual ~CSCGEMMotherboardConfigME11();

  // LUT for which ME1/1 wire group can cross which ME1/a halfstrip
  // 1st index: WG number
  // 2nd index: inclusive HS range
  //with ag a modified LUT for ganged ME1a
  std::vector<std::vector<double>> * lut_wg_vs_hs_me1a;
  std::vector<std::vector<double>> * lut_wg_vs_hs_me1ag;
  std::vector<std::vector<double>> * lut_wg_vs_hs_me1b;
};

class CSCGEMMotherboardConfigME21 : public CSCGEMMotherboardConfig
{
public:

  CSCGEMMotherboardConfigME21();
  virtual ~CSCGEMMotherboardConfigME21();
};


#endif
