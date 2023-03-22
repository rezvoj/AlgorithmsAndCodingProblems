import sys


def rec(words, pos, dicti, trns, done):
    if len(words) <= pos:
        return done 
    

    for pmatch in dicti[len(words[pos])]:
        skip = False
        ntrns = {**trns}
        for f, t in zip(words[pos], pmatch):
            if f in ntrns: 
                if ntrns[f] != t:
                    skip = True
                    break
            elif t in ntrns.values():
                skip = True
                break
            else:
                ntrns[f] = t
        if not skip:
            ndone = {**done, words[pos]: pmatch}
            res = rec(words, pos + 1, dicti, ntrns, ndone)
            if res is not None:
                return res
    return None


if __name__ == "__main__":
    num = int(sys.stdin.readline().rstrip())
    dicti = [set() for _ in range(17)]
    for _ in range(num):
        word = sys.stdin.readline().rstrip()
        dicti[len(word)].add(word)
    for line in sys.stdin:
        words = line.rstrip().split(" ")
        swords = sorted(words, key=lambda x: -len(x))
        res = rec(swords, 0, dicti, dict(), dict())
        if res == None:
            print(" ".join(['*' * len(wrd) for wrd in words]))    
        else:
            print(" ".join([res[wrd] for wrd in words]))
