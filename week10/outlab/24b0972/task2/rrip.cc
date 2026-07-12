#include <algorithm>
#include <iterator>
#include <map>

#include "cache.h"
#include "util.h"

std::map<CACHE*,std::vector<uint8_t>> rripBits;

void CACHE::initialize_replacement() {
  rripBits[this] = std::vector<uint8_t>(NUM_SET * NUM_WAY);
  for (int i=0; i < NUM_SET * NUM_WAY; i++) {
    rripBits[this][i] = 0;
  }
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{

  std::vector<uint32_t> evirow;  
  for (uint32_t i=0; i < NUM_WAY; i++) {
    if (rripBits[this][set * NUM_WAY + i] == 0) {
      evirow.push_back(i);
    }
  }
  uint32_t s = evirow.size();
  if(s==0){
    uint8_t minr = 7;
    for (uint32_t i=0; i < NUM_WAY; i++) {
        if(rripBits[this][set * NUM_WAY + i]<minr) minr = rripBits[this][set * NUM_WAY + i];
    }
    for (uint32_t i=0; i < NUM_WAY; i++) {
        rripBits[this][set * NUM_WAY + i]-=minr;
        if(rripBits[this][set * NUM_WAY + i]==0) evirow.push_back(i);
    }
    s = evirow.size();
  }
  return evirow[rand()%s];

  assert(false);

}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
  if (hit && type == WRITEBACK)  {
    return;
  }
    if(!hit){
        rripBits[this][set * NUM_WAY + way]=1; 
    } else{
        rripBits[this][set * NUM_WAY + way]=7;
    }

}

void CACHE::replacement_final_stats() {}
