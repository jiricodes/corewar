.name "test"
.comment "testing"

#train						firstguy	middleguy	lastguy
#0b5401020301ffffffff == 0b540102 - 03010000 - ffffffff == sti r1, r2, r3 live %id

#tower					tower	write	
#0b5404050909ffbb == 0909ffbb - 0b540405 == sti r4, r5, r9 zjmp %-69


start:
		ld %267923456, r8		#lfork %-2000
		st r8, -11
erase:
		st r1, r2				#copy id to r2
		st r8, :erase			#delete id copy
		ld %0, r15				#carry = 1
		zjmp %:prep

tower:
		fork %:write
		ld %-400, r11
		ld %151650235, r4		#0909FFBB == 09 + zjmp %-69 (09 is pointless byte, just need empty reg)
		ld %151649895, r15		#0909FE67
		ld %-60, r5
		st r15, -451
		ld %0, r15
		zjmp %-467

write:
		ld %-404, r11
		ld %190055429, r4		#0B540405 == sti r4, r5...
		ld %190055435, r12		#0B54040B
		ld %-64, r5
		st r12, -498
		ld %0, r15
		zjmp %-510

prep:
		#sti r2, %:zork, %1		#write our id to zork live
		sti r2, %:def, %1	
		st r8, :prep			#delete write
main:
		live %1
		fork %:tower			#create disruption from below
		live %1
		fork %:lastguy			#make a train
		#zjmp %:zork
		zjmp %:def

lastguy:
		live %1
		fork %:middleguy
		live %1
		fork %:firstguy
		st r8, -500				#pointless, have to line up first, middle, last...
		ld %16, r3
		ld %0, r5
		zjmp %:gogogo

middleguy:
		live %1
		fork %:main
		ld %67174400, r2		#04010000 == r4 live ...
		ld %14, r3
		ld %0, r4
		zjmp %:gogogo

firstguy:
		ld %190054915, r2		#0B540102 == sti r2, r3...
		ld %10, r3
		ld %0, r4
		zjmp %:gogogo


def:
		live %1
		st r8, -269
		st r8, -269
		st r8, -269
		zjmp %:def

gogogo:
		sti r2, r3, r4
		live %1

