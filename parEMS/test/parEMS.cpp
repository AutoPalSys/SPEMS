#include "ems.hpp"
#include "ems1.hpp"
#include "ems2.hpp"
// #include "ems2p.hpp"
#include "recursEMS.hpp"
#include "parEMS.hpp"
#include <getopt.h>

using namespace std;

void usage(const char *argv) 
{
    std::cout << "Usage: " << argv << " [OPTIONS] <input-sequence-file>" << std::endl;
    std::cout << "\t-s <version>  Possible versions: 1, 2, 2m, 2p" << std::endl;
    std::cout << "\t-l <l>        Length (l) of (l,d) motif" << std::endl;
    std::cout << "\t-d <d>        Maximum edit distance (d) of (l,d) motif" << std::endl;
    std::cout << "\t-t <int>      Number of threads" << std::endl;
    exit(-1);
}

int main(int argc, char **argv) 
{
  std::cout << "Start the Execution" << std::endl;

  std::string version;
  std::string input;
  Params params;
  params.num_threads = omp_get_max_threads();
  params.l = 1;
  params.d = 1;

  int option_char;
  while ((option_char = getopt(argc, argv, "l:d:s:t:")) != -1) 
  {
    switch (option_char)
      {  
         case 'l': params.l = atoi (optarg); break;
         case 'd': params.d = atoi (optarg); break;
         case 't': params.num_threads = atoi (optarg); break;
         case 's': version = string(optarg); break;
         case '?': usage(argv[0]); break;
      }
  }

  if (argc - optind < 1) 
  {
    usage(argv[0]);
  } 
  input = string(argv[optind]);
  version = "5"; // we force this as parMES
 	
  if (version == "1") 
  {
    cout << "Executing EMS1 " << endl;
    Ems1 ems(input, params.l, params.d, params);
    ems.searchWriteMotifs(params);
  } 
  else if (version == "2") 
  {
    cout << "Executing EMS2 " << endl;
    Ems2 ems2(input, params.l, params.d, params);
    ems2.searchWriteMotifs(params);
  } 
  else if (version == "4") 
  {
    cout << "Executing recursEMS " << endl;
    recursEms recems(input, params.l, params.d, params);
    recems.searchWriteMotifs(params);
  } 
  else if (version == "5") 
  {
    cout << "Executing ParEMS " << endl;
    ParEMS parems(input, params.l, params.d, params);
    parems.searchWriteMotifs(params);
  }    
  else 
  {
    std::cout << "Unknown version: " << version << std::endl;
    exit(-1);
  }
}
