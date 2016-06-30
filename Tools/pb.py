import sys


'''Script to print the bytecode instructions for a compiled Lang file.'''

class InstructionSet(object):
    '''Object to hold and fetch the definitions for instructions.'''
    
    NULLARY = 0
    UNARY = 1
    BINARY = 2
    
    def __init__(self, instructions):
        if instructions:
            self.instructions = instructions
        else:
            self.instructions = []
    
    def add_instruction(self, name, byte, type):
        self.instructions.append( (name, byte, type) )
    
    def set_instructions(self, instructions):
        self.instructions = instructions
    
    def get_instructions(self):
        return self.instructions
    
    def get_name(self, byte):
        for i in self.instructions:
            if (i[1] is byte):
                return (i[0], i[2])

    def get_byte(self, name):
        for i in self.instructions:
            if (i[0] is name):
                return (i[1], i[2])


def init_instruction_set():
    '''Initialize an InstructionSet with instruction definitions.'''
    
    instructions = [ ("halt", 0,  InstructionSet.NULLARY),
                     ("push", 1,  InstructionSet.UNARY),
                     ("pop",  2,  InstructionSet.NULLARY),
    
                     ("add",  3,  InstructionSet.NULLARY),
                     ("sub",  4,  InstructionSet.NULLARY),
                     ("mul",  5,  InstructionSet.NULLARY),
                     ("div",  6,  InstructionSet.NULLARY),
                     ("mod",  7,  InstructionSet.NULLARY),
                    
                     ("jmp",  8,  InstructionSet.UNARY),
                     ("jt ",  9,  InstructionSet.UNARY),
                     ("jf ",  10, InstructionSet.UNARY),
                    
                     ("eq ",  11, InstructionSet.NULLARY),
                     ("lt ",  12, InstructionSet.NULLARY),
                     ("gt ",  13, InstructionSet.NULLARY),
                    
                     ("load", 14, InstructionSet.UNARY),
                     ("store",15, InstructionSet.UNARY),
                    
                     ("prnt", 16, InstructionSet.NULLARY),
                     ("call", 17, InstructionSet.BINARY),
                     ("ret",  18, InstructionSet.NULLARY),
                    
                     ("dup",  19, InstructionSet.NULLARY),
                    ]

    return InstructionSet(instructions)


class LangFile(object):
    '''Iterator that parses a Lang bytecode file.'''
    
    def __init__(self, file, instruction_set):
        self.inc_set = instruction_set

        self.file = file
        self.file.seek(0)
        if self._magic():
            self._valid = True
        else:
            self._valid = False

        self._index = 0
            
        self._format = "{:>8}:  {:<6} {} {}"

    def _magic(self):
        m = self.file.read(8)
        if m == "HRBDRGNS":
            return True
        else:
            return False

    def __iter__(self):
        if not self._valid:
            return None
        return self

    def next(self):
        instruction = self.file.read(1)
        if instruction == '':
            raise StopIteration()
        
        name = self.inc_set.get_name(ord(instruction))
        index = self._index
        if name[1] == InstructionSet.NULLARY:
            self._index += 1
            return self._format.format(str(index), name[0], '', '')
        elif name[1] == InstructionSet.UNARY:
            operand = ord(self.file.read(1))
            self._index += 2
            return self._format.format(str(index), name[0], str(operand), '')
        elif name[1] == InstructionSet.BINARY:
            operand1 = ord(self.file.read(1))
            operand2 = ord(self.file.read(1))
            self._index += 3
            return self._format.format(str(index), name[0], str(operand1), str(operand2))


def main():
    try:
        with open(sys.argv[1], 'rb') as f:
            inc_set = init_instruction_set()
            l = LangFile(f, inc_set)
            for i in l:
                print(i)
    except IOError as e:
        print(e)

if __name__ == '__main__':
    main()