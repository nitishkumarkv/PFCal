#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4ProcessTypeEnumerator.h" 

#include "G4Step.hh"
#include "G4RunManager.hh"

#include "HGCSSGenParticle.hh"

#include "HGCSSFirstHadInt.hh"
#include "HGCSSpi0Info.hh"
#include "G4SystemOfUnits.hh"

//
SteppingAction::SteppingAction()                                         
{
  eventAction_ = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();               
  eventAction_->Add(  ((DetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction())->getStructure() );
  saturationEngine = new G4EmSaturation(0);
  timeLimit_ = 100;//ns
}

//
SteppingAction::~SteppingAction()
{ }

//
void SteppingAction::UserSteppingAction(const G4Step* aStep)
{

////////////////////////////////////////b///////////////////////////

    HGCSSFirstHadInt firstHadInt;
    HGCSSpi0Info pi0Info;   

    int nSec = 0;   
    bool foundHadInt = false;
    //double x = -999999.0;
    //double y = -999999.0;
    //double z = -999999.0;

    const G4TrackVector* tkV  = aStep->GetSecondary();
    G4Track* thTk = aStep->GetTrack();
    const G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
    if (tkV != nullptr && postStepPoint != nullptr) {
      int nsc = (*tkV).size();
      const G4VProcess*  proc = postStepPoint->GetProcessDefinedStep();
      G4ProcessTypeEnumerator* typeEnumerator = new G4ProcessTypeEnumerator();

      if (proc != nullptr) {
        int procid = typeEnumerator->processIdLong(proc);
        std::string name = proc->GetProcessName();

        if(thTk->GetParentID() <= 0 && procid >= 121 && procid <= 151) {
          foundHadInt = true;
          int process = procid;

          firstHadInt.x(postStepPoint->GetPosition().getX()/cm);
          firstHadInt.y(postStepPoint->GetPosition().getY()/cm);
          firstHadInt.z(postStepPoint->GetPosition().getZ()/cm);


          firstHadInt.foundHadInt(foundHadInt);
          firstHadInt.process(process);

          firstHadInt.parent_id(thTk->GetParentID());
          firstHadInt.track_id(thTk->GetTrackID());

          for(int i = 0; i < nsc; i++) {
            G4Track *tk = (*tkV)[i];
            if(tk->GetCreatorProcess()->GetProcessName() == "hIoni") continue;
            nSec++;
            
            firstHadInt.nsec(nSec);
            firstHadInt.sec_pdgID(tk->GetDefinition()->GetPDGEncoding());
            firstHadInt.sec_charge(tk->GetDefinition()->GetPDGCharge());
            firstHadInt.sec_kin(tk->GetKineticEnergy()/GeV);

            eventAction_->InfoSec(firstHadInt);
          }
        }



          for(int i = 0; i < nsc; i++) {
            G4Track *tk = (*tkV)[i];
 
            if(tk->GetDefinition()->GetPDGEncoding() == 111   //pi0
               || tk->GetDefinition()->GetPDGEncoding() == 221){   //eta

               if(tk->GetCreatorProcess()->GetProcessName() == "hIoni") continue;

               pi0Info.particle_pdgID(tk->GetDefinition()->GetPDGEncoding());
               pi0Info.particle_charge(tk->GetDefinition()->GetPDGCharge());
               pi0Info.particle_kin(tk->GetKineticEnergy()/GeV);

               pi0Info.x(postStepPoint->GetPosition().getX()/cm);
               pi0Info.y(postStepPoint->GetPosition().getY()/cm);
               pi0Info.z(postStepPoint->GetPosition().getZ()/cm);
  
               pi0Info.process(procid);
  
               pi0Info.parent_id(thTk->GetParentID());
               pi0Info.track_id(thTk->GetTrackID());
  
               eventAction_->Infopi0(pi0Info);
            }
          }
        

      }
    }
 
//////////////////////////////e////////////////////////////////////////////////


  // get PreStepPoint
  const G4StepPoint *thePreStepPoint = aStep->GetPreStepPoint();
  const G4StepPoint *thePostStepPoint = aStep->GetPostStepPoint();
  // get TouchableHandle
  //G4TouchableHandle theTouchable = thePreStepPoint->GetTouchableHandle();
  const G4Track* lTrack = aStep->GetTrack();
  G4int trackID = lTrack->GetTrackID();
  G4int parentID = lTrack->GetParentID();

  G4VPhysicalVolume* volume = thePreStepPoint->GetPhysicalVolume();
  std::string thePrePVname("null");
  if(volume==0) {
  } else {
    thePrePVname=volume->GetName();
  }
  G4VPhysicalVolume* postvolume = thePostStepPoint->GetPhysicalVolume();
  std::string thePostPVname("null");
  if(postvolume==0) {
  } else {
    thePostPVname=postvolume->GetName();
  }

  G4double edep = aStep->GetTotalEnergyDeposit();

  //correct with Birk's law for scintillator material
  if (volume->GetName().find("Scint")!=volume->GetName().npos) {
    G4double attEdep = saturationEngine->VisibleEnergyDeposition(lTrack->GetDefinition(), lTrack->GetMaterialCutsCouple(), aStep->GetStepLength(), edep, 0.);  // this is the attenuated visible energy
    //std::cout << " -- Correcting energy for scintillator: " << edep << " " << attEdep;
    edep = attEdep;
    //std::cout << " " << edep  << std::endl;
  }

  G4double stepl = 0.;
  if (lTrack->GetDefinition()->GetPDGCharge() != 0.) stepl = aStep->GetStepLength();

  //const G4ThreeVector &pos=aStep->GetPreStepPoint()->GetPosition();

  //Int_t iz=Int_t(pos.z()/eventAction_->GetCellSize())+4;
  //if(iz<0) iz=0; if(iz>8) iz=8;
  //Int_t iy=Int_t(pos.y()/eventAction_->GetCellSize())+4;
  //if(iy<0) iy=0; if(iy>8) iy=8;
  //Int_t iyiz(iz+iy*9);

  G4int pdgId=lTrack->GetDefinition()->GetPDGEncoding(); 
  G4double globalTime=lTrack->GetGlobalTime();

  const G4ThreeVector & position = thePreStepPoint->GetPosition();

  // get local hit position using touchable with theGlobalPos
  //G4ThreeVector LocalHitPos = theTouchable->GetHistory()->GetTopTransform().TransformPoint(position);

  /*if ( thePrePVname.find("Wphys")!=thePrePVname.npos &&
       thePostPVname.find("CuExtra")!=thePostPVname.npos){
    G4cout << " -- debug Pre   position " << volume->GetName() << " " << position << " " ;
    //G4cout << " -- debug Post  position " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << " " << aStep->GetPostStepPoint()->GetPosition() << G4endl;
    G4cout << thePreStepPoint->GetMaterial()->GetName()
	   << " " << thePostStepPoint->GetMaterial()->GetName()
	   << G4endl;
    //G4cout << "Local position " << LocalHitPos << G4endl;
    }*/

  HGCSSGenParticle genPart;
  //record truth particles
  //time cut: we don't want neutrons re-entering the front-face a long time after...
  //bit for muons study
  /*if (abs(pdgId)==13 && 
      thePrePVname=="Scintillator51phys" && 
      thePostPVname=="Air51phys"){
    eventAction_->fout() << thePrePVname
			 << " " << thePostPVname
			 << " " << trackID
			 << " " << pdgId
			 << " " << globalTime
			 << " " << thePostStepPoint->GetPosition()[0]
			 << " " << thePostStepPoint->GetPosition()[1]
			 << " " << thePostStepPoint->GetPosition()[2]
			 << " " << lTrack->GetMomentum()[0]
			 << " " << lTrack->GetMomentum()[1]
			 << " " << lTrack->GetMomentum()[2]
			 << std::endl;
			 }*/
    


  //bit for particles study
  
  /*if (abs(pdgId)==11 && 
      ((thePrePVname=="Si11_0phys" || thePrePVname=="Si11_1phys" || thePrePVname=="Si11_2phys" || thePrePVname=="PCB12phys") && 
      (thePostPVname=="WCu11phys" || thePostPVname=="Si11_0phys"|| thePostPVname=="Si11_1phys"|| thePostPVname=="Si11_2phys" || (thePostPVname=="PCB12phys" && thePrePVname=="Si11_2phys"))) ||
      ((thePrePVname=="Si18_0phys" || thePrePVname=="Si18_1phys" || thePrePVname=="Si18_2phys" || thePrePVname=="WCu19phys") && 
       (thePostPVname=="PCB18phys" || thePostPVname=="Si18_0phys"|| thePostPVname=="Si18_1phys"|| thePostPVname=="Si18_2phys" || (thePostPVname=="WCu18phys" && thePrePVname=="Si18_2phys")))
       )*/
  /*if (edep>1.)
    {
      std::ostringstream lss;
      lss << thePrePVname
	  << " " << thePostPVname
	  << " e " << edep
	  << " pdg " << pdgId
	  << " t " << globalTime  
	  << " p " << lTrack->GetMomentum().mag();
      //if (abs(pdgId)>1000000000) 
      lss << " status " << lTrack->GetTrackStatus()
	  << " l " << stepl
	  << " Edep " << aStep->GetTotalEnergyDeposit()
	  << " nonion. " << aStep->GetNonIonizingEnergyDeposit()
	  << " " << lTrack->GetCreatorProcess()->GetProcessName()
	  << " Ekin " << lTrack->GetKineticEnergy()
	;
      lss << std::endl;
      std::cout << lss.str();
      eventAction_->fout() << lss.str();
      }*/
  
  //return;
  //*/

  //if (thePrePVname=="Wphys") std::cout << "-- debug: " << thePrePVname << " " << thePostPVname << " " << eventAction_->isFirstVolume(thePostPVname) << " time " << globalTime << " trackid=" << trackID << std::endl;
  //if (abs(pdgId)==11 && 
  //((thePrePVname=="Si11_0phys" && thePostPVname=="Si11_1phys") || 
  //(thePrePVname=="Si11_1phys" && thePostPVname=="Si11_0phys")) || 
  //((thePrePVname=="Si18_0phys" && thePostPVname=="Si18_1phys") || 
  //(thePrePVname=="Si18_1phys" && thePostPVname=="Si18_0phys"))
//)
  if (globalTime < timeLimit_ && 
      (thePrePVname=="Wphys"
	&& eventAction_->isFirstVolume(thePostPVname))
      )
    {
    //if (pdgId == 2112) 
    //const G4ThreeVector & preposition = thePreStepPoint->GetPosition();
    const G4ThreeVector & postposition = thePostStepPoint->GetPosition();
    //std::cout << "pre " << preposition[0] << " " << preposition[1] << " " << postposition[2]
    //	      << std::endl
    //	      << "post " << postposition[0] << " " << postposition[1] << " " << postposition[2]
    //	      << std::endl;
    const G4ThreeVector &p = lTrack->GetMomentum();
    G4ParticleDefinition *pd = lTrack->GetDefinition();
    genPart.setPosition(postposition[0],postposition[1],postposition[2]);
    genPart.setMomentum(p[0],p[1],p[2]);
    genPart.mass(pd->GetPDGMass());
    genPart.time(globalTime);
    genPart.pdgid(pdgId);
    genPart.charge(pd->GetPDGCharge());
    genPart.trackID(trackID);
    //double tmpE = sqrt(pd->GetPDGMass()*pd->GetPDGMass()+(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]));
    //std::cout << "-- found incoming: " << thePrePVname << " " << thePostPVname << " " << trackID << " id=" << pdgId << " t=" << globalTime << " E=" << tmpE << std::endl;
    //if (pdgId == 2112) genPart.Print(G4cout);
  }

  //if (globalTime < 10) //timeLimit_) 
  eventAction_->Detect(edep,stepl,globalTime,pdgId,volume,position,trackID,parentID,genPart);
  //eventAction_->Detect(edep,stepl,globalTime,pdgId,volume,iyiz);
}
