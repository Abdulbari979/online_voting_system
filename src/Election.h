#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include <vector> // Still useful for general purposes or temporary lists
#include "Voter.h"
#include "Candidate.h"
#include "HashTable.h" // Include the HashTable header
#include "Queue.h"     // Include the Queue header
#include "BST.h"       // Include the BST header

// Define a simple struct for a pending vote to be enqueued
struct PendingVote {
    std::string voterID;
    std::string candidateID;
};

class Election {
private:
    HashTable<std::string, Voter> votersHashTable;         // Stores voters by ID
    HashTable<std::string, Candidate> candidatesHashTable; // Stores candidates by ID
    Queue<PendingVote> voteQueue;                         // Queue for pending votes

public:
    Election(); // Constructor

    void loadVoters(const std::string& filename);
    void loadCandidates(const std::string& filename);

    // Authenticates voter using the hash table
    Voter* authenticateVoter();

    // Displays candidates from the hash table
    void displayCandidates();

    // Enqueues a vote
    void castVote(Voter* voter);

    // Processes votes from the queue and updates candidate votes in hash table
    void processPendingVotes();

    // Builds a BST from current candidates in hash table and displays results
    void displayResults();

    void startElection();
};

#endif // ELECTION_H