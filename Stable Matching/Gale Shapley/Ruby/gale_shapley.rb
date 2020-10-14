def gale_shapley(men_prefs, women_prefs)
  men = men_prefs.keys
  women = women_prefs.keys
  matches = {}
  until men.empty?
    m = men[0]
    w = men_prefs[m].shift
    if matches.has_value?(w)
      mtag = matches.key(w)
      if women_prefs[w].index(mtag) > women_prefs[w].index(m)
        matches[m] = w
        matches.delete(mtag)
        men.shift
      end
    else
      matches[m] = w
      men.shift
    end
  end
  matches
end

men_prefs = {
  'A': %w[Y X Z],
  'B': %w[Z Y X],
  'C': %w[X Z Y]
}
women_prefs = {
  'X': %w[B A C],
  'Y': %w[C B A],
  'Z': %w[A C B]
}

puts gale_shapley(men_prefs, women_prefs)
