# Bitkeg, yet another key-value store

Bitkeg is a C++ implementation of [Bitcask](https://riak.com/assets/bitcask-intro.pdf),
a K-V store based on the log-structured merge tree. It is modified for optimized scans and other enhancements.

Progress:
- [ ] Initial Bitcask implementation
- [ ] Optimize in-memory dictionary for faster scans
- [ ] Add a bloom filter because, why not?