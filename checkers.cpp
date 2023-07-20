/*****************************************
 ** File:    checkers.cpp
 ** Project: CMSC 341 Project 0, Spring 2023
 ** Author:  Oritsejolomisan Mebaghanje
 ** Date:    02/11/23
 ** E-mail:  xz94254@umbc.edu
 **
 ** This file contains the program for checkers.cpp .
 **
 **
 **
 **
 **
 **
 **
 ***********************************************/

#include "checkers.h"
Checkers::Checkers() {
  m_numRows = 0;
  m_numColumns = 0;
  m_currPlayer = BPLAYER;
  m_whiteDisks = 0;
  m_blackDisks = 0;
  m_game = nullptr;
}

Checkers::Checkers(int rows, int columns) {
  if ((rows >= 8) or (columns >= 8)) {
    m_numRows = rows;
    m_numColumns = columns;
    m_blackDisks = m_numColumns / 2 * 3;
    m_whiteDisks = m_numColumns / 2 * 3;
    m_game = new CELL * [m_numRows];
    for (int i = 0; i < m_numRows; i++) {
      m_game[i] = new CELL[m_numColumns];
    }
  }
  else {
    m_numRows = 0;
    m_numColumns = 0;
    m_whiteDisks = 0;
    m_blackDisks = 0;
    m_game = nullptr;
  }
  m_currPlayer = BPLAYER;
}

Checkers::~Checkers() {
  clear();
}

void Checkers::clear() {
  for (int i = 0; i < m_numRows; i++) {
    delete[] m_game[i];
  }
  delete[] m_game;
}

void Checkers::initBoard() {
  for (int i = 0; i < m_numRows; i++) {
    for (int j = 0; j < m_numColumns; j++) {
      if (((i + j) % 2) == 1) {
	m_game[i][j] = BCELL;
      }
      else {
	m_game[i][j] = WCELL;
      }
    }
  }
}

void Checkers::reportLostDisks() {
  int initial_numb = (m_numColumns / 2 * 3);
  int white_lost = initial_numb - m_whiteDisks;
  int black_lost = initial_numb - m_blackDisks;
  cout << "White Player lost disk: " << white_lost << endl;
  cout << "Black Player lost disk: " << black_lost << endl;
}

void Checkers::initGame() {
  int w_counter = 0;
  int white = (m_numColumns / 2 * 3);
  for (int i = 0; i < m_numRows; i++) {
    for (int j = 0; j < m_numColumns; j++) {
      if ((((i + j) % 2) == 1) and ( w_counter != white)) {
	m_game[i][j] = WDISK;
	w_counter++;
      }
    }
  }
  int b_counter = 0;
  int black = (m_numColumns / 2 * 3);
  for (int i = m_numRows - 1; i >= 0; i--) {
    for (int j = m_numColumns - 1; j >= 0; j--) {
      if ((((i + j) % 2) == 1) and (b_counter != black)) {
	m_game[i][j] = BDISK;
	b_counter++;
      }
    }
  }


}
// +1 +1, -1 -1, +1 -1
bool Checkers::play(pair<int, int> origin, pair<int, int> destination) {
  //checks if it's your turn to play
  if ((m_game[origin.first][origin.second] == WDISK) and m_currPlayer == WPLAYER) {
    //checks if destination cell is empty
    if (m_game[destination.first][destination.second] == BCELL) {
      //checks if it's a diagonal move
      if (abs(destination.first - origin.first) == abs(destination.second - origin.second)) {

	//changes to king and allows king to move in any direction
	if (destination.first == m_numRows - 1) {
	  //it's a capture move
	  if (abs(destination.first - origin.first) == 2) {
	    int captureFirst = (origin.first + destination.first) / 2;
	    int captureSecond = (origin.second + destination.second) / 2;
	    if (m_game[captureFirst][captureSecond] == BDISK) {
	      m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	      m_game[origin.first][origin.second] = BCELL;
	      m_game[captureFirst][captureSecond] = BCELL;
	      m_blackDisks = m_blackDisks - 1;
	      m_currPlayer = BPLAYER;
	      m_game[destination.first][destination.second] = WKING;
	      return true;
	    }
	  }
	  //moves the piece normally
	  else {
	    m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	    m_game[origin.first][origin.second] = BCELL;
	    m_currPlayer = BPLAYER;
	    m_game[destination.first][destination.second] = WKING;
	    return true;
	  }
	}

	//white disk can only move down
	if (destination.first > origin.first) {
	  //it's a capture move
	  if (abs(destination.first - origin.first) == 2) {
	    int captureFirst = (origin.first + destination.first) / 2;
	    int captureSecond = (origin.second + destination.second) / 2;
	    if (m_game[captureFirst][captureSecond] == BDISK) {
	      m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	      m_game[origin.first][origin.second] = BCELL;
	      m_game[captureFirst][captureSecond] = BCELL;
	      m_blackDisks = m_blackDisks - 1;
	      m_currPlayer = BPLAYER;
	      return true;
	    }
	  }
	  //moves the piece normally
	  else {
	    m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	    m_game[origin.first][origin.second] = BCELL;
	    m_currPlayer = BPLAYER;
	    return true;
	  }
	}
	//makes player replay for wrong move
	else {
	  m_currPlayer = WPLAYER;
	}
      }
    }
  }

  //checks if it's your turn to play
  else if ((m_game[origin.first][origin.second] == BDISK) and m_currPlayer == BPLAYER) {
    //checks if destination cell is empty
    if (m_game[destination.first][destination.second] == BCELL) {
      //checks if it's a diagonal move
      if (abs(destination.first - origin.first) == abs(destination.second - origin.second)) {

	//changes to king and allows king to move in any direction
	if (destination.first == 0) {
	  //it's a capture move
	  if (abs(destination.first - origin.first) == 2) {
	    int captureFirst = (origin.first + destination.first) / 2;
	    int captureSecond = (origin.second + destination.second) / 2;
	    if (m_game[captureFirst][captureSecond] == WDISK) {
	      m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	      m_game[origin.first][origin.second] = BCELL;
	      m_game[captureFirst][captureSecond] = BCELL;
	      m_whiteDisks = m_whiteDisks - 1;
	      m_currPlayer = WPLAYER;
	      m_game[destination.first][destination.second] = BKING;
	      return true;
	    }
	  }
	  //moves the piece normally
	  else {
	    m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	    m_game[origin.first][origin.second] = BCELL;
	    m_currPlayer = WPLAYER;
	    m_game[destination.first][destination.second] = BKING;
	    return true;
	  }
	}

	//black disk can only move up
	if (destination.first < origin.first) {
	  //it's a capture move
	  if (abs(destination.first - origin.first) == 2) {
	    int captureFirst = (origin.first + destination.first) / 2;
	    int captureSecond = (origin.second + destination.second) / 2;
	    if (m_game[captureFirst][captureSecond] == WDISK) {
	      m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	      m_game[origin.first][origin.second] = BCELL;
	      m_game[captureFirst][captureSecond] = BCELL;
	      m_whiteDisks = m_whiteDisks - 1;
	      m_currPlayer = WPLAYER;
	      return true;
	    }
	  }
	  //moves the piece normally
	  else {
	    m_game[destination.first][destination.second] = m_game[origin.first][origin.second];
	    m_game[origin.first][origin.second] = BCELL;
	    m_currPlayer = WPLAYER;
	    return true;
	  }
	}
	else {
	  //makes player replay for wrong move
	  m_currPlayer = BPLAYER;
	}
      }
    }
  }
  return false;
}


void Checkers::setGameState(CELL game[], int n, PLAYER player) {

  int count = 0;
  for (int i = 0; i < m_numRows; i++) {
    for (int j = 0; j < m_numColumns; j++) {

      if (game[count] == BCELL) {
	m_game[i][j] = BCELL;
      }
      else if (game[count] == WCELL) {
	m_game[i][j] = WCELL;
      }
      else if (game[count] == WKING) {
	m_game[i][j] = WKING;
      }
      else if (game[count] == BKING) {
	m_game[i][j] = BKING;
      }
      else if (game[count] == WDISK) {
	m_game[i][j] = WDISK;
      }
      else if (game[count] == BDISK) {
	m_game[i][j] = BDISK;
      }
      count++;
    }
  }

  m_currPlayer = player;
}

void Checkers::dumpGame() {
  if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr) {
    cout << "  ";
    for (int k = 0; k < m_numColumns; k++) {
      cout << k << " ";
    }
    cout << endl;
    for (int i = 1; i <= m_numRows; i++) {
      cout << i - 1 << " ";
      for (int j = 1; j <= m_numColumns; j++) {
	cout << m_game[i - 1][j - 1];
      }
      cout << endl;
    }
    cout << endl;
  }
}


