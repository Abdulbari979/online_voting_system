#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

class Candidate {
private:
    std::string candidateID;
    std::string name;
    int votes;

public:
    Candidate(const std::string& id, const std::string& n);

    std::string getCandidateID() const;
    std::string getName() const;
    int getVotes() const;
    void addVote();
    void setVotes(int count); // <--- ADD THIS LINE
};

#endif // CANDIDATE_H