compiler : parser.o semantic_analysis.o ir.o obj.o
	gcc parser.o semantic_analysis.o ir.o obj.o -lfl -ly -o compiler

semantic_analysis.o : src/semantic_analysis.c header/tree.h header/semantic.h
	gcc src/semantic_analysis.c -std=c99 -g -c -o semantic_analysis.o

parser.o : src/syntax_analysis.c src/syntax_analysis.h header/tree.h header/tree.h 
	gcc src/syntax_analysis.c -g -c -o parser.o

obj.o : src/obj.c header/obj.h
	gcc src/obj.c -std=c99 -g -c -o obj.o

ir.o : src/ir.c header/ir.h
	gcc src/ir.c -std=c99 -g -c -o ir.o

src/syntax_analysis.c src/syntax_analysis.h: src/syntax_analysis.y src/lex_analysis.c 
	bison -d src/syntax_analysis.y -o src/syntax_analysis.c 

src/lex_analysis.c : src/lex_analysis.l
	flex -o src/lex_analysis.c src/lex_analysis.l


clean :
	rm -rf *.o src/lex_analysis.c src/syntax_analysis.c src/syntax_analysis.h compiler


