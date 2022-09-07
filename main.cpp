#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include "data.h"
#include "technicals.h"


int main()
{
    // Fetching MSFT Stock Data
    std::vector<std::vector<std::string>> df = data_frame::get_frame("MSFT.csv");
    std::vector<double> adjClose = data_frame::cut_column(df, 6);
    std::vector<double> volume = data_frame::cut_column(df, 7);

    std::reverse(adjClose.begin(), adjClose.end());
    std::reverse(volume.begin(), volume.end());

    std::vector<double> bdown = technicals::bollinger_bands(adjClose, 50, 2, -1);
    std::vector<double> bup = technicals::bollinger_bands(adjClose, 50, 2, 1);
    
    std::vector<double> ma = technicals::moving_average(adjClose, 50);

    std::vector<double> Vwap = technicals::vwap(adjClose, volume, 50);

    std::vector<double> RSI = technicals::RSI(adjClose, 50);

    std::ofstream writer;
    writer.open("indicators.csv");

    for(int i = 0; i < adjClose.size(); ++i){
        writer << std::to_string(adjClose[i]) << "," << std::to_string(bdown[i]) << "," << std::to_string(bup[i]) << "," << std::to_string(Vwap[i]) << "\n";
        writer.flush();
    }

    writer.close();

    return 0;
}