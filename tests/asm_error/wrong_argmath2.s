.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1 - r3			#erronous argmath
		and r1, %0, r1

live:	live %1	
		zjmp %:live
