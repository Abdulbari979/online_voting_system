#include <iostream>
#include "Election.h"
#include <limits>

int main() {
    std::cout << "Program started. Creating Election object.\n"; // New diagnostic output
    Election election;

    std::cout << "--- Initializing Election System ---\n";
    election.loadVoters("data/voters.txt");
    election.loadCandidates("data/candidates.txt");
    std::cout << "Data loading functions called.\n"; // New diagnostic output

    election.startElection();
    std::cout << "Election started function called.\n"; // New diagnostic output

    std::cout << "Program finishing. Press Enter to close...\n"; // New diagnostic output
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    std::cin.get(); // Wait for user input

    return 0;
}