#Humberto Atondo Martín del Campo
#A00959979

def main():

	word = input("Enter a string: ")
	letterList = []
	words = []

	for letter in word:
		if letter not in letterList:
			letterList.append(letter)
		else:
			words.append("".join(letterList))
			letterList = [letter]

	finalWord = max(x for x in words)
	lenght = max(len(x) for x in words)

	print("Word:", finalWord)
	print("Length:", lenght)

	return 0

main()