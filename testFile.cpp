#include <iostream>
#include "checkers.h"

using namespace std;
class Tester {
public:
  //test white capturing black, capture meant to return true
  bool testCaptureSuccess(Checkers& checkers) {
    bool result = true;
    // before play we expect a BCELL in (3,2)
    result = result && (checkers.m_game[3][2] == BCELL);
    // before play we expect a WDISK in (1,4)
    result = result && (checkers.m_game[1][4] == WDISK);
    // before play we expect that it is WPLAYER turn to play
    result = result && (checkers.m_currPlayer == WPLAYER);
    // before play we expect a BDISK in (2,3), there is an opponent disk
    result = result && (checkers.m_game[2][3] == BDISK);
    // store the ccurrent opponent number of disks
    int opponentDisks = checkers.m_blackDisks;
    // now call the play(...) function
    result = checkers.play(pair<int, int>(1, 4), pair<int, int>(3, 2));
    // we are trying to move (1,4) to (3,2), we expect that move is successful
    // after play we expect a BCELL in (1,4)
    result = result && (checkers.m_game[1][4] == BCELL);
    // after play we expect a WDISK in (3,2)
    result = result && (checkers.m_game[3][2] == WDISK);
    // after play we expect that it is BPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);
    // after play we expect a BCELL in (2,3), an opponent disk is captured
    result = result && (checkers.m_game[2][3] == BCELL);
    // after play we expect one less disk for the opponent
    result = result && (checkers.m_blackDisks == (opponentDisks - 1));
    return result;
  }

  //test black capturing white, capture meant to return true
  bool testCaptureSuccessBlack(Checkers& checkers) {
    bool result = true;
    // before play we expect a BCELL in (2,5)
    result = result && (checkers.m_game[2][5] == BCELL);
    // before play we expect a BDISK in (4,3)
    result = result && (checkers.m_game[4][3] == BDISK);
    // before play we expect that it is BPLAYER turn to play
    result = result && (checkers.m_currPlayer == BPLAYER);
    // before play we expect a WDISK in (3,4), there is an opponent disk
    result = result && (checkers.m_game[3][4] == WDISK);
    // store the ccurrent opponent number of disks
    int opponentDisks = checkers.m_whiteDisks;
    // now call the play(...) function
    result = checkers.play(pair<int, int>(4, 3), pair<int, int>(2, 5));
    // we are trying to move (4,3) to (2,5), we expect that move is successful
    // after play we expect a BCELL in (4,3)
    result = result && (checkers.m_game[4][3] == BCELL);
    // after play we expect a BDISK in (2,5)
    result = result && (checkers.m_game[2][5] == BDISK);
    // after play we expect that it is WPLAYER turn
    result = result && (checkers.m_currPlayer == WPLAYER);
    // after play we expect a BCELL in (3,4), an opponent disk is captured
    result = result && (checkers.m_game[3][4] == BCELL);
    // after play we expect one less disk for the opponent
    result = result && (checkers.m_whiteDisks == (opponentDisks - 1));
    return result;
  }

  //test white single move, returns true
  bool testSingleMoveSuccess(Checkers& checkers) {
    bool result = true;

    // before play we expect a WDISK in (1,6)
    result = result && (checkers.m_game[1][6] == WDISK);
    // before play we expect that it is WPLAYER turn to play
    result = result && (checkers.m_currPlayer == WPLAYER);

    // now call the play(...) function
    result = checkers.play(pair<int, int>(1, 6), pair<int, int>(2, 5));
    // we are trying to move (1,6) to (2,5), we expect that move is successful
    // after play we expect a BCELL in (1,6)
    result = result && (checkers.m_game[1][6] == BCELL);

    // after play we expect that it is BPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);

    return result;
  }
  //test black wrong move, meant to return false
  bool testWrongMove(Checkers& checkers) {
    bool result = true;
    //before we play we expect a BDISK in (4,3)
    result = result && (checkers.m_game[4][3] == BDISK);
    // before play we expect that it is BPLAYER turn to play
    result = result && (checkers.m_currPlayer == BPLAYER);
    // now call the play(...) function
    result = checkers.play(pair<int, int>(4, 3), pair<int, int>(3, 3));
    // after play we expect that it is BPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);

    return result;
  }

  //test black wrong turn, returns false
  bool testNotBlackTurn(Checkers& checkers) {
    bool result = true;
    //before we play we expect a BDISK in (5,0)
    result = result && (checkers.m_game[5][0] == BDISK);
    // before play we expect that it is NOT BPLAYER turn to play
    result = result && (checkers.m_currPlayer == BPLAYER);
    // now call the play(...) function
    result = checkers.play(pair<int, int>(5, 0), pair<int, int>(4, 1));
    // after play we expect that it is still WPLAYER turn
    result = result && (checkers.m_currPlayer == WPLAYER);
    return result;
  }
  //test changing WDISK to WKING, returns true
  bool testWhiteKing(Checkers& checkers) {
    bool result = true;
    //before we play we expect a WDISK in (6,1)
    result = result && (checkers.m_game[6][1] == WDISK);
    // before play we expect that it is WPLAYER turn to play
    result = result && (checkers.m_currPlayer == WPLAYER);
    // now call the play(...) function
    result = checkers.play(pair<int, int>(6, 1), pair<int, int>(7, 2));
    // we are trying to move (6,1) to (7,2), we expect that move is successful
    // after play we expect a BCELL in (6,1)
    result = result && (checkers.m_game[6][1] == BCELL);
    // after play we expect a WKING in (7,2)
    result = result && (checkers.m_game[7][2] == WKING);
    // after play we expect that it is BPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);

    return result;
  }

  //test for moving black disk backwards, returns false
  bool testMoveBdiskBACK(Checkers& checkers) {
    bool result = true;
    //before we play we expect a BDISK in (4,3)
    result = result && (checkers.m_game[4][3] == BDISK);
    // before play we expect that it is BPLAYER turn to play
    result = result && (checkers.m_currPlayer == BPLAYER);
    // now call the play(...) function
    result = checkers.play(pair<int, int>(4, 3), pair<int, int>(5, 2));
    // we are trying to move (4,3) to (5,2), we expect that move is false
    // after play we expect a BDISK still in (4,3)
    result = result && (checkers.m_game[4][3] == BDISK);
    // after play we expect that it is WPLAYER turn
    result = result && (checkers.m_currPlayer == BPLAYER);

    return result;
  }

  //tests error case for constructor
  bool testConstructorErrorCase(int rows, int columns) {
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows == 0);
    result = result and (checkers1.m_numColumns == 0);
    result = result and (checkers1.m_game == nullptr);
    return result;
  }

  //tests normal case for constructor
  bool testConstructorNormalCase(int rows, int columns) {
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows == rows);
    result = result and (checkers1.m_numColumns == columns);
    return result;
  }

  //tests InitBoard for an error case
  bool testInitBoardErrorCase(int rows, int columns) {
    int counter = 0;
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows != rows);
    result = result and (checkers1.m_numColumns != columns);
    checkers1.initBoard();
    for (int i = 0; i < checkers1.m_numRows; i++) {
      for (int j = 0; j < checkers1.m_numColumns; j++) {
	counter++;
      }
    }
    result = result and (counter == (checkers1.m_numRows * checkers1.m_numColumns));
    result = result and (counter == 0);
    return result;
  }

  //tests InitBoard for a normal case
  bool testInitBoardNormalCase(int rows, int columns) {
    int counter = 0;
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows == rows);
    result = result and (checkers1.m_numColumns = columns);
    checkers1.initBoard();
    for (int i = 0; i < checkers1.m_numRows; i++) {
      for (int j = 0; j < checkers1.m_numColumns; j++) {
	counter++;
      }
    }
    result = result and (counter == (checkers1.m_numRows * checkers1.m_numColumns));
    return result;
  }

  bool testInitGameErrorCase(int rows, int columns) {
    int counter = 0;
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows != rows);
    result = result and (checkers1.m_numColumns != columns);
    checkers1.initBoard();
    checkers1.initGame();
    for (int i = 0; i < checkers1.m_numRows; i++) {
      for (int j = 0; j < checkers1.m_numColumns; j++) {
	counter++;
      }
    }
    result = result and (counter == (checkers1.m_numRows * checkers1.m_numColumns));
    result = result and (counter == 0);
    result = result and (checkers1.m_blackDisks == 0);
    result = result and (checkers1.m_whiteDisks == 0);

    return result;
  }

  bool testInitGameNormalCase(int rows, int columns) {
    int counter = 0;
    bool result = true;
    Checkers checkers1(rows, columns);
    result = result and (checkers1.m_numRows == rows);
    result = result and (checkers1.m_numColumns == columns);
    checkers1.initBoard();
    checkers1.initGame();
    for (int i = 0; i < checkers1.m_numRows; i++) {
      for (int j = 0; j < checkers1.m_numColumns; j++) {
	counter++;
      }
    }
    result = result and (counter == (checkers1.m_numRows * checkers1.m_numColumns));
    result = result and (checkers1.m_blackDisks == checkers1.m_numColumns / 2 * 3);
    result = result and (checkers1.m_whiteDisks == checkers1.m_numColumns / 2 * 3);

    return result;
  }

  bool testSetGameState(CELL game[], Checkers& checkers, int n, PLAYER player) {
    checkers.setGameState(game, n, player);
    int counter = 0;
    bool result = true;
    for (int i = 0; i < checkers.m_numRows; i++) {
      for (int j = 0; j < checkers.m_numColumns; j++) {
	if (checkers.m_game[i][j] == game[counter]) {
	  result = true;
	}
	else {
	  result = false;
	}
	counter++;
      }
    }
    return result;
  }

};


int main() {
  //this tests an error case for the constructor
  Tester tester1;
  if (tester1.testConstructorErrorCase(-5, -5))
    cout << "\ttestConstructorErrorCase() returned true." << endl;
  else
    cout << "\ttestConstructorErrorCase() returned false." << endl;

  //this tests a normal case for the constructor
  if (tester1.testConstructorNormalCase(8, 8))
    cout << "\ttestConstructorNormalCase() returned true." << endl;
  else
    cout << "\ttestConstructorNormalCase() returned false." << endl;

  //this tests an error case for the InitBoard()
  if (tester1.testInitBoardErrorCase(6, 6))
    cout << "\ttestInitBoardErrorCase() returned true." << endl;
  else
    cout << "\ttestInitBoardErrorCase() returned false." << endl;

  //this tests a normal case for the InitBoard()
  if (tester1.testInitBoardNormalCase(8, 8))
    cout << "\ttestInitBoardNormalCase() returned true." << endl;
  else
    cout << "\ttestInitBoardNormalCase() returned false." << endl;

  //this tests an error case for the InitGame()
  if (tester1.testInitGameErrorCase(5, 5))
    cout << "\ttestInitGameErrorCase() returned true." << endl;
  else
    cout << "\ttestInitGameErrorCase() returned false." << endl;

  //this tests a normal case for the InitGame()
  if (tester1.testInitGameNormalCase(10, 10))
    cout << "\ttestInitGameNormalCase() returned true." << endl;
  else
    cout << "\ttestInitGameNormalCase() returned false." << endl;




  Tester tester;
  Checkers checkers(DEFBOARDSIZE, DEFBOARDSIZE);
  checkers.initBoard();
  //cout << "\nthe following is the rendering of the board:\n\n";
  //checkers.dumpGame(); // render the board
  checkers.initGame();
  //cout << "\nthe following shows the initial state of the game:\n\n";
  //checkers.dumpGame(); // render the initial state of the game
  const int size = DEFBOARDSIZE * DEFBOARDSIZE;
      CELL game[size] =
	{ "", "", "", "", "", "", "", "",
	  "", "", "", "", "", "", "", "",
	  "", BCELL, "", BDISK, "", BCELL, "", BCELL,
	  WDISK, "", "", "", WDISK, "", WDISK, "",
	  "", "", "", BDISK, "", BDISK, "", "",
	  "", "", BCELL, "", BCELL, "", BCELL, "",
	  "", "", "", "", "", "", "", "",
	  "", "", "", "", "", "", "", "", };


      //should return true
      checkers.setGameState(game, size, WPLAYER);
      //cout << "\nthe following shows the current state of the game:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << "\nthe following tests a capturing move for white which we expect success:\n\n";
      if (tester.testCaptureSuccess(checkers))
	cout << "\ttestCaptureSuccess() returned true." << endl;
      else
	cout << "\ttestCaptureSuccess() returned false." << endl;
      //cout << "\nthe following shows the state of the game after the capturing move:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      checkers.reportLostDisks();
      cout << endl;

      //should return true
      checkers.setGameState(game, size, BPLAYER);
      //cout << "\nthe following shows the current state of the game:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << "\nthe following tests a capturing move for black which we expect success:\n\n";
      if (tester.testCaptureSuccessBlack(checkers))
	cout << "\tTestCaptureSuccessBlack() returned true." << endl;
      else
	cout << "\tTestCaptureSuccessBlack() returned false." << endl;
      //cout << "\nthe following shows the state of the game after the capturing move:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      checkers.reportLostDisks();
      cout << endl;

      //should return true
      checkers.setGameState(game, size, WPLAYER);
      //cout << "\nthe following shows the current state of the game:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << "\nthe following tests a Single move for which we expect success:\n\n";
      if (tester.testSingleMoveSuccess(checkers))
	cout << "\ttestSingleMoveSuccess() returned true." << endl;
      else
	cout << "\ttestSingleMoveSuccess() returned false." << endl;
      //cout << "\nthe following shows the state of the game after single move:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << endl;

      //should return false
      checkers.setGameState(game, size, BPLAYER);
      //cout << "\nthe following shows the current state of the game:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << "\nthe following tests a wrong move for which we expect failure:\n\n";
      if (tester.testWrongMove(checkers))
	cout << "\ttestWrongMove() returned true." << endl;
      else
	cout << "\ttestWrongMove() returned false." << endl;
      //cout << "\nthe following shows the state of the game after Wrong move:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << endl;

      //should return false
      checkers.setGameState(game, size, WPLAYER);
      //cout << "\nthe following shows the current state of the game:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << "\nthe following tests a wrong turn for which we expect failure:\n\n";
      if (tester.testNotBlackTurn(checkers))
	cout << "\ttestWrongTurn() returned true." << endl;
      else
	cout << "\ttestWrongTurn() returned false." << endl;
      //cout << "\nthe following shows the state of the game after Wrong Turn:\n\n";
      //checkers.dumpGame(); // render the current state of the game
      cout << endl;


          CELL game2[size] =
	    { "", "", "", "", "", "", "", "",
	      "", "", "", "", "", "", BDISK, "",
	      "", BCELL, "", BDISK, "", BCELL, "", BCELL,
	      "", "", "", "", WDISK, "", WDISK, "",
	      "", "", "", BDISK, "", BDISK, "", "",
	      "", "", BCELL, "", BCELL, "", BCELL, "",
	      "", WDISK, "", "", "", "", "", "",
	      "", "", BCELL, "", "", "", "", "", };

	  //should return true
	  checkers.setGameState(game2, size, WPLAYER);
	  //cout << "\nthe following shows the current state of the game:\n\n";
	  //checkers.dumpGame(); // render the current state of the game
	  cout << "\nthe following tests a WDISK->WKING move for which we expect Success:\n\n";
	  if (tester.testWhiteKing(checkers))
	    cout << "\tTestWhiteKing() returned true." << endl;
	  else
	    cout << "\tTestWhiteKing() returned false." << endl;
	  //cout << "\nthe following shows the state of the game after WDISK->WKING move:\n\n";
	  //checkers.dumpGame(); // render the current state of the game
	  cout << endl;

	  //should return false
	  checkers.setGameState(game2, size, BPLAYER);
	  //cout << "\nthe following shows the current state of the game:\n\n";
	  //checkers.dumpGame(); // render the current state of the game
	  cout << "\nthe following tests a wrong black move for which we expect failure:\n\n";
	  if (tester.testMoveBdiskBACK(checkers))
	    cout << "\tTestMoveBDISKBack() returned true." << endl;
	  else
	    cout << "\tTestMoveBDISKBack() returned false." << endl;
	  //cout << "\nthe following shows the state of the game afterTestMoveBdiskBACK() move:\n\n";
	  //checkers.dumpGame(); // render the current state of the game
	  cout << endl;


	  return 0;
}


