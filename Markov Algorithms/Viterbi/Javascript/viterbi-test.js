const Viterbi = require('./viterbi.js').Viterbi;

const obs = ["normal", "cold", "dizzy"]
const states = ["Healthy", "Fever"]
const start_p = {"Healthy": 0.6, "Fever": 0.4}
const trans_p = {
    "Healthy": {"Healthy": 0.7, "Fever": 0.3},
    "Fever": {"Healthy": 0.4, "Fever": 0.6},
}
const emit_p = {
    "Healthy": {"normal": 0.5, "cold": 0.4, "dizzy": 0.1},
    "Fever": {"normal": 0.1, "cold": 0.3, "dizzy": 0.6},
}

console.log(Viterbi(obs, states, start_p, trans_p, emit_p));

//Expected Output:
// { opt: [ 'Healthy', 'Healthy', 'Fever' ], prob: 0.01512 }
