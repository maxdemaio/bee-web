# or just use https://github.com/dwyl/english-words/
with open('/usr/share/dict/words', "r") as f, open("dict.txt", "w") as out:
  lines = f.readlines()
  for i, line in enumerate(lines):
      word = line.strip()
      if len(word) >= 4:
          out.write(word.lower())
          if i != len(lines) - 1:
              out.write("\n")