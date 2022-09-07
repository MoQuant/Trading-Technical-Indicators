#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace data_frame {

    void PrintS(std::vector<std::vector<std::string>> f)
    {
        for(auto & g : f){
            for(auto & t : g){
                std::cout << t << "\t";
            }
            std::cout << std::endl;
        }
    }

    void PrintNumeric(std::vector<double> x)
    {
        for(auto & q : x){
            std::cout << q << std::endl;
        }
    }

    std::vector<std::vector<std::string>> get_frame(std::string filename)
    {
        std::fstream fn;
        std::vector<std::vector<std::string>> data, storage;
        std::vector<std::string> temp, lemp;

        fn.open(filename);
        std::string hold, word;

        int debug = 0;
        int ii = 0;

        while(fn >> hold){
            std::stringstream s(hold);
            temp.clear();
            while(getline(s, word, ',')){
                if(word != ""){
                    temp.push_back(word);
                }   
            }
            if(temp.size() > 0){
                data.push_back(temp);
            }
        }
        return data;
    }

    std::vector<double> cut_column(std::vector<std::vector<std::string>> x, int c)
    {
        std::vector<double> cs;
        for(int i = 1; i < x.size(); ++i){
            cs.push_back(std::stod(x[i][c]));
        }

        return cs;
    }

    
}