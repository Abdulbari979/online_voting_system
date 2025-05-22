#include "Candidate.h" // Make sure this includes the correct header file

// Constructor implementation
Candidate::Candidate(const std::string& id, const std::string& n)
        : candidateID(id), name(n), votes(0) {}

std::string Candidate::getCandidateID() const {
    return candidateID;
}

std::string Candidate::getName() const {
    return name;
}

int Candidate::getVotes() const {
    return votes;
}

void Candidate::addVote() {
    votes++;
}

// Definition for the setVotes method
// This must match the declaration in Candidate.h exactly
void Candidate::setVotes(int count) {
    votes = count;
}