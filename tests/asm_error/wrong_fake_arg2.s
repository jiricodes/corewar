.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1
		and r1, %0, s1				#fake argument

live:	live %1
		zjmp %:live
