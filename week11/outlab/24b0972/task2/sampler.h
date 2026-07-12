#ifndef SAMPLER_H
#define SAMPLER_H

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <cstdint>
#include <numeric>

class DeadBlockPredictor {
    private:
        static const int TABLES = 3;
        static const int ENTRIES = 4096;
        static const int THRESHOLD = 8;
        std::vector<std::vector<int>> counters;

        inline uint32_t hash1(uint32_t x)const {
            x ^= (x >> 16);
            x *= 0x7feb352d;
            x ^= (x >> 15);
            return x & 0xFFF;  // 12-bit index (0–4095)
        }

        inline uint32_t hash2(uint32_t x) const{
            x ^= (x >> 13);
            x *= 0x846ca68b;
            x ^= (x >> 16);
            return x & 0xFFF;  
        }

        inline uint32_t hash3(uint32_t x) const{
            x ^= (x << 7);
            x *= 0x165667b1;
            x ^= (x >> 11);
            return x & 0xFFF;
        }

        std::map<uint32_t,uint32_t> num_dead;
        std::map<uint32_t,uint32_t> num_live;
    public:
        DeadBlockPredictor() : counters(TABLES, std::vector<int>(ENTRIES, 0)) {}

        bool predict_to_be_dead(uint32_t signature){
            // Return true if predicted dead, false if live
            if(counters[0][hash1(signature)]+counters[1][hash2(signature)]+counters[2][hash3(signature)]>THRESHOLD) return true;
            return false;
        }

        void update(uint32_t signature, bool dead){
            // Update the predictor based on actual outcome for an LLC fill
            // ( Call this on LLC eviction and hit)
            auto i1 = hash1(signature);
            auto i2 = hash2(signature);
            auto i3 = hash3(signature);
            if(dead){
                num_dead[signature]++;
                if (counters[0][i1]<3)  counters[0][i1]++;
                if (counters[1][i2]<3)  counters[1][i2]++;
                if (counters[2][i3]<3)  counters[2][i3]++;
            } else {
                num_live[signature]++;
                if (counters[0][i1]>0)  counters[0][i1]--;
                if (counters[1][i2]>0)  counters[1][i2]--;
                if (counters[2][i3]>0)  counters[2][i3]--;
            }
            return;
        }
};
#endif 