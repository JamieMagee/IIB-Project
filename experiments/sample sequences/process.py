import re
import glob
from operator import sub

for fname in glob.glob("*.yml"):
    print('Processing '+fname)
    with open(fname, "r") as myfile:
        data, frames, nextpts, prevpts = [], [], [], []
        data = ''.join([line.replace('\n', '').replace(" ", "") for line in myfile.readlines()])
        for val in re.findall(r'\[([^]]*)\]', data):
            frames.append([float(x) for x in val.split(',')])
        if "farneback" not in fname:
            for i in range(0, len(frames), 2):
                nextpts.append(frames[i])
                prevpts.append(frames[i+1])
            frames = []
            for i in range(0, len(nextpts)):
                frames.append(list(map(sub, nextpts[i], prevpts[i])))
    f = open(fname[:-4]+'.txt', 'w')
    frame_num = 2 #int(input('Which frame would you like to grab? '))
    for i in range(0, len(frames[frame_num]), 2):
        f.write(str((frames[frame_num])[i])+', '+str((frames[frame_num])[i+1])+'\n')
    f.write('\n')
    f.close()
    print('Finished processing '+fname)