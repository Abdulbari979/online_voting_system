
#include "Voter.h"

// Constructor implementation
Voter::Voter(const std::string& id) : voterID(id), hasVoted(false) {}

std::string Voter::getVoterID() const {
    return voterID;
}

bool Voter::getHasVoted() const {
    return hasVoted;
}

void Voter::setHasVoted(bool voted) {
    hasVoted = voted;
}