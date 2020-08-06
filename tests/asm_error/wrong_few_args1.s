.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live			#not enough args
		and r1, %0, r1

live:	live %1
		zjmp %:live
