
import random
class Symbol:
	def __init__(self, symbol):
		self.types = {};
		self.types['+'] = 'operator';
		self.types['-'] = 'operator';
		self.types['='] = 'operator';
		self.types['*'] = 'operator';
		self.symbol = symbol;
		self.addr = random.randint(20000000,50000000);
		self.type = self.types.get(symbol, 'identifier');
	def __str__(self):
		return self.symbol + "  " + str(self.addr) + " " + self.type;
st = [];

def CreateST(string):
	for symbol in string:
		st.append(Symbol(symbol));

def InsertST(symbol):
	st.append(Symbol(symbol));

def SearchST(symbol):
	return [s for s in st if symbol == s.symbol];

def DeleteST(symbol):
	st = [s for s in st if symbol != s.symbol];

def DisplayST(st):
	for s in st:
		print(s);
def Run():
	while True:
		print("1 Create");
		print("2 Search");
		print("3 Insert");
		print("4 Remove");
		print("5 Display");
		print("6 Exit");
		choice = input('Enter Choice\t:')
	
		if (choice == '1'):
			symbol = input('String?')
			CreateST(symbol)
		if (choice == '2'):
			symbol = input('Symbol?')
			DisplayST(SearchST(symbol))
		if (choice == '3'):
			symbol = input('Symbol?')
			InsertST(symbol)
		if (choice == '4'):
			symbol = input('Symbol?')
			DeleteST(symbol)
		if (choice == '5'):
			DisplayST(st)
		if (choice == '6'):
			exit()
Run()