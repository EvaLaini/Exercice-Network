#include "network.h"
#include "random.h"
#include <iostream>

void Network::resize(const size_t& size){
	Network::values.clear();
	for (size_t i(0); i<size ;++i){
		RandomNumbers RG;
		Network::values.push_back(RG.normal());
		}
	}

bool Network::add_link(const size_t& nodeA, const size_t& nodeB){
	if((nodeB != nodeA) and (Network::size()>nodeA) and (Network::size()>nodeB)){
		for (auto link : Network::neighbors(nodeA)){
			if (link == nodeB){
				return false;}
		}
				Network::links.insert({nodeA,nodeB});
				Network::links.insert({nodeB,nodeA});
				return true;
				}else{
				return false;
				}
		}

size_t Network::random_connect(const double& meanP){
	Network::links.clear();
	int nbLinks(0);
	RandomNumbers RG;
	std::vector<int> deg;
	deg.resize(Network::size());
	RG.poisson(deg, meanP);
	for (size_t i(0); i<Network::size(); ++i){
		
		RandomNumbers RGj;
		std::vector<int> n;
		n.resize(deg[i]);
		RGj.uniform_int(n,0, Network::size());
		for (int j(0); j<deg[i]; ++j){
				if (Network::add_link(i,n[j])){
					nbLinks++;
					}				
			}
		}
	return nbLinks;
	}

size_t Network::set_values(const std::vector<double>& _values){

	size_t nbOK(0);
	if (_values.size() <= Network::size()){
		nbOK = _values.size();
		} else {
			nbOK = Network::size();
			}
	for (size_t i(0); i < nbOK;++i){
		
	Network::values[i]= _values[i];
	}
	return nbOK;
	}

size_t Network::size() const {
	
	return Network::values.size();
	}

size_t Network::degree(const size_t &_n) const{
	
	size_t deg(0);
	deg = Network::links.count(_n);
	return deg;
	}

double Network::value(const size_t &_n) const{
	
	return Network::values[_n];
	}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sortedV(Network::values);
	std::sort(sortedV.begin(), sortedV.end());
	std::reverse(sortedV.begin(), sortedV.end());
	return sortedV;
	}

std::vector<size_t> Network::neighbors(const size_t&_n) const{
	std::vector<size_t> neighb;
	for (auto link : Network::links){
		if (link.first == _n){
			neighb.push_back(link.second);
		}
	}
	return neighb;
	}


