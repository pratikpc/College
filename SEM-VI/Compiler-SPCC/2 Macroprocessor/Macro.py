def Write(name, data):
    data = [ala.strip() + "\n" for ala in data]
    with open(name, 'w') as file:
        file.writelines(data) 

def Read(name):
    with open(name, 'r') as file:
        Lines = file.readlines() 
        # Strips the newline character 
        Lines = [line.upper().strip().replace("\t", " ") for line in Lines];
        return Lines

def Pass1():
    Lines = Read('input.txt') 

    MNT_LINES = [];
    MDT_LINES = [];
    ALA_LINES = [];

    count = 0
    is_macro = False
    macro_lines = 0
    for line in Lines: 
        if line ==  "MACRO":
            is_macro = True
            macro_lines = 0
            continue
        if not is_macro:
            continue

        MDT_LINES.append(line)

        if line == "MEND":
            is_macro = False
            continue

        # Keep Adding Macro to MNT and MDT

        # Add First Line In
        if macro_lines == 0:
            MNT_LINES.append(line.split(' ', 1)[0])
            ALA_LINES.append(line.split(' ', 1)[0])
            ALA_LINES += line.split(' ', 1)[1].split(',')
            ALA_LINES.append("=========")
        macro_lines += 1

    Write("MNT.txt", MNT_LINES);
    Write("ALA.txt", ALA_LINES);
    Write("MDT.txt", MDT_LINES);

def FindInMDT(macro_name, MDT_LINES):
    for index, line in enumerate(MDT_LINES):
        if(line.split(' ', 1)[0] == macro_name):
            return index
def LoadALAForMacro(macro_name, ALA_LINES):
    vars = []
    idx = ALA_LINES.index(macro_name)
    idx += 1
    while True:
        vars.append(ALA_LINES[idx][1:])
        idx += 1
        if(ALA_LINES[idx] == "========="):
            break
    return vars
def Pass2():
    Lines = Read('input.txt') 
    MNT_LINES = Read('MNT.txt')
    MDT_LINES = Read('MDT.txt')
    ALA_LINES = Read('ALA.txt')
    
    count = 0
    is_started = False
    macro_lines = 0
    ESC = []
    for line in Lines: 
        if "START" in line:
            is_started = True
            ESC.append(line)
            continue
        if not is_started:
            continue
        split = line.split(' ', 1)
        macro_name = split[0]
        if len(split) == 1:
            ESC.append(line)
            continue

        if macro_name in MNT_LINES:
            ALA = (LoadALAForMacro(macro_name, ALA_LINES))
            mdt_pos = FindInMDT(macro_name, MDT_LINES)
            macro_calls = (split[1].strip().split(','))

            while True:
                mdt_pos += 1
                line = MDT_LINES[mdt_pos]
                if(line == "MEND"):
                    break
                for index, macro_call in enumerate(macro_calls):
                    line = line.replace("&" + ALA[index], macro_call)
                ESC.append(line)
            
            continue

        ESC.append(line)
    Write("ESC.txt", ESC);
Pass1()
Pass2()