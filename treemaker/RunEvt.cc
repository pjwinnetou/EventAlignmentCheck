#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "processFiles.cc"

int RunEvt(int runNumber) {
  auto fileDataVector = std::make_shared<std::vector<FileData>>(getFileDataVector());
  processFiles(runNumber, *fileDataVector.get());

  return 0;
}

