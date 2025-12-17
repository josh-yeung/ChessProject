#include "tempPiece.h"

tempPiece::tempPiece(Piece& p) : type{p.getType()}, letter{p.getLetter()},
                                 num{p.getNum()}, isWhite{p.getPlayer()} {}

tempPiece::tempPiece(char type, int letter, int num, bool isWhite) : type{type}, letter{letter},
                                                                    num{num}, isWhite{isWhite} {}
                                                                                                                   