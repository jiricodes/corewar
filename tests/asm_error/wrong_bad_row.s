.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1
		here is error			#uncommented line
		and r1, %0, r1

live:	live %1
		zjmp %:live
