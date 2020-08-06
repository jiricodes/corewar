.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1
		sd r1, %0, r1			#nonexistent operation

live:	live %1
		zjmp %:live
