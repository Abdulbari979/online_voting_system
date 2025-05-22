#include "Election.h"
#include <iostream>
#include <fstream>
#include <algorithm> // For std::max_element (though BST handles sorting now)
#include <sstream>   // For std::stringstream
#include <limits>    // For std::numeric_limits
#include <chrono>    // For simulating delay
#include <thread>    // For simulating delay

// Assuming these are defined in Election.h or other included headers
// For example:
// #include "Voter.h"
// #include "Candidate.h"
// #include "HashTable.h"
// #include "Queue.h"
// #include "BST.h"

Election::Election() {
    // Constructor, hash tables and queue are default-constructed
}

void Election::loadVoters(const std::string& filename) {
    std::ifstream file(filename); // Keep this declaration
    if (!file.is_open()) {       // CHANGE THIS LINE: Remove the 'std::ifstream file(filename);' part inside the if
        std::cerr << "Error: Could not open voters file: " << filename << std::endl;
        return;
    }

    std::string id;
    int loadedCount = 0;
    while (file >> id) { // Reads whitespace-separated "words" (IDs in this case)
        votersHashTable.insert(id, Voter(id)); // Insert into hash table
        loadedCount++;
    }
    file.close();
    std::cout << "Loaded " << loadedCount << " voters from " << filename << std::endl;
}

void Election::loadCandidates(const std::string& filename) {
    std::ifstream file(filename); // Keep this declaration
    if (!file.is_open()) {       // CHANGE THIS LINE: Remove the 'std::ifstream file(filename);' part inside the if
        std::cerr << "Error: Could not open candidates file: " << filename << std::endl;
        return;
    }

    std::string line;
    int loadedCount = 0;
    while (std::getline(file, line)) { // Read the entire line
        if (line.empty()) continue; // Skip empty lines

        std::stringstream ss(line);
        std::string id_str;
        std::string name_str;

        // Expecting "ID,Name" format, so read up to the comma for ID
        if (std::getline(ss, id_str, ',')) {
            // Read the rest of the line for the Name
            if (std::getline(ss, name_str)) {
                candidatesHashTable.insert(id_str, Candidate(id_str, name_str)); // Insert into hash table
                loadedCount++;
            } else {
                std::cerr << "Warning: Missing name for candidate ID: '" << id_str << "' in file " << filename << ". Skipping.\n";
            }
        } else {
            std::cerr << "Warning: Invalid format for line: '" << line << "' in file " << filename << ". Skipping.\n";
        }
    }
    file.close();
    std::cout << "Loaded " << loadedCount << " candidates from " << filename << std::endl;
}


Voter* Election::authenticateVoter() {
    std::string id;
    std::cout << "Enter Voter ID: ";
    std::cin >> id;
    // Clear the input buffer to prevent issues with subsequent cin calls
    (void)std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Added (void) to suppress warning

    Voter* voter = votersHashTable.get(id); // Use hash table for lookup
    if (voter != nullptr) {
        if (voter->getHasVoted()) {
            std::cout << "You have already voted.\n";
            return nullptr;
        }
        return voter;
    }
    std::cout << "Voter ID not found.\n";
    return nullptr;
}

void Election::displayCandidates() {
    std::cout << "\nCandidates:\n";
    // Retrieve all candidates from the hash table for display
    std::vector<Candidate> allCandidates = candidatesHashTable.getAllValues();
    if (allCandidates.empty()) {
        std::cout << "No candidates loaded.\n";
        return;
    }
    for (const auto& candidate : allCandidates) {
        std::cout << candidate.getCandidateID() << " - " << candidate.getName() << "\n";
    }
}

void Election::castVote(Voter* voter) {
    std::string candidateID_input;
    std::string candidateName_input;

    std::cout << "Enter Candidate ID (e.g., C001): ";
    std::cin >> candidateID_input;
    (void)std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Added (void) to suppress warning // Clear buffer

    std::cout << "Enter Candidate Name (e.g., Alice): ";
    std::getline(std::cin, candidateName_input); // Read full line for name

    Candidate* candidate = candidatesHashTable.get(candidateID_input); // Lookup candidate by ID

    if (candidate != nullptr) {
        // Check if the provided name matches the stored name for this ID
        if (candidate->getName() == candidateName_input) {
            // Enqueue the vote for processing later
            voteQueue.enqueue({voter->getVoterID(), candidateID_input});
            voter->setHasVoted(true); // Mark voter as having voted immediately

            std::cout << "Vote submitted successfully. It will be processed shortly.\n";
            std::cout << "Congratulations! Your vote has been recorded.\n"; // Congratulations message
        } else {
            std::cout << "Error: Candidate name '" << candidateName_input << "' does not match for ID '" << candidateID_input << "'. Please check the name.\n";
        }
    } else {
        std::cout << "Error: Candidate ID '" << candidateID_input << "' not found.\n";
    }
}

void Election::processPendingVotes() {
    if (voteQueue.isEmpty()) {
        std::cout << "No pending votes to process.\n";
        return;
    }
    std::cout << "\nProcessing pending votes...\n";
    // Simulate processing time
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    while (!voteQueue.isEmpty()) {
        PendingVote pVote = voteQueue.dequeue();
        Candidate* candidate = candidatesHashTable.get(pVote.candidateID);

        if (candidate != nullptr) {
            candidate->addVote(); // Increment vote count for the actual candidate object
            std::cout << "Vote for " << candidate->getName() << " (ID: " << candidate->getCandidateID() << ") from Voter " << pVote.voterID << " processed.\n";
        } else {
            std::cerr << "Warning: Candidate ID '" << pVote.candidateID << "' from pending vote not found in candidate list. Vote not counted.\n";
        }
    }
    std::cout << "All pending votes processed.\n";
}


void Election::displayResults() {
    std::cout << "\n--- Election Results ---\n";

    // First, process any votes that are still in the queue
    processPendingVotes();

    // Get all candidates from the hash table (where actual vote counts are stored)
    std::vector<Candidate> currentCandidates = candidatesHashTable.getAllValues();

    if (currentCandidates.empty()) {
        std::cout << "No candidates to display results for.\n";
        return;
    }

    // Build a BST from the current candidate data to display sorted results
    BST resultsBST;
    for (const auto& candidate : currentCandidates) {
        resultsBST.insertCandidate(candidate);
    }

    if (resultsBST.isEmpty()) {
        std::cout << "No valid candidates in results tree.\n";
        return;
    }

    std::cout << "\nCandidates by Votes (Lowest to Highest):\n";
    resultsBST.displaySortedResults(); // Displays candidates sorted by votes

    // Find the winner(s)
    const Candidate* winner = resultsBST.getWinner();
    if (winner != nullptr) {
        int maxVotes = winner->getVotes();
        std::vector<std::string> winnersNames;
        std::vector<std::string> winnersIDs; // To store IDs for tie-breaking by ID
        for (const auto& cand : currentCandidates) {
            if (cand.getVotes() == maxVotes) {
                winnersNames.push_back(cand.getName());
                winnersIDs.push_back(cand.getCandidateID());
            }
        }

        if (winnersNames.size() > 1) {
            std::cout << "\nIt's a tie! Multiple winners with " << maxVotes << " votes:\n";
            // Sort tied winners alphabetically by name or ID for consistent display
            std::sort(winnersNames.begin(), winnersNames.end());
            for (const auto& name : winnersNames) {
                std::cout << "- " << name << "\n";
            }
        } else {
            std::cout << "\nWinner: " << winner->getName() << " with " << winner->getVotes() << " votes.\n";
        }
    } else {
        std::cout << "\nNo winner determined (perhaps no votes cast).\n";
    }
}


void Election::startElection() {
    int choice;
    do {
        std::cout << "\n--- Election System Menu ---\n";
        std::cout << "1. Cast Vote\n";
        std::cout << "2. Process Pending Votes (Manual Trigger)\n"; // New option
        std::cout << "3. View Results\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Handle invalid input for choice (non-integer)
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear the error flag
            (void)std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Added (void) to suppress warning // Discard invalid input
            continue; // Go back to the start of the loop
        }
        (void)std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Added (void) to suppress warning // Clear remaining newline character

        switch (choice) {
            case 1: {
                Voter* voter = authenticateVoter();
                if (voter) {
                    displayCandidates(); // Display candidates before prompting for vote
                    castVote(voter);
                }
                break;
            }
            case 2: // New case for processing votes
                processPendingVotes();
                break;
            case 3:
                displayResults();
                break;
            case 0:
                std::cout << "Exiting election system.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}