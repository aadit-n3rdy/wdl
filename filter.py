a = open('words_all.txt', 'r')
b = open('words.txt', 'w')

for l in a:
    if len(l) == 6:
        b.write(l)

a.close()
b.close()
