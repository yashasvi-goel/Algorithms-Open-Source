const matching = require('./galeshapley.js');

const men = ['A', 'B', 'C'];
const women = ['X', 'Y', 'Z'];
const men_preference = {
  A: ['Y', 'X', 'Z'],
  B: ['Z', 'Y', 'X'],
  C: ['X', 'Z', 'Y']
};
const women_preference = {
  X: ['B', 'A', 'C'],
  Y: ['C', 'B', 'A'],
  Z: ['A', 'C', 'B']
};

console.log(matching.GaleShapley(men, women, men_preference, women_preference));

// Expected Output:
// { A: 'Y', C: 'X', B: 'Z' }
