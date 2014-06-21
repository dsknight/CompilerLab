/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "src/syntax_analysis.y"

	#include<ctype.h>
	#include<stdio.h>
	#include<stdarg.h>
	#include"../header/tree.h"
    #include"../header/semantic.h"
	#include"lex_analysis.c"
	
	void yyerror(char*);
    tree_node *root;
 


/* Line 268 of yacc.c  */
#line 85 "src/syntax_analysis.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEC = 258,
     OTC = 259,
     HEX = 260,
     FLOAT = 261,
     ID = 262,
     TYPE = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     STRUCT = 267,
     RETURN = 268,
     SEMI = 269,
     COMMA = 270,
     ASSIGNOP = 271,
     OR = 272,
     AND = 273,
     RELOP = 274,
     MINUS = 275,
     PLUS = 276,
     DIV = 277,
     STAR = 278,
     NOT = 279,
     RC = 280,
     LC = 281,
     RB = 282,
     LB = 283,
     RP = 284,
     LP = 285,
     DOT = 286,
     LOWER_THAN_ELSE = 287
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 17 "src/syntax_analysis.y"

	tree_node *attr_node;



/* Line 293 of yacc.c  */
#line 159 "src/syntax_analysis.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 184 "src/syntax_analysis.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      26,    30,    32,    34,    40,    43,    45,    46,    48,    50,
      55,    60,    64,    67,    71,    73,    76,    81,    84,    87,
      88,    91,    93,    97,   103,   111,   117,   120,   123,   126,
     127,   131,   133,   137,   139,   143,   147,   151,   155,   159,
     163,   167,   171,   175,   179,   182,   185,   190,   194,   199,
     203,   205,   207,   209,   211,   213,   217,   219
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    -1,    36,    35,    -1,    -1,    38,
      37,    14,    -1,    38,    14,    -1,    38,    43,    46,    -1,
      38,    43,    14,    -1,    42,    -1,    42,    15,    37,    -1,
       8,    -1,    39,    -1,    12,    40,    26,    49,    25,    -1,
      12,    41,    -1,     7,    -1,    -1,     7,    -1,     7,    -1,
      42,    28,     3,    27,    -1,     7,    30,    44,    29,    -1,
       7,    30,    29,    -1,     1,    29,    -1,    45,    15,    44,
      -1,    45,    -1,    38,    42,    -1,    26,    49,    47,    25,
      -1,     1,    25,    -1,    48,    47,    -1,    -1,    53,    14,
      -1,    46,    -1,    13,    53,    14,    -1,     9,    30,    53,
      29,    48,    -1,     9,    30,    53,    29,    48,    10,    48,
      -1,    11,    30,    53,    29,    48,    -1,     1,    14,    -1,
       1,    29,    -1,    50,    49,    -1,    -1,    38,    51,    14,
      -1,    52,    -1,    52,    15,    51,    -1,    42,    -1,    42,
      16,    53,    -1,    53,    16,    53,    -1,    53,    18,    53,
      -1,    53,    17,    53,    -1,    53,    19,    53,    -1,    53,
      21,    53,    -1,    53,    20,    53,    -1,    53,    23,    53,
      -1,    53,    22,    53,    -1,    30,    53,    29,    -1,    20,
      53,    -1,    24,    53,    -1,     7,    30,    54,    29,    -1,
       7,    30,    29,    -1,    53,    28,    53,    27,    -1,    53,
      31,     7,    -1,     7,    -1,     3,    -1,     4,    -1,     5,
      -1,     6,    -1,    53,    15,    54,    -1,    53,    -1,     1,
      29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    50,    50,    54,    55,    57,    58,    59,    60,    61,
      62,    65,    66,    67,    68,    69,    70,    71,    74,    75,
      76,    77,    78,    79,    80,    81,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    97,    98,
      99,   100,   101,   102,   103,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEC", "OTC", "HEX", "FLOAT", "ID",
  "TYPE", "IF", "ELSE", "WHILE", "STRUCT", "RETURN", "SEMI", "COMMA",
  "ASSIGNOP", "OR", "AND", "RELOP", "MINUS", "PLUS", "DIV", "STAR", "NOT",
  "RC", "LC", "RB", "LB", "RP", "LP", "DOT", "LOWER_THAN_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    37,
      37,    38,    38,    39,    39,    40,    40,    41,    42,    42,
      43,    43,    43,    44,    44,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      50,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     2,     3,     1,     2,     4,     2,     2,     0,
       2,     1,     3,     5,     7,     5,     2,     2,     2,     0,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     1,     1,     3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    11,    16,     0,     2,     4,     0,    12,    17,     0,
      14,     1,     3,     0,    18,     6,     0,     9,     0,    39,
      22,     0,     5,     0,     0,     0,     8,    39,     7,     0,
       0,    39,    21,     0,     0,    24,    18,    10,     0,    27,
       0,    43,     0,    41,    13,    38,    25,    20,     0,    19,
       0,    61,    62,    63,    64,    60,     0,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,    40,     0,    23,
      36,    37,     0,     0,     0,     0,    54,    55,     0,    26,
      28,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    42,     0,    57,    66,     0,     0,     0,
      32,    53,    45,    47,    46,    48,    50,    49,    52,    51,
       0,    59,    67,     0,    56,     0,     0,    58,    65,    33,
      35,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    29,     7,     9,    10,    17,
      18,    34,    35,    62,    63,    64,    30,    31,    42,    43,
      65,    97
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int16 yypact[] =
{
      88,   -59,    -3,    11,   -59,    88,    91,   -59,   -13,    -6,
     -59,   -59,   -59,    -8,    29,   -59,    28,    -9,     9,    88,
     -59,    35,   -59,    54,    65,    48,   -59,    88,   -59,    54,
      56,    88,   -59,    54,    72,    79,   -59,   -59,    75,   -59,
      45,    67,    92,   112,   -59,   -59,   103,   -59,    88,   -59,
      -7,   -59,   -59,   -59,   -59,    77,    86,   104,   106,   106,
     106,   106,   -59,   108,    45,   101,   106,   -59,    54,   -59,
     -59,   -59,    33,   106,   106,   121,   256,    97,   154,   -59,
     -59,   -59,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   139,   218,   -59,   116,   -59,   138,   118,   170,   186,
     -59,   -59,   218,   232,   245,   249,   256,   256,    97,    97,
     202,   -59,   -59,    84,   -59,    73,    73,   -59,   -59,   140,
     -59,    73,   -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   143,   -59,   128,    12,   -59,   -59,   -59,   -24,
     -59,   114,   -59,   145,   100,   -49,    14,   -59,    99,   -59,
     -58,    52
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -30
static const yytype_int8 yytable[] =
{
      75,    76,    77,    78,     8,    41,    23,    70,    92,    46,
      25,    11,     6,   -15,    96,    98,    99,     6,    39,    24,
      19,    20,    71,    26,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    33,    94,    27,    51,    52,    53,    54,
      55,    40,    22,     1,    41,    45,    50,     2,    51,    52,
      53,    54,    55,    59,    56,    96,    57,    60,    58,    21,
      33,    36,    95,    61,    32,    59,   119,   120,    38,    60,
     -29,    27,   122,    39,    50,    61,    51,    52,    53,    54,
      55,    44,    56,    66,    57,    94,    58,    51,    52,    53,
      54,    55,    13,    59,    48,    24,     1,    60,    14,    27,
       2,    47,    49,    61,    59,    15,    67,    72,    60,    51,
      52,    53,    54,    55,    61,    81,    73,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    59,    68,    91,    90,
      60,    24,    91,    79,    74,   100,    61,    82,    83,    84,
      85,    86,    87,    88,    89,   112,   111,   114,    12,    90,
     121,    37,    91,   113,    82,    83,    84,    85,    86,    87,
      88,    89,    69,    28,    80,   118,    90,    93,     0,    91,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,   101,     0,    91,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,     0,    90,   115,
       0,    91,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,     0,    90,   116,     0,    91,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,   117,
      90,     0,     0,    91,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,     0,     0,    91,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
      90,     0,     0,    91,    85,    86,    87,    88,    89,    86,
      87,    88,    89,    90,     0,     0,    91,    90,    88,    89,
      91,     0,     0,     0,    90,     0,     0,    91
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-59))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      58,    59,    60,    61,     7,    29,    15,    14,    66,    33,
       1,     0,     0,    26,    72,    73,    74,     5,    25,    28,
      26,    29,    29,    14,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    21,     1,    26,     3,     4,     5,     6,
       7,    27,    14,     8,    68,    31,     1,    12,     3,     4,
       5,     6,     7,    20,     9,   113,    11,    24,    13,    30,
      48,     7,    29,    30,    29,    20,   115,   116,     3,    24,
      25,    26,   121,    25,     1,    30,     3,     4,     5,     6,
       7,    25,     9,    16,    11,     1,    13,     3,     4,     5,
       6,     7,     1,    20,    15,    28,     8,    24,     7,    26,
      12,    29,    27,    30,    20,    14,    14,    30,    24,     3,
       4,     5,     6,     7,    30,    14,    30,    16,    17,    18,
      19,    20,    21,    22,    23,    28,    20,    15,    31,    28,
      24,    28,    31,    25,    30,    14,    30,    16,    17,    18,
      19,    20,    21,    22,    23,    29,     7,    29,     5,    28,
      10,    23,    31,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    48,    18,    64,   113,    28,    68,    -1,    31,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    28,    29,    -1,    31,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,
      -1,    31,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    28,    29,    -1,    31,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    27,
      28,    -1,    -1,    31,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    31,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    31,    19,    20,    21,    22,    23,    20,
      21,    22,    23,    28,    -1,    -1,    31,    28,    22,    23,
      31,    -1,    -1,    -1,    28,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    12,    34,    35,    36,    38,    39,     7,    40,
      41,     0,    35,     1,     7,    14,    37,    42,    43,    26,
      29,    30,    14,    15,    28,     1,    14,    26,    46,    38,
      49,    50,    29,    38,    44,    45,     7,    37,     3,    25,
      49,    42,    51,    52,    25,    49,    42,    29,    15,    27,
       1,     3,     4,     5,     6,     7,     9,    11,    13,    20,
      24,    30,    46,    47,    48,    53,    16,    14,    15,    44,
      14,    29,    30,    30,    30,    53,    53,    53,    53,    25,
      47,    14,    16,    17,    18,    19,    20,    21,    22,    23,
      28,    31,    53,    51,     1,    29,    53,    54,    53,    53,
      14,    29,    53,    53,    53,    53,    53,    53,    53,    53,
      53,     7,    29,    15,    29,    29,    29,    27,    54,    48,
      48,    10,    48
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 50 "src/syntax_analysis.y"
    {  (yyval.attr_node) = reduce("Program", 1, (yyvsp[(1) - (1)].attr_node)); 
                                root = (yyval.attr_node);
                             }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 54 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDefList", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 55 "src/syntax_analysis.y"
    {(yyval.attr_node) = reduce("ExtDefList",0);}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 57 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDef", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node) ,(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 58 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDef", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 59 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDef", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node), (yyvsp[(3) - (3)].attr_node)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 60 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDef", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node), (yyvsp[(3) - (3)].attr_node)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 61 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDecList", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 62 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ExtDecList", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node), (yyvsp[(3) - (3)].attr_node)); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 65 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Specifier", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 66 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Specifier", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 67 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("StructSpecifier", 5, (yyvsp[(1) - (5)].attr_node), (yyvsp[(2) - (5)].attr_node),(yyvsp[(3) - (5)].attr_node),(yyvsp[(4) - (5)].attr_node),(yyvsp[(5) - (5)].attr_node)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 68 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("StructSpecifier", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 69 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("OptTag", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 70 "src/syntax_analysis.y"
    {(yyval.attr_node) = reduce("OptTag",0);}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 71 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Tag", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 74 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("VarDec", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 75 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("VarDec", 4, (yyvsp[(1) - (4)].attr_node), (yyvsp[(2) - (4)].attr_node) ,(yyvsp[(3) - (4)].attr_node) ,(yyvsp[(4) - (4)].attr_node)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 76 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("FunDec", 4, (yyvsp[(1) - (4)].attr_node), (yyvsp[(2) - (4)].attr_node) ,(yyvsp[(3) - (4)].attr_node) ,(yyvsp[(4) - (4)].attr_node)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 77 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("FunDec", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node) ,(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 79 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("VarList", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 80 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("VarList", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 81 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("ParamDec", 2, (yyvsp[(1) - (2)].attr_node) ,(yyvsp[(2) - (2)].attr_node)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 84 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("CompSt", 4, (yyvsp[(1) - (4)].attr_node), (yyvsp[(2) - (4)].attr_node) ,(yyvsp[(3) - (4)].attr_node) ,(yyvsp[(4) - (4)].attr_node)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 86 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("StmtList", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 87 "src/syntax_analysis.y"
    {(yyval.attr_node) = reduce("StmtList",0);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 88 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 89 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 90 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node), (yyvsp[(3) - (3)].attr_node)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 91 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 5, (yyvsp[(1) - (5)].attr_node), (yyvsp[(2) - (5)].attr_node),(yyvsp[(3) - (5)].attr_node),(yyvsp[(4) - (5)].attr_node),(yyvsp[(5) - (5)].attr_node)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 92 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 7, (yyvsp[(1) - (7)].attr_node), (yyvsp[(2) - (7)].attr_node),(yyvsp[(3) - (7)].attr_node),(yyvsp[(4) - (7)].attr_node),(yyvsp[(5) - (7)].attr_node),(yyvsp[(6) - (7)].attr_node),(yyvsp[(7) - (7)].attr_node)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 93 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Stmt", 5,(yyvsp[(1) - (5)].attr_node), (yyvsp[(2) - (5)].attr_node) ,(yyvsp[(3) - (5)].attr_node) ,(yyvsp[(4) - (5)].attr_node), (yyvsp[(5) - (5)].attr_node)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 97 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("DefList", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 98 "src/syntax_analysis.y"
    {(yyval.attr_node) = reduce("DefList",0);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 99 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Def", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node) ,(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 100 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("DecList", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 101 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("DecList", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 102 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Dec", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 103 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Dec", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node) ,(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 106 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 107 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 108 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 109 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 110 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 111 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 112 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 113 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 114 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 115 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 116 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 2, (yyvsp[(1) - (2)].attr_node), (yyvsp[(2) - (2)].attr_node)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 117 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 4, (yyvsp[(1) - (4)].attr_node), (yyvsp[(2) - (4)].attr_node),(yyvsp[(3) - (4)].attr_node),(yyvsp[(4) - (4)].attr_node)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 118 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 119 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 4, (yyvsp[(1) - (4)].attr_node), (yyvsp[(2) - (4)].attr_node) ,(yyvsp[(3) - (4)].attr_node) ,(yyvsp[(4) - (4)].attr_node)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 120 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node),(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 121 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 1 ,(yyvsp[(1) - (1)].attr_node)); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 122 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 1 ,(yyvsp[(1) - (1)].attr_node)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 123 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 1 ,(yyvsp[(1) - (1)].attr_node)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 124 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 1 ,(yyvsp[(1) - (1)].attr_node)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 125 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Exp", 1 ,(yyvsp[(1) - (1)].attr_node)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 126 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Args", 3, (yyvsp[(1) - (3)].attr_node), (yyvsp[(2) - (3)].attr_node) ,(yyvsp[(3) - (3)].attr_node)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 127 "src/syntax_analysis.y"
    { (yyval.attr_node) = reduce("Args", 1, (yyvsp[(1) - (1)].attr_node)); }
    break;



/* Line 1806 of yacc.c  */
#line 2022 "src/syntax_analysis.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 131 "src/syntax_analysis.y"


void yyerror(char *msg){
	error_flag = 1;
	printf("Error type B at line %d: %s\n",yylineno,msg);
}


tree_node* reduce(char* name, int num, ...){
	va_list ap;
	tree_node *p;
	int i;

	p = malloc(sizeof(tree_node));
	p->nt_node.node = malloc(num * 4);

	p->type = NONTERMINAL_T;
	p->lineno = 0;

	strncpy(p->nt_node.name,name,MAX_LEN);
	p->nt_node.num = num;

	va_start(ap,num);
	for(i = 0; i < num ; i++)
		p->nt_node.node[i] = va_arg(ap,tree_node*);
	if(num != 0)
		p->lineno = p->nt_node.node[0]->lineno;

	va_end(ap);
	return p;
}


void print_tree(tree_node *p,int depth){
	int i;
	if(p->type == NONTERMINAL_T && p->nt_node.num == 0)
		return ;
	for(i = 0;i < depth;i++)
		printf("  ");
	if(p->type == INT_T)
		printf("INT: %d\n",p->int_attr);
	else if(p->type == FLOAT_T)
		printf("FLOAT: %f\n ",p->float_attr);
	else if(p->type == ID_T)
		printf("ID: %s\n",p->id_attr);
	else if(p->type == OTHER_TERMINAL_T){
		if(strcmp(p->other_terminal,"INT") == 0)
			printf("TYPE: int\n");
		else if(strcmp(p->other_terminal,"FLOAT") == 0)
			printf("TYPE: float\n");
		else
			printf("%s\n",p->other_terminal);
	}
	else if(p->type == NONTERMINAL_T){
		if(p->nt_node.num != 0){
			depth++;
			printf("%s (%d)\n",p->nt_node.name,p->lineno);
			for(i = 0; i < p->nt_node.num; i++)
				print_tree(p->nt_node.node[i],depth);
		}
	}

	
}	


void destroy_tree(tree_node* p){
	int i;
	
	if(!p) return;
	if(p->type == NONTERMINAL_T){
		for(i = 0; i < p->nt_node.num ; i++)
			destroy_tree(p->nt_node.node[i]);
		free(p->nt_node.node);
	}
	free(p); 
}
















