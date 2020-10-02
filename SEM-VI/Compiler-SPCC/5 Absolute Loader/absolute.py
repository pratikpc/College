def Read(name):
    with open(name, 'r') as file:
        return [line.upper().strip().replace("\t", " ") for line in file.readlines()]
import re
def SplitString(line):
	return re.findall('.{1,2}', line)
def AsHex(num):
	return format(num, '02x')
max_pos = 0
outs = {}
lines = Read('absolute.txt')
for line in lines:
	token = line.split(' ')
	if (token[0] == 'H'):
		outs['vals'], outs['name'], outs['size'], outs['start'] =  {}, token[1], int(token[3], 16), int(token[2], 16)
		max_pos = outs['start']
	if (token[0] == 'T'):
		start, size, counter = int(token[1], 16), int(token[2], 16), 0
		for i in range(3,len(token)):
			for num in SplitString(token[i]):
				outs['vals'][start+counter] = int(num, 16)
				counter = counter + 1
				max_pos = max(start+counter, max_pos)
	if (token[0] == 'E'):
		start, size = int(token[1], 16), outs['size']
		cur_start = (start // 16) * 16
		for i in range(cur_start, max_pos):
			if(i%16 == 0):
				print (AsHex(i), end=' ')
			if i not in outs['vals'] or i < start:
				print('xx', end=' ')
			else:
				print( AsHex(outs['vals'][i]),sep='', end=' ')
			if(i%16 == 15):
				print (end='\n')
