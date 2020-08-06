.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1
		and 					#no args

live:	live %1
		zjmp %:live
