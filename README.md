# Online Voting System (C++)

This is a C++ console-based Online Voting System. It simulates a basic election process including candidate registration, voter registration, vote casting, and result display.

## 📁 Project Structure

```
src/
├── main.cpp
├── Candidate.cpp / Candidate.h
├── Voter.cpp / Voter.h
├── Election.cpp / Election.h
├── Queue.h
├── HashTable.h
├── BST.h
├── clang_verbose_output.txt
cmake-build-debug/
data/
├── Voters.txt
├── candidates.txt
```

## 🚀 Features

- Candidate & Voter management
- Secure vote casting
- Results tallying
- File-based data storage (`data/` folder)

## 🛠 Build & Run

### Requirements
- C++ Compiler (g++, clang, etc.)
- CMake (optional for build)

### Compile manually:
```bash
g++ src/*.cpp -o online_voting_system
```

### Or using CMake:
```bash
mkdir build
cd build
cmake ..
make
./online_voting_system
```

## 📦 Data Files

- `data/Voters.txt`: List of registered voters
- `data/candidates.txt`: List of candidates

## 📄 License

This project is licensed under the MIT License.

## 🙌 Acknowledgements

Developed by Abdulbari979.
