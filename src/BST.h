#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector> // For collecting results
#include "Candidate.h" // Assuming Candidate class is defined

// Node structure for the BST
struct BSTNode {
    Candidate data; // Stores a copy of the candidate object
    BSTNode* left;
    BSTNode* right;

    // Constructor
    BSTNode(const Candidate& candidate) : data(candidate), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Recursive helper for insertion. Orders by votes, then by ID for ties.
    BSTNode* insert(BSTNode* node, const Candidate& candidate) {
        if (node == nullptr) {
            return new BSTNode(candidate);
        }

        // Primary sort key: Votes (ascending order for in-order traversal from least to most votes)
        if (candidate.getVotes() < node->data.getVotes()) {
            node->left = insert(node->left, candidate);
        } else if (candidate.getVotes() > node->data.getVotes()) {
            node->right = insert(node->right, candidate);
        } else {
            // Secondary sort key: Candidate ID (for stability and unique paths if votes are equal)
            if (candidate.getCandidateID() < node->data.getCandidateID()) {
                node->left = insert(node->left, candidate);
            } else if (candidate.getCandidateID() > node->data.getCandidateID()) {
                node->right = insert(node->right, candidate);
            } else {
                // This case means a candidate with the exact same ID and vote count is being inserted.
                // In this specific BST (used for display), we don't allow duplicates.
                // The actual vote updates happen in the HashTable.
                std::cerr << "Debug: Duplicate candidate ID with same vote count attempted insertion in BST: " << candidate.getCandidateID() << std::endl;
            }
        }
        return node;
    }

    // In-order traversal to print candidates (sorted by vote count, then ID)
    void inOrderTraversal(BSTNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data.getName() << ": " << node->data.getVotes() << " votes (ID: " << node->data.getCandidateID() << ")\n";
            inOrderTraversal(node->right);
        }
    }

    // Helper to find the candidate with maximum votes (rightmost node in BST)
    const Candidate* findMaxVotes(BSTNode* node) const {
        if (node == nullptr) {
            return nullptr;
        }
        // Traverse to the rightmost node to find the highest vote count
        while (node->right != nullptr) {
            node = node->right;
        }
        return &(node->data);
    }

    // Helper for cleaning up memory (post-order traversal to delete nodes)
    void deleteTree(BSTNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    // Destructor to free memory
    ~BST() {
        deleteTree(root);
    }

    // Inserts a candidate into the BST
    void insertCandidate(const Candidate& candidate) {
        root = insert(root, candidate);
    }

    // Displays candidates in sorted order of votes (ascending)
    void displaySortedResults() const {
        inOrderTraversal(root);
    }

    // Get candidate with maximum votes
    const Candidate* getWinner() const {
        return findMaxVotes(root);
    }

    // Clears the entire tree (useful before rebuilding for new results)
    void clear() {
        deleteTree(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif // BST_H