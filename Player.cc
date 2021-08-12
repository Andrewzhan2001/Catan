#include "Player.h"
#include "Dice.h"
#include "DiceFactory.h"
#include <string>
#include <random>
#include <algorithm>
#include <iostream>
#include <utility>

Player::~Player() {}

Player::Player()
	: buildpoints{ 0 }, color{ "" }, resources{ {{"BRICK", 0},
													{"ENERGY", 0},
													{"GLASS", 0},
													{"HEAT", 0},
													{"WIFI", 0}} },
	roads{}, residences{}, dice{ "load" } {
	d.emplace_back(DiceFactory::createObject("FairDice"));
	d.emplace_back(DiceFactory::createObject("LoadedDice"));
}

void Player::setDice(std::string type) {
	dice = type;
	std::cout << "Switches to " << type << " dice." << std::endl;
}

void Player::setBuildPoints(int point) {
	buildpoints = point;
}

Dice* Player::getDice() {
	if (dice == "fair") {
		return d[0].get();
	}
	else {
		return d[1].get();
	}
}

int Player::rollDice() {
	Dice* d = getDice();
	int retval = 0;
	if (dice == "fair") {
		// fair dice, roll twice
		retval += d->getNum();
		retval += d->getNum();
	}
	else {
		retval += d->getNum();
	}
	return retval;
}

void Player::pointIncrement() { ++buildpoints; }

void Player::modifyResources(const std::string type, int amount) {
	for (auto& it : resources) {
		if (it.first == type) {
			it.second += amount;
		}
	}
}

void Player::addBasement(int x) {
	residences.emplace_back(x, 'B');
}

int Player::getResources(const std::string type) {
	int retval = -1;
	for (auto it : resources) {
		if (it.first == type) {
			retval = it.second;
			break;
		}
	}
	return retval;
}

int Player::getTotal() {
	int sum = 0;
	for (auto it : resources) {
		sum += it.second;
	}
	return sum;
}

int Player::getPoints() const { return buildpoints; }

std::string Player::getColor() const { return color; }

void Player::setColor(std::string color) { this->color = std::move(color); }

void Player::setResource(const std::vector<std::pair<std::string, int>>& r) {
	resources.clear();
	resources = r;
}

void Player::setseed(size_t seed) {
	this->seed = seed;
	this->rng = std::default_random_engine{ seed };
	for (auto&& i : d) {
		i->setseed(seed);
	}
}

void Player::setResidence(int x, char type) {
	residences.push_back(std::make_pair(x, type));
}

void Player::setRoad(int x) {
	roads.push_back(x);
}

bool Player::attempbuild(int x, char type) {
	// store the buildingpoint that needs to be added, only add
	// if has enough resource
	int addPoint = 0;
	// store all visited resource numbers, recover if needed
	std::vector<int> oldNum;
	// check resources and modify
	for (auto it = resources.begin(); it != resources.end(); ++it) {
		oldNum.push_back(it->second);
		if ((type == 'B') && (it->first != "HEAT")) {
			it->second = it->second - 1;
			addPoint = 1;
		}
		else if (type == 'H') {
			if (it->first == "GLASS") {
				it->second = it->second - 2;
			}
			else if (it->first == "HEAT") {
				it->second = it->second - 3;
			}
			addPoint = 2;
		}
		else if (type == 'T') {
			if (it->first == "BRICK")
				it->second = it->second - 3;
			if ((it->first == "ENERGY") || (it->first == "GLASS") ||
				(it->first == "HEAT"))
				it->second = it->second - 2;
			if (it->first == "WIFI")
				it->second = it->second - 1;
			addPoint = 3;
		}
		else if (type == 'R') {
			if ((it->first == "HEAT") || (it->first == "WIFI"))
				it->second = it->second - 1;
			addPoint = 0;
		}
		if (it->second < 0) { // if not enough resource
		  // recover modified numbers
			for (size_t i = 0; i < oldNum.size(); i++) {
				resources[i].second = oldNum[i];
			}
			return false;
		}
	} // loop
	// reach here means enough resource
	buildpoints += addPoint;
	// modify residence/road
	if (type == 'R') {
		roads.push_back(x);
	}
	else {
		residences.emplace_back(x, type);
	}
	return true;
}

void Player::loseHalf() {
	const std::vector<std::pair<std::string, int>> Oldresources = resources;
	int total = getTotal();
	if (total >= 10) {
		total /= 2;
		std::cout << "Builder " << getColor() << " loses " << total
			<< " resources to the geese. They lose:" << std::endl;
		while (total > 0) { // make sure the sum of deduction is half
			for (auto& i : resources) {
				int max = total;
				if (i.second < total) {
					max = i.second;
				}
				std::uniform_int_distribution<> distr(0, max); // define the range
				const int lose = distr(rng);
				modifyResources(i.first, -lose); // generate number and modify
				total -= lose;
				if (total <= 0) { // half has been deducted
				  // print the total lose of each resource
					int idx = 0;
					for (auto& i : resources) {
						const int change = (Oldresources[idx].second) - (i.second);
						if (change != 0) { // losed some resources of this type
							std::cout << change << " " << i.first << std::endl;
						}
						idx++;
					}

					return;
				}
			} // for
		}   // while
	} // if
}

bool Player::belongs(int x, char type) {
	if (type == 'R') {
		for (auto& i : roads) {
			if (i == x)
				return true;
		}
	}
	else {
		for (auto& i : residences) {
			if (i.first == x) {
				return true;
			}
		}
	}
	// not found
	return false;
}

void Player::printBuildings() {
	std::cout << getColor() << " has built:" << std::endl;
	for (auto& i : residences) {
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Player::printStatus() {
	std::cout << getColor() << " has " << buildpoints << " building points, ";
	for (int i = 0; i <= 3; i++) {
		std::cout << resources[i].second << " " << resources[i].first << ", ";
	}
	std::cout << "and " << resources[4].second << " " << resources[4].first << "."
		<< std::endl;
}

bool Player::upgradeResidence(int x) {
	for (auto& i : residences) {
		if (i.first == x) {
			if (i.second == 'T') {
				return false;
			}
			else if (i.second == 'B') {
				// if has enough resource
				if (attempbuild(x, 'H')) {
					buildpoints--;         // since one basement delete
					residences.pop_back(); // do not add this residence
					for (auto& i : residences) {
						if (i.first == x) {
							if (i.second == 'B') {
								i.second = 'H';
							}
						}
					}
					return true;
				}
			}
			else if (i.second == 'H') {
				if (attempbuild(x, 'T')) { // point += 3
					buildpoints -= 2;        // since one house deleted
					residences.pop_back();   // do not add this residence
					for (auto& i : residences) {
						if (i.first == x) {
							if (i.second == 'H') {
								i.second = 'T';
							}
						}
					}
					return true;
				}
			}
			break;
		}
	}
	return false;
}

void Player::award(int x, const std::string type) {
	for (auto& i : residences) {
		if (i.first == x) {
			if (i.second == 'T') {
				modifyResources(type, 3);
			}
			else if (i.second == 'H') {
				modifyResources(type, 2);
			}
			else if (i.second == 'B') {
				modifyResources(type, 1);
			}
			return;
		}
	}
}

void Player::printData(std::ostream& out) {
	out << resources[0].second << " " << resources[1].second << " ";
	out << resources[2].second << " " << resources[3].second << " ";
	out << resources[4].second << " "
		<< "r ";
	for (auto p : roads) {
		out << p << " ";
	}
	out << "h ";
	for (size_t i = 0; i < residences.size(); ++i) {
		if (i != residences.size() - 1) {
			out << residences[i].first << " " << residences[i].second << " ";
		}
		else {
			out << residences[i].first << " " << residences[i].second;
		}
	}
}

std::string Player::loseOneResourceRandomly() {
	std::vector<std::string>
		hasResource; // store the resource that builder has num > 0
	for (auto& i : resources) {
		// if player has this resource, add number of this resource times
		for (int j = 0; j < i.second; j++) {
			hasResource.push_back(i.first);
		}
	}
	std::shuffle(hasResource.begin(), hasResource.end(), rng);
	std::string random_resource = hasResource[0];
	modifyResources(random_resource, -1); // modify
	return random_resource;
}

bool Player::hasType(const std::string type) {
	for (auto i : resources) {
		if (i.first == type) {
			if (i.second > 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}