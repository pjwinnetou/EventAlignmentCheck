#ifndef FILEDATAMAP_H
#define FILEDATAMAP_H

#include <map>
#include <vector>
#include <string>

struct FileData {
  std::string directory;
  std::string fileName;
};


std::vector<FileData> getFileDataVector(){
  return {
   {"HCal", "beam_West"},
   {"HCal", "beam_East"},
   {"emcal", "beam_seb00"},
   {"emcal", "beam_seb01"},
   {"emcal", "beam_seb02"},
   {"emcal", "beam_seb03"},
   {"emcal", "beam_seb04"},
   {"emcal", "beam_seb05"},
   {"emcal", "beam_seb06"},
   {"emcal", "beam_seb07"},
   {"mbd", "beam_seb18"},
   {"ZDC", "beam_seb14"}
  };
}

#endif
