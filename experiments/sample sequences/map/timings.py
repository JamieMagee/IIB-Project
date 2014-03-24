import glob
import re

for fname in glob.glob('*.txt'):
    with open(fname, "r") as myfile:
        f = open(fname[:-4]+'average.txt', 'w')
        average, frames, count = 0, 0, 0
        for line in myfile.readlines():
            if re.findall('\d+\.\d{2}', line):
                if count != 0:
                    average += float(''.join(re.findall('\d+\.\d{2}', line)))
                    frames += 1
                count += 1
            else:
                if line is not '\n' and not re.findall('0\.\d{2}', line):
                    if re.findall('Output', line):
                        f.write(line)
                    if average is not 0:
                        f.write("{0:.2f}".format(average/frames)+'s average per frame\n\n')
                    average, frames, count = 0, 0, 0
        f.close()