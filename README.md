# CoreWar
![](corewar_preview.gif)

This is our solution of the final algorithmic branch's project within Hive Helsinki 1st year curriculum.

> Final Grade 125/100
## Installation
```
git clone https://github.com/jiricodes/corewar.git; cd corewar; make
```
## Assembler
```
./asm <champion.s>
```

Compiles a champion file written in restricted assembly language to champion.cor file binary that is then used by CoreWar executable.
## De-Assembler
```
./deasm <champion.cor>
```

Creates human readible assembly language champion.s file out of given champion.cor binary file.
## CoreWar
```
./corewar -[flag] [-n [player_number] [player.cor]] ...

Flags:
-n [number] <player.cor>	Assign number n to the player
-d [number]			Dumps memory after that cycle. 64 octets
-dump [number]			Dumps memory after that cycle. 32 octets
-v				toggle visualiser (supports -log 1 flag)
-a				aff support

-log [number]			Can be added together for multiple
				1 - operations, includes cycle
				2 - details
				4 - deaths
				8 - cycle to die changes
				16 - fork & lfork info
				32 - Carriage movement
				64 - Carriage Count

-s				silent run
-l				sets champs max size = MEM_SIZE / MAX_PLAYERS
```
