#!python3.7

import argparse
import shutil

# These parameters change the hashing characteristics
BASE = 256
PRIME_MODULO = 1000000007


# function to setup argparse arguments
def setup_arguments():
    parser = argparse.ArgumentParser(description="Rabin-Karp string matching demo")
    parser.add_argument("haystack", help="String to search needle(pattern) in")
    parser.add_argument("needle", help="Pattern to search for in haystack")
    parser.add_argument("-t", "--test",
                        action="store_true",
                        help="Test rolling hash functions - All other parameters are ignored")
    return parser.parse_args()


# compute new hash from scratch
def static_hash(p_word):
    l_hash = 0
    for i in range(len(p_word)):
        l_hash = ((l_hash * BASE) + ord(p_word[i])) % PRIME_MODULO
    return l_hash


# compute new hash using existing hash, removed char, appended char and needle length
def rolling_hash(p_prev_hash, p_first_char, p_next_char, p_length):
    l_first_char_hash = (ord(p_first_char) * pow(BASE, p_length - 1, PRIME_MODULO)) % PRIME_MODULO
    l_new_hash = (((p_prev_hash - l_first_char_hash) * BASE) + ord(p_next_char)) % PRIME_MODULO
    return l_new_hash if l_new_hash > 0 else l_new_hash + PRIME_MODULO


# function to execute rabin-karp string matching
def rabin_karp(haystack, needle):
    if len(haystack) < len(needle):
        return None

    l_pattern_hash = static_hash(p_word=needle)
    l_prev_hash = static_hash(p_word=haystack[:len(needle)])

    for i in range(1, len(haystack) - len(needle) + 1):
        if l_prev_hash == l_pattern_hash:
            return i
        l_prev_hash = rolling_hash(p_prev_hash=l_prev_hash,
                                   p_first_char=haystack[i - 1],
                                   p_next_char=haystack[i + len(needle) - 1],
                                   p_length=len(needle))
    if l_prev_hash == l_pattern_hash:
        return len(haystack) - len(needle) + 1
    return None


# function to test if rolling hash is valid
def test_hash():
    word1 = "Hello"
    word2 = "elloW"
    word1_hash = static_hash(word1)
    word2_hash = static_hash(word2)
    print(f"Static hash [{word1}] : {word1_hash}")
    print(f"Static hash [{word2}] : {word2_hash}")
    rolled_hash = rolling_hash(word1_hash, 'H', 'W', len(word1))
    print(f"Rolling Hash : {rolled_hash}")
    print(f"Hash {'matched' if rolled_hash == word2_hash else 'mismatch'}")


def main():
    args = setup_arguments()
    if args.test:
        test_hash()
        return
    l_position = rabin_karp(args.haystack, args.needle)
    if l_position is None:
        print(f"Pattern [{args.needle}] not found in string[{args.haystack}]")
    else:
        out_str = f"Pattern [{args.needle}] found at position [{l_position}] in string[{args.haystack}]"
        print(out_str)

        # Display a visual cue "^" at the position ( only activate if the out_str can be printed in one line )
        console_width = int((shutil.get_terminal_size((80, 20)))[0])
        if len(out_str) < console_width:
            print(f"{' ' * (len(out_str) - len(args.haystack) - 1 + l_position - 1)}^")


if __name__ == '__main__':
    main()
