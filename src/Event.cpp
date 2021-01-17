#include "Event.hpp"

bfu::MemBlockBase* 	bfu::EventSystem::m_mBlock = 0;
/*
std::map<const char*, bfu::EventBase*, bfu::cmpByStringLength> 	
														bfu::EventSystem::m_events;
std::vector<std::pair<std::string, int>> 				bfu::EventSystem::m_propagationTargets;
bfu::udp 												bfu::EventSystem::m_udp;
bfu::udp::packet 										bfu::EventSystem::m_pkg;

*/