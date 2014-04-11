#define OP_PLUS 1
#define OP_MINUS 2
#define OP_MULT 3
#define OP_DIV 4
#define OP_MINUS_U 5
#define OP_GREATER 6
#define OP_LESS 7
#define OP_NO 8
#define OP_AND 9
#define OP_OR 10

#define INTEGER 1
#define FLOAT 2
#define CHAR 3
#define STRING 4
#define BOOL 5
#define VOID 6


class Cube {
	int cube[11][7][7];
public:

	Cube() {

	}



	void buildCube()
	{
		//plus
		cube[1][1][1] = { 1 };
		cube[OP_PLUS][INTEGER][FLOAT] = FLOAT;
		cube[OP_PLUS][INTEGER][CHAR] = 0;
		cube[OP_PLUS][INTEGER][STRING] = STRING;
		cube[OP_PLUS][INTEGER][BOOL] = 0;
		cube[OP_PLUS][INTEGER][VOID] = 0;
		cube[OP_PLUS][FLOAT][INTEGER] = FLOAT;
		cube[OP_PLUS][FLOAT][FLOAT] = FLOAT;
		cube[OP_PLUS][FLOAT][CHAR] = 0;
		cube[OP_PLUS][FLOAT][STRING] = STRING;
		cube[OP_PLUS][FLOAT][BOOL] = 0;
		cube[OP_PLUS][FLOAT][VOID] = 0;
		cube[OP_PLUS][CHAR][INTEGER] = 0;
		cube[OP_PLUS][CHAR][FLOAT] = 0;
		cube[OP_PLUS][CHAR][CHAR] = 0;
		cube[OP_PLUS][CHAR][STRING] = STRING;
		cube[OP_PLUS][CHAR][BOOL] = 0;
		cube[OP_PLUS][CHAR][VOID] = 0;
		cube[OP_PLUS][STRING][INTEGER] = STRING;
		cube[OP_PLUS][STRING][FLOAT] = STRING;
		cube[OP_PLUS][STRING][CHAR] = STRING;
		cube[OP_PLUS][STRING][STRING] = STRING;
		cube[OP_PLUS][STRING][BOOL] = STRING;
		cube[OP_PLUS][STRING][VOID] = 0;
		cube[OP_PLUS][BOOL][INTEGER] = 0;
		cube[OP_PLUS][BOOL][FLOAT] = 0;
		cube[OP_PLUS][BOOL][CHAR] = 0;
		cube[OP_PLUS][BOOL][STRING] = STRING;
		cube[OP_PLUS][BOOL][BOOL] = 0;
		cube[OP_PLUS][BOOL][VOID] = 0;
		cube[OP_PLUS][VOID][INTEGER] = 0;
		cube[OP_PLUS][VOID][FLOAT] = 0;
		cube[OP_PLUS][VOID][CHAR] = 0;
		cube[OP_PLUS][VOID][STRING] = 0;
		cube[OP_PLUS][VOID][BOOL] = 0;
		cube[OP_PLUS][VOID][VOID] = 0;



		//minus

		cube[OP_MINUS][INTEGER][INTEGER] = INTEGER;
		cube[OP_MINUS][INTEGER][FLOAT] = FLOAT;
		cube[OP_MINUS][INTEGER][CHAR] = 0;
		cube[OP_MINUS][INTEGER][STRING] = 0;
		cube[OP_MINUS][INTEGER][BOOL] = 0;
		cube[OP_MINUS][INTEGER][VOID] = 0;
		cube[OP_MINUS][FLOAT][INTEGER] = FLOAT;
		cube[OP_MINUS][FLOAT][FLOAT] = FLOAT;
		cube[OP_MINUS][FLOAT][CHAR] = 0;
		cube[OP_MINUS][FLOAT][STRING] = 0;
		cube[OP_MINUS][FLOAT][BOOL] = 0;
		cube[OP_MINUS][FLOAT][VOID] = 0;
		cube[OP_MINUS][CHAR][INTEGER] = 0;
		cube[OP_MINUS][CHAR][FLOAT] = 0;
		cube[OP_MINUS][CHAR][CHAR] = 0;
		cube[OP_MINUS][CHAR][STRING] = 0;
		cube[OP_MINUS][CHAR][BOOL] = 0;
		cube[OP_MINUS][CHAR][VOID] = 0;
		cube[OP_MINUS][STRING][INTEGER] = 0;
		cube[OP_MINUS][STRING][FLOAT] = 0;
		cube[OP_MINUS][STRING][CHAR] = 0;
		cube[OP_MINUS][STRING][STRING] = 0;
		cube[OP_MINUS][STRING][BOOL] = 0;
		cube[OP_MINUS][STRING][VOID] = 0;
		cube[OP_MINUS][BOOL][INTEGER] = 0;
		cube[OP_MINUS][BOOL][FLOAT] = 0;
		cube[OP_MINUS][BOOL][CHAR] = 0;
		cube[OP_MINUS][BOOL][STRING] = 0;
		cube[OP_MINUS][BOOL][BOOL] = 0;
		cube[OP_MINUS][BOOL][VOID] = 0;
		cube[OP_MINUS][VOID][INTEGER] = 0;
		cube[OP_MINUS][VOID][FLOAT] = 0;
		cube[OP_MINUS][VOID][CHAR] = 0;
		cube[OP_MINUS][VOID][STRING] = 0;
		cube[OP_MINUS][VOID][BOOL] = 0;
		cube[OP_MINUS][VOID][VOID] = 0;



		//Multiplication

		cube[OP_MULT][INTEGER][INTEGER] = INTEGER;
		cube[OP_MULT][INTEGER][FLOAT] = FLOAT;
		cube[OP_MULT][INTEGER][CHAR] = 0;
		cube[OP_MULT][INTEGER][STRING] = 0;
		cube[OP_MULT][INTEGER][BOOL] = 0;
		cube[OP_MULT][INTEGER][VOID] = 0;
		cube[OP_MULT][FLOAT][INTEGER] = FLOAT;
		cube[OP_MULT][FLOAT][FLOAT] = FLOAT;
		cube[OP_MULT][FLOAT][CHAR] = 0;
		cube[OP_MULT][FLOAT][STRING] = 0;
		cube[OP_MULT][FLOAT][BOOL] = 0;
		cube[OP_MULT][FLOAT][VOID] = 0;
		cube[OP_MULT][CHAR][INTEGER] = 0;
		cube[OP_MULT][CHAR][FLOAT] = 0;
		cube[OP_MULT][CHAR][CHAR] = 0;
		cube[OP_MULT][CHAR][STRING] = 0;
		cube[OP_MULT][CHAR][BOOL] = 0;
		cube[OP_MULT][CHAR][VOID] = 0;
		cube[OP_MULT][STRING][INTEGER] = 0;
		cube[OP_MULT][STRING][FLOAT] = 0;
		cube[OP_MULT][STRING][CHAR] = 0;
		cube[OP_MULT][STRING][STRING] = 0;
		cube[OP_MULT][STRING][BOOL] = 0;
		cube[OP_MULT][STRING][VOID] = 0;
		cube[OP_MULT][BOOL][INTEGER] = 0;
		cube[OP_MULT][BOOL][FLOAT] = 0;
		cube[OP_MULT][BOOL][CHAR] = 0;
		cube[OP_MULT][BOOL][STRING] = 0;
		cube[OP_MULT][BOOL][BOOL] = 0;
		cube[OP_MULT][BOOL][VOID] = 0;
		cube[OP_MULT][VOID][INTEGER] = 0;
		cube[OP_MULT][VOID][FLOAT] = 0;
		cube[OP_MULT][VOID][CHAR] = 0;
		cube[OP_MULT][VOID][STRING] = 0;
		cube[OP_MULT][VOID][BOOL] = 0;
		cube[OP_MULT][VOID][VOID] = 0;



		//division

		cube[OP_DIV][INTEGER][INTEGER] = INTEGER;
		cube[OP_DIV][INTEGER][FLOAT] = FLOAT;
		cube[OP_DIV][INTEGER][CHAR] = 0;
		cube[OP_DIV][INTEGER][STRING] = 0;
		cube[OP_DIV][INTEGER][BOOL] = 0;
		cube[OP_DIV][INTEGER][VOID] = 0;
		cube[OP_DIV][FLOAT][INTEGER] = FLOAT;
		cube[OP_DIV][FLOAT][FLOAT] = FLOAT;
		cube[OP_DIV][FLOAT][CHAR] = 0;
		cube[OP_DIV][FLOAT][STRING] = 0;
		cube[OP_DIV][FLOAT][BOOL] = 0;
		cube[OP_DIV][FLOAT][VOID] = 0;
		cube[OP_DIV][CHAR][INTEGER] = 0;
		cube[OP_DIV][CHAR][FLOAT] = 0;
		cube[OP_DIV][CHAR][CHAR] = 0;
		cube[OP_DIV][CHAR][STRING] = 0;
		cube[OP_DIV][CHAR][BOOL] = 0;
		cube[OP_DIV][CHAR][VOID] = 0;
		cube[OP_DIV][STRING][INTEGER] = 0;
		cube[OP_DIV][STRING][FLOAT] = 0;
		cube[OP_DIV][STRING][CHAR] = 0;
		cube[OP_DIV][STRING][STRING] = 0;
		cube[OP_DIV][STRING][BOOL] = 0;
		cube[OP_DIV][STRING][VOID] = 0;
		cube[OP_DIV][BOOL][INTEGER] = 0;
		cube[OP_DIV][BOOL][FLOAT] = 0;
		cube[OP_DIV][BOOL][CHAR] = 0;
		cube[OP_DIV][BOOL][STRING] = 0;
		cube[OP_DIV][BOOL][BOOL] = 0;
		cube[OP_DIV][BOOL][VOID] = 0;
		cube[OP_DIV][VOID][INTEGER] = 0;
		cube[OP_DIV][VOID][FLOAT] = 0;
		cube[OP_DIV][VOID][CHAR] = 0;
		cube[OP_DIV][VOID][STRING] = 0;
		cube[OP_DIV][VOID][BOOL] = 0;
		cube[OP_DIV][VOID][VOID] = 0;



		//minus Unary

		cube[OP_MINUS_U][INTEGER][0] = INTEGER;
		cube[OP_MINUS_U][INTEGER][0] = FLOAT;
		cube[OP_MINUS_U][INTEGER][0] = 0;
		cube[OP_MINUS_U][INTEGER][0] = 0;
		cube[OP_MINUS_U][INTEGER][0] = 0;
		cube[OP_MINUS_U][INTEGER][0] = 0;


		//CONSTRUCT CUBE OF TYPES FOR 'GREATER THAN' OPERATION
		cube[OP_GREATER][INTEGER][INTEGER] = BOOL;
		cube[OP_GREATER][INTEGER][FLOAT] = BOOL;
		cube[OP_GREATER][INTEGER][CHAR] = 0;
		cube[OP_GREATER][INTEGER][STRING] = 0;
		cube[OP_GREATER][INTEGER][BOOL] = 0;
		cube[OP_GREATER][INTEGER][VOID] = 0;
		cube[OP_GREATER][FLOAT][INTEGER] = BOOL;
		cube[OP_GREATER][FLOAT][FLOAT] = BOOL;
		cube[OP_GREATER][FLOAT][CHAR] = 0;
		cube[OP_GREATER][FLOAT][STRING] = 0;
		cube[OP_GREATER][FLOAT][BOOL] = 0;
		cube[OP_GREATER][FLOAT][VOID] = 0;
		cube[OP_GREATER][CHAR][INTEGER] = 0;
		cube[OP_GREATER][CHAR][FLOAT] = 0;
		cube[OP_GREATER][CHAR][CHAR] = 0;
		cube[OP_GREATER][CHAR][STRING] = 0;
		cube[OP_GREATER][CHAR][BOOL] = 0;
		cube[OP_GREATER][CHAR][VOID] = 0;
		cube[OP_GREATER][STRING][INTEGER] = 0;
		cube[OP_GREATER][STRING][FLOAT] = 0;
		cube[OP_GREATER][STRING][CHAR] = 0;
		cube[OP_GREATER][STRING][STRING] = 0;
		cube[OP_GREATER][STRING][BOOL] = 0;
		cube[OP_GREATER][STRING][VOID] = 0;
		cube[OP_GREATER][BOOL][INTEGER] = 0;
		cube[OP_GREATER][BOOL][FLOAT] = 0;
		cube[OP_GREATER][BOOL][CHAR] = 0;
		cube[OP_GREATER][BOOL][STRING] = 0;
		cube[OP_GREATER][BOOL][BOOL] = 0;
		cube[OP_GREATER][BOOL][VOID] = 0;
		cube[OP_GREATER][VOID][INTEGER] = 0;
		cube[OP_GREATER][VOID][FLOAT] = 0;
		cube[OP_GREATER][VOID][CHAR] = 0;
		cube[OP_GREATER][VOID][STRING] = 0;
		cube[OP_GREATER][VOID][BOOL] = 0;
		cube[OP_GREATER][VOID][VOID] = 0;


		//CONSTRUCT CUBE OF TYPES FOR 'LESS THAN' OPERATION
		cube[OP_LESS][INTEGER][INTEGER] = BOOL;
		cube[OP_LESS][INTEGER][FLOAT] = BOOL;
		cube[OP_LESS][INTEGER][CHAR] = 0;
		cube[OP_LESS][INTEGER][STRING] = 0;
		cube[OP_LESS][INTEGER][BOOL] = 0;
		cube[OP_LESS][INTEGER][VOID] = 0;
		cube[OP_LESS][FLOAT][INTEGER] = BOOL;
		cube[OP_LESS][FLOAT][FLOAT] = BOOL;
		cube[OP_LESS][FLOAT][CHAR] = 0;
		cube[OP_LESS][FLOAT][STRING] = 0;
		cube[OP_LESS][FLOAT][BOOL] = 0;
		cube[OP_LESS][FLOAT][VOID] = 0;
		cube[OP_LESS][CHAR][INTEGER] = 0;
		cube[OP_LESS][CHAR][FLOAT] = 0;
		cube[OP_LESS][CHAR][CHAR] = 0;
		cube[OP_LESS][CHAR][STRING] = 0;
		cube[OP_LESS][CHAR][BOOL] = 0;
		cube[OP_LESS][CHAR][VOID] = 0;
		cube[OP_LESS][STRING][INTEGER] = 0;
		cube[OP_LESS][STRING][FLOAT] = 0;
		cube[OP_LESS][STRING][CHAR] = 0;
		cube[OP_LESS][STRING][STRING] = 0;
		cube[OP_LESS][STRING][BOOL] = 0;
		cube[OP_LESS][STRING][VOID] = 0;
		cube[OP_LESS][BOOL][INTEGER] = 0;
		cube[OP_LESS][BOOL][FLOAT] = 0;
		cube[OP_LESS][BOOL][CHAR] = 0;
		cube[OP_LESS][BOOL][STRING] = 0;
		cube[OP_LESS][BOOL][BOOL] = 0;
		cube[OP_LESS][BOOL][VOID] = 0;
		cube[OP_LESS][VOID][INTEGER] = 0;
		cube[OP_LESS][VOID][FLOAT] = 0;
		cube[OP_LESS][VOID][CHAR] = 0;
		cube[OP_LESS][VOID][STRING] = 0;
		cube[OP_LESS][VOID][BOOL] = 0;
		cube[OP_LESS][VOID][VOID] = 0;


		//CONSTRUCT 'NOT' OPERATION
		cube[OP_NO][INTEGER][0] = 0;
		cube[OP_NO][FLOAT][0] = 0;
		cube[OP_NO][CHAR][0] = 0;
		cube[OP_NO][STRING][0] = 0;
		cube[OP_NO][BOOL][0] = BOOL;
		cube[OP_NO][VOID][0] = 0;


		//CONSTRUCT 'AND' OPERATION
		cube[OP_AND][INTEGER][INTEGER] = 0;
		cube[OP_AND][INTEGER][FLOAT] = 0;
		cube[OP_AND][INTEGER][CHAR] = 0;
		cube[OP_AND][INTEGER][STRING] = 0;
		cube[OP_AND][INTEGER][BOOL] = 0;
		cube[OP_AND][INTEGER][VOID] = 0;
		cube[OP_AND][FLOAT][INTEGER] = 0;
		cube[OP_AND][FLOAT][FLOAT] = 0;
		cube[OP_AND][FLOAT][CHAR] = 0;
		cube[OP_AND][FLOAT][STRING] = 0;
		cube[OP_AND][FLOAT][BOOL] = 0;
		cube[OP_AND][FLOAT][VOID] = 0;
		cube[OP_AND][CHAR][INTEGER] = 0;
		cube[OP_AND][CHAR][FLOAT] = 0;
		cube[OP_AND][CHAR][CHAR] = 0;
		cube[OP_AND][CHAR][STRING] = 0;
		cube[OP_AND][CHAR][BOOL] = 0;
		cube[OP_AND][CHAR][VOID] = 0;
		cube[OP_AND][STRING][INTEGER] = 0;
		cube[OP_AND][STRING][FLOAT] = 0;
		cube[OP_AND][STRING][CHAR] = 0;
		cube[OP_AND][STRING][STRING] = 0;
		cube[OP_AND][STRING][BOOL] = 0;
		cube[OP_AND][STRING][VOID] = 0;
		cube[OP_AND][BOOL][INTEGER] = 0;
		cube[OP_AND][BOOL][FLOAT] = 0;
		cube[OP_AND][BOOL][CHAR] = 0;
		cube[OP_AND][BOOL][STRING] = 0;
		cube[OP_AND][BOOL][BOOL] = BOOL;
		cube[OP_AND][BOOL][VOID] = 0;
		cube[OP_AND][VOID][INTEGER] = 0;
		cube[OP_AND][VOID][FLOAT] = 0;
		cube[OP_AND][VOID][CHAR] = 0;
		cube[OP_AND][VOID][STRING] = 0;
		cube[OP_AND][VOID][BOOL] = 0;
		cube[OP_AND][VOID][VOID] = 0;


		//CONSTRUCT 'OR' OPERATION
		cube[OP_OR][INTEGER][INTEGER] = 0;
		cube[OP_OR][INTEGER][FLOAT] = 0;
		cube[OP_OR][INTEGER][CHAR] = 0;
		cube[OP_OR][INTEGER][STRING] = 0;
		cube[OP_OR][INTEGER][BOOL] = 0;
		cube[OP_OR][INTEGER][VOID] = 0;
		cube[OP_OR][FLOAT][INTEGER] = 0;
		cube[OP_OR][FLOAT][FLOAT] = 0;
		cube[OP_OR][FLOAT][CHAR] = 0;
		cube[OP_OR][FLOAT][STRING] = 0;
		cube[OP_OR][FLOAT][BOOL] = 0;
		cube[OP_OR][FLOAT][VOID] = 0;
		cube[OP_OR][CHAR][INTEGER] = 0;
		cube[OP_OR][CHAR][FLOAT] = 0;
		cube[OP_OR][CHAR][CHAR] = 0;
		cube[OP_OR][CHAR][STRING] = 0;
		cube[OP_OR][CHAR][BOOL] = 0;
		cube[OP_OR][CHAR][VOID] = 0;
		cube[OP_OR][STRING][INTEGER] = 0;
		cube[OP_OR][STRING][FLOAT] = 0;
		cube[OP_OR][STRING][CHAR] = 0;
		cube[OP_OR][STRING][STRING] = 0;
		cube[OP_OR][STRING][BOOL] = 0;
		cube[OP_OR][STRING][VOID] = 0;
		cube[OP_OR][BOOL][INTEGER] = 0;
		cube[OP_OR][BOOL][FLOAT] = 0;
		cube[OP_OR][BOOL][CHAR] = 0;
		cube[OP_OR][BOOL][STRING] = 0;
		cube[OP_OR][BOOL][BOOL] = BOOL;
		cube[OP_OR][BOOL][VOID] = 0;
		cube[OP_OR][VOID][INTEGER] = 0;
		cube[OP_OR][VOID][FLOAT] = 0;
		cube[OP_OR][VOID][CHAR] = 0;
		cube[OP_OR][VOID][STRING] = 0;
		cube[OP_OR][VOID][BOOL] = 0;
		cube[OP_OR][VOID][VOID] = 0;


	}

};