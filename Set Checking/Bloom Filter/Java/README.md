# Bloom Filter Basic Implementation

Bloom Filters are used in operations which require a fast response and have limited memory.

In this case it's a probablistic approach to check if a URL belongs to the Blacklisted (Unsafe) list of URLs or not.

Motivation is [here](https://www.eecs.harvard.edu/~michaelm/postscripts/tr-02-05.pdf)

The drawback of a Bloom Filter is that it may result in false positives (in our case URLs which are safe maybe labelled as unsafe). However no unsafe URL will be marked as safe which is a strength of this data structure.

Used [Guava](https://github.com/google/guava) for the Hashing Algorithms.
