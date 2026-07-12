#include <algorithm>
#include <iterator>
#include <map>

#include "cache.h"
#include "util.h"

std::map<CACHE*,std::vector<uint16_t>> IP;
std::map<uint16_t,uint8_t> pcCount;

void CACHE::initialize_replacement() {
  IP[this] = std::vector<uint16_t>(NUM_SET * NUM_WAY,0);
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
  uint8_t minpc = 255;   
  uint32_t evi = 0;
  for (uint32_t i=0; i < NUM_WAY; i++) {
    if(pcCount[IP[this][set * NUM_WAY+i]]<minpc){
        minpc = pcCount[IP[this][set * NUM_WAY+i]];
        evi=i;
    }
  }
  return evi;
  assert(false);

}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
  if (hit && type == WRITEBACK)  {
    return;
  }
  uint16_t pc = ip & 0xFFFF;
  
  if(!hit){
    if(pcCount[pc]>0) pcCount[pc]--;
    IP[this][set * NUM_WAY+way] = pc;
  }else{
    if(pcCount[pc]<255) pcCount[pc]++;
  }

}

void CACHE::replacement_final_stats() {}
