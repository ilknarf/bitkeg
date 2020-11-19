# Bitkeg, yet another key-value store

Bitkeg is a C++ implementation of [Bitcask](https://riak.com/assets/bitcask-intro.pdf),
a log-structured K-V store. It is modified for optimized scans and other enhancements.

Progress:
- [x] Initialization of a keg
- [x] Generation of random storage files
- [x] Write to a keg
- [x] Storage of entries on in-memory keydir (currently `unordered_map`)
- [x] Get values from disk using keydir
- [x] Fold over all values using accumulator function
- [ ] Load existing keg into memory
- [ ] Add merge algorithm to flatten keg
- [ ] Add `flock` to keg