words =  set(open('passes.csv').read().split())

unique = len(words)
print "Unique ", unique, "/ 10000000 words."
print ((1-(unique/ float(10000000))) * 100), "% collisions"