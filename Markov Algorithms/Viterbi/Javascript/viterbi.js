// Given an array of observations, an array of possible states, the starting
// probabilities for each state, the transition probabilities between states,
// and the probabilities of observations being emitted from each state, return
// an object of the most likely state path and the probability of that path.
// obs - array of observations
// states - array of possible states
// start_p - starting probabilities
// trans_p - transition probabiltiies
// emit_p - emit probabilities
const Viterbi = (obs, states, start_p, trans_p, emit_p) => {
  // Set up initial starting probabilties of emitting initial observation
  const V = [{}];
  for (const s of states) {
    V[0][s] = {
      prob: start_p[s] * emit_p[s][obs[0]],
      prev: ""
    };
  }

  //For the rest of the observations
  for (let i = 1; i < obs.length; i++) {
    V.push({});
    //For each possible state
    for (const s of states) {
      //Find the maximum transition probability into that state
      let max_tr_prob = V[i-1][states[0]].prob * trans_p[states[0]][s];
      let prev_state_selected = states[0];

      for (const prev_state of states.slice(1,)) {
        tr_prob = V[i-1][prev_state].prob * trans_p[prev_state][s];
        if (tr_prob > max_tr_prob) {
          max_tr_prob = tr_prob;
          prev_state_selected = prev_state;
        }

        //The probability of the state emitting the current observation
        const max_prob = max_tr_prob * emit_p[s][obs[i]];
        V[i][s] = {
          prob: max_prob,
          prev: prev_state_selected
        };
      }
    }
  }

  //Find final state with maximum probability
  const opt = [];
  let max_prob = 0.0;
  let previous = ""
  for (const s of Object.keys(V[V.length - 1])) {
    const data = V[V.length - 1][s];
    if (data.prob > max_prob) {
      max_prob = data.prob;
      previous = s;
    }
  }
  opt.push(previous);

  //Backtrack from final state to generate optimal path
  for (let i = V.length - 2; i > -1; i--) {
    const p = V[i+1][previous].prev;
    opt.unshift(p);
    previous = p;
  }

  return {opt: opt, prob: max_prob};
};

module.exports = {
  Viterbi
}
