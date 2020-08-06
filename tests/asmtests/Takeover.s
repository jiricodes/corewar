.name "Takeover"
.comment "Yup, it's pretty hostile"

r1:
		sti r1, %:live, %1
		sti r1, %:gener, %1
		sti r1, %:gener2, %1
		sti r1, %:attack, %1
		ld %418817, r4
		ld %17367088, r5
		st r4, :r1
		st r6, :r1 + 3
		st r5, :r1 + 7
		st r7, :r1 + 11
		st r7, :r1 + 14

live:
		live %1
		ld %57672193, r2
		fork %:attack

gener:
		live %1
		and r1, %0, r3
		fork %:attack
gener2:
		live %1
		fork %:gener
		zjmp %:gener

attack:
		live %1
		st r2, 260
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
		st r2, 261
