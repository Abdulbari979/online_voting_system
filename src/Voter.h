#ifndef VOTER_H
#define VOTER_H

#include <string>

class Voter {
private:
    std::string voterID;
    bool hasVoted;

public:
    // Constructor for voters with only an ID
    Voter(const std::string& id);

    std::string getVoterID() const;
    bool getHasVoted() const;
    void setHasVoted(bool voted);
};

#endif // VOTER_H