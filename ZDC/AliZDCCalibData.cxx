/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id$ */

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// class for ZDC calibration                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "AliZDCCalibData.h"

ClassImp(AliZDCCalibData)

//________________________________________________________________
AliZDCCalibData::AliZDCCalibData()
{
  Reset();
}

//________________________________________________________________
AliZDCCalibData::AliZDCCalibData(const char* name)
{
  // Constructor
  TString namst = "Calib_";
  namst += name;
  SetName(namst.Data());
  SetTitle(namst.Data());
  Reset();
}

//________________________________________________________________
AliZDCCalibData::AliZDCCalibData(const AliZDCCalibData& calibda) :
  TNamed(calibda)
{
  // Copy constructor
  SetName(calibda.GetName());
  SetTitle(calibda.GetName());
  Reset();
  for(int t=0; t<48; t++){
     fMeanPedestal[t] = calibda.GetMeanPed(t);
     fMeanPedWidth[t] = calibda.GetMeanPedWidth(t);
     fOOTPedestal[t]  = calibda.GetOOTPed(t);
     fOOTPedWidth[t]  = calibda.GetOOTPedWidth(t);
     fPedCorrCoeff[0][t] = calibda.GetPedCorrCoeff0(t);
     fPedCorrCoeff[1][t] = calibda.GetPedCorrCoeff1(t);
  }
  for(int t=0; t<6; t++)  fEnCalibration[t] = calibda.GetEnCalib(t);
  //
  fZEMEndValue    = calibda.GetZEMEndValue();   
  fZEMCutFraction = calibda.GetZEMCutFraction();
  fDZEMSup	  = calibda.GetDZEMSup();
  fDZEMInf	  = calibda.GetDZEMInf();
}

//________________________________________________________________
AliZDCCalibData &AliZDCCalibData::operator =(const AliZDCCalibData& calibda)
{
// assignment operator
  SetName(calibda.GetName());
  SetTitle(calibda.GetName());
  Reset();
  for(int t=0; t<48; t++){
     fMeanPedestal[t] = calibda.GetMeanPed(t);
     fMeanPedWidth[t] = calibda.GetMeanPedWidth(t);
     fOOTPedestal[t]  = calibda.GetOOTPed(t);
     fOOTPedWidth[t]  = calibda.GetOOTPedWidth(t);
     fPedCorrCoeff[0][t] = calibda.GetPedCorrCoeff0(t);
     fPedCorrCoeff[1][t] = calibda.GetPedCorrCoeff1(t);
  }
  for(int t=0; t<6; t++) fEnCalibration[t] = calibda.GetEnCalib(t);
  fZEMEndValue    = calibda.GetZEMEndValue();
  fZEMCutFraction = calibda.GetZEMCutFraction();

  return *this;
}

//________________________________________________________________
AliZDCCalibData::~AliZDCCalibData()
{
}

//________________________________________________________________
void AliZDCCalibData::Reset()
{
  // Reset
  memset(fMeanPedestal,0,48*sizeof(Float_t));
  memset(fMeanPedWidth,0,48*sizeof(Float_t));
  memset(fOOTPedestal,0,48*sizeof(Float_t));
  memset(fOOTPedWidth,0,48*sizeof(Float_t));
  memset(fEnCalibration,0,6*sizeof(Float_t));
}                                                                                       


//________________________________________________________________
void  AliZDCCalibData::Print(Option_t *) const
{
   // Printing of calibration object
   printf("\n #######	In-time pedestal values (mean value, sigma)	####### \n");
   for(int t=0; t<48; t++){
     if(t==0 || t==24) printf("\n-------- ZN1 HighRes -------- \n");
     else if(t==5 || t==29) printf("\n-------- ZN1 LowRes -------- \n");
     else if(t==10 || t==34) printf("\n-------- ZP1 HighRes -------- \n");
     else if(t==15 || t==39) printf("\n-------- ZP1 LowRes -------- \n");
     else if(t==20) printf("\n-------- ZEM1 HighRes --------  \n");
     else if(t==21) printf("\n-------- ZEM1 LowRes --------  \n");
     else if(t==22) printf("\n-------- ZEM2 HighRes --------  \n");
     else if(t==23) printf("\n-------- ZEM2 LowRes --------  \n");
     printf("ADC%d (%.1f, %.1f)  ",t,fMeanPedestal[t],fMeanPedWidth[t]);
   }
   //
   printf("\n\n #######	Out-of-time pedestal values (mean value, sigma)	####### \n");
   for(int t=0; t<48; t++){
     if(t==0 || t==24) printf("\n-------- ZN1 HighRes -------- \n");
     else if(t==5 || t==29) printf("\n-------- ZN1 LowRes -------- \n");
     else if(t==10 || t==34) printf("\n-------- ZP1 HighRes -------- \n");
     else if(t==15 || t==39) printf("\n-------- ZP1 LowRes -------- \n");
     else if(t==20) printf("\n-------- ZEM1 HighRes --------  \n");
     else if(t==21) printf("\n-------- ZEM1 LowRes --------  \n");
     else if(t==22) printf("\n-------- ZEM2 HighRes --------  \n");
     else if(t==23) printf("\n-------- ZEM2 LowRes --------  \n");
     printf("ADC%d (%.1f, %.1f)  ",t,fOOTPedestal[t],fOOTPedWidth[t]);
   }
 
   printf("\n\n #######	Energy calibration coefficients #######	\n");
   printf("  ZN1 = %.4f (E[TeV]/ADCch.) \n",fEnCalibration[0]);
   printf("  ZP1 = %.4f (E[TeV]/ADCch.) \n",fEnCalibration[1]);
   printf("  ZN2 = %.4f (E[TeV]/ADCch.) \n",fEnCalibration[2]);
   printf("  ZP2 = %.4f (E[TeV]/ADCch.) \n",fEnCalibration[3]);
   printf("  ZEM1 = %.2f (E[TeV]/ADCch.) \n",fEnCalibration[4]);
   printf("  ZEM2 = %.2f (E[TeV]/ADCch.) \n",fEnCalibration[5]);
 
   printf("\n\n #######	Equalization coefficients #######	\n");
   printf("  ZN1 -> %1.2f %1.2f %1.2f %1.2f %1.2f  \n",
    fZN1EqualCoeff[0],fZN1EqualCoeff[1],fZN1EqualCoeff[2],fZN1EqualCoeff[3],fZN1EqualCoeff[4]);
   printf("  ZP1 -> %1.2f %1.2f %1.2f %1.2f %1.2f  \n",
    fZP1EqualCoeff[0],fZP1EqualCoeff[1],fZP1EqualCoeff[2],fZP1EqualCoeff[3],fZP1EqualCoeff[4]);
   printf("  ZN2 -> %1.2f %1.2f %1.2f %1.2f %1.2f  \n",
    fZN2EqualCoeff[0],fZN2EqualCoeff[1],fZN2EqualCoeff[2],fZN2EqualCoeff[3],fZN2EqualCoeff[4]);
   printf("  ZP2 -> %1.2f %1.2f %1.2f %1.2f %1.2f  \n",
    fZP2EqualCoeff[0],fZP2EqualCoeff[1],fZP2EqualCoeff[2],fZP2EqualCoeff[3],fZP2EqualCoeff[4]);
 
   printf("\n\n #######	Parameters from EZDC vs. ZEM correlation #######	\n");
   printf("  ZEMEndPoint = %1.2f, ZEMCutFraction = %1.2f \n"
     "	DZEMInf = %1.2f, DZEMSup = %1.2f\n",
     fZEMEndValue, fZEMCutFraction, fDZEMInf, fDZEMSup);
 
   printf("\n\n #######	Parameters from EZDC vs. Nspec correlation #######	\n");
   printf("  EZN1MaxValue = %1.2f, EZP1MaxValue = %1.2f, EZDC1MaxValue = %1.2f \n"
     "  EZN2MaxValue = %1.2f, EZP2MaxValue = %1.2f, EZDC2MaxValue = %1.2f \n\n",
     fEZN1MaxValue, fEZP1MaxValue, fEZDC1MaxValue,
     fEZN2MaxValue, fEZP2MaxValue, fEZDC2MaxValue);

} 

//________________________________________________________________
void AliZDCCalibData::SetMeanPed(Float_t* MeanPed)
{
  if(MeanPed) for(int t=0; t<48; t++) fMeanPedestal[t] = MeanPed[t];
  else for(int t=0; t<48; t++) fMeanPedestal[t] = 0.;
}
//________________________________________________________________
void AliZDCCalibData::SetMeanPedWidth(Float_t* MeanPedWidth)
{
  if(MeanPedWidth) for(int t=0; t<48; t++) fMeanPedWidth[t] = MeanPedWidth[t];
  else for(int t=0; t<48; t++) fMeanPedWidth[t] = 0.;
}

//________________________________________________________________
void AliZDCCalibData::SetOOTPed(Float_t* OOTPed)
{
  if(OOTPed) for(int t=0; t<48; t++) fOOTPedestal[t] = OOTPed[t];
  else for(int t=0; t<48; t++) fOOTPedestal[t] = 0.;
}

//________________________________________________________________
void AliZDCCalibData::SetOOTPedWidth(Float_t* OOTPedWidth)
{
  if(OOTPedWidth) for(int t=0; t<48; t++) fOOTPedWidth[t] = OOTPedWidth[t];
  else for(int t=0; t<48; t++) fOOTPedWidth[t] = 0.;
}

//________________________________________________________________
void AliZDCCalibData:: SetPedCorrCoeff(Float_t* PedCorrCoeff)
{
  // Set coefficients for pedestal correlations
  if(PedCorrCoeff){
    for(Int_t j=0; j<2; j++){
     for(int t=0; t<48; t++)
       fPedCorrCoeff[j][t] = PedCorrCoeff[t];
    }
  }
  else{
    for(Int_t j=0; j<2; j++){
     for(int t=0; t<48; t++)
       fPedCorrCoeff[j][t] = 0.;
    }
  }
 
}

//________________________________________________________________
void AliZDCCalibData:: SetPedCorrCoeff(Float_t* PedCorrCoeff0, Float_t* PedCorrCoeff1)
{
  // Set coefficients for pedestal correlations
  if(PedCorrCoeff0 && PedCorrCoeff1){
    for(int t=0; t<48; t++){
       fPedCorrCoeff[0][t] = PedCorrCoeff0[t];
       fPedCorrCoeff[0][t] = PedCorrCoeff1[t];
    }
  }
  else{
     for(int t=0; t<48; t++){
       fPedCorrCoeff[0][t] = 0.;
       fPedCorrCoeff[1][t] = 0.;
    }
  }
 
}

//________________________________________________________________
void AliZDCCalibData::SetEnCalib(Float_t* EnCalib) 
{
  // Set energy calibration coefficients
  if(EnCalib) for(int t=0; t<6; t++) fEnCalibration[t] = EnCalib[t];
  else for(int t=0; t<6; t++) fEnCalibration[t] = 0.;
}

//________________________________________________________________
void AliZDCCalibData::SetZN1EqualCoeff(Float_t* EqualCoeff)
{
  // Set ZN1 equalization coefficients
  if(EqualCoeff) for(int t=0; t<5; t++) fZN1EqualCoeff[t] = EqualCoeff[t];
  else for(int t=0; t<5; t++) fZN1EqualCoeff[t] = 1.;
}
 
//________________________________________________________________
void AliZDCCalibData::SetZP1EqualCoeff(Float_t* EqualCoeff)
{
  // Set ZP1 equalization coefficients
  if(EqualCoeff) for(int t=0; t<5; t++) fZP1EqualCoeff[t] = EqualCoeff[t];
  else for(int t=0; t<5; t++) fZP1EqualCoeff[t] = 1.;
}
//________________________________________________________________
void AliZDCCalibData::SetZN2EqualCoeff(Float_t* EqualCoeff)
{
  // Set ZN2 equalization coefficients
  if(EqualCoeff) for(int t=0; t<5; t++) fZN2EqualCoeff[t] = EqualCoeff[t];
  else for(int t=0; t<5; t++) fZN2EqualCoeff[t] = 1.;
}
 
//________________________________________________________________
void AliZDCCalibData::SetZP2EqualCoeff(Float_t* EqualCoeff)
{
  // Set ZN1 equalization coefficients
  if(EqualCoeff) for(int t=0; t<5; t++) fZP2EqualCoeff[t] = EqualCoeff[t];
  else for(int t=0; t<5; t++) fZP2EqualCoeff[t] = 1.;
}
 
