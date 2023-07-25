#include <fstream>
#include <iostream>
#include <sstream>
#include "FILEDATAMAP.h"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

// Event library

#include "Event.h"
#include "Eventiterator.h"
#include "fileEventiterator.h"
//#include "packet_hbd_fpgashort.h"

// ROOT

#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include <vector>

// Interpolator class and root of derivative

#include "Math/Interpolator.h"
#include "Math/Functor.h"
#include "Math/RootFinderAlgorithms.h" 

using namespace std;
void processFiles(int runNumber, const std::vector<FileData>& fileDataVector) {

  std::unique_ptr<TFile> wf(new TFile(Form("Output_Run%d.root",runNumber),"recreate"));
    
  int ic=0;

  for (const auto& fileData : fileDataVector) {
    std::stringstream filePath;
    filePath << "/sphenix/lustre01/sphnxpro/commissioning/" << fileData.directory << "/beam/" << fileData.fileName << "-000" << runNumber << "-0000.prdf";
    //filePath << "/bbox/commissioning/" << fileData.directory << "/" << fileData.fileName << "-000" << runNumber << "-0000.prdf";

    std::ifstream infile(filePath.str());
    if (!infile.good()) {
      continue;
    }
    std::cout << "Processing: " << filePath.str() << std::endl;

    int status;
    std::string temp_str = filePath.str();
    const char* cstr = temp_str.c_str(); 
    std::unique_ptr<Eventiterator> it(new fileEventiterator(cstr, status));
    if (status) {
      throw std::runtime_error("Couldn't open input file " + std::string(cstr));
    }

    std::unique_ptr<TTree> tree(new TTree(Form("tree_%s_%s",fileData.directory.c_str(),fileData.fileName.c_str()),""));
    Packet **plist = nullptr;
    plist = new Packet *[16];
    Event *evt;
    while ( (evt = it->getNextEvent()) ) {
      if(evt->getEvtType() == 1) break;
    }
    int npackets = evt->getPacketList(plist, 16);
    const int NXMIT = npackets; 
    int EvtNum[NXMIT];
    int FEMClock[NXMIT];
    int Clock[NXMIT];
    cout << "NXMIT : " << NXMIT << endl;
    for(int ip=0; ip<NXMIT; ip++){
      tree->Branch(Form("EvtNum_packet%d",plist[ip]->getIdentifier()),&EvtNum[ip]);
      tree->Branch(Form("FEMClock_packet%d",plist[ip]->getIdentifier()),&FEMClock[ip]);
      tree->Branch(Form("Clock_packet%d",plist[ip]->getIdentifier()),&Clock[ip]);
      //tree->Branch(Form("EvtNum_packet%d",fileData.PACKET.at(ip)),&EvtNum[ip]);
      //tree->Branch(Form("FEMClock_packet%d",fileData.PACKET.at(ip)),&FEMClock[ip]);
      //tree->Branch(Form("Clock_packet%d",fileData.PACKET.at(ip)),&Clock[ip]);
    }
    while ( (evt = it->getNextEvent()) ) {
      if ( evt->getEvtType() != 1 ) continue;
      for ( Int_t ixmit = 0; ixmit < NXMIT; ixmit++ ) {
        Packet *p;
        p = evt->getPacket( plist[ixmit]->getIdentifier());
        //p = evt->getPacket( fileData.PACKET.at(ixmit));
        if ( p != nullptr ) {
          EvtNum[ixmit] = p->iValue(0,"EVTNR");
          Clock[ixmit]     = p->iValue(0,"CLOCK");
          FEMClock[ixmit]  = p->iValue(0,"FEMCLOCK");
          delete p; 
        }
      }
      tree->Fill();
    }
    ic++;
    wf->cd();
    tree->Write();
    for(int i=0;i<NXMIT;i++){
      delete plist[i];
      plist[i] = nullptr;
    }
    delete[] plist; 
    plist = nullptr;
  }

  std::cout << "Total number of files : " << ic << std::endl;
  wf->Close();
}
