#ifndef AliAnalysisTaskPHOSEmbedding_H
#define AliAnalysisTaskPHOSEmbedding_H

// Author: Daiki Sekihata (Hiroshima University)

class TList;
class AliVEvent;
class AliESDEvent;
class AliAODEvent;
class AliPHOSGeometry;
class AliPHOSClusterizerv1;
class AliPHOSReconstructor;
class TClonesArray;
class AliESDtrackCuts;
class AliMultSelection;
class AliStack;
//class AliEventCuts;

#include "AliAnalysisTaskSE.h"
#include "AliAnalysisTaskESDfilter.h"

class AliAnalysisTaskPHOSEmbedding : public AliAnalysisTaskSE {

  public:
    AliAnalysisTaskPHOSEmbedding(const char *name="PHOSEmbedding");
    virtual ~AliAnalysisTaskPHOSEmbedding(); 
    void SetInputFileArray(TObjArray *array) {fAODPathArray = array;}//array of path to MC AOD.
    void SetParticle(TString par) {fParticle = par;}//Pi0/Eta/Gamma

  protected:
    virtual void UserCreateOutputObjects();
    virtual void UserExec(Option_t *option);
    virtual void Terminate(Option_t *option);
    virtual Bool_t UserNotify();

    void ConvertAODtoESD();
    void ConvertESDtoAOD();

    void Init();
    void InitMF();
    void InitGeometry();

    Int_t SelectAODFile();
    Bool_t OpenAODFile();
    void CopyRecalibrateDigits();

    void SetSignalCalibration(Double_t corr) {fSignalECorrection=corr;}
    Double_t DecalibrateSignal(Double_t cellAmplitude,Int_t cellNumber);

  protected:
    TString fParticle;
    AliVEvent *fEvent;
    TRandom3 *fRandom3;
    TObjArray *fAODPathArray;
    TString fAODPath;
    TFile *fAODInput;//external AOD MC input.
    TTree *fAODTree;//aodTree of external AOD MC.
    AliAODEvent *fAODEvent;//AOD MC event
    Int_t fNEvents;//event counter for real event loop
    Int_t fEventCounter;//event counter for real event loop
    Int_t fEventLoopMin;
    Int_t fEventLoopMax;
    AliAODCaloCells *fCellsPHOS;
    TTree *fDigitsTree ;  //! Digits
    TTree *fClustersTree; //! Clusters 
    TClonesArray *fDigitsArr;
    AliPHOSReconstructor *fPHOSReconstructor;
    AliPHOSClusterizerv1 *fClusterizer;
    Bool_t fInitialized;
    Int_t fRunNumber;
    AliESDEvent *fESDEvent;
    TClonesArray *fMCArray;
    TClonesArray *fEmbeddedClusterArray;
    AliAODCaloCells *fEmbeddedCells;
    Double_t fSignalECorrection;
    AliPHOSCalibData * fSignalCalibData; //! Decalibration of signal, inverse to OADB. //new memeber variable for an additional calibration.

  private:
    AliAnalysisTaskPHOSEmbedding(const AliAnalysisTaskPHOSEmbedding&);
    AliAnalysisTaskPHOSEmbedding& operator=(const AliAnalysisTaskPHOSEmbedding&);

    ClassDef(AliAnalysisTaskPHOSEmbedding, 6);
};

#endif