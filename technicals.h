#include <iostream>
#include <math.h>
#include <vector>

namespace technicals {

    double sumx(std::vector<double> h){
        double res;
        for(auto & v : h){
            res += v;
        }
        return res;
    }

    double mean(std::vector<double> h){
        double res;
        double N = h.size();
        for(auto & v : h){
            res += v;
        }
        res /= N;
        return res;
    }

    double stdev(std::vector<double> h){
        double res;
        double N = h.size();
        double mu = mean(h);
        double factor = 1.0 / (N - 1);
        for(auto & v : h){
            res += pow(v - mu, 2);
        }
        res *= factor;
        return sqrt(res);
    }

    std::vector<double> bollinger_bands(std::vector<double> prices, int N, double level, double sign){
        
        std::vector<double> res, temp;
        double nan = std::strtod("NaN", NULL);
        double sd;
        for(int i = 0; i < N; ++i){
            res.push_back(nan);
        }
        for(int i = N; i < prices.size(); ++i){
            temp = {prices.begin() + (i - N), prices.begin() + i};
            sd = stdev(temp);
            res.push_back(prices[i] + sign*level*sd);
        }
        return res;
    }

    std::vector<double> moving_average(std::vector<double> prices, int N){
        std::vector<double> res, temp;
        double average;
        for(int i = 0; i < N; ++i){
            res.push_back(std::strtod("NaN", NULL));
        }
        for(int i = N; i < prices.size(); ++i){
            temp = {prices.begin()+(i - N), prices.begin() + i};
            average = mean(temp);
            res.push_back(average);
        }
        return res;
    }

    std::vector<double> vwap(std::vector<double> p, std::vector<double> v, int N){
        auto solve = [](std::vector<double> ux, std::vector<double> uy){
            double sumA = 0, sumB = 0;
            for(int i = 0; i < ux.size(); ++i){
                sumA += ux[i]*uy[i];
                sumB += uy[i];
            }
            return sumA/sumB;
        };
        
        std::vector<double> res, tP, tV;
        for(int i = 0; i < N; ++i){
            res.push_back(std::strtod("NaN", NULL));
        }
        for(int i = N; i < p.size(); ++i){
            tP = {p.begin()+(i-N), p.begin()+i};
            tV = {v.begin()+(i-N), v.begin()+i};
            res.push_back(solve(tP, tV));
        }
        return res;
    }

    std::vector<double> RSI(std::vector<double> prices, int N){
        auto value = [&](std::vector<double> h){
            std::vector<double> up, down;
            for(int i = 1; i < h.size(); ++i){
                if(h[i] - h[i-1] >= 0){
                    up.push_back(h[i] - h[i - 1]);
                }
                if(h[i] - h[i-1] < 0){
                    down.push_back(abs(h[i] - h[i - 1]));
                }
            }
            double u = sumx(up) / N;
            double d = sumx(down) / N;
            return 100 - 100 / (1 + u/d);
        };
        std::vector<double> res, temp;
        for(int i = 0; i < N; ++i){
            res.push_back(std::strtod("NaN",NULL));
        }
        for(int i = N; i < prices.size(); ++i){
            temp = {prices.begin()+(i-N), prices.begin()+i};
            res.push_back(value(temp));
        }

        return res;
    }

}