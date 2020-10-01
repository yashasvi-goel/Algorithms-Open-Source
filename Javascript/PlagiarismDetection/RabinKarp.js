const SingleCharacterHash = (char, vector = 0) => {
  return char.charCodeAt(0) * 256 ** vector;
};

const Hash = (str) => {
  const add = (a, b) => {return a+b};
  return str.split('').map(SingleCharacterHash).reduce(add, 0);
};

const ShiftHash = (hash, firstChar) => {
  return (hash - Hash(firstChar)) / 256;
};

const PushHash = (hash, strLen, nextChar) => {
  return hash + SingleCharacterHash(nextChar, strLen-1);
};

const RollingHash = (hash, firstChar, nextChar, strLen) => {
  const shiftedHash = ShiftHash(hash, firstChar);
  return PushHash(shiftedHash, strLen, nextChar);
};

//TODO: Implement Multipattern search
// s - String to be searched
// pattern - String pattern to be matched
// returns index of string patern, or -1 if not found
const RabinKarp = (s, pattern) => {
  let hpattern = Hash(pattern);
  const n = s.length;
  const m = pattern.length;
  let hs = -1;
  for (i = 0; i < n-m+1; i++) {
    if (hs === -1) {
      hs = Hash(s.substring(i, i+m));
    }
    else {
      hs = RollingHash(hs, s[i-1], s[i+m-1], m);
    }

    if (hs === hpattern) {
      if (s.substring(i, i+m) === pattern) {
        return i;
      }
    }
  }
  return -1;
}

module.exports = {
  SingleSearch: RabinKarp
};
