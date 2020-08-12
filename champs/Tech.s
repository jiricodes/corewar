.name "Technical"
.comment "Advanced strats and asm showcase"

start:
		ld %0x0FFE0C00, r8		#0FF83000 == 267923456 == lfork %-500 (for defence)
		st r8, -11
erase:
		st r1, r2				#copy id to r2 (enemy can hijack train)
		st r8, :erase			#delete id copy
		ld %0, r15				#carry = 1
		zjmp %:prep

tower:
		fork %:write
		ld %-400, r11
		ld %0x0C09FFBB, r4		#1409FFBB == 151650235 == (0C) zjmp %-69 (0E is extra byte we don't need)
		ld %0x0C09FE67, r13		#1409FE67 == 352976487 == (0C) zjmp %-409 (12 == 0C is chosen because it is fork)
		ld %-60, r5
		st r13, -451
		ld %0, r13
		zjmp %-467

write:
		ld %-404, r11
		ld %0x0B540405, r4		#0B540405 == 190055429 == sti r4, r5... (sti needs 5 bytes, can only fit 4)
		ld %0x0B54040B, r14		#0B54040B == 190055435 == sti r4, r11...
		ld %-64, r5
		st r14, -498
		ld %0, r13
		zjmp %-510

prep:
		st r2, :def+1			#with arg math, can use st like sti
prep2:
		st r2, :zork+1
		st r8, :prep			#delete write
		st r8, :prep2
main:
		live %1
		fork %:tower			#create disruption from below
		live %1
		fork %:lastguy			#make a train

def:
		live %1
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		st r8, -500
		zjmp %:zork

lastguy:						#this guys job is to write our id for live
		live %1
		fork %:middleguy
		live %1
		fork %:firstguy
		st r8, -249				#pointless instru, have to line up first, middle, last...
		ld %16, r3
		ld %0, r5
		zjmp %:gogogo

middleguy:						#this guy writes the sti last byte and live
		live %1
		fork %:lastguy
		ld %0x04010000, r2		#04010000 == 67174400 == r4 live...
		ld %14, r3				#writing pos
		ld %0, r4				#activate carry
		zjmp %:gogogo

firstguy:						#this guy writes the writer
		ld %0x0B540203, r2		#0B540203 == 190054915 == sti r2, r3...
		ld %10, r3				#writing pos
		ld %0, r4				#activate carry
		zjmp %:gogogo

zork:
		live %1
		zjmp %:zork

gogogo:
		sti r2, r3, r4			#instruction that starts the train
		live %1
