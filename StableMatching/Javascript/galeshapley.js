//Given two sets of equal cardinality and a ranking of preferences for each set
//Find the stable matching between the two sets
// m - Array of "proposers"
// w - Array of "proposed"
// mp - dictionary of proposers preferences
// wp - dictionary of proposed preferences
// Returns stable matching as a dictionary, where the proposer is the key
// and the proposed is the value
const GaleShapley = (m, w, mp, wp) => {
  const single = m;

  //Dictionary that keeps track of who each proposer has proposed to
  const singleProposed = {};
  for (const proposer of m) {
    singleProposed[proposer] = [];
  }
  const stableMatching = {};

  const getKeyByValue = (object, value) => {
    return Object.keys(object).find(key => object[key] === value);
  }

  //While there are single proposers
  while (single.length > 0) {
    //Variable representing those that are proposing that round
    const roundProposing = single;
    for (let i = 0; i < roundProposing.length; i++) {
      const proposer = roundProposing[i];
      //For each prospect that the proposer can propose to
      for (const prospect of mp[proposer]) {
        //If they haven't proposed to that prospect yet, propose
        if (!singleProposed[proposer].includes(prospect)) {
          //If prospect is single, form engagement
          if (!Object.values(stableMatching).includes(prospect)) {
            stableMatching[proposer] = prospect;
            single.splice(single.indexOf(proposer), 1);
          } else {
            //Else, if prospect is engage
            //If prospect prefers proposer to current Engagement
            //Swap proposer and current engagement
            const currentEngagement = getKeyByValue(stableMatching, w);
            if (wp[prospect].indexOf(proposer) < wp[prospect].indexOf(currentEngagement)) {
              delete stableMatching[currentEngagement];
              stableMatching[proposer] = prospect;
              single.splice(single.indexOf(proposer), 1);
              single.push(currentEngagement);
            }
          }

          singleProposed[proposer] = prospect;
          break;
        }
      }
    }
  }

  return stableMatching;
}

module.exports = {
  GaleShapley: GaleShapley
};
