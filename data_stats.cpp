#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
 
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/kurtosis.hpp>
#include <boost/accumulators/statistics/skewness.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

// COMPILE WITH
// 				g++ pulse_stats.cpp -o pulse_stats -lboost_program_options

using namespace boost;
using namespace boost::accumulators;
using namespace boost::program_options; 

int main(int argc, char* argv[])
{

	double time_step = 1.0/62.5;// 65 MSPS DAQ
	int N=4095;// Number of data points per acquisition
	int threshold=2100;
	bool invert=true;
	int invert_level=2048;
	std::string measure;

	options_description desc("Basic data processing program, takes data on stdin and extracts various stats, \n the allowed options are");
	desc.add_options()
    	("help,h", "produce help message")
    	("max", "gets maximum")
    	("min", "gets minimum")
    	("mean", "gets mean")
    	("std-dev", "gets standard deviation")
    	("moment1", "gets 1st moment")
    	("moment2", "gets 2nd moment")
    	("moment3", "gets 3rd moment")
    	("moment4", "gets 4th moment")
    	("skewness", "gets skewness")
    	("kurtosis", "gets skewness")
    	("count", "gets number of data points")
    	("spread", "gets spread (max-mean)")
    	("all", "gets all stats measures")
	("quiet-labels,q", value<bool>()->default_value("false"),"if true, just output numbers with no labels");
;
	
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);    
	
	bool quiet_labels = vm["quiet-labels"].as<bool>();

	if (vm.count("help")) {
    		std::cout << desc << "\n";
    	return 1;
	}

	//create an accumulator
	accumulator_set<double, features<tag::mean,tag::max,tag::min,tag::count,tag::kurtosis,tag::moment<1>,tag::moment<2>,tag::moment<3>,tag::moment<4>,tag::skewness,tag::variance,tag::median> > myAccumulator;

	std::string line;
	std::cin >> line;
	while(!line.empty()){
		myAccumulator(atof(line.c_str()));
		line.clear();
		std::cin>>line;
		// std::cout << data.size() << std::endl;
	}


if(!quiet_labels){

	if (vm.count("max")|vm.count("all")) {
		std::cout  << std::setw(30) << " Max" << std::setw(30) << max(myAccumulator) << std::endl;
	}
	if (vm.count("min")|vm.count("all")) {
		std::cout  << std::setw(30) << " Min" << std::setw(30) << min(myAccumulator) << std::endl;
	}
	if (vm.count("spread")|vm.count("all")) {
		std::cout  << std::setw(30) << " Spread"  << std::setw(30) <<  max(myAccumulator)-min(myAccumulator) << std::endl;
	}
	if (vm.count("mean")|vm.count("all")) {
		std::cout  << std::setw(30) << " Mean" << std::setw(30) <<  mean(myAccumulator) << std::endl;
	}
	if (vm.count("std-dev")|vm.count("all")) {
		std::cout  << std::setw(30) << " Std. Dev." << std::setw(30) <<  sqrt(variance(myAccumulator)) << std::endl;
	}
	if (vm.count("count")|vm.count("all")) {
		std::cout  << std::setw(30) << " Count" << std::setw(30) <<  count(myAccumulator) << std::endl;
	}
	if (vm.count("moment1")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Moment (1st)" << std::setw(30) <<  moment<1>(myAccumulator) << std::endl;
	}
	if (vm.count("moment2")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Moment (2nd)" << std::setw(30) <<  moment<2>(myAccumulator) << std::endl;
	}
	if (vm.count("moment3")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Moment (3rd)" << std::setw(30) <<  moment<3>(myAccumulator) << std::endl;
	}
	if (vm.count("moment4")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Moment (4th)" << std::setw(30) <<  moment<4>(myAccumulator) << std::endl;
	}
	if (vm.count("skewness")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Skewness" << std::setw(30) <<  skewness(myAccumulator) << std::endl;
	}
	if (vm.count("kurtosis")|vm.count("all")) {
		std::cout  << std::setw(30) <<  " Kurtosis" << std::setw(30) <<  kurtosis(myAccumulator) << std::endl;
	}
}else{
int text_w=20;
	if (vm.count("max")|vm.count("all")) {
		std::cout  << std::setw(text_w) << max(myAccumulator);
	}
	if (vm.count("min")|vm.count("all")) {
		std::cout  << std::setw(text_w) << min(myAccumulator);
	}
	if (vm.count("mean")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  mean(myAccumulator);
	}
	if (vm.count("std-dev")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  sqrt(variance(myAccumulator));
	}
	if (vm.count("spread")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  max(myAccumulator)-min(myAccumulator);
	}
	if (vm.count("count")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  count(myAccumulator);
	}
	if (vm.count("moment1")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  moment<1>(myAccumulator);
	}
	if (vm.count("moment2")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  moment<2>(myAccumulator);
	}
	if (vm.count("moment3")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  moment<3>(myAccumulator);
	}
	if (vm.count("moment4")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  moment<4>(myAccumulator);
	}
	if (vm.count("skewness")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  skewness(myAccumulator);
	}
	if (vm.count("kurtosis")|vm.count("all")) {
		std::cout  << std::setw(text_w) <<  kurtosis(myAccumulator);
	}
std::cout  << std::endl;
}




		
 return 0;
}
