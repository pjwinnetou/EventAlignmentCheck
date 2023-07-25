#include <iostream>
#include <cstdlib>

int RunEvt(int runNumber);

using namespace std;

int main( int argc, char* argv[] )
{
  if ( argc < 2 ) {
    cerr << "usage: " << argv[0] << " runNumber\n";
    return 1;
  } 
  
  int runNumber = std::stoi(argv[1]);

  try {
    int nevents = RunEvt(runNumber);
    return nevents;
  }
  catch (const std::runtime_error& e){
    std::cerr << "Error : " << e.what() << "\n";
    return 1;
  }

}
