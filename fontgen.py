table = [None] * 128

while True:
	try:
		line = raw_input()
	except:
		break

	line = line.strip()
	if len(line) != 1:
		raise ValueError

	n = ord(line)
	if table[n] is not None:
		raise ValueError

	table[n] = []
	for i in xrange(8):
		row = raw_input().strip()
		if len(row) != 8:
			raise ValueError

		table[n].append(int(row, 2))

	try:
		if raw_input().strip() != "":
			raise ValueError
	except:
		break

table[32] = ([0 for i in xrange(8)])

print "#ifndef _FONTDEF_H_"
print "#define _FONTDEF_H_"
print ""
print "#include <stdint.h>"
print ""

print "const uint_fast8_t fontdef[128][8] =\n{"

for i in xrange(128):
	if table[i] is None:
		print "\t{0, 0, 0, 0, 0, 0, 0, 0}%s\t/* not implemented or blank */" % ("," if i < 127 else "")
	else:
		print "\t{ /* '%c' */" % chr(i)
		for j in xrange(8):
			b = bin(table[i][j])[2:]
			b = "0b" + ("0" * (8 - len(b))) + b
			print "\t\t" + hex(table[i][j]) + ",\t/* " + b + " */"
		print "\t}" + ("," if i < 127 else "")

print "};"
print ""
print "#endif"
