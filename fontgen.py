####
	#fontgen.py - a Python 2 "compiler" for translating bitmap font definitions
	#into C code, usable by font.c.
	#Copyright (C) 2015 Adam Richardson

	#This program is free software: you can redistribute it and/or modify
	#it under the terms of the GNU General Public License as published by
	#the Free Software Foundation, either version 3 of the License, or
	#(at your option) any later version.

	#This program is distributed in the hope that it will be useful,
	#but WITHOUT ANY WARRANTY; without even the implied warranty of
	#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	#GNU General Public License for more details.

	#You should have received a copy of the GNU General Public License
	#along with this program.  If not, see <http://www.gnu.org/licenses/>.
####

table = [None] * 128

INTERNAL_SIZE = 32

while True:
	try:
		line = raw_input()
	except EOFError:
		break

	line = line.strip()
	if len(line) != 1:
		raise ValueError

	n = ord(line)
	if not (0 <= n < 128) or table[n] is not None:
		raise ValueError

	table[n] = []
	for i in xrange(INTERNAL_SIZE):
		row = raw_input().strip()
		if len(row) != INTERNAL_SIZE:
			print i
			print chr(n)
			raise ValueError

		table[n].append(int(row, 2))

	try:
		line = raw_input()
		if line.strip() != "":
			print chr(n)
			print line
			raise ValueError
	except EOFError:
		break

table[32] = ([0 for i in xrange(INTERNAL_SIZE)])

print "#ifndef _FONTDEF_H_"
print "#define _FONTDEF_H_"
print ""
print "#include <stdint.h>"
print ""
print "#define internal_size %d" % INTERNAL_SIZE
print ""

print "const uint_fast32_t fontdef[128][internal_size] =\n{"

for i in xrange(128):
	if table[i] is None:
		print "\t{" + ", ".join("0" for j in xrange(INTERNAL_SIZE)) + "}%s\t/* not implemented or blank */" % ("," if i < 127 else "")
	else:
		print "\t{ /* '%c' */" % chr(i)
		for j in xrange(INTERNAL_SIZE):
			b = bin(table[i][j])[2:]
			b = "0b" + ("0" * (INTERNAL_SIZE - len(b))) + b
			print "\t\t" + hex(table[i][j]) + ",\t/* " + b + " */"
		print "\t}" + ("," if i < 127 else "")

print "};"
print ""
print "#endif"
